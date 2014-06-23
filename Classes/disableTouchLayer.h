//
//  disableTouchLayer.h
//  Grimore
//
//  Created by raharu on 2014/06/23.
//
//

#ifndef __Grimore__disableTouchLayer__
#define __Grimore__disableTouchLayer__

#include <iostream>
#include "cocos2d.h"

class disableTouchLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    CREATE_FUNC(disableTouchLayer);
    
    int push_count;
};

#endif /* defined(__Grimore__disableTouchLayer__) */
