//
//  RPGAbstractMapScene.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGAbstractMapScene_hpp
#define RPGAbstractMapScene_hpp

#include "RPGScene.hpp"

#include "RPGCharacter.hpp"

class rpg_mapScene: public rpg_scene {
public:
    using updateCharacterCallback = std::function<void(const rpg_character&)>;
    
    virtual ~rpg_mapScene(void) noexcept = default;
    
    virtual void setUpdateCharacterCallback(updateCharacterCallback) noexcept = 0;
protected:
    rpg_mapScene(rpg_dependenciesInjector::injector& injector) noexcept: rpg_scene(injector) { }
};

#endif /* RPGAbstractMapScene_hpp */
