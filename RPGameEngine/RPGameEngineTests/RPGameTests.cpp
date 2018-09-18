//
//  RPGameTests.cpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 10/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include <stdio.h>

#include "catch.hpp"

#include "MockScene.hpp"
#include "RPGDefaultGame.hpp"

//STATEFULL
rpg_game *testsGame;

std::shared_ptr<rpg_scene> lastScenePtr;
void addSceneCallback(std::shared_ptr<rpg_scene> scenePtr) {
    lastScenePtr = scenePtr;
}
std::shared_ptr<rpg_scene> removedScenePtr;
void removeSceneCallback(std::shared_ptr<rpg_scene> scenePtr) {
    removedScenePtr = scenePtr;
}

SCENARIO ("Push / Pop / SetRoot scene", "[rpg_game::push/pop/setRootScene]") {
    
    GIVEN ("A game") {
        
        WHEN ("Creating the game object, callbacks initialised") {
            testsGame = new rpg_default_game("testsGame");
            testsGame->setAddSceneCallBack(addSceneCallback);
            testsGame->setRemoveSceneCallBack(removeSceneCallback);
            
            THEN ("No scenes are loaded yet") {
                REQUIRE (testsGame->getScenes().size() == 0);
            }
        }
        
        WHEN ("Creating a new scene and adding it as root") {
            std::shared_ptr<rpg_scene> newScenePtr = testsGame->createScene<mock_scene>();
            testsGame->setRootScene(newScenePtr);
            THEN ("The game contains one scene and add callback is called") {
                REQUIRE (testsGame->getScenes().size() == 1);
                REQUIRE (lastScenePtr == newScenePtr);
            }
        }
        
        WHEN ("Creating a scene and pushing it into the game object") {
            std::shared_ptr<rpg_scene> newScenePtr = testsGame->createScene<mock_scene>();
            testsGame->pushScene(newScenePtr);
            THEN ("The game contains two scenes and add scene callback was called") {
                REQUIRE (testsGame->getScenes().size() == 2);
                REQUIRE (lastScenePtr == newScenePtr);
            }
        }
        
        WHEN ("Creating a third scene and pushing it into the game object") {
            std::shared_ptr<rpg_scene> newScenePtr = testsGame->createScene<mock_scene>();
            testsGame->pushScene(newScenePtr);
            THEN ("The game contains three scenes and add scene callback was called") {
                REQUIRE (testsGame->getScenes().size() == 3);
                REQUIRE (lastScenePtr == newScenePtr);
            }
        }
        
        WHEN ("Poping a scene") {
            const std::shared_ptr<rpg_scene> topScene = testsGame->getScenes().back();
            testsGame->popScene();
            THEN ("The game contains two scenes and remove scene callback was called") {
                REQUIRE (testsGame->getScenes().size() == 2);
                REQUIRE (removedScenePtr == topScene);
            }
        }
        
        WHEN ("Creating a last new scene and adding it as root") {
            std::shared_ptr<rpg_scene> newScenePtr = testsGame->createScene<mock_scene>();
            const std::shared_ptr<rpg_scene> topScene = testsGame->getScenes().back();
            testsGame->setRootScene(newScenePtr);
            THEN ("The game contains only one scene and both add and remove scene callback were called") {
                REQUIRE (testsGame->getScenes().size() == 1);
                REQUIRE (lastScenePtr == newScenePtr);
                REQUIRE (removedScenePtr == topScene);
            }
        }
    }
}
