//
//  MagicManager.cpp
//  Grimore
//
//  Created by raharu on 2014/06/27.
//
//

#include "MagicManager.h"
#include "../PlayerCard.h"

MagicManager* MagicManager::_instance = nullptr;

MagicManager::MagicManager()
{
    setTableName("data_magic");
}

MagicManager::~MagicManager()
{
}

MagicManager* MagicManager::getInstance()
{
    if (!_instance) {
        _instance = new MagicManager;
    }
    return _instance;
}

//取得
Magic* MagicManager::getById(int id)
{
    std::string sql = "SELECT * FROM " + getTableName() + " WHERE id = ?";
    const char *pzTest;
    sqlite3_prepare_v2(_db, sql.c_str(), strlen(sql.c_str()), &_stmt, &pzTest);
    
    sqlite3_bind_int(_stmt, 1, id);
    sqlite3_step(_stmt);
    
    auto magic = Magic::getInstance();
    
    if(sqlite3_data_count(_stmt)){
        magic->setId(sqlite3_column_int(_stmt, 0));
        magic->setRank(sqlite3_column_int(_stmt, 1));
        magic->setName((char*)sqlite3_column_text(_stmt, 2));
        magic->setParamAttack(sqlite3_column_int(_stmt, 3));
        magic->setParamCure(sqlite3_column_int(_stmt, 4));
        magic->setParamStan(sqlite3_column_int(_stmt, 5));
    }
    
    sqlite3_reset(_stmt);
    sqlite3_clear_bindings(_stmt);
    sqlite3_finalize(_stmt);
    
    return magic;
}

//デッキから魔法を取得
Magic* MagicManager::getMagicByHandCards(cocos2d::__Array &handcards)
{
    int id = 0;
    for (auto idx = 0; idx < handcards.count(); idx++) {
        auto card  = (PlayerCard*) handcards.getObjectAtIndex(idx);
        if(card->getSelected()){
            id += card->getIdentifer();
        }
    }
    
    return getById(id);
}
