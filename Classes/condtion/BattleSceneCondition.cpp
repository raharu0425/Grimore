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

//バトル開始
void BattleSceneCondition::executeBattle()
{
    //レイヤーの取得
    auto layer = (BattleScene*) delegate;
    
    //タッチ無効にする
    auto disableTouchlayer = disableTouchLayer::create();
    disableTouchlayer->setTag(1);
    layer->addChild(disableTouchlayer, kBattleScenePriorty::DisableTouchLayer);
    
    //現在選択されているものから魔法を取得

    /*
    auto callFunc = CallFunc::create([layer, disableTouchlayer](){
        //CCParticleSystemQuad* particle = CCParticleSystemQuad::create("MagicPlist/86.plist");
        //layer->addChild(particle,5);
        disableTouchlayer->removeFromParentAndCleanup(true);
    });
    auto BattleStart = ActionManagerEx::getInstance()->playActionByName("BattleSceneLayout.json", "AnimationBattleStart");
    
    auto callFunc2 = CallFunc::create([BattleStart](){
        BattleStart->play();
    });
    
    //layer->addChild(BattleStart);
     
     */
    //まずは結果を取得
    //auto result = getMagicTurn();
    
    //バトルスタート
    auto startBar = Sprite::create("BattleSceneLayout/layout/BattleStart.png");
    //ターンチェンジ
    auto changeBar = Sprite::create("BattleSceneLayout/layout/BattleStart.png");
    //終了
    auto endBar = Sprite::create("BattleSceneLayout/layout/BattleStart.png");
    
    //共通アニメーション
    auto startPoint = Point(500,230);
    auto centerPoint = Point(160, 230);
    auto endPoint = Point(-200, 230);
    
    auto movefrom = MoveTo::create(0.2f, centerPoint);
    auto delayto = DelayTime::create(0.5f);
    auto delayto2 = DelayTime::create(1.5f);
    auto moveto = MoveTo::create(0.2f, endPoint);
    
    auto sprite = Sprite::create();
    sprite->setPosition(160,240 + layer->origin.y);
    sprite->setTextureRect(Rect(0,0,320,480));
    sprite->setColor(Color3B(0,0,0));
    sprite->setOpacity(100);
    sprite->retain();
    auto callFunc2 = CallFunc::create([layer, sprite](){
        layer->addChild(sprite, 4);
    });
    
    auto callFunc = CallFunc::create([layer](){
        CCParticleSystemQuad* particle = CCParticleSystemQuad::create("MagicPlist/259.plist");
        particle->setScale(0.5f);
        particle->setPosition(Point(230,240));
        layer->addChild(particle,5);
    });
    
    auto callFunc3 = CallFunc::create([sprite,disableTouchlayer](){
        sprite->removeFromParentAndCleanup(true);
        disableTouchlayer->removeFromParentAndCleanup(true);
    });
    
    auto seq = Sequence::create(movefrom,delayto,moveto,callFunc2,delayto,callFunc,delayto2,callFunc3, NULL);
    
    //スタートバー
    startBar->setPosition(startPoint);
    startBar->setScale(2.0f);
    layer->addChild(startBar, kBattleScenePriorty::Action);
    startBar->runAction(seq);
    
    
    
}