#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QPalette>


class MenuButton : public QPushButton
{
    Q_OBJECT

public:
    MenuButton(const QString& text, QWidget* parent = nullptr, QColor color=QColor(115, 119, 122));
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QColor hoverColor;
};

#endif // MENUBUTTON_H
