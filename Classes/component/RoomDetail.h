//
//  RoomDetail.h
//  Grimore
//
//  Created by raharu on 2014/07/26.
//
//

#ifndef __Grimore__RoomDetail__
#define __Grimore__RoomDetail__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

//RoomDetail
class RoomDetail: public Ref
{
private:
    RoomDetail();
    virtual ~RoomDetail();
public:
    //Method
    static RoomDetail* getInstance();
    bool init();
    
    // struct
    CC_SYNTHESIZE(int, _detail_id, Id);
    CC_SYNTHESIZE(int, _room_id, Condition);
    CC_SYNTHESIZE(int, _turn, Turn);
    CC_SYNTHESIZE(int, _my_hp, MyHp);
    CC_SYNTHESIZE(int, _my_magic_id, MyMagicId);
    CC_SYNTHESIZE(int, _opp_hp, OppHp);
    CC_SYNTHESIZE(int, _opp_magic_id, OppMagicId);
    
};

#endif /* defined(__Grimore__RoomDetail__) */
