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

class rpg_scene {
public:
    friend class rpg_game;
    
    //Destructor
    virtual ~rpg_scene(void) noexcept = default;
    
    //Life cycle
    
    //Updates
    /**
     called a each loop whatever elapsedtimestamp value

     @param elapsedTimestamp elapsed time stamp (in seconds)
     */
    virtual void update(const float elapsedTimestamp) noexcept;
    /**
     called 30 times a second
     */
    virtual void fixedUpdate(void) noexcept;
    
protected:
    //Constructor
    rpg_scene(rpg_dependenciesInjector::injector& injector) noexcept;
};

#endif /* RPGScene_hpp */
