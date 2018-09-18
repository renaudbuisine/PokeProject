//
//  RPGDependenciesInjectorUnretainedDependencyImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 19/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDependenciesInjectorUnretainedDependencyImpl_hpp
#define RPGDependenciesInjectorUnretainedDependencyImpl_hpp

template<typename T>
rpg_dependenciesInjector::injector::unretainedDependency<T>::unretainedDependency(const std::function<T *(rpg_dependenciesInjector::injector&)>& factory, bool shouldRetain) noexcept: m_factory(factory), m_shouldRetain(shouldRetain) { }

// FUNCTIONS

template<typename T>
void *rpg_dependenciesInjector::injector::unretainedDependency<T>::callFactory(rpg_dependenciesInjector::injector& injector) const {
    return m_factory(injector);
}

template<typename T>
bool rpg_dependenciesInjector::injector::unretainedDependency<T>::shouldRetain(void) const { return m_shouldRetain; }

#endif /* RPGDependenciesInjectorUnretainedDependencyImpl_hpp */
