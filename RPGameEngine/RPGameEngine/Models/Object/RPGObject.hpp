//
//  RPGObject.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 06/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGObject_hpp
#define RPGObject_hpp

#include "RPGPoint.hpp"

class rpg_object {
public:
    rpg_object(void) noexcept;
    rpg_object(const rpg_point) noexcept;
    virtual ~rpg_object(void) noexcept = default;
    
    rpg_point getPosition(void) const noexcept;
    void setPosition(const rpg_point) noexcept;
private:
    rpg_point m_position;
};

#endif /* RPGObject_hpp */
