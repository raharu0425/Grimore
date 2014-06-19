//
//  PlayerDeckManager.h
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#ifndef __Grimore__PlayerDeckManager__
#define __Grimore__PlayerDeckManager__

#include <iostream>
#include "cocos2d.h"
#include "../Config.h"

class PlayerDeckManager : public cocos2d::Ref
{
private:
    virtual ~PlayerDeckManager();
public:
    //Method
    static PlayerDeckManager* getInstance();
    bool init();
    
    //各種カード達
    CC_SYNTHESIZE(cocos2d::__Array*, _player_deck, Deck);
    CC_SYNTHESIZE(cocos2d::__Array*, _hands_cards, HandsCards);
    CC_SYNTHESIZE(cocos2d::__Array*, _used_cards, Used_Cards);
    
    //デッキにセットする
    void setDeckByCard(int identifer, int count);
    //デッキのリロードを行う(足りないカードを追加する)
    void reload2HandsCards();
};

#endif /* defined(__Grimore__PlayerDeckManager__) */
