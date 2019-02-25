//
//  RPGame.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGame_hpp
#define RPGame_hpp

#include <stdio.h>
#include <mutex>
#include <time.h>
#include <thread>
#include <vector>
#include <string>

#include "RPGDependenciesInjector.hpp"
#include "RPGAsyncTask.hpp"

#define RPG_FPS 30

#define RPGAME_PRESENTATION rpg_game::presentationType
#define RPGAME_PRESENTATION_PUSH RPGAME_PRESENTATION::push
#define RPGAME_PRESENTATION_ROOT RPGAME_PRESENTATION::root

class rpg_scene;

class rpg_game {
public:
    
    // PRESENTATION TYPE ENUM
    enum presentationType { push, root };
    
    //TYPEALIAS
    using updateCallBack = std::function<void(const float)>;
    using fixedUpdateCallBack = std::function<void(void)>;
    using addSceneCallBack = std::function<void(std::shared_ptr<rpg_scene>)>;
    using removeSceneCallBack = std::function<void(std::shared_ptr<rpg_scene>)>;
    
    friend class rpg_router;
    
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
    
    /**
     Load initial components of game - Needs calling - Synchrone function by default
     (needs overriding)
     */
    virtual void load(void) noexcept = 0;
    
    //Updates
    /**
     called a each loop whatever elapsedtimestamp value
     (needs overriding)
     
     @param elapsedTimestamp elapsed time stamp (in seconds)
     */
    virtual void update(const float elapsedTimestamp) = 0;
    /**
     called 30 times a second
     (needs overriding)
     */
    virtual void fixedUpdate(void) = 0;
    
    //SCENES
    template<typename T = rpg_scene>
    std::shared_ptr<T> createScene(void) noexcept;
    
    /**
     Add new scene to the stack

     @param scenePtr Pointer to new scene
     @param subScenesPaused Are scene below paused, default true
     */
    void pushScene(std::shared_ptr<rpg_scene>& scenePtr, const bool subScenesPaused = true) noexcept;
    
    /**
     Remove scene from the stack
     */
    void popScene(void) noexcept;
    
    /**
     Replace scenes stack with provided scene

     @param scenePtr New root scene
     */
    void setRootScene(std::shared_ptr<rpg_scene>& scenePtr) noexcept;
    
    
    /**
     Call transition callback to animate transition between scenes

     @param nextScene next scene to display
     @param type type of transition (push, root)
     @return....
     */
//    bool transitionToNextScene(std::shared_ptr<rpg_scene> nextScene, const presentationType type) noexcept;
    
    
    // TASKS
    void runTask(std::shared_ptr<rpg_asyncTask>) noexcept;
    size_t runningTasksSize(void) const noexcept;
    
    // SCENES
    const std::vector<std::shared_ptr<rpg_scene>>& getScenes(void) const noexcept;
    
    //GETTER SETTER
    void setUpdateCallback(updateCallBack) noexcept;
    void setFixedUpdateCallback(fixedUpdateCallBack) noexcept;
    void setAddSceneCallBack(addSceneCallBack) noexcept;
    void setRemoveSceneCallBack(removeSceneCallBack) noexcept;
    
protected:
    
    template<typename T>
    void registerDependency(const std::function<T *(rpg_dependenciesInjector::injector&)>&, bool = false) noexcept;
    
private:
    //OTHERS
    const std::string m_name;
    
    //Attributes
    rpg_dependenciesInjector m_dependenciesInjector;
    std::vector<std::shared_ptr<rpg_scene>> m_scenes;
    std::vector<std::shared_ptr<rpg_asyncTask>> m_tasks;
    
    //CALLBACKS
    updateCallBack m_updateCallBack;
    fixedUpdateCallBack m_fixedUpdateCallback;
    addSceneCallBack m_addSceneCallBack;
    removeSceneCallBack m_removeSceneCallBack;
    
    //STATUS
    bool m_isRunning;
    bool m_isPaused;
    //THREADING
    std::thread m_runThread;
    std::mutex m_runThreadMutex;
    std::condition_variable m_runThreadCV;
    //TIMESTAMP
    float m_runningTimestamp;
    
    //PRIVATE FUNC
    void setPaused(bool) noexcept;
    void innerUpdate(const float);
    void innerFixedUpdate(void);
    void addScene(const std::shared_ptr<rpg_scene>&) noexcept;
};

#include "RPGGameImpl.hpp"
#include "RPGScene.hpp"
#include "RPGRouter.hpp"

#endif /* RPGame_hpp */
