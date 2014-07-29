//
//  BattleProcessor.cpp
//  Grimore
//
//  Created by raharu on 2014/06/30.
//
//

#include "BattleProcessor.h"
#include "Config.h"
#include "data/RoomManager.h"
#include "../library/json/picojson.h"

static BattleProcessor *s_Shared = nullptr;

BattleProcessor::BattleProcessor()
{
}

BattleProcessor::~BattleProcessor()
{
}

//getInstance
BattleProcessor* BattleProcessor::getInstance()
{
    s_Shared = new BattleProcessor();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }else{
        CC_SAFE_DELETE(s_Shared);
        return NULL;
    }
}

// init
bool BattleProcessor::init()
{
    return true;
}

//処理実行
void BattleProcessor::execute()
{
    srand((unsigned int)time(NULL));
    
    //自分の攻撃をする
    this->executeBattle(getMyMagic(), true);
    this->executeCure(getMyMagic(), true);
    
    //敵の攻撃をする
    this->executeBattle(getOppMagic(), false);
    this->executeCure(getOppMagic(), false);
    
    //ターンカウントをあげる
    auto room = getNowRoom();
    room->setTurn(room->getTurn() + 1);
    RoomManager::getInstance()->saveRoomByEmbody(room);
    
    //結果考慮
    auto my_result = getMyResult();
    auto opp_result = getOppResult();
    if(room->getTurn() >= MAX_TURN){
        my_result.is_finish = true;
        opp_result.is_finish = true;
        
        if(my_result.hp > opp_result.hp){
            my_result.is_win = true;
            opp_result.is_lose = true;
        }else{
            my_result.is_lose = true;
            opp_result.is_win = true;
        }
    }
    
    //どちらかが死んだ
    if(my_result.hp <= 0){
        my_result.is_finish = true;
        opp_result.is_finish = true;
        my_result.is_win = true;
        opp_result.is_lose = true;
    }else if(opp_result.hp <= 0){
        my_result.is_finish = true;
        opp_result.is_finish = true;
        my_result.is_lose = true;
        opp_result.is_win = true;
    }
    
    //終了フラグ立てる
    if(my_result.is_finish){
        room->setCondition(kBattleCondition::Finish);
        RoomManager::getInstance()->saveRoomByEmbody(room);
    }
    
    //結果を保存
    picojson::object object;
    object.clear();
    
    object.insert(std::make_pair("room_id", picojson::value((double)room->getId())));
    object.insert(std::make_pair("turn", picojson::value((double)room->getTurn())));
    object.insert(std::make_pair("my_hp", picojson::value((double)getMyResult().hp)));
    object.insert(std::make_pair("my_magic_id", picojson::value((double)getMyMagic()->getId())));
    object.insert(std::make_pair("opp_hp", picojson::value((double)getOppResult().hp)));
    object.insert(std::make_pair("opp_magic_id", picojson::value((double)getOppMagic()->getId())));
    
    RoomManager::getInstance()->addRoomDetail(object);
};


//攻撃実行
void BattleProcessor::executeBattle(Magic *magic, bool is_my)
{
    
    //現在のルームの詳細を取得する
    auto room = getNowRoom();
    auto room_detail = room->getDetail();
    
    BattleResult result;
    
    //自分の攻撃
    if(is_my){
        result.hp = room_detail->getOppHp();
    }else{
        result.hp = room_detail->getMyHp();
    }
    result.damage = magic->getParamAttack();
    result.hp = result.hp - magic->getParamAttack();
    
    //スタン判定
    auto rand_value = rand() % 100 + 1;
    if(rand_value <= magic->getParamStan()){
        result.is_stan = true;
    }
    
    if (is_my) {
        setOppResult(result);
    }else{
        setMyResult(result);
    }
    
}

//回復実行
void BattleProcessor::executeCure(Magic *magic, bool is_my)
{
    //自分の攻撃
    BattleResult result;
    if(is_my){
        result = getMyResult();
    }else{
        result = getOppResult();
    }
    
    //回復判定
    if(magic->getParamCure()){
        result.is_cure = true;
        result.cure = magic->getParamCure();
        result.hp += magic->getParamCure();
        if(result.hp > MAX_HP){
            result.hp = MAX_HP;
        }
    }
    
    if (is_my) {
        setMyResult(result);
    }else{
        setOppResult(result);
    }
    
}



