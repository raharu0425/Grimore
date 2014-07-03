//
//  Config.h
//  Grimore
//
//  Created by raharu on 2014/06/16.
//
//

#ifndef Grimore_Config_h
#define Grimore_Config_h

//バージョン
#define APP_VERSION 1

//手持ちの札数
#define HANDS_DECK 6
//デッキの総枚数
#define DECK_COUNT 60
//使い終わったカード
#define USED_COUNT 60

//カード識別番号
#define CARD_EARTH 1
#define CARD_LIQUID 7
#define CARD_FIRE 43
#define CARD_THUNDER 259
#define CARD_DARK 1555
#define CARD_HOLY 9331

//ZIndexはそのまま優先度となる
enum kBattleScenePriorty{
    Layout = 1,
    Cards = 2,
    Action = 101,
    DisableTouchLayer = 128
};

#endif // Grimore_Config_h
