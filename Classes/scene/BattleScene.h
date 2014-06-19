//
//  BattleScene.h
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#ifndef __Grimore__BattleScene__
#define __Grimore__BattleScene__

#include <iostream>
#include "cocos2d.h"

#include "../Config.h"

#include "../component/PlayerDeckManager.h"

class BattleScene : public cocos2d::Layer
{
private:
    virtual ~BattleScene();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(BattleScene);
    
    //Properties
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    cocos2d::Sprite *background;
    PlayerDeckManager* deck;
    
    
    //Debug
    void complted(float delta);
};

#endif /* defined(__Grimore__BattleScene__) */
