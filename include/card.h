#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QString>
#include <QImage>
class Card
{

public:
    Card(QString id);
    ~Card();
QString id;//номер
QString Name;//имя
QString Type;//тип
QString Picture_path;// путь к картинке
QImage Picture;//картинка

int Requirements;//цена
int Damage_enemy;//урон врагу
int Damage_self;//урон себе


int PlayerMod_beasts;//изменение зоопарка(свои)
int PlayerMod_bricks;//изменение рудников(свои)
int PlayerMod_gems;//изменение магии(свои)

int EnemyMod_beasts;//изменение зоопарка(врага)
int EnemyMod_bricks;//изменение рудников(врага)
int EnemyMod_gems;//изменение магии(врага)

//изменение ресурсов
//свои
int PlayerChanges_beasts;//животные
int PlayerChanges_bricks;//кирпичи
int PlayerChanges_gems;//мана
int PlayerChanges_tower;//башня
int PlayerChanges_wall;//стена

//врага
int EnemyChanges_beasts;//животные
int EnemyChanges_bricks;//кирпичи
int EnemyChanges_gems;//мана
int EnemyChanges_tower;//башня
int EnemyChanges_wall;//стена

bool AdditionalTurn;//ещё ход
bool DiscardCard;//выкинуть карту
//описание карты
QString Description;
};

#endif // CARD_H
