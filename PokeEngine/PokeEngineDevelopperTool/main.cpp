//
//  main.cpp
//  PokeEngineDevelopperTool
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include <iostream>

#include "PokeGame.hpp"

int main(int argc, const char * argv[]) {
    
    poke_game game;
    
    std::cout << game.toString() << std::endl;
    
    return 0;
}
