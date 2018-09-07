//
//  RPGDefaultMapScene.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDefaultMapScene_hpp
#define RPGDefaultMapScene_hpp

#include <vector>

#include "RPGAbstractMapScene.hpp"

#include "RPGAbstractCrossControl.hpp"

#include "RPGCharacter.hpp"

class rpg_default_mapScene: public rpg_mapScene {
public:
    rpg_default_mapScene(rpg_dependenciesInjector::injector& injector) noexcept;
    ~rpg_default_mapScene(void) noexcept;
    
    //CONTROLS
    void addControl(std::weak_ptr<rpg_control> controlPtr) noexcept final;
    
    //CALLBACKS
    void setUpdateCharacterCallback(updateCharacterCallback) noexcept final;
    
    //Loading
    void load(void) noexcept final;
    //Updates
    virtual void update(const float) noexcept;
    virtual void fixedUpdate(void) noexcept;
private:
    //CONTROLS
    std::weak_ptr<rpg_crossControl> m_crossControlPtr;
    
    //CHARACTERS
    std::vector<rpg_character *> m_characters;
    rpg_character *m_playerCharacter;
    
    //CALLBACKS
    updateCharacterCallback m_updateCharacterCallback;
    
    // PRIVATE FUNCTIONS :: PLAYER CHARACTER
    void updatePlayerCharacter(const float) noexcept;
    void fixedUpdatePlayerCharacter(void) noexcept;
};

#endif /* RPGDefaultMapScene_hpp */
