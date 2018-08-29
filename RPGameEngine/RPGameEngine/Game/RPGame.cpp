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

rpg_game::rpg_game(const std::string& name) noexcept: m_name(name) { }

rpg_game::rpg_game(const std::shared_ptr<delegate>& delegate) noexcept: m_delegate(delegate) { }

rpg_game::~rpg_game(void) noexcept {
    stop();
}

// GETTER/ SETTER

void rpg_game::setDelegate(const std::shared_ptr<delegate>& delegate) {
    m_delegate = delegate;
}

// PURE VIRTUAL FUNCTIONS
void rpg_game::load(void) noexcept { }
void rpg_game::unload(void) noexcept { }
void rpg_game::update(const float elapsedTimestamp) noexcept {  }
void rpg_game::fixedUpdate(void) noexcept {  }

//LIFE CYCLE

void rpg_game::run(void) {
    
    std::stringstream ss;
    ss << m_name << ".log";
    loguru::add_file(ss.str().c_str(), loguru::Truncate, loguru::Verbosity_INFO);
    // Only show most relevant things on stderr:
    loguru::g_stderr_verbosity = 1;
    
    m_runThread = std::thread([&]{
        
        m_runningTimestamp = 0;
        clock_t accumulatedTimestamp = 0;
        clock_t previousTimestamp = clock();
        
        LOG_F(INFO, "START RUNNING %s - %ld", m_name.c_str(), previousTimestamp);
        
        while (m_isRunning) {
            
            if (m_isPaused) {
                std::unique_lock<decltype(m_runThreadMutex)> lock(m_runThreadMutex);
                LOG_F(INFO, "PAUSED %s - %ld", m_name.c_str(), clock());
                m_runThreadCV.wait(lock);
                
                LOG_F(INFO, "RESUMED %s - %ld", m_name.c_str(), clock());
            }
            
            clock_t updatedTimeStamp = clock();
            clock_t clockElapsedTimeStamp = updatedTimeStamp - previousTimestamp;
            
            float elapsedTimestamp = clockElapsedTimeStamp / CLOCKS_PER_SEC;
            update(elapsedTimestamp);
            
            accumulatedTimestamp += clockElapsedTimeStamp;
            if (accumulatedTimestamp > CLOCKS_PER_SEC / RPG_FPS) {
                fixedUpdate();
                accumulatedTimestamp -= CLOCKS_PER_SEC / RPG_FPS;
            }
            
            m_runningTimestamp += elapsedTimestamp;
        }
        
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
        m_isRunning = false;
        m_runThread.join();
        unload();
    }
}

// UTILS
std::string rpg_game::toString(void) const noexcept {
    std::stringstream ss;
    ss << "[rpg_game:{scenes:" << m_scenes.size() << "}]";
    return ss.str();
}

// PROTECTED FUNCTIONS

template<typename T>
void rpg_game::registerDependency(T *(*factory)(rpg_dependenciesInjector::injector&), bool retained) {
    m_dependenciesInjector.registerDependency(factory, retained);
}
