//
//  main.cpp
//  RPGameEngineDeveloperTool
//
//  Created by Renaud Buisine on 17/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include <iostream>
#include <functional>
#include <unistd.h>

#include "RPGDependenciesInjector.hpp"
#include "RPGame.hpp"

struct A {
    A() { std::cout << "CREATED: Class A" << std::endl; }
    ~A() { std::cout << "DELETED: Class A" << std::endl; }
    
    void print() { std::cout << "PRINT: Class A" << std::endl; }
    
    static A *create(rpg_dependenciesInjector::injector& injector) {
        return new A();
    }
};
struct B {
    B(rpg_dependenciesInjector::injector& injector): m_a(injector.getDependency<A>()){
        std::cout << "CREATED: Class B" << std::endl;
    }
    ~B() { std::cout << "DELETED: Class B" << std::endl; }
    
    void print() {
        std::cout << "PRINT: Class B" << std::endl << "SUB";
        m_a->print();
    }
    
    static B *create(rpg_dependenciesInjector::injector& injector) {
        return new B(injector);
    }
    
    rpg_dependenciesInjector::injector::injectedPtr<A> m_a;
};
struct C {
    C() { std::cout << "CREATED: Class C" << std::endl; }
    ~C() { std::cout << "DELETED: Class C" << std::endl; }

    static C* create(rpg_dependenciesInjector::injector& injector) {
        return new C();
    }
};

void runDependencies() {
    rpg_dependenciesInjector dependenciesInjector;
    dependenciesInjector.registerDependency<A>(A::create);
    dependenciesInjector.registerDependency<B>(B::create);
    dependenciesInjector.registerDependency<C>(C::create,true);
    
    auto dependency1 = dependenciesInjector.getInjector()->getDependency<B>();
    auto dependency2 = dependenciesInjector.getInjector()->getDependency<B>();
    auto dependency3 = dependenciesInjector.getInjector()->getDependency<C>();
    auto dependency4 = dependenciesInjector.getInjector()->getDependency<C>();
    dependency1->print();
    
    std::cout << (dependenciesInjector.getInjector()->getDependency<int>() == NULL) << std::endl;
}

void runGameLoop() {
    rpg_game game("testDevGame");
    
    game.run();
    sleep(3);
    
    game.pause();
    sleep(3);
    
    game.resume();
    
    sleep(3);
    
}

int main(int argc, const char * argv[]) {
    
    runGameLoop();

    return 0;
}
