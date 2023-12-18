#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QWidget>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

private slots:
    void on_loginButton_clicked();

    void on_signupButton_clicked();

    void on_skipButton_clicked();

    void on_usernameLineEdit_returnPressed();

    void on_passwordLineEdit_returnPressed();

signals:
    void loggedIn(QString);
    void signedUp(QString);
    void skipped(QString);

private:
    Ui::AuthWindow *ui;
    QString mUsername;
    QString mPassword;
};

#endif // AUTHWINDOW_H
