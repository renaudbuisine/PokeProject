//
//  RPGRouterImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 10/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGScene.hpp"

template<typename T>
bool rpg_router::prepareScene(const presentationType type) noexcept {
    m_presentationType = type;
    m_nextScene = m_game->createScene<T>();
    return m_nextScene && runLoading();
}
