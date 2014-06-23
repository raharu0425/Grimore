//
//  BattleScene.cpp
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#include "BattleScene.h"
#include "../component/PlayerCard.h"
#include "../HelloWorldScene.h"
#include <editor-support/cocostudio/CocoStudio.h>
#include "cocos-ext.h"
#include "../disableTouchLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio;
using namespace ui;

Scene* BattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = BattleScene::create();
    scene->addChild(layer);
    
    return scene;
}

//コンストラクタ
BattleScene::BattleScene(){
    //setSeletedCard(false);
}

//デストラクタ
BattleScene::~BattleScene()
{
    CCLOG("DeleteBattleScene");
}


// on "init" you need to initialize your instance
bool BattleScene::init()
{
    if ( !Layer::init() ) return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("vsizeX:%f", visibleSize.width);
    CCLOG("vsizeY:%f", visibleSize.height);
    CCLOG("originx:%f", origin.x);
    CCLOG("originy:%f", origin.y);
    
    //Cocostudio
    auto widget = GUIReader::getInstance()->widgetFromJsonFile("BattleSceneLayout/BattleSceneLayout.json");
    this->addChild(widget);
    
    //攻撃ボタンリスナー
    button = (Button*)widget->getChildByName("AttackButton");
    button->addTouchEventListener(this, toucheventselector(BattleScene::onTouchAttackButton));
    button->setTouchEnabled(false);
    button->setBright(false);
    
    //プレイヤーデッキインスタンス
    deck = PlayerDeckManager::getInstance();
    
    //手札をリロード
    deck->reload2HandsCards();
    
    //手札を取得
    hand_cards = deck->getHandsCards();
    hand_cards->retain();
    
    //表示
    for (auto idx = 0; idx < hand_cards->count(); idx++) {
        auto card  = (Sprite*) hand_cards->getObjectAtIndex(idx);
        card->setPosition(Point(((visibleSize.width / HANDS_DECK) * idx) + (card->getContentSize().width / 2) + 3 , 55 + origin.y));
        this->addChild(card, 1);
    }
    

    //Baseフレーム処理
    this->scheduleUpdate();
    
    //デバック用
    //scheduleOnce(schedule_selector(BattleScene::complted), 2.0f);
    
    return true;
}

//フレーム処理
void BattleScene::update(float delta)
{
    //この処理マネージャーに持っていくべきかな？持っていくのも一苦労なんだけども
    auto is_select = false;
    for (auto idx = 0; idx < hand_cards->count(); idx++) {
        auto card  = (PlayerCard*) hand_cards->getObjectAtIndex(idx);
        if(card->getSelected()){
            is_select = true;
        }
    }
    
    //Enbale > Disbale
    if(getSeletedCard() && !is_select){
        button->setTouchEnabled(false);
        button->setBright(false);
        setSeletedCard(is_select);
    }else if(!getSeletedCard() && is_select){
        button->setTouchEnabled(true);
        button->setBright(true);
        setSeletedCard(is_select);
    }
}

//攻撃ボタンタッチリスナー
bool BattleScene::onTouchAttackButton(cocos2d::Ref* sender, cocos2d::ui::TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN){
        CCLOG("%s : %s(%d)", "button", "BattleScene:Began", __LINE__);
    }else if(type == TOUCH_EVENT_ENDED){
        
        CCLOG("%s : %s(%d)", "button", "BattleScene::Ended:攻撃開始!!", __LINE__);
        
        //タッチ無効にする
        auto disableTouchlayer = disableTouchLayer::create();
        this->addChild(disableTouchlayer, 128);
        
    }
    return true;
}

//シーンの切り替え
void BattleScene::complted(float delta)
{
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));
}
