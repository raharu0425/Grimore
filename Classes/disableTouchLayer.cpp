//
//  disableTouchLayer.cpp
//  Grimore
//
//  Created by raharu on 2014/06/23.
//
//

#include "disableTouchLayer.h"

USING_NS_CC;

bool disableTouchLayer::init()
{
    if ( !Layer::init() ) return false;
    
    //リスナーのセット
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(disableTouchLayer::onTouchBegan, this);
    listener->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool disableTouchLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    push_count++;
    if(push_count >= 10){
        this->removeFromParentAndCleanup(true);
    }
    CCLOG("%d : %s(%d)", push_count, "disableTouch", __LINE__);
    return true;
}