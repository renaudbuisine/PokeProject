//
//  PokeGame.hpp
//  PokeEngine
//
//  Created by Renaud Buisine on 21/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef PokeGame_hpp
#define PokeGame_hpp

#include <stdio.h>
#include <RPGameEngine/RPGame.hpp>

class poke_game: public rpg_game {
public:
    poke_game(std::string name) noexcept;
};

#endif /* PokeGame_hpp */
