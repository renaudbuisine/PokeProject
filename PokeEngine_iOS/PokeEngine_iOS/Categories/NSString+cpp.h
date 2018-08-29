//
//  NSString+cpp.h
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 27/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <string>

@interface NSString(cpp)

@property (nonatomic, readonly) std::string stdString;

@end
