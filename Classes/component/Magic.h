//
//  Magic.h
//  Grimore
//
//  Created by raharu on 2014/06/27.
//
//

#ifndef __Grimore__Magic__
#define __Grimore__Magic__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Magic : public Ref
{
private:
    Magic();
    virtual ~Magic();
public:
    //Method
    static Magic* getInstance();
    bool init();
    
    // struct
    CC_SYNTHESIZE(int, _id, Id);
    CC_SYNTHESIZE(int, _rank, Rank);
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _param_attack, ParamAttack);
    CC_SYNTHESIZE(int, _param_cure, ParamCure);
    CC_SYNTHESIZE(int, _param_stan, ParamStan);
};
#endif /* defined(__Grimore__Magic__) */
