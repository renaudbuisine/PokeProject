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
rpg_scene::rpg_scene(rpg_dependenciesInjector::injector& injector) noexcept: m_loaded(false), m_running(false) {
    LOG_F(INFO, "CREATE SCENE::typeid(%s)", typeid(this).name());
}

bool rpg_scene::isLoaded(void) noexcept {
    return m_loaded;
}

bool rpg_scene::isRunning(void) const noexcept {
    return m_running;
}

void rpg_scene::setIsLoaded(bool loaded) noexcept {
    m_loaded = loaded;
}

void rpg_scene::setIsRunning(bool running) noexcept {
    m_running = running;
}
