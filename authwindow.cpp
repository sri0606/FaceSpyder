#include "pch.h"
#include "authwindow.h"
#include "ui_authwindow.h"
#include <QLayout>
#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    showMaximized();
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_loginButton_clicked()
{
    //if (mUsername and mPassword{
    //}

    // just emit the loggedIn signal
    emit loggedIn(mUsername);

}


void AuthWindow::on_signupButton_clicked()
{
    //if (mUsername and mPassword{
    //}
    // emit the signedUp signal
    emit signedUp(mUsername);
}


void AuthWindow::on_skipButton_clicked()
{
    QMessageBox::information(this, "Skipped", "Skipping login/signup");
    // Emit a signal to indicate skipping
    emit loggedIn("Guest");
}


void AuthWindow::on_usernameLineEdit_returnPressed()
{
    mUsername = ui->usernameLineEdit->text();
}


void AuthWindow::on_passwordLineEdit_returnPressed()
{
    mPassword = ui->passwordLineEdit->text();
}

