#pragma once

#include <QToolButton>

class CButton : public QToolButton
{
    Q_OBJECT

public:
    explicit CButton(const QString& Text, QWidget* Parent = nullptr);
};
