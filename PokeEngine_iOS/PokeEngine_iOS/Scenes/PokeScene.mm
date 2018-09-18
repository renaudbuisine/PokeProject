//
//  PokeScene.m
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 07/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import "PokeScene.h"
#import "PokeScene+Private.h"

#import <memory>

@interface PokeScene() {
    std::weak_ptr<rpg_scene> _wrappedScenePtr;
}
@end

@implementation PokeScene

- (instancetype)initWithWrappedScenePointer:(std::shared_ptr<rpg_scene>) wrappedScenePtr {
    self = [super init];
    if(self) {
        _wrappedScenePtr = wrappedScenePtr;
    }
    return self;
}

- (std::weak_ptr<rpg_scene>)wrappedScenePtr {
    return _wrappedScenePtr;
}

@end
