//
//  MockDependencies.hpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 19/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef MockDependencies_hpp
#define MockDependencies_hpp

#include <stdio.h>

#include "RPGDependenciesInjector.hpp"

int instCount = 0;

struct A: rpg_dependenciesInjector::dependency {
    A(rpg_dependenciesInjector::injector& injector): rpg_dependenciesInjector::dependency(injector) { instCount++; }
    ~A() { instCount--; }
    
    void doSomething(void) { functionCalled = true; }
    
    bool functionCalled;
};

struct B: rpg_dependenciesInjector::dependency {
    B(rpg_dependenciesInjector::injector& injector): rpg_dependenciesInjector::dependency(injector), m_a(injector.getDependency<A>()){ instCount++; }
    ~B() { instCount--; }
    
    void doSomething(void) { m_a->doSomething(); functionCalled = true; }
    
    rpg_dependenciesInjector::injector::injectedPtr<A> m_a;
    bool functionCalled;
};

struct C: rpg_dependenciesInjector::dependency {
    C(rpg_dependenciesInjector::injector& injector): rpg_dependenciesInjector::dependency(injector) { instCount++; }
    ~C() { instCount--; }
    
    void doSomething(void) { functionCalled = true; }
    
    bool functionCalled;
};

#endif /* MockDependencies_hpp */
