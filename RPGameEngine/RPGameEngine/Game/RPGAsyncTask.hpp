//
//  RPGAsyncTask.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGAsyncTask_hpp
#define RPGAsyncTask_hpp

#include <functional>

class rpg_game;

class rpg_asyncTask {
public:
    
    friend class rpg_game;
    
    //DELEGATION
    struct delegate {
        virtual ~delegate(void) = default;
        
        virtual void didCompleteTask(const rpg_asyncTask&) = 0;
    };
    
    //CONSTRUCTOR
    rpg_asyncTask(const std::function<void(void)>&) noexcept;
    virtual ~rpg_asyncTask(void) noexcept;
    
    void setDelegate(delegate *) noexcept;
    
private:
    bool m_completed;
    delegate *m_delegate;
    const std::function<void(void)> m_runBlock;
    
    bool isCompleted(void) const noexcept;
    void runTask(void);
    void broadcastDidComplete(void) noexcept;
};

#endif /* RPGAsyncTask_hpp */
