//
//  PokeGameWrapper.hpp
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 22/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef PokeGameWrapper_hpp
#define PokeGameWrapper_hpp

#ifdef __cplusplus
extern "C" {
#endif
    const long new_poke_game(void);
    void delete_poke_game(const long);
    
    const char *poke_game_toString(const long);
    
#ifdef __cplusplus
}
#endif

#endif /* PokeGameWrapper_hpp */
