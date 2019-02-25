//
//  MockRouter.hpp
//  RPGameEngineTests
//
//  Created by Renaud Buisine on 18/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef MockRouter_hpp
#define MockRouter_hpp

#include "RPGRouter.hpp"
#include "MockScene.hpp"

struct mock_router final: public rpg_router {
    mock_router(rpg_game *game) noexcept: rpg_router(game), didEndTransitionCalled(false), didLoadCalled(false) { }
    
    void didEndTransition(void) noexcept {
        didEndTransitionCalled = true;
    }
    
    void didLoad(void) noexcept {
        didLoadCalled = true;
    }
    
    bool prepareScene(void) noexcept {
        return rpg_router::prepareScene<mock_scene>();
    }
    
    bool didEndTransitionCalled;
    bool didLoadCalled;
};

#endif /* MockRouter_hpp */
