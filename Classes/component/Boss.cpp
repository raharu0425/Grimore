//
//  Boss.cpp
//  Grimore
//
//  Created by raharu on 2014/07/03.
//
//

#include "Boss.h"

static Boss *s_Shared = nullptr;

Boss::Boss()
{
}

Boss::~Boss()
{
}

//getInstance
Boss* Boss::getInstance()
{
    s_Shared = new Boss();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }else{
        CC_SAFE_DELETE(s_Shared);
        return NULL;
    }
}

// init
bool Boss::init()
{
    return true;
}