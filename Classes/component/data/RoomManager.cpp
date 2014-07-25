//
//  RoomManager.cpp
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#include "RoomManager.h"

RoomManager* RoomManager::_instance = nullptr;

RoomManager::RoomManager()
{
    setTableName("room");
    setTableDetail("room_detail");
}

RoomManager::~RoomManager()
{
}

RoomManager* RoomManager::getInstance()
{
    if (!_instance) {
        _instance = new RoomManager;
    }
    return _instance;
}

//ルーム作成（初期作成execute）
void RoomManager::createRoom(Boss *boss)
{
    //ルーム
    picojson::object object;
    object.clear();
    
    object.insert(std::make_pair("condition", picojson::value((double)1)));
    object.insert(std::make_pair("boss_id", picojson::value((double)boss->getId())));
    object.insert(std::make_pair("stage_id", picojson::value((double)boss->getStageId())));
    object.insert(std::make_pair("my_name", picojson::value((std::string)"my_name")));
    object.insert(std::make_pair("opp_name", picojson::value((std::string)boss->getName())));
    
    this->addRoom(object);
    
    auto battling_room = this->getBattlingRoom();
    
    //ルーム詳細
    picojson::object object2;
    object2.clear();
    
    object2.insert(std::make_pair("room_id", picojson::value((double)battling_room->getId())));
    object2.insert(std::make_pair("turn", picojson::value((double)battling_room->getTurn())));
    object2.insert(std::make_pair("my_hp", picojson::value((double)MAX_HP)));
    object2.insert(std::make_pair("opp_hp", picojson::value((double)MAX_HP)));
    
    this->addRoomDetail(object2);
    
}

//ルーム追加
void RoomManager::addRoom(picojson::object& object)
{
    this->addPicoJsonObject(getTableName(), object);
}

//現在バトル中のレコード取得
Room* RoomManager::getBattlingRoom()
{
    std::string sql = "SELECT * FROM " + getTableName() + " WHERE condition = ?";
    const char *pzTest;
    sqlite3_prepare_v2(_db, sql.c_str(), strlen(sql.c_str()), &_stmt, &pzTest);
    
    sqlite3_bind_int(_stmt, 1, kBattleCondition::Battling);
    sqlite3_step(_stmt);
    
    auto embody = Room::getInstance();
    
    if(sqlite3_data_count(_stmt)){
        embody->setId(sqlite3_column_int(_stmt, 0));
        embody->setCondition(sqlite3_column_int(_stmt, 1));
        embody->setBossId(sqlite3_column_int(_stmt, 2));
        embody->setStageId(sqlite3_column_int(_stmt, 3));
        embody->setTurn(sqlite3_column_int(_stmt, 4));
        embody->setMyName((char*)sqlite3_column_text(_stmt, 5));
        embody->setOppName((char*)sqlite3_column_text(_stmt, 6));
    }
    
    sqlite3_reset(_stmt);
    sqlite3_clear_bindings(_stmt);
    sqlite3_finalize(_stmt);
    
    return embody;
}


//ルーム詳細追加
void RoomManager::addRoomDetail(picojson::object& object)
{
    this->addPicoJsonObject(getTableDetail(), object);
}
