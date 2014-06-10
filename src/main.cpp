#include <QApplication>
#include "mapsettingswindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MapSettingsWindow mswMapSettings;
    mswMapSettings.show();
    return a.exec();
}
