//
//  PokeGame.m
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 22/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import "PokeGame.h"

#import "NSString+cpp.h"

#include <PokeEngine/PokeGame.hpp>
#include <PokeEngine/PokeMapScene.hpp>

#include "PokeScene.h"
#include "PokeScene+Private.h"
#include "PokeMapScene.h"

@interface PokeGame() {
    poke_game *_game;
}

@end

@implementation PokeGame

#pragma mark - Constructor / Destructor

- (instancetype)initWithName:(NSString *)name {
    self = [super init];
    if (self) {
        _game = new poke_game(name.stdString);
        
        __weak PokeGame *weakSelf = self;
        
        _game->setAddSceneCallBack(^(std::shared_ptr<rpg_scene> scenePtr){ plutot pour le create
            PokeScene *scene = [self sceneFromWrappedScenePtr:scenePtr];
            [weakSelf.delegate game:self didAddScene:scene];
        });
    }
    return self;
}

- (void)dealloc {
    delete(_game);
}

#pragma mark - Factory

- (PokeScene * _Nonnull)sceneFromWrappedScenePtr:(std::shared_ptr<rpg_scene>)scenePtr{
    if(std::dynamic_pointer_cast<poke_mapScene>(scenePtr)) {
        return [[PokeMapScene alloc] initWithWrappedScenePointer:scenePtr];
    } else {
        return [[PokeScene alloc] initWithWrappedScenePointer:scenePtr];
    }
}

#pragma mark - Delegation

/**
 override setter to define callback regarding which functions implements the delegate object

 @param delegate new Delegate object
 */
- (void)setDelegate:(id<PokeGameDelegate>)delegate {
    _delegate = delegate;
    
    __weak PokeGame *weakSelf = self;
    
    //OPTIONALS
    if ([_delegate respondsToSelector:@selector(game:didUpdateWithElapsedTimestamp:)]) {
        _game->setUpdateCallback(^(const float elapsedTimestamp){
            [weakSelf.delegate game:self didUpdateWithElapsedTimestamp:elapsedTimestamp];
        });
    } else {
        _game->setUpdateCallback(NULL);
    }
    
    if ([_delegate respondsToSelector:@selector(didFixedUpdate:)]) {
        _game->setFixedUpdateCallback(^{
            [weakSelf.delegate didFixedUpdate:self];
        });
    } else {
        _game->setFixedUpdateCallback(NULL);
    }
}

#pragma mark - Life cycle

- (void)load {
    _game->load();
}

- (void)run {
    _game->run();
}

- (void)pause {
    _game->pause();
}

- (void)resume {
    _game->resume();
}

- (void)stop {
    _game->stop();
}

@end
