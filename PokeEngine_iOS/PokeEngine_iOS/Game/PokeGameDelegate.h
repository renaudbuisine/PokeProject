//
//  PokeGameDelegate.h
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 02/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol PokeGameDelegate <NSObject>
    @optional
    -(void) didUpdateWithElapsedTimestamp:(float)elapsedTimestamp;
    @optional
    -(void) didFixedUpdate;
@end
