//
//  PlayerCard.h
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#ifndef __Grimore__PlayerCard__
#define __Grimore__PlayerCard__

#include <iostream>
#include "cocos2d.h"

class PlayerCard : public cocos2d::Sprite
{
    
public :
    PlayerCard();
    CREATE_FUNC(PlayerCard);
    
    static PlayerCard* create(const std::string& filename);
    
    CC_SYNTHESIZE(int, _index, Index);
    CC_SYNTHESIZE(bool, _is_Selected, Selected);
    
    //タッチイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__Grimore__PlayerCard__) */
