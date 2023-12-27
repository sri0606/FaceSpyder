#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QWidget>

class loadingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit loadingWindow(QWidget *parent = nullptr);

signals:
};

#endif // LOADINGWINDOW_H
