//
//  BattleProcessor.h
//  Grimore
//
//  Created by raharu on 2014/06/30.
//
//

#ifndef __Grimore__BattleProcessor__
#define __Grimore__BattleProcessor__

#include <iostream>
#include "cocos2d.h"

#include "Magic.h"

USING_NS_CC;

//結果構造
struct BattleResult{
    int my_damage = 0;
    int opp_damage = 0;
    bool is_my_die = false;
    bool is_opp_die = false;
    bool is_win = false;
};

//本体
class BattleProcessor : public Ref
{
private:
    BattleResult result;
    BattleProcessor();
    virtual ~BattleProcessor();
public:
    //Method
    static BattleProcessor* getInstance();
    bool init();
    
    // 必要なパラメータ
    CC_SYNTHESIZE(Magic*, _my_magic , MyMagic);
    CC_SYNTHESIZE(Magic*, _opp_magic , OppMagic);
    CC_SYNTHESIZE(int, _turn, Turn);
    
    //バトル実行
    void execute();
    
    //値の取得
    BattleResult getResult();
    
};

#endif /* defined(__Grimore__BattleProcessor__) */
