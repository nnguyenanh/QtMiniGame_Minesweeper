#include "stdafx.h"
#include "DialogAccount.h"

DialogAccount::DialogAccount(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(":/QtMiniGame/icons/icon_10_setting.ico"));
	setWindowTitle("Account Setting");
	setFont(QFont("Courier New", 11, QFont::Bold));
	setFixedSize(380, 470);

	setupLayout();
	setupConnect();

}

void DialogAccount::setupLayout()
{
	QFont font("Courier New", 11, QFont::Bold);
	m_label_username = new QLabel("guest");
	m_label_role = new QLabel("none");
	m_radbtn_username = new QRadioButton("USERNAME");
	m_radbtn_password = new QRadioButton("PASSWORD");
	m_radbtn_delete_account = new QRadioButton("DELETE");
	
	m_edit_new_username = new QLineEdit();
	m_edit_new_username->setFixedHeight(25);

	m_edit_current_password = new QLineEdit();
	m_edit_current_password->setFixedHeight(25);
	m_edit_current_password->setEchoMode(QLineEdit::Password);

	m_edit_new_password = new QLineEdit();
	m_edit_new_password->setFixedHeight(25);
	m_edit_new_password->setEchoMode(QLineEdit::Password);

	m_edit_newagain_password = new QLineEdit();
	m_edit_newagain_password->setFixedHeight(25);
	m_edit_newagain_password->setEchoMode(QLineEdit::Password);

	m_edit_username = new QLineEdit();
	m_edit_username->setFixedHeight(25);

	m_edit_password = new QLineEdit();
	m_edit_password->setFixedHeight(25);
	m_edit_password->setEchoMode(QLineEdit::Password);
	
	m_edit_again_password = new QLineEdit();
	m_edit_again_password->setFixedHeight(25);
	m_edit_again_password->setEchoMode(QLineEdit::Password);

	m_btn_apply = new QPushButton("APPLY");
	m_btn_apply->setFixedSize(110, 50);
	m_btn_logout = new QPushButton("LOG OUT");
	m_btn_logout->setFixedSize(110, 50);

	m_label_error_username = new QLabel();
	m_label_error_username->setFixedHeight(11);
	m_label_error_new_password = new QLabel();
	m_label_error_new_password->setFixedHeight(11);
	m_label_error_password = new QLabel();
	m_label_error_password->setFixedHeight(11);
	m_label_error_not_user = new QLabel();
	m_label_error_not_user->setFixedHeight(11);

	m_btn_logout->setStyleSheet("color: red; font: bold 15px 'Courier New'; font-style: bold;");

	disableAllEdits();

	QFormLayout* layout_form_information = new QFormLayout();
	layout_form_information->addRow(new QLabel("USERNAME:"), m_label_username);
	layout_form_information->addRow(new QLabel("ROLE    :"), m_label_role);
	layout_form_information->addItem(new QSpacerItem(0, 5, QSizePolicy::Minimum, QSizePolicy::Fixed));
	layout_form_information->addRow(makeLine());
	layout_form_information->addItem(new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Fixed));
	layout_form_information->setContentsMargins(15, 10, 15, 0);

	QFormLayout* layout_form_change = new QFormLayout();
	//layout_form_change->addRow(new QLabel("CHANGE INFORMATION"));
	layout_form_change->addItem(new QSpacerItem(0, 3, QSizePolicy::Minimum, QSizePolicy::Fixed));
	//layout_form_change->addRow(nullptr, new QLabel("hello"));
	layout_form_change->addRow(m_radbtn_username, m_edit_new_username);
	layout_form_change->addRow(nullptr, m_label_error_username);
	layout_form_change->addRow(m_radbtn_password, m_edit_current_password);
	layout_form_change->addRow(nullptr, m_edit_new_password);
	layout_form_change->addRow(nullptr, m_edit_newagain_password);
	layout_form_change->addRow(nullptr, m_label_error_new_password);
	layout_form_change->addRow(m_radbtn_delete_account, m_edit_username);
	layout_form_change->addRow(nullptr, m_edit_password);
	layout_form_change->addRow(nullptr, m_edit_again_password);
	layout_form_change->addRow(nullptr, m_label_error_password);
	layout_form_change->addRow(m_label_error_not_user);
	layout_form_change->addRow(makeLine());
	layout_form_change->addItem(new QSpacerItem(0, 3, QSizePolicy::Minimum, QSizePolicy::Fixed));

	//layout_form->addRow();
	layout_form_change->setContentsMargins(15, 0, 15, 0);
	

	QHBoxLayout* layout_h_btn = new QHBoxLayout();
	layout_h_btn->addStretch();
	layout_h_btn->addWidget(m_btn_apply);
	layout_h_btn->addWidget(m_btn_logout);
	layout_h_btn->setContentsMargins(15, 0, 15, 10);

	QVBoxLayout* layout_v_account = new QVBoxLayout();
	//layout_v->addWidget(label_account_information);
	layout_v_account->addLayout(layout_form_information);
	layout_v_account->addLayout(layout_form_change);
	layout_v_account->addStretch();

	layout_v_account->addLayout(layout_h_btn);
	//layout_v_account->addWidget(m_btn_apply, 0, Qt::AlignHCenter);

	setLayout(layout_v_account);
}

void DialogAccount::setupConnect()
{
	connect(m_btn_logout, &QPushButton::pressed, this, &DialogAccount::clickLogout);
	connect(m_btn_apply, &QPushButton::pressed, this, &DialogAccount::clickApply);

	connect(m_radbtn_username, &QRadioButton::toggled, this, [=]() {
		disableAllEdits();
		m_edit_new_username->setEnabled(true);
		m_edit_new_username->setPlaceholderText("Enter new username");
		m_edit_new_username->setFocus();
		});

	connect(m_radbtn_password, &QRadioButton::toggled, this, [=]() {
		disableAllEdits();
		m_edit_current_password->setEnabled(true);
		m_edit_new_password->setEnabled(true);
		m_edit_newagain_password->setEnabled(true);
		m_edit_current_password->setPlaceholderText("Enter current password");
		m_edit_new_password->setPlaceholderText("Enter new password");
		m_edit_newagain_password->setPlaceholderText("Re-enter new password");
		m_edit_current_password->setFocus();
		});

	connect(m_radbtn_delete_account, &QRadioButton::toggled, this, [=]() {
		disableAllEdits();
		m_edit_username->setEnabled(true);
		m_edit_password->setEnabled(true);
		m_edit_again_password->setEnabled(true);
		m_edit_username->setPlaceholderText("Enter username");
		m_edit_password->setPlaceholderText("Enter password");
		m_edit_again_password->setPlaceholderText("Re-enter password");
		m_edit_username->setFocus();
		});

	auto connectRadioClickSound = [&](QAbstractButton* btn) {
		connect(btn, &QAbstractButton::pressed, this, [=]() {
			if (m_ptr_is_sound && *m_ptr_is_sound && m_playClickSound)
				m_playClickSound();
			});
		};

	connectRadioClickSound(m_radbtn_username);
	connectRadioClickSound(m_radbtn_password);
	connectRadioClickSound(m_radbtn_delete_account);
}

void DialogAccount::clickLogout()
{
	emit requestLogout();
	close();
}

void DialogAccount::clickApply()
{
	if (m_ptr_is_sound && *m_ptr_is_sound && m_playClickSound) { m_playClickSound(); }
	if (!m_user_data.getIsUser())
	{
		//QMessageBox::warning(this, "Guest Mode", "Sign in or create account to use account settings.");
		m_label_error_not_user->setStyleSheet(m_sheetstyle_error);
		m_label_error_not_user->setText("Sign in or create account use account setting.");
		return;
	}
	QSqlDatabase database_connection = m_user_data.getDatabaseConnection();
	if (!database_connection.isValid())
	{
		QMessageBox::critical(this, "Account Setting", "Cannot connect to database");
		return;
	}
	QSqlQuery query(database_connection);
	updateUserLogInData(query);
	emit applyClicked(m_user_data);
}


void DialogAccount::updateUserLogInData(QSqlQuery& query)
{
	if (m_radbtn_username->isChecked())
	{
		DialogAccount::updateUsername(query);
	}
	else if (m_radbtn_password->isChecked())
	{
		DialogAccount::updatePassword(query);
	}
	else if (m_radbtn_delete_account->isChecked())
	{
		DialogAccount::deleteAccount(query);
	}
	else
	{
		return;
	}
}

void DialogAccount::updateUsername(QSqlQuery& query)
{
	QString new_username = m_edit_new_username->text().trimmed();
	m_label_error_username->setStyleSheet(m_sheetstyle_error);
	if (new_username.isEmpty())
	{
		m_label_error_username->setText("Username cannot be empty.");
		return;
	}

	query.prepare("SELECT COUNT(*) FROM accounts WHERE username = ?");
	query.addBindValue(new_username);
	query.exec();
	query.next();
	if (query.value(0).toInt() > 0)
	{
		m_label_error_username->setText("Username is already taken.");
		return;
	}

	query.prepare("UPDATE accounts SET username = ? WHERE username = ?");
	query.addBindValue(new_username);
	query.addBindValue(m_user_data.getUsername());
	if (query.exec())
	{
		m_user_data.setUsername(new_username);
		updateUserUsernameOnScreen();
		m_label_error_username->setStyleSheet(m_sheetstyle_success);
		m_label_error_username->setText("Username changed successfully.");
	}
}

void DialogAccount::updatePassword(QSqlQuery& query)
{
	QString current_password = m_edit_current_password->text();
	QString new_password = m_edit_new_password->text();
	QString newagain_password = m_edit_newagain_password->text();
	m_label_error_new_password->setStyleSheet(m_sheetstyle_error);

	if (current_password.isEmpty() || new_password.isEmpty() || newagain_password.isEmpty()) {
		m_label_error_new_password->setText("Please fill in all password fields.");
		return;
	}
	query.prepare("SELECT password FROM accounts WHERE username = ?");
	query.addBindValue(m_user_data.getUsername());
	query.exec();
	query.next();
	if (current_password != query.value(0).toString())
	{
		m_label_error_new_password->setText("Current password is incorrect.");
		return;
	}
	if (new_password != newagain_password)
	{
		m_label_error_new_password->setText("Passwords do not match.");
		return;
	}
	query.prepare("UPDATE accounts SET password = ? WHERE username = ?");
	query.addBindValue(new_password);
	query.addBindValue(m_user_data.getUsername());
	if (query.exec())
	{
		m_label_error_new_password->setStyleSheet(m_sheetstyle_success);
		m_label_error_new_password->setText("Password changed successfully.");
	}
	else 
	{
		m_label_error_new_password->setText("Failed to update password.");
	}
}

void DialogAccount::deleteAccount(QSqlQuery& query)
{
	QString username = m_edit_username->text().trimmed();
	QString password = m_edit_password->text();
	QString reentered_password = m_edit_again_password->text();
	m_label_error_password->setStyleSheet(m_sheetstyle_error);

	if (username.isEmpty() || password.isEmpty() || reentered_password.isEmpty()) {
		m_label_error_password->setText("Please fill in all password fields.");
		return;
	}
	if (username != m_user_data.getUsername())
	{
		m_label_error_password->setText("Account username does not match.");
		return;
	}

	query.prepare("SELECT COUNT(*) FROM accounts WHERE username = ? AND password = ?");
	query.addBindValue(username);
	query.addBindValue(password);
	query.exec();
	query.next();
	if (query.value(0).toInt() == 0) 
	{
		m_label_error_password->setText("Password is incorrect.");
		return;
	}

	if (password != reentered_password) {
		m_label_error_password->setText("Passwords do not match.");
		return;
	}

	QMessageBox::StandardButton confirm = QMessageBox::question(
		this,
		"Account Setting",
		"Account and data deleted cannot be restored.",
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::No
	);

	if (confirm != QMessageBox::Yes)
		return;

	query.prepare("DELETE FROM accounts WHERE username = ? AND password = ?");
	query.addBindValue(username);
	query.addBindValue(password);

	if (query.exec() && query.numRowsAffected() > 0) {
		QMessageBox::information(this, "Account Setting", "Account deleted successfully.");
		emit requestLogout();  
		close();
	}
	else {
		m_label_error_password->setText("Failed to delete account.");
	}

}

void DialogAccount::disableAllEdits()
{
	m_edit_new_username->setDisabled(true);
	m_edit_current_password->setDisabled(true);
	m_edit_new_password->setDisabled(true);
	m_edit_newagain_password->setDisabled(true);
	m_edit_username->setDisabled(true);
	m_edit_password->setDisabled(true);
	m_edit_again_password->setDisabled(true);
	m_edit_new_username->clear();
	m_edit_new_password->clear();
	m_edit_current_password->clear();
	m_edit_newagain_password->clear();
	m_edit_username->clear();
	m_edit_password->clear();
	m_edit_again_password->clear();
	m_edit_new_username->setPlaceholderText("");
	m_edit_current_password->setPlaceholderText("");
	m_edit_new_password->setPlaceholderText("");
	m_edit_newagain_password->setPlaceholderText("");
	m_edit_username->setPlaceholderText("");
	m_edit_password->setPlaceholderText("");
	m_edit_again_password->setPlaceholderText("");

	m_label_error_username->setText("");
	m_label_error_new_password->setText("");
	m_label_error_password->setText("");
}

void DialogAccount::updateUserUsernameOnScreen()
{
	m_label_username->setText(m_user_data.getUsername());
}

void DialogAccount::updateUserRoleOnScreen()
{
	m_label_role->setText(m_user_data.getRole());
}

void DialogAccount::setSoundControl(bool* soundFlag, std::function<void()> playClick)
{
	m_ptr_is_sound = soundFlag;
	m_playClickSound = playClick;
}


DialogAccount::~DialogAccount()
{
}

