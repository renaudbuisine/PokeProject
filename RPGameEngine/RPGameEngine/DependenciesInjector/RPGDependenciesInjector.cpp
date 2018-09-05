//
//  RPGDependenciesInjector.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 17/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGDependenciesInjector.hpp"

// CONSTRUCTOR / DESTRUCTOR

rpg_dependenciesInjector::rpg_dependenciesInjector(void) noexcept { }
rpg_dependenciesInjector::~rpg_dependenciesInjector(void) noexcept { }

rpg_dependenciesInjector::injector::injector(void) noexcept { }
rpg_dependenciesInjector::injector::~injector(void) noexcept {
    clear();
}

rpg_dependenciesInjector::dependency::dependency(rpg_dependenciesInjector::injector& injector) { }

// FUNCTION

void rpg_dependenciesInjector::clear(void) noexcept {
    m_injector.clear();
}

void rpg_dependenciesInjector::injector::clear(void) noexcept {
    for (auto dependencyPair: m_dependencies) {
        if (dependencyPair.second) {
            delete dependencyPair.second;
        }
    }
    m_dependencies.clear();
}

// GETTERs
size_t rpg_dependenciesInjector::size(void) const noexcept {
    return m_injector.m_dependencies.size();
}
rpg_dependenciesInjector::injector *rpg_dependenciesInjector::getInjector(void) noexcept { return &m_injector; }
