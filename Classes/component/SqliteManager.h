//
//  SqliteManager.h
//  Grimore
//
//  Created by raharu on 2014/06/26.
//
//

#ifndef __Grimore__SqliteManager__
#define __Grimore__SqliteManager__

#include <iostream>
#include "cocos2d.h"
#include "../library/sqlite/sqlite3.h"
#include "../library/json/picojson.h"

class SqliteManager
{
protected:
    static SqliteManager* _instance;
    sqlite3 * _db;
    sqlite3_stmt* _stmt;
    int _result;
    char* _error_msg;
    std::string _query_string;
    
    static int _isExist(void *para, int n_col, char ** col_value, char ** col_name);
    
public:
    SqliteManager();
    virtual ~SqliteManager();
    
    static SqliteManager* getInstance();
    bool setDB(const char* db_path);
    
    //Exists
    bool tableIsExist(const std::string &name);
    
    //クエリ実行
    int executeQuery(const std::string &query);
    int executeQuery(const std::string &query, sqlite3_callback &xCallback);
    void executeQueryByString(const std::string &query);
    
    //テーブル削除
    void dropTable(const std::string &name);
    
    //picojsonデータを追加
    void addPicoJsonObject(const std::string &table_name, picojson::object &values);
    
};


#endif /* defined(__Grimore__SqliteManager__) */
