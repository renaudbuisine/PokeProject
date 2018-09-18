//
//  RPGRouter.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGRouter.hpp"

//CONSTRUCTOR/DESTRUCTOR
rpg_router::rpg_router(rpg_game *game) noexcept: m_game(game), m_transitioning(false), m_loading(false), m_loaded(false), m_presentationType(RPGROUTER_PRESENTATION_ROOT) { }
rpg_router::~rpg_router(void) noexcept {
    removeFromGame();
}

void rpg_router::removeFromGame(void) noexcept {
    m_game->removeRouter(this);
}

//TRANSITIONING
bool rpg_router::transitionToNextScene(void) noexcept {
    if(!isLoaded() || !m_transitionToSceneCallback) {
        return false;
    }
    
    m_transitioning = true;
    m_game->addRouter(this);

    std::thread([&]{
        
        m_transitionToSceneCallback(m_nextScene);
        m_transitioning = false;
    }).detach();
    
    return true;
}

void rpg_router::endTransition(void) noexcept {
    switch(m_presentationType) {
        case root:
            m_game->setRootScene(m_nextScene);
            break;
        case push:
            m_game->pushScene(m_nextScene);
            break;
    }
    didEndTransition();
}

void rpg_router::didEndTransition(void) noexcept { }

//UPDATES
void rpg_router::update(const float elapsedTimestamp) noexcept {
    if(isTransitioningToNextScene()) {
        return;
    }
    
    // no updates required anymore
    removeFromGame();
    
    // apply transition at the end
    endTransition();
}

//CALLBACKS
void rpg_router::setLoadResourcesCallback(loadResourcesCallback callback) noexcept {
    m_loadResourcesCallback = callback;
}

void rpg_router::setTransitionToSceneCallbackCallback(transitionToSceneCallback callback) noexcept {
    m_transitionToSceneCallback = callback;
}

//GETTER SETTER
bool rpg_router::isLoading(void) noexcept {
    std::lock_guard<decltype(m_loadThreadMutex)> lock(m_loadThreadMutex);
    return m_loading;
}

bool rpg_router::isLoaded(void) noexcept {
    std::lock_guard<decltype(m_loadThreadMutex)> lock(m_loadThreadMutex);
    return m_loaded;
}

bool rpg_router::isTransitioningToNextScene(void) const noexcept {
    return m_transitioning;
}

// LOADING

bool rpg_router::runLoading(void) noexcept {
    if(isLoaded()) {
        return false;
    }
    m_loading = true;
    
    std::thread([&]{
        m_nextScene->load();
        m_nextScene->setIsLoaded(true);
        
        if(m_loadResourcesCallback) {
            m_loadResourcesCallback();
        }
        
        // loaded and loading needs to be updated in the same time
        std::lock_guard<decltype(m_loadThreadMutex)> lock(m_loadThreadMutex);
        m_loaded = true;
        m_loading = false;
    }).detach();
    return true;
}

