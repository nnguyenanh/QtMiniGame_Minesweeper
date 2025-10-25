#pragma once

#include <QDialog>
#include "ui_DialogSignIn.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSQLDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "UserLogInData.h"
//#include <QDebug>


//#include <mysql/jdbc.h>
//#include <mysqlx/xdevapi.h>

class DialogSignIn : public QDialog
{
	Q_OBJECT

public:
	DialogSignIn(QWidget *parent = nullptr);
	~DialogSignIn();

private:
	Ui::DialogSignInClass ui;

private:
    QSqlDatabase m_database_connection;
    bool m_is_connect_database = false;
public:
    QSqlDatabase getDatabaseConnection() { return m_database_connection; }
    //bool getIsConnectDatabase() { return m_is_connect_database; }

    //sql::Driver* m_driver;
    //std::unique_ptr<sql::Connection> m_database_connection;
    //QString m_string_error_database_connection;


private:
    QLabel* m_label_error;

    QLineEdit* m_edit_username;
    QLineEdit* m_edit_password;
    QPushButton* m_btn_login;
    QPushButton* m_btn_create_account;
    QPushButton* m_btn_guest;

    QMediaPlayer m_player_click;
    QAudioOutput m_audio_click;

    UserLogInData m_user_data;


    QString m_sheetstyle_error = "color: red; font: bold 10px 'Courier New'; font-style: italic;";
    QString m_sheetstyle_success = "color: #50C878; font: bold 10px 'Courier New'; font-style: italic;";

public:
    void connectMinesweeperAccountsDatabase();
    bool isConnectedDatabase();
    void playClickSound();
    void setupLayout();

    //QSqlDatabase getDatabaseConnection() { return m_database_connection; }
    bool getIsConnectedDatabase() { return m_is_connect_database; }
    UserLogInData getUserLoginData() { return m_user_data; }

    QFrame* makeLine(QWidget* parent = nullptr) {
        QFrame* line = new QFrame(parent);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setStyleSheet("color: #696969;");
        return line;
    }

private slots:
    void clickSignIn();
    void clickCreate();
    void clickGuest() { accept(); }
};

