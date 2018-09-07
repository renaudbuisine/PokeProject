//
//  PokeGame.cpp
//  PokeEngine
//
//  Created by Renaud Buisine on 21/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "PokeGame.hpp"

#include "PokeDefaultMapRouter.hpp"

poke_game::poke_game(std::string name) noexcept: rpg_game(name) { }

// LOAD

void poke_game::load(void) noexcept {
    loadDependencies();
    loadRootScene();
}

void poke_game::loadDependencies(void) noexcept {
    auto mapRouterFactory = [&](rpg_dependenciesInjector::injector& injector){
        return new poke_default_mapRouter(*this);
    };
    registerDependency<poke_mapRouter>(mapRouterFactory);
}

void poke_game::loadRootScene(void) noexcept {
    
}
