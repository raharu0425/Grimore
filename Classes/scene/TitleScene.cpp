//
//  TitleScene.cpp
//  Grimore
//
//  Created by raharu on 2014/06/26.
//
//

#include "TitleScene.h"
#include "BattleScene.h"
#include "StoryModeScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //初期化
    if ( !Layer::init() ) return false;
    
    //状態管理の初期化
    condition = TitleSceneCondition::getInstance();
    
    //Sqlite
    sqlite = SqliteManager::getInstance();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //NowLoading
    auto sp_nowloading = Sprite::create("BattleSceneLayout/layout/NowLoadingWhite.png");
    sp_nowloading->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    sp_nowloading->setPosition(Point(visibleSize.width, 20.0f));
    this->addChild(sp_nowloading);
    
    //UserDefault
    userDefault = UserDefault::getInstance();
    
    auto db_version = userDefault->getIntegerForKey("database_version", 0);
    
#if COCOS2D_DEBUG
    CCLOG("old_version:%d", db_version);
    CCLOG("new_version:%d", APP_VERSION);
#endif
    
    //バージョン判定の終了
    if(db_version == APP_VERSION){
        scheduleOnce(schedule_selector(TitleScene::complted), 2.0f);
    }else{
        //ロードの読み込み
        condition->onStart();
    }
    
    //基本フレーム処理
    this->scheduleUpdate();
    
    return true;
}

//基本フレーム処理
void TitleScene::update(float delta)
{
    //Error
    CCASSERT(!condition->isError(), condition->getErrorMessage().c_str());
    
    //DBの存在チェックをおこなってから開始
    if(condition->isStart()){
        /*
        std::string dbPath = FileUtils::getInstance()->getWritablePath() + "Grimore.db";
        CCLOG("%s", dbPath.c_str());
        sqlite->setDB(dbPath.c_str());
         */
        condition->onCreateSkillData();
    }
    
    //スキルテーブルの作成
    if(condition->isCreateSkillData()){
        createData("data_magic");
        condition->onCreateBossData();
    }
    
    //ボスデータテーブル作成
    if(condition->isCreateBossData()){
        createData("data_boss");
        condition->onCreateStageData();
    }
    
    //ステージデータテーブル作成
    if(condition->isCreateStageData()){
        createData("data_stage");
        condition->onCreateElementData();
    }
    
    //属性データテーブル作成
    if(condition->isCreateElementData()){
        createData("data_element");
        condition->onComplete();
    }
}

//データの作成
void TitleScene::createData(const char* data_name)
{
    auto sql_path = StringUtils::format("sql/%s.sql", data_name);
    auto json_path = StringUtils::format("data/%s.json", data_name);
    
    //テーブルが存在する場合は削除
    if(sqlite->tableIsExist(data_name)){
        sqlite->dropTable(data_name);
    }
    
    //作成
    if(!sqlite->tableIsExist(data_name)){
        std::string query = FileUtils::getInstance()->getStringFromFile(sql_path);
        sqlite->executeQueryByString(query);
    }
    
    // レスポンスデータ
    std::string buffer = FileUtils::getInstance()->getStringFromFile(json_path);
    
    //データの挿入
    if(buffer.size() && sqlite->tableIsExist(data_name)){
        char * json = (char *) malloc(buffer.size() + 1);
        std::string s2(buffer.begin(), buffer.end());
        strcpy(json, s2.c_str());
        picojson::value pico_value;
        std::string error_msg;
        picojson::parse(pico_value, json, json + strlen(json), &error_msg);
    
        picojson::array& records = pico_value.get<picojson::array>();
    
        // arrayの中の値をループで取得
        for (picojson::array::iterator i = records.begin(); i != records.end(); i++) {
            picojson::object& record = i->get<picojson::object>();
            sqlite->addPicoJsonObject(data_name, record);
        }
    }
}


//シーンの切り替え
void TitleScene::complted(float delta)
{
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StoryModeScene::createScene()));
}