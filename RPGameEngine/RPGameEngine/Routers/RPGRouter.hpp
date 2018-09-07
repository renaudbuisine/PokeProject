//
//  RPGRouter.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGRouter_hpp
#define RPGRouter_hpp

#include "RPGame.hpp"

class rpg_router {
public:
    rpg_router(const rpg_game&) noexcept;
    virtual ~rpg_router(void) noexcept = default;
protected:
    const rpg_game& m_game;
};

#endif /* RPGRouter_hpp */
