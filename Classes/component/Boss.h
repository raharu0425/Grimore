//
//  Boss.h
//  Grimore
//
//  Created by raharu on 2014/07/03.
//
//

#ifndef __Grimore__Boss__
#define __Grimore__Boss__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Boss : public Ref
{
private:
    Boss();
    virtual ~Boss();
public:
    //Method
    static Boss* getInstance();
    bool init();
    
    // struct
    CC_SYNTHESIZE(int, _id, Id);
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _element_identifer, ElementIdentifer);
    CC_SYNTHESIZE(int, _stage_id, StageId);
    CC_SYNTHESIZE(std::string, _message_start, MessageStart);
    CC_SYNTHESIZE(std::string, _message_win, MessageWin);
    CC_SYNTHESIZE(std::string, _message_lose, MessageLose);
};

#endif /* defined(__Grimore__Boss__) */
