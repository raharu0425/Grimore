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

USING_NS_CC;
using namespace cocostudio;

Scene* BattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = BattleScene::create();
    scene->addChild(layer);
    
    return scene;
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
    
    CCLOG("vsize:%f", visibleSize.width);
    CCLOG("origin:%f", origin.x);
    
    /*
    Cocostudioは後回しかな
    auto widget = GUIReader::getInstance()->widgetFromJsonFile("BattleUILayout/BattleUILayout.json");
    this->addChild(widget);
     */
    
    //ステージ
    background = Sprite::create("stage/BackGround_001.png");
    background->setScale(2.0f);
    background-> setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);
    
    //プレイヤーデッキインスタンス
    deck = PlayerDeckManager::getInstance();
    
    //手札をリロード
    deck->reload2HandsCards();
    
    //手札を取得
    auto hand_cards = deck->getHandsCards();
    
    //表示
    for (auto idx = 0; idx < hand_cards->count(); idx++) {
        auto card  = (Sprite*) hand_cards->getObjectAtIndex(idx);
        card->setPosition(Point(((visibleSize.width / HANDS_DECK) * idx) + (card->getContentSize().width / 2) + 3 , 80 + origin.y));
        this->addChild(card, 1);
    }
    
    //デバック用
    //scheduleOnce(schedule_selector(BattleScene::complted), 2.0f);
    
    return true;
}

//シーンの切り替え
void BattleScene::complted(float delta)
{
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));
}
