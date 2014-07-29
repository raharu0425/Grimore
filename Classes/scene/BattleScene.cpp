
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
    deck->release();
    hand_cards->release();
    used_cards->release();
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
    button->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
        if(type == Widget::TouchEventType::ENDED){
            condition->onExecuteBattle();
            auto disableLayer = disableTouchLayer::create();
            disableLayer->setTag(1);
            addChild(disableLayer, kBattleScenePriorty::DisableTouchLayer);
            //scheduleOnce(schedule_selector(BattleScene::battleUpdate), 0.5f );
        }
    });
    button->setTouchEnabled(false);
    button->setBright(false);
    
    //名前
    auto my_name = (Text*)widget->getChildByName("NameRight");
    my_name->setString(room->getMyName());
    auto opp_name = (Text*)widget->getChildByName("NameLeft");
    opp_name->setString(room->getOppName());
    
    //ターンカウント
    auto turn_count = (ImageView*)widget->getChildByName("TurnCount");
    auto turn_label = (TextAtlas*)turn_count->getChildByName("TurnCountLabel");
    turn_label->setString(std::to_string(room->getTurn()));
    
    
    //プレイヤーデッキインスタンス
    deck = PlayerDeckManager::getInstance();
    
    //手札をリロード
    deck->reload2HandsCards();
    
    //手札を取得(ここでリテインするもんなの？)
    deck_cards = deck->getDeck();
    deck_cards->retain();
    hand_cards = deck->getHandsCards();
    hand_cards->retain();
    used_cards = deck->getUsedCards();
    used_cards->retain();
    
    
    //表示
    for (auto idx = 0; idx < hand_cards->count(); idx++) {
        auto card  = (Sprite*) hand_cards->getObjectAtIndex(idx);
        card->setPosition(Point(((visibleSize.width / HANDS_DECK) * idx) + (card->getContentSize().width / 2) + 3 , 55 + origin.y));
        auto tag = 1000 + idx;
        card->setTag(tag);
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
    
    //計算する
    if(condition->isCalcing()){
        auto magicManager = MagicManager::getInstance();
        auto magic = magicManager->getMagicByHandCards(*hand_cards);
        auto opp_magic = magicManager->getById(43);
        
        CCLOG("my_skill_name:%s", magic->getName().c_str());
        CCLOG("opp_skill_name:%s", opp_magic->getName().c_str());
        
        //ルーム取得
        auto roomManager = RoomManager::getInstance();
        auto room = roomManager->getBattlingRoom();
        
        battleProcessor = BattleProcessor::getInstance();
        battleProcessor->setMyMagic(magic);
        battleProcessor->setOppMagic(opp_magic);
        battleProcessor->setNowRoom(room);
        battleProcessor->execute();
        
        condition->onActionStart();
        
        auto my_result = battleProcessor->getMyResult();
        auto opp_result = battleProcessor->getOppResult();
    
    }
    
    //スタート処理
    if(condition->isActionStart()){
        //処理をIdleに戻す
        condition->setCondition(IS_EXECUTE_BATTLE);
        CCLOG("スタート処理");
        
        //透過度変える
        //auto feed_in = FadeTo::create(0.5f, 150);
        auto feed_in = CallFunc::create([this]{
            auto background = dynamic_cast<ImageView*>(widget->getChildByName("BackGround"));
            background->runAction(FadeTo::create(1.0f, 150));
        });
        auto delay = DelayTime::create(1.0f);
        //スタートアニメーション(アニメーションいらない？)
        auto battlestart = CallFunc::create([]{
            ActionManagerEx::getInstance()->playActionByName("BattleSceneLayout.json","BattleStart");
        });
        //次の処理へ
        auto nextCahin = CallFunc::create([this]{
            condition->onMyUseCard();
        });
        
        widget->runAction(Sequence::create(feed_in,delay,nextCahin, NULL));
    }
    
    //自分の攻撃(カード削除)
    if(condition->isMyUseCard()){
        //処理をIdleに戻す
        condition->setCondition(IS_EXECUTE_BATTLE);
        CCLOG("自分のカード削除");
        
        for (auto idx = 0; idx < hand_cards->count(); idx++) {
            auto card  = (PlayerCard*) hand_cards->getObjectAtIndex(idx);
            if(card->getSelected()){
                auto tag = 1000 + idx;
                auto delete_card = (PlayerCard*) this->getChildByTag(tag);
                auto move = MoveTo::create(0.3, Vec2(delete_card->getPositionX(), delete_card->getPositionY() + 30));
                auto fadeto = FadeTo::create(0.3f, 0);
                auto spawn = Spawn::create(move,fadeto, NULL);
                auto remove = RemoveSelf::create(true);
                auto removeArray = CallFunc::create([this, card]{
                    deck->usedCard(card);
                });
                
                //次の処理へ
                auto nextCahin = CallFunc::create([this]{
                    condition->onMyMoveCard();
                });
                delete_card->runAction(Sequence::create(spawn,remove,removeArray,nextCahin, NULL));
            }
        }
        
        //CCLOG("count:%zd", hand_cards->count());
    }
    
    //カードの場所変更
    if(condition->isMyMoveCard()){
        //処理をIdleに戻す
        condition->setCondition(IS_EXECUTE_BATTLE);
        CCLOG("自分のカードの移動");
        
        CCLOG("カード枚数:%zd", hand_cards->count());
        
        //足りないカードを補充
        deck->reload2HandsCards();
        //Indexの降り直し
        for (auto idx = 0; idx < hand_cards->count(); idx++) {
            auto move_card = (PlayerCard*) hand_cards->getObjectAtIndex(idx);
            auto old_tag = 1000 + move_card->getIndex();
            auto card = (PlayerCard*) this->getChildByTag(old_tag);
            //タグ貼り直し
            auto tag = 1000 + idx;
            move_card->setTag(tag);
            
            if(card){
                //Indexを変更
                move_card->setIndex(idx);
                //移動するよ
                auto move_pos = Vec2(((visibleSize.width / HANDS_DECK) * idx) + (card->getContentSize().width / 2) + 3 , 55 + origin.y);
                auto move = MoveTo::create(0.2f, move_pos);
                card->runAction(Sequence::create(move, NULL));
            }else{
                auto move_pos = Vec2(((visibleSize.width / HANDS_DECK) * idx) + (move_card->getContentSize().width / 2) + 3 , 55 + origin.y);
                move_card->setPosition(move_pos);
                move_card->setOpacity(0);
                addChild(move_card, kBattleScenePriorty::Cards);
                
                auto delay = DelayTime::create(0.2f);
                auto feed_in = FadeTo::create(0.2f, 255);
                //次の処理へ
                auto nextCahin = CallFunc::create([this]{
                    condition->onMyAttack();
                });
                move_card->runAction(Sequence::create(delay, feed_in, nextCahin, NULL));
                
            }
            
                
            //CCLOG("種類:%d", move_card->getIndex());
            //CCLOG("タグ:%d", move_card->getIndex());
            
        }
    }
    
    //攻撃魔法発動
    if(condition->isMyAttack()){
        //処理をIdleに戻す
        condition->setCondition(IS_EXECUTE_BATTLE);
        CCLOG("自分の攻撃");
        
        auto delay = DelayTime::create(1.0f);
        //魔法名
        auto magic_name = CallFunc::create([this]{
            auto name = dynamic_cast<Text*>(widget->getChildByName("MagicName"));
            auto my_magic = battleProcessor->getMyMagic();
            name->setString(my_magic->getName());
            name->runAction(FadeTo::create(0.5f, 255));
        });
        
        //攻撃エフェクト
        auto myAttack = CallFunc::create([this](){
            ParticleSystemQuad* particle = ParticleSystemQuad::create("MagicPlist/1295.plist");
            particle->setPosition(Point(250,240));
            this->addChild(particle,5);
        });
        
        //次の処理へ
        auto nextCahin = CallFunc::create([this]{
            condition->onMyMagicGaugeChange();
        });
        
        widget->runAction(Sequence::create(magic_name,delay,myAttack,delay,nextCahin, NULL));
    }
    if(condition->isOppAttack()){
        //処理をIdleに戻す
        condition->setCondition(IS_EXECUTE_BATTLE);
        CCLOG("敵の攻撃");
        
        auto delay = DelayTime::create(1.0f);
        //魔法名
        auto magic_name = CallFunc::create([this]{
            auto name = dynamic_cast<Text*>(widget->getChildByName("MagicName"));
            auto op_magic = battleProcessor->getOppMagic();
            name->setString(op_magic->getName());
            name->runAction(FadeTo::create(0.5f, 255));
        });
        
        //攻撃エフェクト
        auto opAttack = CallFunc::create([this](){
            ParticleSystemQuad* particle = ParticleSystemQuad::create("MagicPlist/1295.plist");
            particle->setPosition(Point(70,240));
            this->addChild(particle,5);
        });
        
        //次の処理へ
        auto nextCahin = CallFunc::create([this]{
            condition->onOppMagicGaugeChange();
        });
        
        widget->runAction(Sequence::create(magic_name,delay,opAttack,delay,nextCahin, NULL));
        
    }
    
    //ゲージ変動
    if(condition->isMyMagicGaugeChange()){
        auto loadingBar = dynamic_cast<LoadingBar*>(widget->getChildByName("HPGaugeRight"));
        auto pers = loadingBar->getPercent();
        auto oppresut = battleProcessor->getOppResult();
        auto oppgauge_pers = (float)oppresut.hp / MAX_HP * 100;
        
        if(pers && pers > oppgauge_pers){
            loadingBar->setPercent(pers - 1);
        }else{
            condition->onOppAttack();
            CCLOG("自分の攻撃のゲージ減らす");
        }
    }
    if(condition->isOppMagicGaugeChange()){
        auto loadingBar = dynamic_cast<LoadingBar*>(widget->getChildByName("HPGaugeLeft"));
        auto pers = loadingBar->getPercent();
        auto myresut = battleProcessor->getMyResult();
        auto mygauge_pers = (float)myresut.hp / MAX_HP * 100;
        
        if(pers && pers > mygauge_pers){
            loadingBar->setPercent(pers - 1);
        }else{
            condition->onBattleEnd();
            CCLOG("敵の攻撃のゲージ減らす");
        }
    }
    
    //バトル終了
    if(condition->isBattleEnd()){
        //処理をIdleに戻す
        condition->delCondition(IS_EXECUTE_BATTLE);
        CCLOG("終了処理");
        
        //ルーム取得
        auto room = RoomManager::getInstance()->getBattlingRoom();
        auto turn_count = (ImageView*)widget->getChildByName("TurnCount");
        auto turn_label = (TextAtlas*)turn_count->getChildByName("TurnCountLabel");
        turn_label->setString(std::to_string(room->getTurn()));
        
        //透過度変える
        auto background = dynamic_cast<ImageView*>(widget->getChildByName("BackGround"));
        background->runAction(FadeTo::create(1.0f, 255));
        auto disabelLayer = (disableTouchLayer*) getChildByTag(1);
        disabelLayer->removeFromParentAndCleanup(true);
    }

}

//シーンの切り替え
void BattleScene::complted(float delta)
{
    //Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StoryModeScene::createScene()));
}
