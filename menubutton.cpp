#include "menubutton.h"

MenuButton::MenuButton(const QString& placeholdertext, QWidget* parent, QColor color)
    : QPushButton( placeholdertext, parent), hoverColor(color)
{
    setStyleSheet("background-color:transparent;color:white;border-radius:5px;");
    setContentsMargins(5, 5, 5, 5);

    QFont font;
    font.setPointSize(15);
    setFont(font);
    // Connect to enter and leave events
    installEventFilter(this);
}

bool MenuButton::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        // Change color on hover
        setStyleSheet("background-color:" + hoverColor.name() + ";color:white;border-radius:5px;");

    }
    else if (event->type() == QEvent::Leave)
    {
        // Restore the original color when not hovered
        setStyleSheet("background-color: transparent;color:white;border-radius:5px;");
    }

    // Pass the event to the base class
    return QPushButton::eventFilter(obj, event);
}
