//
//  RPGame.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGame_hpp
#define RPGame_hpp

#include <stack>
#include "RPGDependenciesInjector.hpp"
#include "RPGScene.hpp"

class rpg_game {
public:
    
    struct delegate {
    };
    
    rpg_game(void) noexcept;
    rpg_game(const std::shared_ptr<delegate>& delegate) noexcept;
    virtual ~rpg_game(void) noexcept;
    
    /**
     Return basic information of rpg_game class as String

     @return Description of obj
     */
    virtual std::string toString(void) const noexcept;
    
    /**
     Load game object
     (needs override)
     */
    virtual void load(void) noexcept;
    /**
     Unload game object
     (needs override)
     */
    virtual void unload(void) noexcept;
    
    //Updates
    /**
     called a each loop whatever elapsedtimestamp value
     (needs override)
     
     @param elapsedTimestamp elapsed time stamp (in seconds)
     */
    virtual void update(const float elapsedTimestamp) noexcept;
    /**
     called 30 times a second
     (needs override)
     */
    virtual void fixedUpdate(void) noexcept;
    
    /**
     Set delegate object
     
     @param delegate delegate object
     */
    void setDelegate(const std::shared_ptr<delegate>& delegate);
    
protected:
    
    template<typename T>
    void registerDependency(T *(*)(rpg_dependenciesInjector::injector&), bool = false);
    
private:
    rpg_dependenciesInjector m_dependenciesInjector;
    std::stack<std::unique_ptr<rpg_scene>> m_scenes;
    
    std::weak_ptr<delegate> m_delegate;
};

#endif /* RPGame_hpp */
