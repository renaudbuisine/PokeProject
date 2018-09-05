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

struct A {
    A() { instCount++; }
    ~A() { instCount--; }
    
    void doSomething(void) { functionCalled = true; }
    
    static A *create(rpg_dependenciesInjector::injector& injector) {
        return new A();
    }
    bool functionCalled;
};

struct B {
    B(rpg_dependenciesInjector::injector& injector): m_a(injector.getDependency<A>()){ instCount++; }
    ~B() { instCount--; }
    
    void doSomething(void) { m_a->doSomething(); functionCalled = true; }
    
    static B *create(rpg_dependenciesInjector::injector& injector) {
        return new B(injector);
    }
    
    rpg_dependenciesInjector::injector::injectedPtr<A> m_a;
    bool functionCalled;
};

struct C {
    C() { instCount++; }
    ~C() { instCount--; }
    
    void doSomething(void) { functionCalled = true; }
    
    static C* create(rpg_dependenciesInjector::injector& injector) {
        return new C();
    }
    
    bool functionCalled;
};

#endif /* MockDependencies_hpp */
