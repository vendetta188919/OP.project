#include <QApplication>
#include <QTextCodec>

#include "Widget.h"

using namespace std;

int main(int iArgc, char* pArgv[])
{
    QApplication App(iArgc, pArgv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

    Widget mainWidget;
    mainWidget.setWindowTitle(QString::fromLocal8Bit("страховая компания <<СтрахДом Сервис>>"));
    mainWidget.show();

    return App.exec();
}

