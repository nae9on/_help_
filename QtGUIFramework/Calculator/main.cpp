/*
 * Reference
 * https://doc.qt.io/qt-5/qtwidgets-widgets-calculator-example.html
 * https://doc.qt.io/archives/qt-4.8/signalsandslots.html
 */

#include <QApplication>

#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    Calculator Calc;

    Calc.show();

    return App.exec();
}
