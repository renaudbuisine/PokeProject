//
//  RPGMapSceneTests.cpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "catch.hpp"

#include "RPGDefaultGame.hpp"
#include "RPGDefaultMapScene.hpp"
#include "RPGDefaultCrossControl.hpp"
#include "RPGDependenciesInjector.hpp"

// STATEFULL VAR
rpg_game *mapSceneTestsGame;
rpg_dependenciesInjector *dependenciesInjector;
rpg_mapScene *mapScene;


SCENARIO ("Add cross control", "[rpg_mapScene::addControl]") {
    
    if(!mapSceneTestsGame) {
        mapSceneTestsGame = new rpg_default_game("mapSceneTestsGame");
        dependenciesInjector = new rpg_dependenciesInjector();
        mapScene = new rpg_default_mapScene(*dependenciesInjector->getInjector());
    }
    
    GIVEN ("A dependencies injector, a cross control and a map scene, all initialized") {
        bool callbackCalled = false;
        rpg_character::animationStatus characterAnimation;
        rpg_character::orientation characterOrientation;
        
        auto crossControlPtr = std::make_shared<rpg_default_crossControl>();
        mapScene->addControl(crossControlPtr);
        mapScene->setUpdateCharacterCallback([&callbackCalled, &characterAnimation, &characterOrientation](const rpg_character& character){
            characterAnimation = character.getStatus();
            characterOrientation = character.getOrientation();
            callbackCalled = true;
        });
        
        WHEN ("Doing nothing on control") {
            crossControlPtr->update(CROSSCONTROL_DIRECTION_NONE);
            mapScene->fixedUpdate();
            THEN ("The player character is not updated") {
                REQUIRE (callbackCalled == false);
            }
        }
        
        WHEN ("Performing cross control to right") {
            crossControlPtr->update(CROSSCONTROL_DIRECTION_RIGHT);
            mapScene->fixedUpdate();
            THEN ("Player character updates its orientation and start animating") {
                REQUIRE (callbackCalled == true);
                REQUIRE (characterAnimation == CHARACTER_ANIMATION_STATUS_WALK);
                REQUIRE (characterOrientation == CHARACTER_ORIENTATION_RIGHT);
            }
        }
        
        WHEN ("Performing cross control to top") {
            crossControlPtr->update(CROSSCONTROL_DIRECTION_TOP);
            mapScene->fixedUpdate();
            THEN ("Player character updates its orientation") {
                REQUIRE (callbackCalled == true);
                REQUIRE (characterAnimation == CHARACTER_ANIMATION_STATUS_WALK);
                REQUIRE (characterOrientation == CHARACTER_ORIENTATION_TOP);
            }
        }
        
        WHEN ("Stop performing control") {
            crossControlPtr->update(CROSSCONTROL_DIRECTION_NONE);
            mapScene->fixedUpdate();
            THEN ("Player character updates its animation to idle") {
                REQUIRE (callbackCalled == true);
                REQUIRE (characterAnimation == CHARACTER_ANIMATION_STATUS_IDLE);
                REQUIRE (characterOrientation == CHARACTER_ORIENTATION_TOP);
            }
        }
    }
}
