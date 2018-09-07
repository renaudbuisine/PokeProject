//
//  PokeAbstractMapRouter.hpp
//  PokeEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef PokeAbstractMapRouter_hpp
#define PokeAbstractMapRouter_hpp

#include <RPGameEngine/RPGRouter.hpp>

struct poke_mapRouter: public rpg_router {
    poke_mapRouter(const rpg_game& game) noexcept: rpg_router(game) { }
};

#endif /* PokeAbstractMapRouter_hpp */
