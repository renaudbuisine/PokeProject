//
//  PokeMapScene.m
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import "PokeMapScene.h"
#import "PokeScene+Private.h"

#include <RPGameEngine/RPGDefaultMapScene.hpp>

@interface PokeMapScene()

@property (nonatomic, readonly) std::shared_ptr<rpg_mapScene> wrappedMapScenePtr;

@end

@implementation PokeMapScene

- (std::shared_ptr<rpg_mapScene>)wrappedMapScenePtr {
    return std::dynamic_pointer_cast<rpg_mapScene>(super.wrappedScenePtr.lock());
}

@end
