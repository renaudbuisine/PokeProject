//
//  PokeMapScene.m
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import "PokeMapScene.h"

#include <RPGameEngine/RPGDefaultMapScene.hpp>

@interface PokeMapScene() {
    rpg_mapScene *_scene;
}

@end

@implementation PokeMapScene

- (instancetype)init
{
    self = [super init];
    if (self) {
        _scene = rpg_default_mapScene
    }
    return self;
}

- (void)dealloc {
    delete _scene;
}

@end
