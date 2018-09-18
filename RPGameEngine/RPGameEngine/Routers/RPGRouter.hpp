//
//  RPGRouter.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGRouter_hpp
#define RPGRouter_hpp

#include "RPGame.hpp"

#include <mutex>

#define RPGROUTER_PRESENTATION_PUSH rpg_router::presentationType::push
#define RPGROUTER_PRESENTATION_ROOT rpg_router::presentationType::root

class rpg_game;
class rpg_router {
public:
    friend class rpg_game;
    
    using loadResourcesCallback = std::function<void(void)>;
    using transitionToSceneCallback = std::function<void(std::shared_ptr<rpg_scene>)>;
    
    // PRESENTATION TYPE ENUM
    enum presentationType { push, root };
    
    //CONSTRUCTOR DESTRUCTOR
    rpg_router(rpg_game *) noexcept;
    virtual ~rpg_router(void) noexcept;
    
    //LOADING
    template<typename T>
    bool prepareScene(const presentationType = presentationType::root) noexcept;
    //TRANSITIONING
    bool transitionToNextScene(void) noexcept;
    virtual void didEndTransition(void) noexcept;
    
    //STATUS GETTER
    bool isLoading(void) noexcept;
    bool isLoaded(void) noexcept;
    bool isTransitioningToNextScene(void) const noexcept;
    
    //CALLBACKS
    void setLoadResourcesCallback(loadResourcesCallback) noexcept;
    void setTransitionToSceneCallbackCallback(transitionToSceneCallback) noexcept;
private:
    rpg_game *m_game;
    std::shared_ptr<rpg_scene> m_nextScene;
    bool m_transitioning;
    presentationType m_presentationType;
    
    //STATUS
    bool m_loading;
    bool m_loaded;
    
    //CALLBACKS
    loadResourcesCallback m_loadResourcesCallback;
    transitionToSceneCallback m_transitionToSceneCallback;
    
    //MUTEX/THREADING
    std::mutex m_loadThreadMutex;
    
    
    //PRIVATE FUNCTIONS
    bool runLoading(void) noexcept;
    void endTransition(void) noexcept;
    void update(const float elapsedTimestamp) noexcept;
    void removeFromGame(void) noexcept;
};

#include "RPGRouterImpl.hpp"

#endif /* RPGRouter_hpp */
