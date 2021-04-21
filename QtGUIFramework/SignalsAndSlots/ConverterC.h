#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class CButton;

/*
 * 1. In Qt, a widget typically extends class QWidget, which is itself a subclass of QObject.
 * 2. The QObject class provides signals and slots mechanism for inter-object communication, RTTI etc via its Meta-Object System (MOS).
 * 3. Therefore, widget classes must also derive (directly or indirectly) from QObject to make use of these meta-object features.
 *
 * Pre-Processor
 * 1. Q_OBJECT macro inside the private section of the class declaration is used to enable the meta-object features.
 * 2. Therefore, all classes that contain signals or slots must mention Q_OBJECT at the top of their declaration.
 * 3. The C++ preprocessor changes or removes the signals, slots, and emit keywords so that the compiler is presented with standard C++.
 */

class CConverter : public QWidget
{
    Q_OBJECT

public:
    CConverter(QWidget *parent = nullptr);

private slots:
    void ButtonClicked();

private:
    // Factory function
    CButton* CreateButton(const QString& Text, const char* Member);

    // State
    int m_Decimal{0};

    // Variables associated with the display and the buttons used to covert from Decimal to Binary and vice-versa.
    QLineEdit* m_Display1;
    QLineEdit* m_Display2;
    CButton* m_DecimalToBinary;
    CButton* m_BinaryToDecimal;
};
