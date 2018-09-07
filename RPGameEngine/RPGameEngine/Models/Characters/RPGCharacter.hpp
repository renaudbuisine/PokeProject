//
//  RPGCharacter.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 06/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGCharacter_hpp
#define RPGCharacter_hpp

#include "RPGObject.hpp"

#define CHARACTER_ORIENTATION_LEFT rpg_character::orientation::left
#define CHARACTER_ORIENTATION_TOP rpg_character::orientation::top
#define CHARACTER_ORIENTATION_RIGHT rpg_character::orientation::right
#define CHARACTER_ORIENTATION_BOTTOM rpg_character::orientation::bottom
#define CHARACTER_ORIENTATION_DEFAULT CHARACTER_ORIENTATION_BOTTOM

#define CHARACTER_ANIMATION_STATUS_NONE rpg_character::animationStatus::none
#define CHARACTER_ANIMATION_STATUS_IDLE rpg_character::animationStatus::idle
#define CHARACTER_ANIMATION_STATUS_WALK rpg_character::animationStatus::walk
#define CHARACTER_ANIMATION_STATUS_RUN rpg_character::animationStatus::run

class rpg_character: public rpg_object {
public:
    enum orientation { left, right, top, bottom };
    enum animationStatus { none, idle, walk, run };
    
    rpg_character(const rpg_point = rpg_point()) noexcept;
    
    orientation getOrientation(void) const noexcept;
    void setOrientation(const orientation) noexcept;
    animationStatus getStatus(void) const noexcept;
    void setStatus(const animationStatus) noexcept;
private:
    orientation m_orientation;
    animationStatus m_status;
};

#endif /* RPGCharacter_hpp */
