//
//  TitleScene.h
//  Grimore
//
//  Created by raharu on 2014/06/26.
//
//

#ifndef __Grimore__TitleScene__
#define __Grimore__TitleScene__

#include <iostream>
#include "cocos2d.h"
#include "../Config.h"

#include "../condtion/TitleSceneCondition.h"

#include "../component/SqliteManager.h"

#include "../library/json/picojson.h"

class TitleScene : public cocos2d::Layer
{
public :
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TitleScene);
    
    //Properties
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    
    TitleSceneCondition* condition;
    SqliteManager* sqlite;
    UserDefault* userDefault;
    
    //基本フレーム処理
    void update(float delta);
    void complted(float delta);
    
    void createData(const char* data_name);
    
    void createSkillData();
    void createBossData();
    void createStageData();
    void createElementData();
};

#endif /* defined(__Grimore__TitleScene__) */
