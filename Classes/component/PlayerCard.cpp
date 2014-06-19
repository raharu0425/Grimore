//
//  PlayerCard.cpp
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#include "PlayerCard.h"

USING_NS_CC;

PlayerCard::PlayerCard()
{
    this->setIndex(0);
    this->setSelected(false);
}

//OverRide
PlayerCard* PlayerCard::create(const std::string& filename)
{
    PlayerCard *sprite = new PlayerCard();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        
        //リスナーのセット
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(PlayerCard::onTouchBegan, sprite);
        listener->onTouchMoved = CC_CALLBACK_2(PlayerCard::onTouchMoved, sprite);
        listener->onTouchEnded = CC_CALLBACK_2(PlayerCard::onTouchEnded, sprite);
        sprite->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
        
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool PlayerCard::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    auto box = this->getBoundingBox();
    auto point = this->getParent()->convertTouchToNodeSpace(touch);
    
    if(box.containsPoint(point)){
        auto moveScale  = ScaleTo::create(0.1f, 0.9f);
        this->runAction(moveScale);
        CCLOG("%s:idx:%d : %s(%d)", "card", this->getIndex(), "PlayerCard::onTouchBegan", __LINE__);
        return true;
    }
    return false;
}

void PlayerCard::onTouchMoved(Touch *touch, Event *unused_event)
{
    CCLOG("%s : %s(%d)", "PlayerCard", __FUNCTION__, __LINE__);
    
}

void PlayerCard::onTouchEnded(Touch *touch, Event *unused_event)
{
    CCLOG("%s:idx:%d : %s(%d)", "card", this->getIndex(), "PlayerCard::onTouchEnded", __LINE__);
    
    auto box = this->getBoundingBox();
    auto point = this->getParent()->convertTouchToNodeSpace(touch);
    
    if(box.containsPoint(point)){
        if(!this->getSelected()){
            auto moveScale  = ScaleTo::create(0.1f, 1.0f);
            auto movePosition = MoveTo::create(0.1f, Point(getPositionX(), getPositionY() + 20));
            auto seq = Sequence::create(moveScale, movePosition, NULL);
            this->runAction(seq);
            this->setSelected(true);
        }else{
            auto moveScale  = ScaleTo::create(0.1f, 1.0f);
            auto movePosition = MoveTo::create(0.1f, Point(getPositionX(), getPositionY() - 20));
            auto seq = Sequence::create(moveScale, movePosition, NULL);
            this->runAction(seq);
            this->setSelected(false);
        }
    }else{
        auto moveScale  = ScaleTo::create(0.1f, 1.0f);
        this->runAction(moveScale);
    }
    
}