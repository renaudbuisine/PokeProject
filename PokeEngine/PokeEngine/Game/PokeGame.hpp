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

#include "PokeRootRouter.hpp"

class poke_game final: public rpg_game, public rpg_router::delegate {
public:
    poke_game(std::string name) noexcept;
    ~poke_game(void) noexcept;
    
    void load(void) noexcept;
    
    //rpg_router::delegate Members
    void didLoad(void) noexcept;
    void didEndTransition(void) noexcept;
    
private:
    void loadDependencies(void) noexcept;
    void loadRootScene(void) noexcept;
    
    poke_rootRouter *m_rootRouter;
};

#endif /* PokeGame_hpp */
