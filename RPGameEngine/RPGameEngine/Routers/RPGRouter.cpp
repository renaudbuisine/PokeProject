//
//  RPGRouter.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGRouter.hpp"

//CONSTRUCTOR/DESTRUCTOR
rpg_router::rpg_router(rpg_game *game) noexcept: m_game(game), m_transitioning(false), m_loading(false), m_parentDelegate(NULL), m_presentationType(RPGAME_PRESENTATION_ROOT) { }

//TRANSITIONING
bool rpg_router::transitionFromScene(std::shared_ptr<rpg_scene> previousScene) noexcept {
    if(!isLoaded() || m_transitioning) {
        return false;
    }
    
    m_transitioning = true;
    
    std::shared_ptr<rpg_asyncTask> transitionTask(new rpg_asyncTask([&]{
        m_transitionCallback(previousScene ,m_pendingScene);
    }));
    transitionTask->setDelegate(this);
    m_game->runTask(transitionTask);
    
    return true;
}

void rpg_router::endTransition(void) noexcept {
    m_transitioning = false;
    switch(m_presentationType) {
        case RPGAME_PRESENTATION_ROOT:
            m_game->setRootScene(m_pendingScene);
            break;
        case RPGAME_PRESENTATION_PUSH:
            m_game->pushScene(m_pendingScene);
            break;
    }
    //release scene object
    m_pendingScene.reset();
    
    if(m_parentDelegate) {
        m_parentDelegate->didEndTransition();
    }
}

//GETTER SETTER
bool rpg_router::isLoading(void) noexcept {
    return m_loading;
}

bool rpg_router::isLoaded(void) noexcept {
    return m_pendingScene->isLoaded() && !m_loading;
}

bool rpg_router::isTransitioningToNextScene(void) const noexcept {
    return m_transitioning;
}

void rpg_router::setPresentationType(const rpg_game::presentationType type) noexcept {
    m_presentationType = type;
}

void rpg_router::setTransitionFromToSceneCallback(rpg_router::transitionFromToSceneCallback callback) noexcept {
    m_transitionCallback = callback;
}

// LOADING

void rpg_router::runLoading(void) noexcept {
    m_loading = true;
    
    std::shared_ptr<rpg_asyncTask> loadTask(new rpg_asyncTask([&]{
        m_pendingScene->innerLoad();
    }));
    loadTask->setDelegate(this);
    m_game->runTask(loadTask);
}

void rpg_router::endLoading(void) noexcept {
    m_loading = false;
    
    if(m_parentDelegate) {
        m_parentDelegate->didLoad();
    }
}

//rpg_asyncTask::delegate

void rpg_router::didCompleteTask(const rpg_asyncTask &task) {
    if(!m_pendingScene->isLoaded() && m_loading) {
        endLoading();
    } else if (m_transitioning) {
        endTransition();
    }
}

