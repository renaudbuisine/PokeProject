//
//  RPGRouterTests.cpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 10/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#include "catch.hpp"

#include "RPGDefaultGame.hpp"

#include "MockScene.hpp"
#include "MockRouter.hpp"

// STATEFULL VAR / CONFIG
rpg_game *routerTestsGame;
rpg_router *router;

bool mockedLoadResourcesIsLoading = false;
void mockedLoadResoures() {
    mockedLoadResourcesIsLoading = true;
    while(mockedLoadResourcesIsLoading);
}

std::weak_ptr<rpg_scene> transitioningScene;
bool isTransitioningScene;
void mockedStartTransition(std::shared_ptr<rpg_scene> scene) {
    isTransitioningScene = true;
    transitioningScene = scene;
    while(isTransitioningScene);
}


SCENARIO ("Load and display new scene", "[rpg_router::prepareScene]") {
    if(!routerTestsGame) {
        routerTestsGame = new rpg_default_game("testGame");
        router = new mock_router(routerTestsGame);
        router->setLoadResourcesCallback(mockedLoadResoures);
        router->setTransitionToSceneCallbackCallback(mockedStartTransition);

        routerTestsGame->run();
    }
    GIVEN ("A game and a linked router and its callbacks") {
        WHEN ("Nothing is done yet") {
            THEN ("Router is not loading and not loaded") {
                REQUIRE (!router->isLoading());
                REQUIRE (!router->isLoaded());
                REQUIRE(routerTestsGame->updatedRoutersSize() == 0);
            }
        }
        
        WHEN ("Transition is started whereas scene is not loaded yet") {
            THEN ("Nothing is happening") {
                bool transitioning = router->transitionToNextScene();
                REQUIRE(!transitioning);
                REQUIRE(!router->isLoading());
                REQUIRE(!router->isLoaded());
                REQUIRE(routerTestsGame->updatedRoutersSize() == 0);
            }
        }
        
        WHEN ("Preparing scene") {
            router->prepareScene();
            THEN ("Scene is created from game object and is loading, no scene are added yet to the game") {
                REQUIRE(mock_scene::mockSceneInst);
                REQUIRE(router->isLoading());
                REQUIRE(routerTestsGame->updatedRoutersSize() == 0);
                REQUIRE(routerTestsGame->getScenes().size() == 0);
            }
        }
        WHEN ("Scene is loaded") {
            mock_scene::mockSceneInst->forceLoaded = true;
            sleep(1);
            THEN ("Scene is loaded and resources callback to load resources") {
                REQUIRE(mock_scene::mockSceneInst->isLoaded());
                REQUIRE(mockedLoadResourcesIsLoading);
                REQUIRE(router->isLoading());
            }
        }
        
        WHEN ("Scene and resources are loaded, another update from game is applied") {
            mockedLoadResourcesIsLoading = false;
            sleep(1); // be sure update is called a last time
            THEN ("Router is loaded, ready for transition") {
                REQUIRE(router->isLoaded());
                REQUIRE(routerTestsGame->updatedRoutersSize() == 0);
                REQUIRE(routerTestsGame->getScenes().size() == 0);
                REQUIRE(!transitioningScene.lock());
                REQUIRE(!router->isTransitioningToNextScene());
            }
        }
        
        WHEN ("Start transitioning to cene") {
            bool transitioning = router->transitionToNextScene();
            THEN ("Router is added to game, start transition callback is called, still no scene added to game") {
                REQUIRE(transitioning);
                REQUIRE(routerTestsGame->updatedRoutersSize() == 1);
                REQUIRE(routerTestsGame->getScenes().size() == 0);
                REQUIRE(transitioningScene.lock());
                REQUIRE(router->isTransitioningToNextScene());
            }
        }
        
        WHEN ("Transition is finished, router is removed from list of updated router from game") {
            isTransitioningScene = false;
            sleep(1);
            THEN ("didEndTransition is called and scene is added to game correctly") {
                REQUIRE(((mock_router *)router)->didEndTransitionCalled);
                REQUIRE(!router->isTransitioningToNextScene());
                REQUIRE(routerTestsGame->updatedRoutersSize() == 0);
                REQUIRE(routerTestsGame->getScenes().size() == 1);
            }
        }
    }
}
