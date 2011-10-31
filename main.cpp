#include <QtGui/QApplication>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
  //  Game *game=new Game();
//w.setimagelabel(game->Deck,"2");
    w.show();
    return a.exec();
}
