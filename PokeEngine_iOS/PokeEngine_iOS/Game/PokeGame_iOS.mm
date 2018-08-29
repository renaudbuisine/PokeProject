//
//  PokeGame_iOS.m
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 22/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import "PokeGame_iOS.h"

#import "NSString+cpp.h"

#include <PokeEngine/PokeGame.hpp>

@implementation PokeGame_iOS

-(instancetype) initWithName:(NSString *)name {
    self = [super init];
    if (self) {
        poke_game game(name.stdString);
        game.load();
    }
    return self;
}

@end
