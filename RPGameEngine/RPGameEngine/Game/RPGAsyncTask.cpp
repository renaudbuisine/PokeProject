//
//  RPGAsyncTask.cpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 20/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#include "RPGAsyncTask.hpp"

#include "RPGMacro.hpp"

    //CONSTRUCTOR
rpg_asyncTask::rpg_asyncTask(const std::function<void(void)>& runBlock) noexcept: m_runBlock(runBlock) { }
rpg_asyncTask::~rpg_asyncTask(void) noexcept { }

void rpg_asyncTask::setDelegate(rpg_asyncTask::delegate *delegate) noexcept {
    m_delegate = delegate;
}
bool rpg_asyncTask::isCompleted(void) const noexcept {
    return m_completed;
}

void rpg_asyncTask::runTask(void) {
    m_runBlock();
    m_completed = true;
}

void rpg_asyncTask::broadcastDidComplete(void) noexcept {
    EXECPTRFUNCTION_1_OR_SKIP(m_delegate, didCompleteTask, *this)
}

