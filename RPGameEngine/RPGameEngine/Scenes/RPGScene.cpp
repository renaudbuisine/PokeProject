//
//  RPGScene.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGScene.hpp"

#include <thread>

#include "loguru.hpp"

//Constructor/destructor
rpg_scene::rpg_scene(rpg_dependenciesInjector::injector& injector) noexcept: m_router(NULL), m_loaded(false), m_running(false) {
    LOG_F(INFO, "CREATE SCENE::typeid(%s)", typeid(this).name());
}

rpg_scene::~rpg_scene(void) noexcept {
    if(m_router) {
        delete m_router;
    }
}

//LOAD
void rpg_scene::innerLoad(void) noexcept {
    load();
    if(m_loadResourcesCallback) {
        m_loadResourcesCallback();
    }
    m_loaded = true;
}

// GETTER / SETTER

bool rpg_scene::isLoaded(void) noexcept {
    return m_loaded;
}

bool rpg_scene::isRunning(void) const noexcept {
    return m_running;
}

void rpg_scene::setIsRunning(bool running) noexcept {
    m_running = running;
}

void rpg_scene::setRouter(rpg_router *router) noexcept {
    m_router = router;
}

//CALLBACKS
void rpg_scene::setLoadResourcesCallback(loadResourcesCallback callback) noexcept {
    m_loadResourcesCallback = callback;
}

