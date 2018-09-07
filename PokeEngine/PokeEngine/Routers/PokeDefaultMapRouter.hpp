//
//  PokeDefaultMapRouter.hpp
//  PokeEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef PokeDefaultMapRouter_hpp
#define PokeDefaultMapRouter_hpp

#include "PokeAbstractMapRouter.hpp"

class poke_default_mapRouter final: poke_mapRouter {
public:
    poke_default_mapRouter(const rpg_game&) noexcept;
private:
};

#endif /* PokeDefaultMapRouter_hpp */
