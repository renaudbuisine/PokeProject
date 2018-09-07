//
//  RPGObject.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 06/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGObject.hpp"

rpg_object::rpg_object(void) noexcept: m_position(rpg_point()) { }
rpg_object::rpg_object(const rpg_point position) noexcept: m_position(position) { }

rpg_point rpg_object::getPosition(void) const noexcept {
    return m_position;
}
void rpg_object::setPosition(const rpg_point position) noexcept {
    m_position = position;
}
