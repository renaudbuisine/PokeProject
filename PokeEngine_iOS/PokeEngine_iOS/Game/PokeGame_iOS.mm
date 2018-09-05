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

@interface PokeGame_iOS() {
    poke_game *_game; // CHECK ARC !!!!
}

@end

@implementation PokeGame_iOS

- (instancetype)initWithName:(NSString *)name {
    self = [super init];
    if (self) {
        _game = new poke_game(name.stdString);
    }
    return self;
}

- (void)dealloc {
    delete(_game);
}

/**
 override setter to define callback regarding which functions implements the delegate object

 @param delegate new Delegate object
 */
- (void)setDelegate:(id<PokeGameDelegate>)delegate {
    _delegate = delegate;
    
    __weak PokeGame_iOS *weakSelf = self;
    
    if ([_delegate respondsToSelector:@selector(didUpdateWithElapsedTimestamp:)]) {
        _game->setUpdateCallback(^(const float elapsedTimestamp){
            [weakSelf.delegate didUpdateWithElapsedTimestamp:elapsedTimestamp];
        });
    } else {
        _game->setUpdateCallback(NULL);
    }
    
    if ([_delegate respondsToSelector:@selector(didFixedUpdate)]) {
        _game->setFixedUpdateCallback(^{
            [weakSelf.delegate didFixedUpdate];
        });
    } else {
        _game->setFixedUpdateCallback(NULL);
    }
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
