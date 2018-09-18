//
//  RPGGameImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGGameImpl_hpp
#define RPGGameImpl_hpp

#include <memory>

//PROTECTED - DEPENDENCIES
template<typename T>
void rpg_game::registerDependency(const std::function<T *(rpg_dependenciesInjector::injector&)>& factory, bool shouldRetain) noexcept {
    m_dependenciesInjector.registerDependency<T>(factory, shouldRetain);
}

//SCENES
template<typename T>
std::shared_ptr<T> rpg_game::createScene(void) noexcept {
    return std::make_shared<T>(* m_dependenciesInjector.getInjector());
}

#endif /* RPGGameImpl_hpp */
