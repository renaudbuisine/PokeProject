//
//  PokeGame.h
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 22/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "PokeGameDelegate.h"

@interface PokeGame : NSObject

@property (nonatomic, weak) id <PokeGameDelegate> _Nullable delegate;

- (instancetype _Nonnull)initWithName:(NSString * _Nonnull)name;

// Life cycle
- (void)load;
- (void)run;
- (void)pause;
- (void)resume;
- (void)stop;

@end
