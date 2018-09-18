//
//  MockScene.hpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 11/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef MockScene_hpp
#define MockScene_hpp

#include "RPGDependenciesInjector.hpp"
#include "RPGScene.hpp"

struct mock_scene final: public rpg_scene {
    static mock_scene *mockSceneInst;
    
    mock_scene(rpg_dependenciesInjector::injector& injector): rpg_scene(injector) {
        mockSceneInst = this;
    }
    ~mock_scene() {
        mockSceneInst = NULL;
    }
    
    void load(void) noexcept {
        while(!forceLoaded);
    }
    
    void update(const float elapsedTimestamp) noexcept { }
    void fixedUpdate(void) noexcept { }
    void addControl(std::weak_ptr<rpg_control> controlPtr) noexcept { }
    
    bool forceLoaded;
};

#endif /* MockScene_hpp */
