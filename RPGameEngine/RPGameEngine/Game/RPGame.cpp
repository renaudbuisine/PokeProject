//
//  RPGame.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGame.hpp"
#include "RPGRouter.hpp"

#include <sstream>

#define LOGURU_IMPLEMENTATION 1
#include "loguru.hpp"

//CONSTRUCTOR / DESTRUCTOR

rpg_game::rpg_game(const std::string& name) noexcept: m_name(name), m_updateCallBack(NULL), m_fixedUpdateCallback(NULL), m_addSceneCallBack(NULL), m_removeSceneCallBack(NULL), m_isPaused(false), m_isRunning(false) {
    
    std::stringstream ss;
    ss << m_name << ".log";
    loguru::add_file(ss.str().c_str(), loguru::Truncate, loguru::Verbosity_INFO);
    // Only show most relevant things on stderr:
    loguru::g_stderr_verbosity = 1;
    
    LOG_F(INFO, "CREATE %s", m_name.c_str());
}

rpg_game::~rpg_game(void) noexcept {
    stop();
    LOG_F(INFO, "DESTROY %s", m_name.c_str());
}

// LOAD / UPDATES

void rpg_game::innerUpdate(const float elapsedTimestamp) {
    // update game
    update(elapsedTimestamp);
    if (m_updateCallBack != NULL) {
        m_updateCallBack(elapsedTimestamp);
    }
    
    //update scenes
    for(auto it = m_scenes.rbegin(); it != m_scenes.rend(); ++it) {
        if(!(*it)->isRunning()) {
            break;
        }
        (*it)->update(elapsedTimestamp);
    }
    
    //update routers
    for(auto router: m_routers) {
        if(router) {
            router->update(elapsedTimestamp);
        }
    }
}

void rpg_game::innerFixedUpdate(void) {
    fixedUpdate();
    if (m_fixedUpdateCallback != NULL) {
        m_fixedUpdateCallback();
    }
    
    //update scenes
    for(auto it = m_scenes.rbegin(); it != m_scenes.rend(); ++it) {
        if(!(*it)->isRunning()) {
            break;
        }
        (*it)->fixedUpdate();
    }
}

//LIFE CYCLE

void rpg_game::run(void) {
    if(m_isRunning) {
        return;
    }
    m_isRunning = true;
    
    m_runThread = std::thread([&]{
        
        m_runningTimestamp = 0;
        clock_t accumulatedTimestamp = 0;
        clock_t previousTimestamp = clock();
        
        LOG_F(INFO, "START RUNNING %s - %ld", m_name.c_str(), previousTimestamp);
        
        // m_running is sensitive variable, needs to lock to read it
        std::unique_lock<decltype(m_runThreadMutex)> lock(m_runThreadMutex);
        while (m_isRunning) {
            lock.unlock(); // running read, we can go on
            
            if (m_isPaused) {
                lock.lock(); // needs to lock to wait
                LOG_F(INFO, "PAUSED %s - %ld", m_name.c_str(), clock());
                m_runThreadCV.wait(lock);
                
                LOG_F(INFO, "RESUMED %s - %ld", m_name.c_str(), clock());
                lock.unlock(); // wait function auto lock on notify
            }
            
            clock_t updatedTimeStamp = clock();
            clock_t clockElapsedTimeStamp = updatedTimeStamp - previousTimestamp;
            
            float elapsedTimestamp = (float)clockElapsedTimeStamp / (float)CLOCKS_PER_SEC;
            innerUpdate(elapsedTimestamp);
            
            accumulatedTimestamp += clockElapsedTimeStamp;
            if (accumulatedTimestamp > CLOCKS_PER_SEC / RPG_FPS) {
                innerFixedUpdate();
                accumulatedTimestamp -= CLOCKS_PER_SEC / RPG_FPS;
            }
            
            m_runningTimestamp += elapsedTimestamp;
            
            previousTimestamp = updatedTimeStamp;
            
            //needs to lock to be sure no update/fixedupdate function is called when game is stopped
            lock.lock();
        }
        lock.unlock();
        LOG_F(INFO, "END RUNNING %s - %ld", m_name.c_str(), clock());
    });
}

void rpg_game::pause(void) noexcept {
    setPaused(true);
}

void rpg_game::resume(void) noexcept {
    setPaused(false);
    m_runThreadCV.notify_one();
}

void rpg_game::setPaused(bool isPaused) noexcept {
    std::lock_guard<decltype(m_runThreadMutex)> lock(m_runThreadMutex);
    m_isPaused = isPaused;
}

void rpg_game::stop(void) noexcept {
    if (m_isRunning) {
        //needs to lock to be sure no update/fixedupdate function is called when game is stopped
        std::unique_lock<decltype(m_runThreadMutex)> lock(m_runThreadMutex);
        m_isRunning = false;
        lock.unlock();
        m_runThread.join();
    }
}

// GETTER SETTER

void rpg_game::setUpdateCallback(rpg_game::updateCallBack callback) noexcept {
    m_updateCallBack = callback;
}
void rpg_game::setFixedUpdateCallback(rpg_game::fixedUpdateCallBack callback) noexcept {
    m_fixedUpdateCallback = callback;
}
void rpg_game::setAddSceneCallBack(addSceneCallBack callback) noexcept {
    m_addSceneCallBack = callback;
}
void rpg_game::setRemoveSceneCallBack(removeSceneCallBack callback) noexcept {
    m_removeSceneCallBack = callback;
}

const std::vector<std::shared_ptr<rpg_scene>>& rpg_game::getScenes(void) const noexcept {
    return m_scenes;
}

size_t rpg_game::updatedRoutersSize(void) const noexcept {
    return m_routers.size();
}

// SCENES

void rpg_game::addScene(const std::shared_ptr<rpg_scene>& scenePtr) noexcept {
    m_scenes.push_back(scenePtr);
    if(m_addSceneCallBack) {
        m_addSceneCallBack(scenePtr);
    }
}

void rpg_game::pushScene(std::shared_ptr<rpg_scene>& scenePtr, const bool subScenesPaused) noexcept {
    if(subScenesPaused) {
        m_scenes.back()->setIsRunning(false);
    }
    
    addScene(scenePtr);
}

/**
 Remove scene from the stack
 */
void rpg_game::popScene(void) noexcept {
    if(m_removeSceneCallBack) {
        m_removeSceneCallBack(m_scenes.back());
    }
    m_scenes.pop_back();
}

/**
 Replace scenes stack with provided scene
 
 @param scenePtr New root scene
 */
void rpg_game::setRootScene(std::shared_ptr<rpg_scene>& scenePtr) noexcept {
    if(m_removeSceneCallBack) {
        for(auto s: m_scenes) {
            m_removeSceneCallBack(s);
        }
    }
    m_scenes.clear();
    addScene(scenePtr);
}

// ROUTERS

void rpg_game::addRouter(rpg_router *router) noexcept {
    m_routers.push_back(router);
}

void rpg_game::removeRouter(rpg_router *router) noexcept {
    auto it = std::find(m_routers.begin(), m_routers.end(), router);
    if(it != m_routers.end()) {
        m_routers.erase(it);
    }
}

// UTILS
std::string rpg_game::toString(void) const noexcept {
    std::stringstream ss;
    ss << "[rpg_game:{name: " << m_name << ";scenes:" << m_scenes.size() << "}]";
    return ss.str();
}
