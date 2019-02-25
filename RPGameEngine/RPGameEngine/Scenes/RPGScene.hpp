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

class rpg_router;

class rpg_scene {
public:
    friend class rpg_router;
    friend class rpg_game;
    
    using loadResourcesCallback = std::function<void(void)>;
    
    //Constructor/Destructor
    virtual ~rpg_scene(void) noexcept;
    
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
    
    //CALLBACKS
    void setLoadResourcesCallback(loadResourcesCallback) noexcept;
    
    // GETTERS
    bool isLoaded(void) noexcept;
    bool isRunning(void) const noexcept;
    
protected:
    rpg_scene(rpg_dependenciesInjector::injector& injector) noexcept;
    
private:
    bool m_loaded;
    bool m_running;
    
    rpg_router *m_router;
    
    //CALLBACKS
    loadResourcesCallback m_loadResourcesCallback;
    
    void innerLoad(void) noexcept;
    void setRouter(rpg_router *) noexcept;
    void setIsRunning(bool) noexcept;
};

#include "RPGRouter.hpp"

#endif /* RPGScene_hpp */
