//
//  PokeGameDelegate.h
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 02/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

@class PokeGame;
@class PokeScene;

@protocol PokeGameDelegate <NSObject>
- (void)game:(PokeGame * _Nonnull)game didAddScene:(PokeScene * _Nonnull)scene;
- (void)game:(PokeGame * _Nonnull)game willRemoveScene:(PokeScene * _Nonnull)scene;
- (void)game:(PokeGame * _Nonnull)game didCreateScene:(PokeScene * _Nonnull)scene;

@optional
- (void)game:(PokeGame * _Nonnull)game didUpdateWithElapsedTimestamp:(float)elapsedTimestamp;
@optional
- (void)didFixedUpdate:(PokeGame * _Nonnull)game;
@end
