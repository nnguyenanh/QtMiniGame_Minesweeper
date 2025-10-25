#pragma once

#include <QDialog>
#include "ui_DialogAccount.h"
#include "UserLogInData.h"
#include <QSQlDatabase>
#include <QSQlQuery>

class DialogAccount : public QDialog
{
	Q_OBJECT

public:
	DialogAccount(QWidget *parent = nullptr);
	~DialogAccount();

private:
	Ui::DialogAccountClass ui;

	UserLogInData m_user_data;

	QLabel* m_label_username = nullptr;
	QLabel* m_label_role = nullptr;
	QLabel* m_label_error_username = nullptr;
	QLabel* m_label_error_new_password = nullptr;
	QLabel* m_label_error_password = nullptr;
	QLabel* m_label_error_not_user = nullptr;
	QRadioButton* m_radbtn_username = nullptr;
	QRadioButton* m_radbtn_password = nullptr;
	QRadioButton* m_radbtn_delete_account = nullptr;
	QLineEdit* m_edit_new_username = nullptr;
	QLineEdit* m_edit_current_password = nullptr;
	QLineEdit* m_edit_new_password = nullptr;
	QLineEdit* m_edit_newagain_password = nullptr;
	QLineEdit* m_edit_username = nullptr;
	QLineEdit* m_edit_password = nullptr;
	QLineEdit* m_edit_again_password = nullptr;
	QPushButton* m_btn_apply = nullptr;
	QPushButton* m_btn_logout = nullptr;

	QString m_sheetstyle_error = "color: red; font: bold 10px 'Courier New'; font-style: italic;";
	QString m_sheetstyle_success = "color: #50C878; font: bold 10px 'Courier New'; font-style: italic;";
	QString m_sheetstyle_placeholder = "color: #696969; font: bold 10px 'Courier New'; font-style: italic;";

	bool* m_ptr_is_sound = nullptr;
	std::function<void()> m_playClickSound;

public:
	void setupLayout();

	void setupConnect();
	void disableAllEdits();
	void updateUserUsernameOnScreen();
	void updateUserRoleOnScreen();
	void setUserLogInData(const UserLogInData& user) { m_user_data = user; }
	void updateUserLogInData(QSqlQuery& query);
	void updateUsername(QSqlQuery& query);
	void updatePassword(QSqlQuery& query);
	void deleteAccount(QSqlQuery& query);

	void setSoundControl(bool* soundFlag, std::function<void()> playClick);

	QFrame* makeLine(QWidget* parent = nullptr) {
		QFrame* line = new QFrame(parent);
		line->setFrameShape(QFrame::HLine);
		line->setFrameShadow(QFrame::Plain);
		line->setLineWidth(3);
		line->setStyleSheet("color: #696969;");
		return line;
	}

signals:
	void requestLogout();
	void applyClicked(const UserLogInData& updated);  

private slots:
	void clickLogout();
	void clickApply();
};

