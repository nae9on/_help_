/*
 * References
 * https://doc.qt.io/archives/qt-4.8/signalsandslots.html
 * https://doc.qt.io/archives/qt-4.8/metaobjects.html#meta-object-system
 */

#include "ConverterC.h"
#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication QApp(argc, argv);

    CConverter Converter;
    Converter.show();

    std::cout << "End of main" << std::endl;

    // exec() is called to start Qt's event loop. Control passes to Qt until this function returns.
    return QApp.exec();
}
