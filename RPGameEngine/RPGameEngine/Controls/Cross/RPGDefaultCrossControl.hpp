//
//  RPGDefaultCrossControl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 05/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDefaultCrossControl_hpp
#define RPGDefaultCrossControl_hpp

#include "RPGAbstractCrossControl.hpp"

class rpg_default_crossControl final: public rpg_crossControl {
public:
    rpg_default_crossControl(void) noexcept;
    ~rpg_default_crossControl(void) noexcept;
    
    // rpg_crossControl implementation
    bool isPerforming(const direction) const noexcept;
    bool isNotPerformed(void) const noexcept;
    
    // updates
    void update(const int);
    
private:
    int m_directions;
};

#endif /* RPGDefaultCrossControl_hpp */
