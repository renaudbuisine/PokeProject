//
//  RPGCharacter.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 06/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGCharacter.hpp"

// CONSTRUCTOR
rpg_character::rpg_character(const rpg_point position) noexcept: rpg_object(position), m_orientation(CHARACTER_ORIENTATION_DEFAULT), m_status(CHARACTER_ANIMATION_STATUS_NONE) { }

// GETTER SETTER
rpg_character::orientation rpg_character::getOrientation(void) const noexcept { return m_orientation; }
void rpg_character::setOrientation(const rpg_character::orientation orientation) noexcept { m_orientation = orientation; }
rpg_character::animationStatus rpg_character::getStatus(void) const noexcept { return m_status; }
void rpg_character::setStatus(const rpg_character::animationStatus status) noexcept { m_status = status; }
