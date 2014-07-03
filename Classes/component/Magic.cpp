//
//  Magic.cpp
//  Grimore
//
//  Created by raharu on 2014/06/27.
//
//

#include "Magic.h"

static Magic *s_Shared = nullptr;

Magic::Magic()
{
    setId(0);
    setName("スカ");
    setRank(1);
    setParamAttack(5);
    setParamCure(0);
    setParamStan(0);
}

Magic::~Magic()
{
}

//getInstance
Magic* Magic::getInstance()
{
    s_Shared = new Magic();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }else{
        CC_SAFE_DELETE(s_Shared);
        return NULL;
    }
}

// init
bool Magic::init()
{
    return true;
}