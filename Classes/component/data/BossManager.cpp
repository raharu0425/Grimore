//
//  BossManager.cpp
//  Grimore
//
//  Created by raharu on 2014/06/30.
//
//

#include "BossManager.h"


BossManager* BossManager::_instance = nullptr;

BossManager::BossManager()
{
    setTableName("data_boss");
}

BossManager::~BossManager()
{
}

BossManager* BossManager::getInstance()
{
    if (!_instance) {
        _instance = new BossManager;
    }
    return _instance;
}

//取得
Boss* BossManager::getById(int id)
{
    std::string sql = "SELECT * FROM " + getTableName() + " WHERE id = ?";
    const char *pzTest;
    sqlite3_prepare_v2(_db, sql.c_str(), strlen(sql.c_str()), &_stmt, &pzTest);
    
    sqlite3_bind_int(_stmt, 1, id);
    sqlite3_step(_stmt);
    
    auto embody = Boss::getInstance();
    
    if(sqlite3_data_count(_stmt)){
        embody->setId(sqlite3_column_int(_stmt, 0));
        embody->setName((char*)sqlite3_column_text(_stmt, 1));
        embody->setElementIdentifer(sqlite3_column_int(_stmt, 2));
        embody->setStageId(sqlite3_column_int(_stmt, 3));
        embody->setMessageStart((char*)sqlite3_column_text(_stmt, 4));
        embody->setMessageWin((char*)sqlite3_column_text(_stmt, 5));
        embody->setMessageLose((char*)sqlite3_column_text(_stmt, 6));
    }
    
    sqlite3_reset(_stmt);
    sqlite3_clear_bindings(_stmt);
    sqlite3_finalize(_stmt);
    
    return embody;
}


//ボスリストの取得
std::vector<Boss*> BossManager::getAllBoss()
{
    std::string sql = StringUtils::format("SELECT * FROM %s WHERE `active` = '1'", getTableName().c_str());
    const char *pzTest;
    sqlite3_prepare_v2(_db, sql.c_str(), (int)strlen(sql.c_str()), &_stmt, &pzTest);
    
    std::vector<Boss*> bosses;
    while (sqlite3_step(_stmt) == SQLITE_ROW) {
        auto embody = Boss::getInstance();
        embody->setId(sqlite3_column_int(_stmt, 0));
        embody->setName((char*)sqlite3_column_text(_stmt, 1));
        embody->setElementIdentifer(sqlite3_column_int(_stmt, 2));
        embody->setStageId(sqlite3_column_int(_stmt, 3));
        embody->setMessageStart((char*)sqlite3_column_text(_stmt, 4));
        embody->setMessageWin((char*)sqlite3_column_text(_stmt, 5));
        embody->setMessageLose((char*)sqlite3_column_text(_stmt, 6));
            
        bosses.push_back(embody);
    }
    
    sqlite3_reset(_stmt);
    sqlite3_clear_bindings(_stmt);
    sqlite3_finalize(_stmt);
    
    return bosses;
}
