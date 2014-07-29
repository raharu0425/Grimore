//
//  BattleSceneCondition.cpp
//  Grimore
//
//  Created by raharu on 2014/06/23.
//
//

#include "BattleSceneCondition.h"
#include "../scene/BattleScene.h"
#include "../disableTouchLayer.h"
#include "../Config.h"

#include <editor-support/cocostudio/CocoStudio.h>

using namespace cocostudio;

static BattleSceneCondition *instance = nullptr;

BattleSceneCondition::BattleSceneCondition()
{
    this->setLock(false);
    this->setCondition(IS_NONE);
}

BattleSceneCondition::~BattleSceneCondition()
{
    
}

//インスタンスの返却
BattleSceneCondition* BattleSceneCondition::getInstance()
{
    instance = new BattleSceneCondition();
    instance->autorelease();
    instance->retain();
    
    return instance;
}


//クライアント処理を追加する
void BattleSceneCondition::setDelegate(BattleSceneConditionDelegate *delegate)
{
    this->delegate = delegate;
}

//コンディションの加算
void BattleSceneCondition::addCondition(int param)
{
    if(getLock()) return;
    if(!(this->getCondition() & param)){
        auto cond = this->getCondition();
        this->setCondition(cond + param);
    }
}

//コンディションの減算
void BattleSceneCondition::delCondition(int param)
{
    if(getLock()) return;
    if((this->getCondition() & param)){
        auto cond = this->getCondition();
        this->setCondition(cond - param);
    }
}


//バトルの開始
void BattleSceneCondition::onExecuteBattle()
{
    this->setCondition(IS_EXECUTE_BATTLE);
    this->addCondition(IS_CALCING);
}