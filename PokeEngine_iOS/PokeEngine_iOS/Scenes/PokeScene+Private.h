//
//  PokeScene+Private.h
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include <RPGameEngine/RPGScene.hpp>

#import <memory>

@interface PokeScene(Private)

@property (nonatomic, readonly) std::weak_ptr<rpg_scene> wrappedScenePtr;

- (instancetype)initWithWrappedScenePointer:(std::shared_ptr<rpg_scene>) wrappedScenePtr;

@end
