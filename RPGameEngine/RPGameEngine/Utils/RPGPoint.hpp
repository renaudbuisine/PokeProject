//
//  RPGPoint.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 06/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGPoint_hpp
#define RPGPoint_hpp

struct rpg_point {
    rpg_point(float = 0, float = 0) noexcept;
    ~rpg_point(void) noexcept;
    
    float x, y;
};

#endif /* RPGPoint_hpp */
