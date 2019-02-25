//
//  RPGMacro.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGMacro_hpp
#define RPGMacro_hpp

#define CALL(f) if(f) f();
#define CALL_1(f,arg1) if(f) f(arg1);
#define CALL_2(f, arg1, arg2) if(f) f(arg1, arg2);

#define EXECPTRFUNCTION_OR_SKIP(ptr, function) if(ptr) ptr->function();
#define EXECPTRFUNCTION_1_OR_SKIP(ptr, function, arg1) if(ptr) ptr->function(arg1);
#define EXECPTRFUNCTION_2_OR_SKIP(ptr, function, arg1, arg2) if(ptr) ptr->function(arg1, arg2);

#endif /* RPGMacro_hpp */
