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
    
    //状態変化
    void onExecuteBattle();
    void onCalcing(){ this->addCondition(IS_CALCING);}
    
    //バトル実行
    void executeBattle();
    
};

#endif /* defined(__Grimore__BattleSceneCondition__) */
