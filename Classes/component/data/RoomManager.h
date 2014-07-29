//
//  RoomManager.h
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#ifndef __Grimore__RoomManager__
#define __Grimore__RoomManager__

#include <iostream>

#include "../SqliteManager.h"
#include "../Room.h"
#include "../Boss.h"
#include "../BattleProcessor.h"

class RoomManager : public SqliteManager
{
private:
    static RoomManager* _instance;
public:
    static RoomManager* getInstance();
    RoomManager();
    virtual ~RoomManager();
    
    //テーブルネーム
    CC_SYNTHESIZE(std::string, _table_name, TableName);
    CC_SYNTHESIZE(std::string, _table_detail, TableDetail);
    
    //ルーム作成(初期の事全部してくれる)
    void createRoom(Boss* boss);
    
    //ルーム追加
    void addRoom(picojson::object& object);
    //ルーム詳細追加
    void addRoomDetail(picojson::object& object);
    //ルームEmbody更新する
    void saveRoomByEmbody(Room* room);
    //ルームを更新する
    void saveRoom(picojson::object& object);
    
    //現在バトル中のレコードを取得
    Room* getBattlingRoom();
    
    //ルームから取得
    RoomDetail* getRoomDetail(Room* room, int turn_id);
    
    
    
    //コールバック
    static int _callBack(void *para, int num_col, char ** col_value, char ** col_name);
    
};


#endif /* defined(__Grimore__RoomManager__) */
