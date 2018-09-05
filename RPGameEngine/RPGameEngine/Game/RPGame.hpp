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
    //TYPEALIAS
    using updateCallBack = std::function<void(const float)>;
    using fixedUpdateCallBack = std::function<void(void)>;
    
    // CONTRUCTOR/DESTRUCTOR
    rpg_game(const std::string&) noexcept;
    virtual ~rpg_game(void) noexcept;
    
    /**
     Return basic information of rpg_game class as String

     @return Description of obj
     */
    virtual std::string toString(void) const noexcept;
    
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
    virtual void update(const float elapsedTimestamp);
    /**
     called 30 times a second
     (needs override)
     */
    virtual void fixedUpdate(void);
    
    //GETTER SETTER
    void setUpdateCallback(updateCallBack callback) noexcept;
    void setFixedUpdateCallback(fixedUpdateCallBack callback) noexcept;
    
protected:
    
    template<typename T>
    void registerDependency();
    
private:
    
    void setPaused(bool) noexcept;
    
    //OTHERS
    const std::string m_name;
    
    //Attributes
    rpg_dependenciesInjector m_dependenciesInjector;
    std::stack<std::unique_ptr<rpg_scene>> m_scenes;
    
    //CALLBACKS
    updateCallBack m_updateCallBack;
    fixedUpdateCallBack m_fixedUpdateCallback;
    
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
