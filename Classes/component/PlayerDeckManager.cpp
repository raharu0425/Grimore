//
//  PlayerDeckManager.cpp
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#include "PlayerDeckManager.h"
#include "PlayerCard.h"

USING_NS_CC;

static PlayerDeckManager *s_Shared = nullptr;

PlayerDeckManager::~PlayerDeckManager()
{
    CC_SAFE_RELEASE_NULL(_hands_cards);
    CC_SAFE_RELEASE_NULL(_player_deck);
    CC_SAFE_RELEASE_NULL(_used_cards);
    
}

//getInstance
PlayerDeckManager* PlayerDeckManager::getInstance()
{
    s_Shared = new PlayerDeckManager();
    
    if (s_Shared && s_Shared->init()) {
        s_Shared->retain();
        return s_Shared;
    }
    
    return nullptr;
}

// init
bool PlayerDeckManager::init()
{
    //初期化
    this->setDeck(CCArray::createWithCapacity(DECK_COUNT));
    this->setHandsCards(CCArray::createWithCapacity(HANDS_DECK));
    this->setUsed_Cards(CCArray::createWithCapacity(USED_COUNT));
    
    //各属性の枚数※後でUserDefaultから取るよ
    auto earth_count_max = 10;
    this->setDeckByCard(CARD_EARTH, earth_count_max);
    
    auto liquid_count_max = 10;
    this->setDeckByCard(CARD_LIQUID, liquid_count_max);
    
    auto fire_count_max = 10;
    this->setDeckByCard(CARD_FIRE, fire_count_max);
    
    auto thunder_count_max = 10;
    this->setDeckByCard(CARD_THUNDER, thunder_count_max);

    auto dark_count_max = 10;
    this->setDeckByCard(CARD_DARK, dark_count_max);
    
    auto holy_count_max = 10;
    this->setDeckByCard(CARD_HOLY, holy_count_max);
    
    return true;
}

//必要枚数デッキにセットする
void PlayerDeckManager::setDeckByCard(int identifer, int count_max)
{
    auto deck = this->getDeck();
    for( auto count = 1; count <= count_max; count++){
        auto cards_name = StringUtils::format("card/%d.png", identifer);
        auto card = PlayerCard::create(cards_name);
        card->setIdentifer(identifer);
        deck->addObject(card);
    }
}

//手持ち札をリロードする
void PlayerDeckManager::reload2HandsCards()
{
    auto deck = this->getDeck();
    auto hans_cards = this->getHandsCards();
    
    auto diff_count = HANDS_DECK - hans_cards->count();
    for(auto count = 1; count <= diff_count; count++){
        auto card = (PlayerCard*) deck->getRandomObject();
        hans_cards->addObject(card);
        deck->removeObject(card);
        
        //Indexのセット
        auto idx = hans_cards->getIndexOfObject(card);
        card->setIndex(idx);
    }
    
    CCLOG("hans_card_count:%zd", hans_cards->count());
    CCLOG("deck_count:%zd", deck->count());
    
}