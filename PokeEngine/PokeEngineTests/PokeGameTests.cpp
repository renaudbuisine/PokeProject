//
//  PokeGameTests.cpp
//  PokeEngineTests
//
//  Created by Renaud Buisine on 21/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include "catch.hpp"

#include "PokeGame.hpp"

SCENARIO("", "") {
    GIVEN ("") {
        WHEN("") {
            poke_game game;
            std::cout << game.toString() << std::endl;
            
            THEN("") {
                REQUIRE(true);
            }
        }
    }
}
