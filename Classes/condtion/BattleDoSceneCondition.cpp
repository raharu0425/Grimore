//
//  BattleDoSceneCondition.cpp
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#include "BattleDoSceneCondition.h"
#include "../scene/BattleScene.h"
#include "../Config.h"

static BattleDoSceneCondition *instance = nullptr;

BattleDoSceneCondition::BattleDoSceneCondition():
_error_msg("No setting")
{
    setLock(false);
}

BattleDoSceneCondition::~BattleDoSceneCondition()
{
    
}

//インスタンスの返却
BattleDoSceneCondition* BattleDoSceneCondition::getInstance()
{
    instance = new BattleDoSceneCondition();
    instance->autorelease();
    instance->retain();
    
    return instance;
}

//クライアント処理を追加する
void BattleDoSceneCondition::setDelegate(BattleDoSceneConditionDelegate *delegate)
{
    this->delegate = delegate;
}

//コンディションの加算
void BattleDoSceneCondition::addCondition(int param)
{
    if(getLock()) return;
    if(!(this->getCondition() & param)){
        auto cond = this->getCondition();
        this->setCondition(cond + param);
    }
}

//コンディションの減算
void BattleDoSceneCondition::delCondition(int param)
{
    if(getLock()) return;
    if((this->getCondition() & param)){
        auto cond = this->getCondition();
        this->setCondition(cond - param);
    }
}

//メッセージの取得
std::string BattleDoSceneCondition::getErrorMessage()
{
    return this->_error_msg;
}

//エラー発生
void BattleDoSceneCondition::onError(std::string error_msg)
{
    this->_error_msg = error_msg;
    this->setCondition(IS_ERROR);
}

//スタート
void BattleDoSceneCondition::onStart()
{
    this->addCondition(IS_START);
}

//コンプリート
void BattleDoSceneCondition::onComplete()
{
    if(getLock()) return;
    setLock(true);
    this->setCondition(IS_COMPLETE);
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, BattleScene::createScene()));
}