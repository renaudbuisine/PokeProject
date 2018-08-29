//
//  RPGame.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGame_hpp
#define RPGame_hpp

#include <mutex>
#include <time.h>
#include <thread>
#include <stack>
#include <string>

#include "RPGDependenciesInjector.hpp"
#include "RPGScene.hpp"

#define RPG_FPS 30

class rpg_game {
public:
    
    struct delegate {

    };
    
    rpg_game(const std::string&) noexcept;
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
    
    /**
     Launch loop
     */
    void run(void);
    
    /**
     Pause the loop
     */
    void pause(void) noexcept;
    /**
     Resume the loop
     */
    void resume(void) noexcept;
    
    /**
     Stop the loop (unload resources)
     */
    void stop(void) noexcept;
    
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
    
    void setPaused(bool) noexcept;
    
    //OTHERS
    const std::string m_name;
    
    //Attributes
    rpg_dependenciesInjector m_dependenciesInjector;
    std::stack<std::unique_ptr<rpg_scene>> m_scenes;
    
    std::weak_ptr<delegate> m_delegate;
    
    //STATUS
    bool m_isRunning;
    bool m_isPaused;
    //THREADING
    std::thread m_runThread;
    std::mutex m_runThreadMutex;
    std::condition_variable m_runThreadCV;
    //TIMESTAMP
    float m_runningTimestamp;
};

#endif /* RPGame_hpp */
