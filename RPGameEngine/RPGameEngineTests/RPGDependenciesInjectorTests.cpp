//
//  main.cpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 19/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "catch.hpp"

#include "MockDependencies.hpp"
#include "RPGDependenciesInjector.hpp"

SCENARIO ("Register/ Clear dependencies", "[dependenciesInjector::registerDependency|clear|size]") {
    GIVEN ("A dependencies injector RPGDependenciesInjector") {
        rpg_dependenciesInjector dependenciesInjector;
        WHEN ("Registering class A as unretained dependency") {
            dependenciesInjector.registerDependency<A>(A::create);

            THEN ("One dependency is registered") {
                REQUIRE (dependenciesInjector.size() == 1);
            }
            THEN ("No instances are created yet") {
                REQUIRE (instCount == 0);
            }
        }
        
        WHEN ("Registering other class B as dependency with sub dependencies") {
            dependenciesInjector.registerDependency<B>(B::create, true);

            THEN ("One dependency is registered") {
                REQUIRE (dependenciesInjector.size() == 1);
            }
            THEN ("No instances are created yet") {
                REQUIRE (instCount == 0);
            }
        }
        
        WHEN ("Registering other class C as retained dependency") {
            dependenciesInjector.registerDependency<C>(C::create, true);
            
            THEN ("One dependency is registered") {
                REQUIRE (dependenciesInjector.size() == 1);
            }
            THEN ("No instances are created yet") {
                REQUIRE (instCount == 0);
            }
        }
        
        WHEN ("Registering several dependencies") {
            dependenciesInjector.registerDependency<A>(A::create);
            dependenciesInjector.registerDependency<B>(B::create);
            dependenciesInjector.registerDependency<C>(C::create, true);
            
            THEN ("3 dependencies are registered") {
                REQUIRE (dependenciesInjector.size() == 3);
            }
        }
        
        WHEN ("Registering dependencies then clearing all") {
            dependenciesInjector.registerDependency<A>(A::create);
            dependenciesInjector.registerDependency<B>(B::create);
            dependenciesInjector.registerDependency<C>(C::create, true);
            
            dependenciesInjector.clear();
            THEN ("No registered dependency") {
                REQUIRE (dependenciesInjector.size() == 0);
            }
        }
    }
}

SCENARIO ("Retrieved unretained dependencies", "[dependenciesInjector::injector::getDependency]") {
    GIVEN ("A dependencies injector RPGDependenciesInjector with A, B, C as registered dependencies") {
        rpg_dependenciesInjector dependenciesInjector;
        dependenciesInjector.registerDependency<A>(A::create);
        dependenciesInjector.registerDependency<B>(B::create);
        dependenciesInjector.registerDependency<C>(C::create, true);

        auto injector = dependenciesInjector.getInjector();

        WHEN ("Getting unretained dependency A") {
            auto a = injector->getDependency<A>();
            
            THEN ("Dependency is created") {
                REQUIRE (instCount == 1);
        
                a->doSomething();
                REQUIRE(a->functionCalled);
            }
        }
        
        WHEN ("Getting dependency B contained dependency A") {
            auto b = injector->getDependency<B>();
            
            THEN ("Dependency is created and sub dependency as well") {
                REQUIRE (instCount == 2);
                
                b->doSomething();
                REQUIRE(b->functionCalled);
                REQUIRE(b->m_a->functionCalled);
            }
        }
        
        WHEN("Getting 2 unretained dependencies A") {
            auto a = injector->getDependency<A>();
            auto a2 = injector->getDependency<A>();
            THEN ("Two instances are created") {
                REQUIRE (instCount == 2);
            }
        }
        
        WHEN("Leaving scopes of unretained dependencies") {
            {
                auto a = injector->getDependency<A>();
                REQUIRE (instCount == 1);
            }// leave scope here
            THEN ("one instance is removed because not retained") {
                REQUIRE (instCount == 0);
            }
        }
        
        WHEN("Getting retained dependency C") {
            auto c = injector->getDependency<C>();
            THEN ("Instance is created") {
                REQUIRE (instCount == 1);
                
                c->doSomething();
                REQUIRE(c->functionCalled);
            }
        }
        
        WHEN("Getting several retained dependencies C") {
            auto c = injector->getDependency<C>();
            auto c2 = injector->getDependency<C>();
            auto c3 = injector->getDependency<C>();
            
            THEN ("Only one instance is created") {
                REQUIRE (instCount == 1);
            }
        }
        
        WHEN("Getting several retained dependencies C") {
            auto c = injector->getDependency<C>();
            auto c2 = injector->getDependency<C>();
            auto c3 = injector->getDependency<C>();
            
            THEN ("Only one instance is created") {
                REQUIRE (instCount == 1);
            }
        }
        
        WHEN("Leaving scopes of retained dependency") {
            {
                auto a = injector->getDependency<C>();
                REQUIRE (instCount == 1);
            }// leave scope here
            THEN ("The instance is not removed because retained by the manager") {
                REQUIRE (instCount == 1);
            }
        }
        
        WHEN("Clearing dependencies after a retained dependencies has been created") {
            auto a = injector->getDependency<C>();
            REQUIRE (instCount == 1);
            
            dependenciesInjector.clear();
            THEN ("all instances has been deleted") {
                REQUIRE (instCount == 0);
            }
        }
        
        WHEN("Getting dependency which has not been registered") {
            auto dependency = injector->getDependency<int>();
            
            THEN ("There are no dependency") {
                REQUIRE (dependency == NULL);
            }
        }
    }
}

