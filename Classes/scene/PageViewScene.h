//
//  PageViewScene.h
//  Grimore
//
//  Created by raharu on 2014/07/01.
//
//

#ifndef __Grimore__PageViewScene__
#define __Grimore__PageViewScene__

#include <iostream>
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include "../component/data/BossManager.h"
#include "../component/SqliteManager.h"

class PageViewScene : public cocos2d::Layer
{
    public :
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PageViewScene);
    
    SqliteManager* sqlite;
    void pageviewCallBack(cocos2d::Ref * psender, cocos2d::ui::PageViewEventType type);
    void touchEvent(cocos2d::Ref * pSender, cocos2d::ui::TouchEventType type);
};


#endif /* defined(__Grimore__PageViewScene__) */
