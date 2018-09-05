//
//  RPGame.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGame.hpp"

#include <sstream>

#define LOGURU_IMPLEMENTATION 1
#include "loguru.hpp"

//CONSTRUCTOR / DESTRUCTOR

rpg_game::rpg_game(const std::string& name) noexcept: m_name(name), m_updateCallBack(NULL), m_fixedUpdateCallback(NULL) {
    
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

// PURE VIRTUAL FUNCTIONS
void rpg_game::update(const float elapsedTimestamp) {
    if (m_updateCallBack != NULL) {
        m_updateCallBack(elapsedTimestamp);
    }
}
void rpg_game::fixedUpdate(void) {
    if (m_fixedUpdateCallback != NULL) {
        m_fixedUpdateCallback();
    }
}

//LIFE CYCLE

void rpg_game::run(void) {
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
            update(elapsedTimestamp);
            
            accumulatedTimestamp += clockElapsedTimeStamp;
            if (accumulatedTimestamp > CLOCKS_PER_SEC / RPG_FPS) {
                fixedUpdate();
                accumulatedTimestamp -= CLOCKS_PER_SEC / RPG_FPS;
            }
            
            m_runningTimestamp += elapsedTimestamp;
            
            previousTimestamp = updatedTimeStamp;
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
    std::unique_lock<decltype(m_runThreadMutex)> lock(m_runThreadMutex);
    m_isPaused = isPaused;
    lock.unlock();
}

void rpg_game::stop(void) noexcept {
    if (m_isRunning) {
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

// UTILS
std::string rpg_game::toString(void) const noexcept {
    std::stringstream ss;
    ss << "[rpg_game:{name: " << m_name << ";scenes:" << m_scenes.size() << "}]";
    return ss.str();
}

// PROTECTED FUNCTIONS

template<typename T>
void rpg_game::registerDependency() {
    m_dependenciesInjector.registerDependency<T>();
}
