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

struct A: rpg_dependenciesInjector::dependency {
    A(rpg_dependenciesInjector::injector& injector): rpg_dependenciesInjector::dependency(injector) { std::cout << "CREATED: Class A" << std::endl; }
    ~A() { std::cout << "DELETED: Class A" << std::endl; }
    
    void print() { std::cout << "PRINT: Class A" << std::endl; }
};
struct B: rpg_dependenciesInjector::dependency {
    B(rpg_dependenciesInjector::injector& injector): rpg_dependenciesInjector::dependency(injector), m_a(injector.getDependency<A>()){
        std::cout << "CREATED: Class B" << std::endl;
    }
    
    void print() {
        std::cout << "PRINT: Class B" << std::endl << "SUB";
        m_a->print();
    }
    
    rpg_dependenciesInjector::injector::injectedPtr<A> m_a;
};
struct C: rpg_dependenciesInjector::dependency {
    C(rpg_dependenciesInjector::injector& injector): rpg_dependenciesInjector::dependency(injector) { std::cout << "CREATED: Class C" << std::endl; }
    ~C() { std::cout << "DELETED: Class C" << std::endl; }
};

void runDependencies() {
    rpg_dependenciesInjector dependenciesInjector;
    dependenciesInjector.registerDependency<B>();
    dependenciesInjector.registerDependency<C>();
    
    auto dependency1 = dependenciesInjector.getInjector()->getDependency<B>();
    auto dependency2 = dependenciesInjector.getInjector()->getDependency<B>();
    auto dependency3 = dependenciesInjector.getInjector()->getDependency<C>();
    auto dependency4 = dependenciesInjector.getInjector()->getDependency<C>();
    dependency1->print();
}

void runGameLoop() {
    rpg_game game("testDevGame");
    
    game.setUpdateCallback([](const float elapsedTimestmp){
        std::cout << "Update callback called with elapsed timestamp: " << elapsedTimestmp << std::endl;
    });
    game.setFixedUpdateCallback([](){
        std::cout << "FixedUpdate callback called" << std::endl;
    });
    
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
