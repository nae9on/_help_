#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class Calculator : public QWidget
{    
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    // private slots associated with the calculator's buttons.
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

private:

    // Factory function
    Button *createButton(const QString &text, const char *member);

    // Essential op's
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);

    // Manage the state of the calculator
    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    // Variables associated with the display and the buttons used to display numerals.
    QLineEdit *display;
    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
};

#endif
