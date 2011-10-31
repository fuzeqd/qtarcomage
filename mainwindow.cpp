#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game=new Game();
  setimagelabel(game->Deck,"2");
nomer=2;

        }

void MainWindow::left(){
   if(nomer>2)nomer--;
  QString id= QObject::tr("%1").arg(nomer);
   qDebug() << id;
   setimagelabel(game->Deck,id);
}
void MainWindow::rith(){
    if(nomer<84)nomer++;
    QString id= QObject::tr("%1").arg(nomer);
     qDebug() << id;
     setimagelabel(game->Deck,id);
 }

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setimagelabel(  QMap<QString, Card*> Deck ,QString id)
{ QMap<QString, Card*>::const_iterator i=Deck.constFind(id);
    Card* n=new Card("");
   if(i!=Deck.begin())i--;
    n=(Card*)i.value();
    ui->label->setPixmap(QPixmap::fromImage(n->Picture, Qt::AutoColor));
    ui->label_2->setText(n->Name);
    ui->label_3->setText(n->Description);

//    i++;
//    n=(Card*)i.value();
//    ui->label_2->setPixmap(QPixmap::fromImage(n->Picture, Qt::AutoColor));

//    i++;
//    n=(Card*)i.value();
//    ui->label_3->setPixmap(QPixmap::fromImage(n->Picture, Qt::AutoColor));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


// ui->label->setPixmap(QPixmap::fromImage(game->Picture, Qt::AutoColor));
