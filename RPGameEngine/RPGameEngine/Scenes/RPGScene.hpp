//
//  RPGScene.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGScene_hpp
#define RPGScene_hpp

#include "RPGDependenciesInjector.hpp"
#include "RPGControl.hpp"

class rpg_scene {
public:
    //Constructor/Destructor
    virtual ~rpg_scene(void) noexcept = default;
    
    //Life cycle
    
    //Loading
    virtual void load(void) noexcept = 0;
    
    //Updates
    /**
     called a each loop whatever elapsedtimestamp value

     @param elapsedTimestamp elapsed time stamp (in seconds)
     */
    virtual void update(const float elapsedTimestamp) noexcept = 0;
    /**
     called 30 times a second
     */
    virtual void fixedUpdate(void) noexcept = 0;
    
    // Controls
    virtual void addControl(std::weak_ptr<rpg_control>) noexcept = 0;
    
protected:
    rpg_scene(rpg_dependenciesInjector::injector& injector) noexcept { }
};

#endif /* RPGScene_hpp */
