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
#include "Room.h"

USING_NS_CC;

//結果構造
struct BattleResult{
    int hp = 0;
    int damage = 0;
    int cure = 0;
    bool is_die = false;
    bool is_stan = false;
    bool is_cure = false;
    bool is_finish = false;
    bool is_win = false;
    bool is_lose = false;
    bool is_draw = false;
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
    CC_SYNTHESIZE(Room*, _now_room, NowRoom);
    CC_SYNTHESIZE(int, _turn, Turn);
    CC_SYNTHESIZE(BattleResult, _my_result, MyResult);
    CC_SYNTHESIZE(BattleResult, _opp_result, OppResult);
    
    //バトル実行
    void execute();
    
    //攻撃実行
    void executeBattle(Magic* magic, bool is_my);
    
    //回復実行
    void executeCure(Magic* magic, bool is_my);
    
};

#endif /* defined(__Grimore__BattleProcessor__) */
