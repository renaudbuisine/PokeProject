//
//  PokeGame.cpp
//  PokeEngine
//
//  Created by Renaud Buisine on 21/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "PokeGame.hpp"

#include "PokeDefaultMapRouter.hpp"
#include "PokeMapScene.hpp"

poke_game::poke_game(std::string name) noexcept: rpg_game(name), m_rootRouter(NULL) { }

poke_game::~poke_game(void) noexcept {
    if(m_rootRouter) {
        delete m_rootRouter;
    }
}

// LOAD

void poke_game::load(void) noexcept {
    loadDependencies();
    loadRootScene();
}

void poke_game::loadDependencies(void) noexcept {
    registerDependency<poke_mapRouter>([&](rpg_dependenciesInjector::injector& injector){
        return new poke_default_mapRouter(*this);
    });
}

void poke_game::loadRootScene(void) noexcept {
    
    m_rootRouter = new poke_rootRouter(this);
    m_rootRouter->setParentDelegate(std::shared_ptr<rpg_router::delegate>(this));
    m_rootRouter->prepareScene()
}

//rpg_router::delegate Members

void poke_game::didLoad(void) noexcept {
    m_rootRouter->
}

void poke_game::didEndTransition(void) noexcept {
    
}
