//
//  RPGDependenciesInjectorImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 18/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

// TEMPLATE FUNCTIONS
template<typename T>
void rpg_dependenciesInjector::registerDependency() noexcept {
    m_injector.m_dependencies[std::type_index(typeid(T))] = NULL;
}

template<typename T>
rpg_dependenciesInjector::injector::injectedPtr<T> rpg_dependenciesInjector::injector::getDependency() {
    std::type_index typeIndex = std::type_index(typeid(T));
    
    auto it = m_dependencies.find(typeIndex);
    if (it != m_dependencies.end()) {
        
        T *inst = (T *)it->second;
        if(!inst) {
            inst = new T(*this);
            it->second = inst;
        }
        return rpg_dependenciesInjector::injector::injectedPtr<T>(inst, true);
    }
    return rpg_dependenciesInjector::injector::injectedPtr<T>(new T(*this), false);
}
