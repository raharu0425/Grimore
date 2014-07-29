//
//  StoryModeScene.h
//  Grimore
//
//  Created by raharu on 2014/07/01.
//
//

#ifndef __Grimore__StoryModeScene__
#define __Grimore__StoryModeScene__

#include <iostream>
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include "../component/data/BossManager.h"
#include "../component/SqliteManager.h"

class StoryModeScene : public cocos2d::Layer
{
public :
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StoryModeScene);

    //ページャーのコールバック（実際には使ってない）
    void pageviewCallBack(cocos2d::Ref * psender, cocos2d::ui::PageViewEventType type);

};


#endif /* defined(__Grimore__StoryModeScene__) */
