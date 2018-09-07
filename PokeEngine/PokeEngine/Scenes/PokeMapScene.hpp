//
//  PokeMapScene.hpp
//  PokeEngine
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef PokeMapScene_hpp
#define PokeMapScene_hpp

#include <RPGameEngine/RPGDefaultMapScene.hpp>

#include "PokeAbstractMapRouter.hpp"

class poke_mapScene final: public rpg_default_mapScene {
public:
    poke_mapScene(rpg_dependenciesInjector::injector&) noexcept;
    
private:
    rpg_dependenciesInjector::injector::injectedPtr<poke_mapRouter> m_routerPtr;
};

#endif /* PokeMapScene_hpp */
