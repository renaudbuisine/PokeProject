//
//  RPGDependenciesInjectorImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 18/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

// TEMPLATE FUNCTIONS
template<typename T>
void rpg_dependenciesInjector::registerDependency(T *(*factory)(rpg_dependenciesInjector::injector&), bool shouldRetain) noexcept {
    m_injector.m_dependencies[std::type_index(typeid(T))] = new rpg_dependenciesInjector::injector::unretainedDependency<T>(factory, shouldRetain);
}

template<typename T>
rpg_dependenciesInjector::injector::injectedPtr<T> rpg_dependenciesInjector::injector::getDependency() noexcept {
    std::type_index typeIndex = std::type_index(typeid(T));
    
    auto it = m_dependencies.find(typeIndex);
    if (it != m_dependencies.end()) {
        
        const rpg_dependenciesInjector::injector::dependency *dependencyPtr = it->second;
        T *inst = (T *)dependencyPtr->getInstance();
        if(inst) {
            return rpg_dependenciesInjector::injector::injectedPtr<T>(inst, true);
        } else {
            inst = (T *)dependencyPtr->callFactory(*this);
            bool shouldRetain = dependencyPtr->shouldRetain();
            
            if (shouldRetain) {
                delete(it->second);
                it->second = new rpg_dependenciesInjector::injector::retainedDependency<T>(inst);
            }
            
            return rpg_dependenciesInjector::injector::injectedPtr<T>(inst, shouldRetain);
        }
    }
    return rpg_dependenciesInjector::injector::injectedPtr<T>(NULL, false);
}
