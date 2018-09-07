//
//  PokeMapScene.cpp
//  PokeEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "PokeMapScene.hpp"

poke_mapScene::poke_mapScene(rpg_dependenciesInjector::injector& injector) noexcept:
    rpg_default_mapScene(injector),
    m_routerPtr(injector.getDependency<poke_mapRouter>()) { }
