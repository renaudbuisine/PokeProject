//
//  RPGRouter.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGRouter_hpp
#define RPGRouter_hpp

#include <stdio.h>

#include "RPGame.hpp"
#include "RPGScene.hpp"

class rpg_scene;

class rpg_router: public rpg_asyncTask::delegate {
public:
    friend class rpg_game;
    
    using transitionFromToSceneCallback = std::function<void(std::shared_ptr<rpg_scene>,std::shared_ptr<rpg_scene>)>;
    
    // INTERNAL DELEGATE
    struct delegate {
        /**
         When scene is loaded
         */
        virtual void didLoad(void) noexcept = 0;
        /**
         When transition to new scene is done
         */
        virtual void didEndTransition(void) noexcept = 0;
    };
    
    //CONSTRUCTOR DESTRUCTOR
    rpg_router(rpg_game *) noexcept;
    virtual ~rpg_router(void) noexcept = default;
    
    //LOADING
    virtual bool prepareScene(void) noexcept = 0;
    
    //TRANSITIONING
    bool transitionFromScene(std::shared_ptr<rpg_scene>) noexcept;
    
    //STATUS GETTER
    bool isLoading(void) noexcept;
    bool isLoaded(void) noexcept;
    bool isTransitioningToNextScene(void) const noexcept;
    void setParentDelegate(std::shared_ptr<delegate>);
    void setTransitionFromToSceneCallback(transitionFromToSceneCallback) noexcept;
    
    //rpg_asyncTask::delegate members
    void didCompleteTask(const rpg_asyncTask&) final;
    
protected:
    //LOADING
    template<typename T>
    bool prepareScene(void) noexcept;
    //SETTER
    void setPresentationType(const RPGAME_PRESENTATION) noexcept;
    
private:
    rpg_game *m_game;
    bool m_transitioning;
    transitionFromToSceneCallback m_transitionCallback;
    RPGAME_PRESENTATION m_presentationType;
    std::shared_ptr<rpg_scene> m_pendingScene;
    std::weak_ptr<rpg_scene> m_scene;
    
    //STATUS
    bool m_loading;
    
    delegate *m_parentDelegate; //weak
    
    //PRIVATE FUNCTIONS
    void runLoading(void) noexcept;
    void endLoading(void) noexcept;
    void endTransition(void) noexcept;
    void update(const float elapsedTimestamp) noexcept;
};

#include "RPGRouterImpl.hpp"

#endif /* RPGRouter_hpp */
