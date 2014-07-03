//
//  PageViewScene.cpp
//  Grimore
//
//  Created by raharu on 2014/07/01.
//
//

#include "PageViewScene.h"
#include "BattleScene.h"

USING_NS_CC;
using namespace ui;

Scene* PageViewScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PageViewScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool PageViewScene::init()
{
    //初期化
    if ( !Layer::init() ) return false;
    
    //画面サイズを取得
    auto windowSize = Director::getInstance()->getWinSize();
    
    //PageViewを作成これにレイアウトを追加していく
    auto pageView = PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setSize(windowSize);
    
    //ボスマネージャーをインスタンス化
    auto bossManager = BossManager::getInstance();
    auto bosses = bossManager->getAllBoss();
    
    std::vector<Boss*>::iterator boss_itr = bosses.begin();
    
    
    //ここはあとでCocostudioで作り直す
    while (boss_itr != bosses.end()) {
        auto layout = Layout::create();
        auto boss = (Boss*) *boss_itr;
        
        CCLOG("boss_id:%d", boss->getId());
        CCLOG("boss_name:%s", boss->getName().c_str());
        
        layout->setSize(windowSize);
        //名前
        auto name = Text::create(boss->getName().c_str(), "Arial", 23);
        name->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2));
        layout->addChild(name);
        
        //メッセージ
        auto message = LabelTTF::create(boss->getMessageStart(), "Futura-Medium", 15);
        message->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2 - 50));
        message->setDimensions(Size(280, 60));
        message->setHorizontalAlignment(TextHAlignment::LEFT);
        message->setVerticalAlignment(TextVAlignment::TOP);
        layout->addChild(message);
        
        //バトル開始ボタン
        auto startButton = Button::create();
        startButton->setTouchEnabled(true);
        startButton->setAnchorPoint(Point(0.5, 1.0));
        startButton->loadTextures("BattleSceneLayout/layout/Attack_Button.png","","");
        startButton->setTitleText("バトルする");
        startButton->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2 - 100));
        startButton->setTag(boss->getId());
        startButton->addTouchEventListener(this, toucheventselector(PageViewScene::touchEvent));
        layout->addChild(startButton);
        
        
        //レイアウトをaddする
        pageView->addPage(layout);
        
        ++boss_itr;
    }
    
    //イベントリスナーを追加（using namespace ui; しないと参照出来ないので注意）
    pageView->addEventListenerPageView(this, pagevieweventselector(PageViewScene::pageviewCallBack));
    
    this->addChild(pageView);
    
    return true;
}

//バトル開始ボタンスタート
void PageViewScene::touchEvent(cocos2d::Ref* sender, cocos2d::ui::TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN){
    }else if(type == TOUCH_EVENT_ENDED){
        auto button = (Button*) sender;
        Director::getInstance()->replaceScene(TransitionFade::create(2.0f, BattleScene::createScene(button->getTag())));
    }
}

//コールバック
void PageViewScene::pageviewCallBack(Ref* sender, PageViewEventType type)
{
    if(type == PAGEVIEW_EVENT_TURNING){
        auto pageView = dynamic_cast<PageView*>(sender);
        //選択されているページをログに出力
        log("%ld",pageView->getCurPageIndex() + 1);
    }
}