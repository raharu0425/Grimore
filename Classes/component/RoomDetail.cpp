//
//  RoomDetail.cpp
//  Grimore
//
//  Created by raharu on 2014/07/26.
//
//

#include "RoomDetail.h"

static RoomDetail *s_Shared = nullptr;


RoomDetail::RoomDetail()
{
    setId(0);
    setCondition(0);
    setTurn(0);
    setMyHp(0);
    setMyMagicId(0);
    setOppHp(0);
    setOppMagicId(0);
}

RoomDetail::~RoomDetail()
{
}

//getInstance
RoomDetail* RoomDetail::getInstance()
{
    s_Shared = new RoomDetail();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }else{
        CC_SAFE_DELETE(s_Shared);
        return NULL;
    }
}

// init
bool RoomDetail::init()
{
    return true;
}
