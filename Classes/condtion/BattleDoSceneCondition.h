//
//  BattleDoSceneCondition.h
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#ifndef __Grimore__BattleDoSceneCondition__
#define __Grimore__BattleDoSceneCondition__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

#define IS_NONE 0
#define IS_START 1
#define IS_COMPLETE 2
#define IS_ERROR 4
#define IS_CREATE_ROOM 8


//Delegateクラス
class BattleDoSceneConditionDelegate
{
public:
};

//mainクラス
class BattleDoSceneCondition : public cocos2d::Ref
{
    //クライアント側
    BattleDoSceneConditionDelegate* delegate;
    BattleDoSceneCondition();
    virtual ~BattleDoSceneCondition();
    
    //エラーメッセージ
    std::string _error_msg;
public:
    //delegate
    void setDelegate(BattleDoSceneConditionDelegate* delegate);
    static BattleDoSceneCondition* getInstance();
    
    CC_SYNTHESIZE(int, _condition, Condition);
    CC_SYNTHESIZE(bool, _lock, Lock);
    void addCondition(int param);
    void delCondition(int param);
    
    //メッセージの取得
    std::string getErrorMessage();
    
    //状態判定
    bool isError(){ return this->getCondition() == IS_ERROR;}
    bool isStart(){ return this->getCondition() & IS_START;}
    bool isComplete(){ return this->getCondition() & IS_COMPLETE; }
    bool isCreateRoom(){ return this->getCondition() & IS_CREATE_ROOM; }
    
    //状態変化
    void onError(std::string msg);
    void onStart();
    void onComplete();
    void onCreateRoom(){ this->setCondition(IS_CREATE_ROOM); }
};

#endif /* defined(__Grimore__BattleDoSceneCondition__) */
