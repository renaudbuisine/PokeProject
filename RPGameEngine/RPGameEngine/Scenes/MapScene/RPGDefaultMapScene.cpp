//
//  RPGDefaultMapScene.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGDefaultMapScene.hpp"

#include <memory>

#include "RPGPlayerCharacter.hpp"

rpg_default_mapScene::rpg_default_mapScene(rpg_dependenciesInjector::injector& injector) noexcept: rpg_mapScene(injector) {

    m_playerCharacter = new rpg_playerCharacter();
    m_characters.push_back(m_playerCharacter);
}

rpg_default_mapScene::~rpg_default_mapScene(void) noexcept {
    for(rpg_character *c: m_characters) {
        delete c;
    }
}

//CONTROLS
void rpg_default_mapScene::addControl(std::weak_ptr<rpg_control> controlPtr) noexcept {
    m_crossControlPtr = std::static_pointer_cast<rpg_crossControl>(controlPtr.lock());
}

//CALLBACKS
void rpg_default_mapScene::setUpdateCharacterCallback(updateCharacterCallback callback) noexcept {
    m_updateCharacterCallback = callback;
}

// LIFE CYCLE

void rpg_default_mapScene::load(void) noexcept {
    
}

void rpg_default_mapScene::update(const float elapsedTimestamp) noexcept {
    updatePlayerCharacter(elapsedTimestamp);
}

void rpg_default_mapScene::updatePlayerCharacter(const float elapsedTimestamp) noexcept {
    if(!m_playerCharacter) {
        return;
    }
    
    auto control = m_crossControlPtr.lock();
    if(!control || control->isNotPerformed()) {
        return;
    }
    
    //update positions here
}

void rpg_default_mapScene::fixedUpdate(void) noexcept {
    fixedUpdatePlayerCharacter();
}

void rpg_default_mapScene::fixedUpdatePlayerCharacter(void) noexcept {
    if(!m_playerCharacter) {
        return;
    }
    
    auto control = m_crossControlPtr.lock();
    if(!control) {
        return;
    }
    
    if(control->isNotPerformed()) {
        if(m_updateCharacterCallback &&
           (m_playerCharacter->getStatus() == CHARACTER_ANIMATION_STATUS_RUN || m_playerCharacter->getStatus() == CHARACTER_ANIMATION_STATUS_WALK)) {
            
            m_playerCharacter->setStatus(CHARACTER_ANIMATION_STATUS_IDLE);
            m_updateCharacterCallback(*m_playerCharacter);
        }
        return;
    }
    
    bool updated = false;
    rpg_character::orientation newOrientation;
    if(control->isPerforming(CROSSCONTROL_DIRECTION_LEFT)) {
        newOrientation = CHARACTER_ORIENTATION_LEFT;
    } else if(control->isPerforming(CROSSCONTROL_DIRECTION_TOP)) {
        newOrientation = CHARACTER_ORIENTATION_TOP;
    } else if(control->isPerforming(CROSSCONTROL_DIRECTION_BOTTOM)) {
        newOrientation = CHARACTER_ORIENTATION_BOTTOM;
    } else if(control->isPerforming(CROSSCONTROL_DIRECTION_RIGHT)) {
        newOrientation = CHARACTER_ORIENTATION_RIGHT;
    } else {
        newOrientation = m_playerCharacter->getOrientation();
    }
    
    updated |= newOrientation != m_playerCharacter->getOrientation();
    m_playerCharacter->setOrientation(newOrientation);
    
    // Update animation between walking and running
    rpg_character::animationStatus newAnimation = CHARACTER_ANIMATION_STATUS_WALK;
    updated |= newAnimation != m_playerCharacter->getStatus();
    m_playerCharacter->setStatus(newAnimation);
    
    if(m_updateCharacterCallback && updated) {
        m_updateCharacterCallback(*m_playerCharacter);
    }
}
