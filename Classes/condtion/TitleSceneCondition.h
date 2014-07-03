//
//  TitleSceneCondition.h
//  Grimore
//
//  Created by raharu on 2014/06/26.
//
//

#ifndef __Grimore__TitleSceneCondition__
#define __Grimore__TitleSceneCondition__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

#define IS_NONE 0
#define IS_START 1
#define IS_COMPLETE 2
#define IS_ERROR 4
#define IS_CREATE_SKILL_DATA 8
#define IS_CREATE_BOSS_DATA 16
#define IS_CREATE_STAGE_DATA 32
#define IS_CREATE_ELEMENT_DATA 64

//Delegateクラス
class TitleSceneConditionDelegate
{
public:
};

//mainクラス
class TitleSceneCondition : public cocos2d::Ref
{
    //クライアント側
    TitleSceneConditionDelegate* delegate;
    TitleSceneCondition();
    virtual ~TitleSceneCondition();
    
    //エラーメッセージ
    std::string _error_msg;
public:
    //delegate
    void setDelegate(TitleSceneConditionDelegate* delegate);
    static TitleSceneCondition* getInstance();
    
    CC_SYNTHESIZE(int, _condition, Condition);
    CC_SYNTHESIZE(bool, _lock, Lock);
    void addCondition(int param);
    void delCondition(int param);
    
    //メッセージの取得
    std::string getErrorMessage();
    
    //状態判定
    bool isError(){ return this->getCondition() == IS_ERROR;}
    bool isStart(){ return this->getCondition() & IS_START;}
    bool isCreateSkillData(){ return this->getCondition() & IS_CREATE_SKILL_DATA;}
    bool isCreateBossData(){ return this->getCondition() & IS_CREATE_BOSS_DATA;}
    bool isCreateStageData(){ return this->getCondition() & IS_CREATE_STAGE_DATA;}
    bool isCreateElementData(){ return this->getCondition() & IS_CREATE_ELEMENT_DATA;}
    bool isComplete(){ return this->getCondition() & IS_COMPLETE; }
    
    //状態変化
    void onError(std::string msg);
    void onStart();
    void onCreateSkillData(){ this->setCondition(IS_CREATE_SKILL_DATA); }
    void onCreateBossData(){ this->setCondition(IS_CREATE_BOSS_DATA); }
    void onCreateStageData(){ this->setCondition(IS_CREATE_STAGE_DATA); }
    void onCreateElementData(){ this->setCondition(IS_CREATE_ELEMENT_DATA); }
    void onComplete();
};

#endif /* defined(__Grimore__TitleSceneCondition__) */
