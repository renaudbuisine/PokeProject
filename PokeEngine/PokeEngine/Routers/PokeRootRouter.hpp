//
//  PokeRootRouter.hpp
//  PokeEngine
//
//  Created by Renaud Buisine on 19/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef PokeRootRouter_hpp
#define PokeRootRouter_hpp

#include <RPGameEngine/RPGRouter.hpp>

class poke_rootRouter final: public rpg_router {
    poke_rootRouter(rpg_game *) noexcept;
    
    void didEndTransition(void) noexcept;
    void didLoad(void) noexcept;
    
    bool prepareScene(void) noexcept;
}

#endif /* PokeRootRouter_hpp */
