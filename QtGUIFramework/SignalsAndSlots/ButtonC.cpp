#include "ButtonC.h"

CButton::CButton(const QString& Text, QWidget* Parent)
    : QToolButton(Parent)
{
    setText(Text);
}
