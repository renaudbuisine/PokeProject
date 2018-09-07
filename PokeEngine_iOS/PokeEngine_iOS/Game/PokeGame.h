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

@property (nonatomic, weak) id<PokeGameDelegate> delegate;

- (instancetype)initWithName:(NSString *)name;

// Life cycle
- (void)run;
- (void)pause;
- (void)resume;
- (void)stop;

@end
