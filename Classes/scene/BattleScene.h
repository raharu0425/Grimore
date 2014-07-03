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
#include "../component/BattleProcessor.h"
#include "../condtion/BattleSceneCondition.h"
#include "../disableTouchLayer.h"


class BattleScene : public cocos2d::Layer,
                    public BattleSceneConditionDelegate
{
private:
    virtual ~BattleScene();
    BattleScene();
    
    int _battle_boss_id;
public:
    static cocos2d::Scene* createScene(int boss_id);
    virtual bool init();
    virtual void onEnter();
    
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
    cocos2d::ui::Button* button;
    
    CC_SYNTHESIZE(bool, _is_selected_card, SeletedCard);
    //CC_SYNTHESIZE(int , _battle_boss_id, BattleBossId);
    
    //フレーム処理
    void update(float delta);
    void battleUpdate(float delta);
    
    //ボタンイベント
    virtual bool onTouchAttackButton(cocos2d::Ref* sender, cocos2d::ui::TouchEventType type);
    
    //Debug
    void complted(float delta);
    
    //バトル結果
    BattleResult result;
};

#endif /* defined(__Grimore__BattleScene__) */
