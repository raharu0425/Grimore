//
//  BattleDoScene.cpp
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#include "BattleDoScene.h"
#include "BattleScene.h"

USING_NS_CC;

Scene* BattleDoScene::createScene(int boss_id)
{
    auto scene = Scene::create();
    auto layer = BattleDoScene::create();
    
    //CCLOG("input_boss_id:%d", boss_id);
    layer->_battle_boss_id = boss_id;
    
    scene->addChild(layer);
    return scene;
}

//コンストラクタ
BattleDoScene::BattleDoScene(){
}

//デストラクタ
BattleDoScene::~BattleDoScene()
{
    CCLOG("DeleteBattleDoScene");
}

// on "init" you need to initialize your instance
bool BattleDoScene::init()
{
    //初期化
    if ( !Layer::init() ) return false;
    
    //状態管理の初期化
    condition = BattleDoSceneCondition::getInstance();
    
    //Sqlite
    sqlite = SqliteManager::getInstance();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //NowLoading
    auto sp_nowloading = Sprite::create("BattleSceneLayout/layout/NowLoadingWhite.png");
    sp_nowloading->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    sp_nowloading->setPosition(Point(visibleSize.width, 20.0f));
    this->addChild(sp_nowloading);
    
    //基本フレーム処理
    this->scheduleUpdate();
    
    return true;
    
}

//シーン描画時
void BattleDoScene::onEnter()
{
    Layer::onEnter();
    //CCLOG("output_boss_id:%d", this->_battle_boss_id);
    condition->onStart();
    
}

//基本フレーム処理
void BattleDoScene::update(float delta)
{
    //Error
    CCASSERT(!condition->isError(), condition->getErrorMessage().c_str());
    
    //boss_idが取得できたらスタート
    if(condition->isStart()){
        CCLOG("output_boss_id:%d", this->_battle_boss_id);
        condition->onCreateRoom();
    }
    
    //ルームデータの作成
    if(condition->isCreateRoom()){
        auto bossManager = BossManager::getInstance();
        auto roomManager = RoomManager::getInstance();
        
        //現在のバトルルームを取得
        auto room = roomManager->getBattlingRoom();
        if(!room->isBattling()){
            auto boss = bossManager->getById(this->_battle_boss_id);
            roomManager->createRoom(boss);
        }
        condition->onComplete();
    }
}