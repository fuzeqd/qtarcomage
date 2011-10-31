#include "include/game.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QTextCodec>
#include <QDomNodeList>
#include <QMessageBox>
#include <QLabel>

Game::Game()
{
//#if defined(Q_OS_LINUX)
 // QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//#endif
//#if defined(Q_OS_WIN32)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//#endif

    qDebug() <<"Deck init ";
    if(init_deck(QLatin1String("Default.deck"))) {
        qDebug() <<"Deck init ok!";
    }else{
         qDebug() <<"Deck init fail!";
    }
}

bool Game::init_deck(QLatin1String path){
zip_reader=new QZipReader(path);

    if (zip_reader->exists()) {
        // вывод информации об архиве
        qDebug() << "Number of items in the zip archive =" << zip_reader->count();
        foreach (QZipReader::FileInfo info, zip_reader->fileInfoList()) {
            if(info.isFile)
                qDebug() << "File:" << info.filePath << info.size;
            else if (info.isDir)
                qDebug() << "Dir:" << info.filePath;
            else
                qDebug() << "SymLink:" << info.filePath;
        }




        QByteArray data =zip_reader->fileData("data/deck.xml");//тут описание карт читаю

xml_parser(data);
//         распаковка архива по указанному пути
//        zip_reader.extractAll(QLatin1String("./"));

return 1;
    }else{
         qDebug() << "no file" ;
         return 0;
    }
}

bool Game::xml_parser(QByteArray doc){



    QString errorStr;
        int errorLine;
        int errorColumn;
        QDomDocument domDocument;

     //   QFile device( "test.html");
       // device.open( QIODevice::ReadOnly);

        if (!domDocument.setContent( doc, true, &errorStr, &errorLine, &errorColumn))
        {
            QMessageBox::information( 0,
                                     QObject::tr("XML"),
                                     QObject::tr("Parse error at line %1, column %2:\n%3")
                                     .arg(errorLine)
                                     .arg(errorColumn)
                                     .arg(errorStr));
            return false;
        }

        QDomElement root = domDocument.documentElement();
        // перечислить
        QDomNodeList children = root.childNodes();
        for (int i = 0; i < children.size(); ++i)
        {
            if (children.at(i).isElement())
            {
                QDomElement childElement = children.at(i).toElement();

                QString tagName = childElement.tagName();
                if (tagName=="Card")
                {

                    QString id = childElement.attribute("id");
                    Card* b= new  Card(id);
                    qDebug() <<" ";
                    qDebug() << tagName << id;
                    QDomNodeList childs=childElement.childNodes();

                    for (int j = 0; j < childs.size(); ++j)
                    {
                        if (childs.at(j).isElement())
                        {
                            QDomElement childElement2 = childs.at(j).toElement();
                            QString tagName2 = childElement2.tagName();
                            QString text2;
                            if(tagName2=="Name")  {
                                text2 = childElement2.attribute("value");
                                b->Name=text2;
                            }

                            if(tagName2=="Type") {

                                text2 = childElement2.attribute("value");
                                b->Type=text2;
                            }
                            if(tagName2=="Picture") {

                                text2 = childElement2.attribute("value");
                                b->Picture_path="images/"+text2;
                                b->Picture.loadFromData(zip_reader->fileData(b->Picture_path),"png");
                            }
                            if(tagName2=="Requirements")  {
                                text2 = childElement2.attribute("value");
                                b->Requirements=text2.toInt();
                            }
                            if(tagName2=="Damage") {
                                b->Damage_enemy=childElement2.attribute("enemy").toInt();
                                b->Damage_self=childElement2.attribute("self").toInt();
                              //  text2 = QString("enemy=%1 self=%2").arg(b->Damage_enemy).arg(b->Damage_self);
                            }
                            if(tagName2=="PlayerMod") {
                                b->PlayerMod_beasts=childElement2.attribute("beasts").toInt();
                                b->PlayerMod_bricks=childElement2.attribute("bricks").toInt();
                                b->PlayerMod_gems=childElement2.attribute("gems").toInt();
                           //     text2 = QString("beasts=%1 bricks=%2 gems=%3").arg(b->PlayerMod_beasts).arg(b->PlayerMod_bricks).arg(b->PlayerMod_gems);
                            }
                             if(tagName2=="EnemyMod") {
                                 b->EnemyMod_beasts=childElement2.attribute("beasts").toInt();
                                 b->EnemyMod_bricks=childElement2.attribute("bricks").toInt();
                                 b->EnemyMod_gems=childElement2.attribute("gems").toInt();
                             }
                             if(tagName2=="PlayerChanges") {
                                 b->PlayerChanges_beasts=childElement2.attribute("beasts").toInt();
                                 b->PlayerChanges_bricks=childElement2.attribute("bricks").toInt();
                                 b->PlayerChanges_gems=childElement2.attribute("gems").toInt();
                                 b->PlayerChanges_tower=childElement2.attribute("tower").toInt();
                                 b->PlayerChanges_wall=childElement2.attribute("wall").toInt();
                             }
                             if(tagName2=="EnemyChanges") {
                                 b->EnemyChanges_beasts=childElement2.attribute("beasts").toInt();
                                 b->EnemyChanges_bricks=childElement2.attribute("bricks").toInt();
                                 b->EnemyChanges_gems=childElement2.attribute("gems").toInt();
                                 b->EnemyChanges_tower=childElement2.attribute("tower").toInt();
                                 b->EnemyChanges_wall=childElement2.attribute("wall").toInt();
                             }
                             if(tagName2=="AdditionalTurn")  {
                                 b->AdditionalTurn = childElement2.attribute("value").toInt();
                             }
                             if(tagName2=="DiscardCard")  {
                                 b->DiscardCard = childElement2.attribute("value").toInt();
                             }
                             if(tagName2=="Description")  {
                                 b->Description = childElement2.attribute("value");
                             }




                        //  qDebug() << tagName2 << text2;

                        }
                    }

                    Deck.insert(id,b);

                }
            }
        }





//   QXmlStreamReader xml(doc);
// тут был большой кусок говна я его выпилил и сделал конфету

        //   //проверка загрузки

        QMap<QString, Card*>::const_iterator i=Deck.begin();


        Card* n=new Card("");
         while(i!=Deck.end()){

              n=(Card*)i.value();

             qDebug() <<QObject::tr ("\n\nКарта %1 Имя=%2 Тип=%3").arg(n->id ).arg(n->Name).arg(n->Type);
             qDebug() <<QObject::tr ("Цена=%1 Урон врагу=%2 Урон себе=%3").arg(n->Requirements).arg(n->Damage_enemy).arg(n->Damage_self);
             qDebug() <<QObject::tr ("картинка=%1 ").arg(n->Picture_path );
             qDebug() <<QObject::tr ("Свои изменения :");
             qDebug() <<QObject::tr ("зоопарка=%1 рудников=%2 магии=%3").arg(n->PlayerMod_beasts).arg(n->PlayerMod_bricks).arg(n->PlayerMod_gems);
             qDebug() <<QObject::tr ("животные=%1 кирпичи=%2 мана=%3 башня=%4 стена=%5").arg(n->PlayerChanges_beasts).arg(n->PlayerChanges_bricks).arg(n->PlayerChanges_gems).arg(n->PlayerChanges_tower).arg(n->PlayerChanges_wall);
             qDebug() <<QObject::tr (" изменения врага:");
             qDebug() <<QObject::tr ("зоопарка=%1 рудников=%2 магии=%3").arg(n->EnemyMod_beasts).arg(n->EnemyMod_bricks).arg(n->EnemyMod_gems);
             qDebug() <<QObject::tr ("животные=%1 кирпичи=%2 мана=%3 башня=%4 стена=%5").arg(n->EnemyChanges_beasts).arg(n->EnemyChanges_bricks).arg(n->EnemyChanges_gems).arg(n->EnemyChanges_tower).arg(n->EnemyChanges_wall);
             qDebug() <<QObject::tr ("ещё ход=%1").arg(n->AdditionalTurn);
             qDebug() <<QObject::tr ("сбросить карту=%1").arg(n->DiscardCard);
             qDebug() <<QObject::tr ("описание : ");
             qDebug() <<n->Description;
             //так делать только для прикола )))
//QLabel* label = new QLabel(n->id);
//label->setPixmap(QPixmap::fromImage(n->Picture, Qt::AutoColor));
//label->show();
              i++;
           }
        delete n;



   return 1;
}



Game::~Game(){
//очищать надо както Deck*
}
