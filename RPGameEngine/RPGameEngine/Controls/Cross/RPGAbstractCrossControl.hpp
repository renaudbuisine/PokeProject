//
//  RPGAbstractCrossControl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGAbstractCrossControl_hpp
#define RPGAbstractCrossControl_hpp

#include "RPGControl.hpp"

#define CROSSCONTROL_DIRECTION_NONE rpg_crossControl::direction::none
#define CROSSCONTROL_DIRECTION_LEFT rpg_crossControl::direction::left
#define CROSSCONTROL_DIRECTION_TOP rpg_crossControl::direction::top
#define CROSSCONTROL_DIRECTION_RIGHT rpg_crossControl::direction::right
#define CROSSCONTROL_DIRECTION_BOTTOM rpg_crossControl::direction::bottom

class rpg_crossControl: public rpg_control {
public:
    
    enum direction {
        none = 0,
        left = 1 << 1,
        top = 1 << 2,
        right = 1 << 3,
        bottom = 1 << 4,
    };
    
    virtual bool isPerforming(const direction) const noexcept = 0;
    virtual bool isNotPerformed(void) const noexcept = 0;
protected:
    rpg_crossControl(void) noexcept: rpg_control() { }
};

#endif /* RPGAbstractCrossControl_hpp */
