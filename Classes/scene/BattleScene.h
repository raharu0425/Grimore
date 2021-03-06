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
#include <ui/CocosGUI.h>
#include "cocos2d.h"

#include "../Config.h"

#include "../component/PlayerDeckManager.h"
#include "../component/data/MagicManager.h"
#include "../component/data/RoomManager.h"
#include "../component/BattleProcessor.h"
#include "../condtion/BattleSceneCondition.h"
#include "../disableTouchLayer.h"


class BattleScene : public cocos2d::Layer,
                    public BattleSceneConditionDelegate
{
private:
    virtual ~BattleScene();
    BattleScene();
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(BattleScene);
    
    //ConditionDelegate
    BattleSceneCondition *condition;
    
    cocos2d::ui::Widget *widget;
    
    //Properties
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    cocos2d::Sprite *background;
    PlayerDeckManager* deck;
    cocos2d::__Array* hand_cards;
    cocos2d::__Array* used_cards;
    cocos2d::__Array* deck_cards;
    cocos2d::ui::Button* button;
    
    CC_SYNTHESIZE(bool, _is_selected_card, SeletedCard);
    //CC_SYNTHESIZE(int , _battle_boss_id, BattleBossId);
    
    //フレーム処理
    void update(float delta);
    void battleUpdate(float delta);
    
    //Debug
    void complted(float delta);
    
    void actionStartDone(Ref* sender);
    
    BattleProcessor* battleProcessor;
    
    //バトル結果
    BattleResult result;
};

#endif /* defined(__Grimore__BattleScene__) */
