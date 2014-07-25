//
//  BossManager.h
//  Grimore
//
//  Created by raharu on 2014/06/30.
//
//

#ifndef __Grimore__BossManager__
#define __Grimore__BossManager__

#include <iostream>
#include "../SqliteManager.h"
#include "../Boss.h"

class BossManager : public SqliteManager
{
private:
    static BossManager* _instance;
public:
    static BossManager* getInstance();
    BossManager();
    virtual ~BossManager();
    
    //テーブルネーム
    CC_SYNTHESIZE(std::string, _table_name, TableName);
    
    //取得
    Boss* getById(int id);
    
    //全てのボスを取得
    std::vector<Boss*> getAllBoss();
    
    //コールバック
    static int _callBack(void *para, int num_col, char ** col_value, char ** col_name);
    
};

#endif /* defined(__Grimore__BossManager__) */
