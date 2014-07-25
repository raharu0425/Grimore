//
//  MagicManager.h
//  Grimore
//
//  Created by raharu on 2014/06/27.
//
//

#ifndef __Grimore__MagicManager__
#define __Grimore__MagicManager__

#include <iostream>
#include "../SqliteManager.h"
#include "../Magic.h"

class MagicManager : public SqliteManager
{
private:
    static MagicManager* _instance;
public:
    static MagicManager* getInstance();
    MagicManager();
    virtual ~MagicManager();
    
    //テーブルネーム
    CC_SYNTHESIZE(std::string, _table_name, TableName);
    
    //取得
    Magic* getById(int id);
    
    //デッキからスキルを選定する
    Magic* getMagicByHandCards(cocos2d::__Array &handcards);
    
    //コールバック
    static int _callBack(void *para, int num_col, char ** col_value, char ** col_name);
    
};

#endif /* defined(__Grimore__MagicManager__) */
