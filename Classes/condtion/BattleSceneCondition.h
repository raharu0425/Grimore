//
//  BattleSceneCondition.h
//  Grimore
//
//  Created by raharu on 2014/06/23.
//
//

#ifndef __Grimore__BattleSceneCondition__
#define __Grimore__BattleSceneCondition__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

#define IS_NONE 0
#define IS_EXECUTE_BATTLE 1
#define IS_CALCING 2
#define IS_ACTION_START 4
#define IS_MYUSECARD 8
#define IS_MYATTACK 16
#define IS_MYMAGIC_GAUGE_CHANGE 32
#define IS_BATTLE_END 64
#define IS_MYMOVECARD 128
#define IS_OPPATTACK 256
#define IS_OPPMAGIC_GAUGE_CHANGE 512
#define IS_FINISH 1024

//Delegateクラス
class BattleSceneConditionDelegate
{
public:
};

//mainクラス
class BattleSceneCondition : public cocos2d::Ref
{
    //クライアント側
    BattleSceneConditionDelegate* delegate;
    BattleSceneCondition();
    virtual ~BattleSceneCondition();
    
public:
    //delegate
    void setDelegate(BattleSceneConditionDelegate* delegate);
    static BattleSceneCondition* getInstance();
    
    CC_SYNTHESIZE(int, _condition, Condition);
    CC_SYNTHESIZE(bool, _lock, Lock);
    void addCondition(int param);
    void delCondition(int param);
    
    //状態判定
    bool isExecuteBattle(){ return this->getCondition() & IS_EXECUTE_BATTLE;}
    bool isCalcing(){ return this->getCondition() & IS_CALCING;}
    bool isActionStart(){ return this->getCondition() & IS_ACTION_START; }
    bool isMyUseCard(){ return this->getCondition() & IS_MYUSECARD; }
    bool isMyAttack(){ return this->getCondition() & IS_MYATTACK; }
    bool isMyMagicGaugeChange(){ return this->getCondition() & IS_MYMAGIC_GAUGE_CHANGE; }
    bool isMyMoveCard(){ return this->getCondition() & IS_MYMOVECARD; }
    bool isOppAttack(){ return this->getCondition() & IS_OPPATTACK; }
    bool isOppMagicGaugeChange(){ return this->getCondition() & IS_OPPMAGIC_GAUGE_CHANGE; }
    bool isBattleEnd(){ return this->getCondition() & IS_BATTLE_END; }
    bool isFinish(){ return this->getCondition() & IS_FINISH; }
    
    //状態変化
    void onExecuteBattle();
    void onCalcing(){ this->addCondition(IS_CALCING);}
    void onActionStart(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_ACTION_START);
    }
    void onMyUseCard(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_MYUSECARD);
    }
    void onMyAttack(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_MYATTACK);
    }
    void onMyMagicGaugeChange(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_MYMAGIC_GAUGE_CHANGE);
    }
    void onMyMoveCard(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_MYMOVECARD);
    }
    void onOppAttack(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_OPPATTACK);
    }
    void onOppMagicGaugeChange(){
        this->setCondition(IS_EXECUTE_BATTLE);
        this->addCondition(IS_OPPMAGIC_GAUGE_CHANGE);
    }
    void onFinish(){ this->setCondition(IS_FINISH); }

    void onBattleEnd(){ this->setCondition(IS_BATTLE_END); }
    
};

#endif /* defined(__Grimore__BattleSceneCondition__) */
