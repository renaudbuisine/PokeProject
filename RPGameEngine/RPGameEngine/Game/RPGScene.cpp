//
//  RPGScene.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGScene.hpp"

//Constructor/destructor
rpg_scene::rpg_scene(rpg_dependenciesInjector::injector& injector) noexcept { }

// PURE VIRTUAL FUNCTIONS
void rpg_scene::update(const float elapsedTimestamp) noexcept { }
void rpg_scene::fixedUpdate(void) noexcept { }
