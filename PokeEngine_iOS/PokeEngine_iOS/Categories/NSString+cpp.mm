//
//  NSString+cpp.m
//  PokeEngine_iOS
//
//  Created by Renaud Buisine on 27/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#import "NSString+cpp.h"

@implementation NSString(cpp)

- (std::string)stdString {
    return std::string([self cStringUsingEncoding:NSUTF8StringEncoding]);
}

@end
