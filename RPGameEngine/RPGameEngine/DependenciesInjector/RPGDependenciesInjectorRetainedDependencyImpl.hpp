//
//  RPGDependenciesInjectorRetainedDependencyImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 19/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDependenciesInjectorRetainedDependencyImpl_hpp
#define RPGDependenciesInjectorRetainedDependencyImpl_hpp

// CONSTRUCTORS

template<typename T>
rpg_dependenciesInjector::injector::retainedDependency<T>::retainedDependency(T *inst) noexcept: m_inst(inst) { }

template<typename T>
rpg_dependenciesInjector::injector::retainedDependency<T>::~retainedDependency(void) noexcept {
    if (m_inst != NULL) {
        delete m_inst;
    }
}

// TEMPLATE GETTERS

template<typename T>
void * rpg_dependenciesInjector::injector::retainedDependency<T>::getInstance(void) const {
    return (void *)m_inst;
}

#endif /* RPGDependenciesInjectorRetainedDependencyImpl_hpp */
