#pragma once

#include <QDialog>
#include "ui_DialogSignIn.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSQLDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DialogSignIn : public QDialog
{
	Q_OBJECT

public:
	DialogSignIn(QWidget *parent = nullptr);
	~DialogSignIn();

private:
	Ui::DialogSignInClass ui;
    bool m_is_connect_database = false;
    QSqlDatabase m_database;

private:
    QLabel* m_label_username;
    QLabel* m_label_password;
    QLineEdit* m_edit_username;
    QLineEdit* m_edit_password;
    QPushButton* m_btn_login;
    QPushButton* m_btn_create_account;
    QPushButton* m_btn_guest;

    QMediaPlayer m_player_click;
    QAudioOutput m_audio_click;

public:
    void connectMinesweeperAccountsDatabase();
    bool isConnectedDatabase();
    void playClickSound();
    void setupLayout();

private slots:
    void clickSignIn();
    void clickCreate();
    void clickGuest() { accept(); }
};

