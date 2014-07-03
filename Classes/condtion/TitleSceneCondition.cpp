//
//  TitleSceneCondition.cpp
//  Grimore
//
//  Created by raharu on 2014/06/26.
//
//

#include "TitleSceneCondition.h"
#include "../scene/BattleScene.h"
#include "../scene/StoryModeScene.h"
#include "../Config.h"

static TitleSceneCondition *instance = nullptr;

TitleSceneCondition::TitleSceneCondition():
_error_msg("No setting")
{
}

TitleSceneCondition::~TitleSceneCondition()
{
    
}

//インスタンスの返却
TitleSceneCondition* TitleSceneCondition::getInstance()
{
    instance = new TitleSceneCondition();
    instance->autorelease();
    instance->retain();
    
    return instance;
}

//クライアント処理を追加する
void TitleSceneCondition::setDelegate(TitleSceneConditionDelegate *delegate)
{
    this->delegate = delegate;
}

//コンディションの加算
void TitleSceneCondition::addCondition(int param)
{
    if(getLock()) return;
    if(!(this->getCondition() & param)){
        auto cond = this->getCondition();
        this->setCondition(cond + param);
    }
}

//コンディションの減算
void TitleSceneCondition::delCondition(int param)
{
    if(getLock()) return;
    if((this->getCondition() & param)){
        auto cond = this->getCondition();
        this->setCondition(cond - param);
    }
}

//メッセージの取得
std::string TitleSceneCondition::getErrorMessage()
{
    return this->_error_msg;
}

//エラー発生
void TitleSceneCondition::onError(std::string error_msg)
{
    this->_error_msg = error_msg;
    this->setCondition(IS_ERROR);
}

//スタート
void TitleSceneCondition::onStart()
{
    this->addCondition(IS_START);
}

//コンプリート
void TitleSceneCondition::onComplete()
{
    if(getLock()) return;
    setLock(true);
    this->setCondition(IS_COMPLETE);
    
    //UserDefault
    UserDefault::getInstance()->setIntegerForKey("database_version", APP_VERSION);
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StoryModeScene::createScene()));
}