//
//  SqliteManager.cpp
//  Grimore
//
//  Created by raharu on 2014/06/26.
//
//

#include "SqliteManager.h"

SqliteManager* SqliteManager::_instance = nullptr;

SqliteManager::SqliteManager():
_db(nullptr),
_result(0),
_error_msg(NULL)
{
    std::string dbPath = cocos2d::FileUtils::getInstance()->getWritablePath() + "Grimore.db";
    this->setDB(dbPath.c_str());
}

SqliteManager::~SqliteManager()
{
    if (_db){
        sqlite3_close(_db);
    }
}

SqliteManager* SqliteManager::getInstance()
{
    if (!_instance) {
        _instance = new SqliteManager;
    }
    return _instance;
}

//DBのセット
bool SqliteManager::setDB(const char *db_path)
{
    _result = sqlite3_open(db_path, &_db);
    if (_result != SQLITE_OK)
    {
        CCLOG("データベース%sを初期化できませんでした。エラー：%s", db_path, _error_msg);
        return false;
    }
    return true;
}

//クエリ実行
int SqliteManager::executeQuery(const std::string &query)
{
    return sqlite3_exec(_db, query.c_str(), NULL, NULL, &_error_msg);
}

int SqliteManager::executeQuery(const std::string &query, sqlite3_callback &xCallback)
{
    return sqlite3_exec(_db, query.c_str(), xCallback, NULL, &_error_msg);
}

//エラーハンドリング月
void SqliteManager::executeQueryByString(const std::string &query)
{
    _result = executeQuery(query);
    if (_result != SQLITE_OK)
    {
        CCLOG("エラー%d：%s", _result, _error_msg);
    }
}

//テーブルの存在チェック
bool SqliteManager::tableIsExist(const std::string &name)
{
    if (_db != NULL)
    {
        bool tableExist = false;
        _query_string = "SELECT name FROM sqlite_master WHERE type = 'table' AND name = '"+ name +"'";
        _result = sqlite3_exec(_db, _query_string.c_str(), _isExist, &tableExist, &_error_msg);
        //CCLOG("%s is %i", name.c_str(), tableExist);
        return tableExist;
    }
    
    return false;
}

//テーブルの削除
void SqliteManager::dropTable(const std::string &name)
{
    std::string sql = "DROP TABLE " + name;
    _result = executeQuery(sql);
    if (_result != SQLITE_OK)
    {
        CCLOG("エラー%d：%s", _result, _error_msg);
    }
}

//追加
void SqliteManager::addPicoJsonObject(const std::string &table_name, picojson::object &object)
{
    std::string cols = "";
    std::string values = "";
    
    picojson::object::iterator it = object.begin();
    while (it != object.end()) {
        cols.append('\''+(*it).first+'\'');
        cols.append(",");
        
        std::string value;
        if(object[it->first].is<double>()){
            auto val = cocos2d::Value(object[it->first].get<double>());
            value = std::to_string(val.asInt());
        }else if(object[it->first].is<std::string>()){
            value = object[it->first].get<std::string>();
        }
        
        values.append('\''+value+'\'');
        values.append(",");
        it++;
    }
    
    std::string create_at = "created_at";
    std::string updated_at = "updated_at";
    std::string now_time = "datetime('now', 'localtime')";
    
    //作成時間
    cols.append('\''+create_at+'\'');
    cols.append(",");
    values.append(now_time);
    values.append(",");
    
    //更新時間
    cols.append('\''+create_at+'\'');
    cols.append(",");
    values.append(now_time);
    values.append(",");
    
    cols.pop_back();
    values.pop_back();
    
    std::string sql = "INSERT INTO "+ table_name +" (" + cols + ") VALUES (" + values + ")";
    CCLOG("sql:%s", sql.c_str());
    
    _result = this->executeQuery(sql);
    if (_result != SQLITE_OK)
    {
        CCLOG("エラー%d：%s", _result, _error_msg);
    }
    
}

//更新
void SqliteManager::savePicoJsonObject(const std::string &table_name, picojson::object &object)
{
    std::string values = "";
    std::string update_id = "";
    
    picojson::object::iterator it = object.begin();
    while (it != object.end()) {
        values.append('\''+(*it).first+'\'');
        values.append("=");
        
        
        std::string value;
        if(object[it->first].is<double>()){
            auto val = cocos2d::Value(object[it->first].get<double>());
            value = std::to_string(val.asInt());
        }else if(object[it->first].is<std::string>()){
            value = object[it->first].get<std::string>();
        }
        
        if ((*it).first == "id") {
            update_id = value;
        }
        
        values.append('\''+value+'\'');
        values.append(",");
        it++;
    }
    std::string updated_at = "updated_at";
    std::string now_time = "datetime('now', 'localtime')";
    
    //更新時間
    values.append('\''+updated_at+'\'');
    values.append("=");
    values.append(now_time);
    
    std::string sql = "UPDATE "+ table_name +" SET " + values + " WHERE id = " + update_id;
    CCLOG("sql:%s", sql.c_str());
    
    _result = this->executeQuery(sql);
    if (_result != SQLITE_OK)
    {
        CCLOG("エラー%d：%s", _result, _error_msg);
    }
    
}




int SqliteManager::_isExist(void *para, int n_col, char ** col_value, char ** col_name)
{
    bool *isExist_ = (bool*)para;
    *isExist_ = (**col_value) != 0;
    return 0;
}

