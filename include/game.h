#ifndef GAME_H
#define GAME_H
#include "card.h"
#include <QMap>

#include "include/qzipreader_p.h"
//#include "include/qzipwriter_p.h"
class Game
{
public:
    Game();
    QMap<QString, Card*> Deck;
    ~Game();
protected:
    QZipReader *zip_reader;
    bool xml_parser(QByteArray doc);
    bool init_deck(QLatin1String path);//загрузка карт
};

#endif // GAME_H
