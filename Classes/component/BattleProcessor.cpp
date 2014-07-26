//
//  BattleProcessor.cpp
//  Grimore
//
//  Created by raharu on 2014/06/30.
//
//

#include "BattleProcessor.h"

static BattleProcessor *s_Shared = nullptr;

BattleProcessor::BattleProcessor()
{
}

BattleProcessor::~BattleProcessor()
{
}

//getInstance
BattleProcessor* BattleProcessor::getInstance()
{
    s_Shared = new BattleProcessor();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }else{
        CC_SAFE_DELETE(s_Shared);
        return NULL;
    }
}

// init
bool BattleProcessor::init()
{
    return true;
}

void BattleProcessor::execute()
{
    //auto my_magic = getMyMagic();
    //auto opp_magic = getOppMagic();
    
    //自分の攻撃を食らわせる
    
}



