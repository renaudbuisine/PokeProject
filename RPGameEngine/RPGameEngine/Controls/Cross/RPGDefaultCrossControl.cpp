//
//  RPGDefaultCrossControl.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGDefaultCrossControl.hpp"

rpg_default_crossControl::rpg_default_crossControl(void) noexcept: rpg_crossControl(), m_directions(CROSSCONTROL_DIRECTION_NONE) { }
rpg_default_crossControl::~rpg_default_crossControl(void) noexcept { }

bool rpg_default_crossControl::isPerforming(const rpg_crossControl::direction directions) const noexcept {
    return m_directions & directions;
}

bool rpg_default_crossControl::isNotPerformed(void) const noexcept {
    return m_directions == CROSSCONTROL_DIRECTION_NONE;
}

void rpg_default_crossControl::update(const int directions) {
    m_directions = directions;
}
