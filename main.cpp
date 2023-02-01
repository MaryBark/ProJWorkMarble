#include "mainwindow.h"

#include <QApplication>
#include <marble/MarbleModel.h>
#include <marble/MarbleWidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;

    Marble::MarbleWidget *mapWidget = new Marble::MarbleWidget();
    mapWidget->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    mapWidget->show();


//    w.show();
    return a.exec();
}
