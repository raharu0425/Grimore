//
//  BattleDoScene.h
//  Grimore
//
//  Created by raharu on 2014/07/08.
//
//

#ifndef __Grimore__BattleDoScene__
#define __Grimore__BattleDoScene__

#include <iostream>
#include "cocos2d.h"

#include "../condtion/BattleDoSceneCondition.h"
#include "../component/SqliteManager.h"
#include "../component/data/BossManager.h"
#include "../component/data/RoomManager.h"


class BattleDoScene : public cocos2d::Layer
{
private:
    BattleDoScene();
    virtual ~BattleDoScene();
    int _battle_boss_id;
public :
    static cocos2d::Scene* createScene(int boss_id);
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(BattleDoScene);
    
    BattleDoSceneCondition* condition;
    SqliteManager* sqlite;
    
    //Properties
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    
    //Room* createRoom(Boss* boss);
    
    void update(float delta);
};

#endif /* defined(__Grimore__BattleDoScene__) */
