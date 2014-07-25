//
//  Room.cpp
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#include "Room.h"

static Room *s_Shared = nullptr;

Room::Room()
{
    setId(0);
    setCondition(0);
    setBossId(0);
    setStageId(0);
    setTurn(0);
}

Room::~Room()
{
}

//getInstance
Room* Room::getInstance()
{
    s_Shared = new Room();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }else{
        CC_SAFE_DELETE(s_Shared);
        return NULL;
    }
}

// init
bool Room::init()
{
    return true;
}

//バトル中か
bool Room::isBattling()
{
    return getCondition() == kBattleCondition::Battling;
}

