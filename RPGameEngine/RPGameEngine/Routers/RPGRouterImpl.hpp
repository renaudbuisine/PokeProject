//
//  RPGRouterImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 10/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

template<typename T>
bool rpg_router::prepareScene(void) noexcept {
    if(m_loading) {
        return false;
    }
    
    m_pendingScene = m_game->createScene<T>();
    m_scene = m_pendingScene;
    m_pendingScene->setRouter(this);
    runLoading();
    
    return true;
}
