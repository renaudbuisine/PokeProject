//
//  RPGDefaultGame.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 11/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDefaultGame_hpp
#define RPGDefaultGame_hpp

#include "RPGame.hpp"

struct rpg_default_game final: public rpg_game {
    rpg_default_game(const std::string&);
    
    void load(void) noexcept;
    void update(const float elapsedTimestamp);
    void fixedUpdate(void);
};

#endif /* RPGDefaultGame_hpp */
