//
//  Room.h
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#ifndef __Grimore__Room__
#define __Grimore__Room__

#include <iostream>
#include "cocos2d.h"
#include "RoomDetail.h"

USING_NS_CC;

//状態
enum kBattleCondition{
    Battling = 1,
    Finish,
};

//Room
class Room : public Ref
{
private:
    Room();
    virtual ~Room();
public:
    //Method
    static Room* getInstance();
    bool init();
    
    // struct
    CC_SYNTHESIZE(int, _id, Id);
    CC_SYNTHESIZE(int, _condition, Condition);
    CC_SYNTHESIZE(int, _boss_id, BossId);
    CC_SYNTHESIZE(int, _stage_id, StageId);
    CC_SYNTHESIZE(int, _turn, Turn);
    CC_SYNTHESIZE(std::string, _my_name, MyName);
    CC_SYNTHESIZE(std::string, _opp_name, OppName);
    
    //Methods
    bool isBattling();
    RoomDetail* getDetail();
};

#endif /* defined(__Grimore__Room__) */
