//
//  BattleScene.cpp
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#include "BattleScene.h"
#include "StoryModeScene.h"
#include "../component/PlayerCard.h"
#include "../HelloWorldScene.h"
#include <editor-support/cocostudio/CocoStudio.h>
#include "cocos-ext.h"

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
    setSeletedCard(false);
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
    
    //基本サイズ
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    //Condition
    condition = BattleSceneCondition::getInstance();
    condition->setDelegate(this);
    
    //ルーム取得
    auto roomManager = RoomManager::getInstance();
    auto room = roomManager->getBattlingRoom();
    
#if COCOS2D_DEBUG
    CCLOG("vsizeX:%f", visibleSize.width);
    CCLOG("vsizeY:%f", visibleSize.height);
    CCLOG("originx:%f", origin.x);
    CCLOG("originy:%f", origin.y);
#endif
    
    //Cocostudio
    widget = GUIReader::getInstance()->widgetFromJsonFile("BattleSceneLayout/BattleSceneLayout.json");
    //差分を出す
    /*
    auto diff = visibleSize.height - 480;
    widget->setPositionY(diff / 2);
    this->origin.y = diff / 2;
     */
    this->addChild(widget, kBattleScenePriorty::Layout);
    
    //攻撃ボタンリスナー
    button = (Button*)widget->getChildByName("AttackButton");
    button->addTouchEventListener(this, toucheventselector(BattleScene::onTouchAttackButton));
    button->setTouchEnabled(false);
    button->setBright(false);
    
    //名前
    auto my_name = (Text*)widget->getChildByName("NameLeft");
    my_name->setText(room->getMyName());
    auto opp_name = (Text*)widget->getChildByName("NameRight");
    opp_name->setText(room->getOppName());
    
    //ターンカウント
    auto turn_count = (ImageView*)widget->getChildByName("TurnCount");
    auto turn_label = (TextAtlas*)turn_count->getChildByName("TurnCountLabel");
    turn_label->setStringValue(std::to_string(room->getTurn()));
    
    
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
        this->addChild(card, kBattleScenePriorty::Cards);
    }
    

    //Baseフレーム処理
    this->scheduleUpdate();
    this->schedule(schedule_selector(BattleScene::battleUpdate));
    
    //デバック用
    //scheduleOnce(schedule_selector(BattleScene::complted), 5.0f);
    
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
    
    //ローディングバー
    /*
    auto loadingBar = dynamic_cast<LoadingBar*>(widget->getChildByName("HPGaugeLeft"));
    auto pers = loadingBar->getPercent();
    loadingBar->setPercent(pers - 1);
     */
}

//バトルフレーム
void BattleScene::battleUpdate(float delta)
{
    if(! condition->isExecuteBattle()) return;
    
    if(condition->isCalcing()){
        CCLOG("calcing...");
        auto magicManager = MagicManager::getInstance();
        auto magic = magicManager->getMagicByHandCards(*hand_cards);
        auto opp_magic = magicManager->getById(2);
        
        auto battleProcessor = BattleProcessor::getInstance();
        battleProcessor->setMyMagic(magic);
        battleProcessor->setOppMagic(opp_magic);
        battleProcessor->setTurn(1);
        battleProcessor->execute();
        CCLOG("skill_name:%s", magic->getName().c_str());
        
    }
    
}

//攻撃ボタンタッチリスナー
bool BattleScene::onTouchAttackButton(cocos2d::Ref* sender, cocos2d::ui::TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN){
        //CCLOG("%s : %s(%d)", "button", "BattleScene:Began", __LINE__);
    }else if(type == TOUCH_EVENT_ENDED){
        //CCLOG("%s : %s(%d)", "button", "BattleScene::Ended:攻撃開始!!", __LINE__);
        condition->onExecuteBattle();
        auto disableLayer = disableTouchLayer::create();
        disableLayer->setTag(1);
        addChild(disableLayer, kBattleScenePriorty::DisableTouchLayer);
    }
    
    return true;
}

//シーンの切り替え
void BattleScene::complted(float delta)
{
    //Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StoryModeScene::createScene()));
}
