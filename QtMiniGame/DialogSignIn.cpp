#include "stdafx.h"
#include "DialogSignIn.h"

DialogSignIn::DialogSignIn(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connectMinesweeperAccountsDatabase();
	QFont font("Courier New", 11, QFont::Bold);
	setFont(font);
	setWindowTitle("Account");
	setWindowIcon(QIcon(":/QtMiniGame/icons/icon_9_account.ico"));
	m_player_click.setAudioOutput(&m_audio_click);
	m_player_click.setSource(QUrl("qrc:/QtMiniGame/sounds/sound_4_click.mp3"));
	m_audio_click.setVolume(1);
	setFixedSize(360, 160);
	setupLayout();

	connect(m_btn_login, &QPushButton::pressed, this, &DialogSignIn::clickSignIn);
	connect(m_btn_create_account, &QPushButton::pressed, this, &DialogSignIn::clickCreate);
	connect(m_btn_guest, &QPushButton::pressed, this, &DialogSignIn::clickGuest);
	/*connect(m_edit_username, &QLineEdit::selectionChanged, this, play_click);
	connect(m_edit_password, &QLineEdit::selectionChanged, this, play_click);*/
}


void DialogSignIn::setupLayout()
{
	m_label_username = new QLabel("USERNAME", this);
	m_label_password = new QLabel("PASSWORD", this);
	m_edit_username = new QLineEdit(this);
	m_edit_password = new QLineEdit(this);
	m_edit_password->setEchoMode(QLineEdit::Password);

	m_btn_login = new QPushButton("LOG IN", this);
	m_btn_login->setFixedSize(100, 50);
	m_btn_create_account = new QPushButton("CREATE", this);
	m_btn_create_account->setFixedSize(100, 50);
	m_btn_guest = new QPushButton("GUEST", this);
	m_btn_guest->setFixedSize(100, 50);

	QFormLayout* layout_form = new QFormLayout();
	layout_form->addRow(m_label_username, m_edit_username);
	layout_form->addRow(m_label_password, m_edit_password);
	layout_form->setContentsMargins(14, 10, 14, 0);

	QHBoxLayout* layout_btn = new QHBoxLayout();
	layout_btn->addStretch();
	layout_btn->addWidget(m_btn_login);
	layout_btn->addWidget(m_btn_create_account);
	layout_btn->addWidget(m_btn_guest);
	layout_btn->addStretch();
	layout_btn->setContentsMargins(0, 0, 0, 10);


	QVBoxLayout* layout_vertical_main = new QVBoxLayout();
	layout_vertical_main->addLayout(layout_form);
	layout_vertical_main->addStretch();
	layout_vertical_main->addLayout(layout_btn);

	//layout_vertical_main->setContentsMargins(30, 25, 30, 25);
	setLayout(layout_vertical_main);
}

void DialogSignIn::connectMinesweeperAccountsDatabase()
{
	QString connect_str =
		"DRIVER={MySQL ODBC 9.5 Unicode Driver};"
		"SERVER=localhost;"
		"PORT=8383;"
		"DATABASE=minesweeper;"
		"USER=admin;"
		"PASSWORD=141103n@N6565;";   // your password

	m_database = QSqlDatabase::addDatabase("QODBC");
	m_database.setDatabaseName(connect_str);
	m_is_connect_database = m_database.open();
}

void DialogSignIn::clickSignIn()
{
	playClickSound();
	if (!isConnectedDatabase()) return;

	QString username = m_edit_username->text();
	QString password = m_edit_password->text();

	if (username.isEmpty() || password.isEmpty())
	{
		QMessageBox::warning(this, "Sign In", "Please enter USERNAME and PASSWORD.");
		return;
	}
	else
	{
		QSqlQuery query(m_database);
		query.prepare("SELECT role FROM accounts WHERE username = ? AND password = ?");
		query.addBindValue(username);
		query.addBindValue(password);
		query.exec();

		if (query.next())
		{
			QString role = query.value("role").toString();
			accept();
		}
		else
		{
			QMessageBox::warning(this, "Sign In", "Invalid USERNAME or PASSWORD.");
			return;
		}
	}
}


void DialogSignIn::clickCreate()
{
	playClickSound();
	if (!isConnectedDatabase()) return;

	QString username = m_edit_username->text();
	QString password = m_edit_password->text();

	if (username.isEmpty())
	{
		QMessageBox::warning(this, "Create Account", "USERNAME cannot be empty.");
		return;
	}
	else
	{
		QSqlQuery query(m_database);
		query.prepare("SELECT COUNT(*) FROM accounts WHERE username = ?");
		query.addBindValue(username);
		query.exec();

		if (query.next() && query.value(0).toInt() > 0) {
			QMessageBox::warning(this, "Create Account", "USERNAME has been taken.");
			return;
		}
		else
		{
			if (password.isEmpty()) password = "1";
			query.prepare("INSERT INTO accounts (username, password, role) VALUES (?, ?, 'user')");
			query.addBindValue(username);
			query.addBindValue(password);
			query.exec();
			QMessageBox::information(this, "Create Account", "Account created successfully.\nDefault PASSWORD is 1.");
		}
	}
}

bool DialogSignIn::isConnectedDatabase()
{
	if (!m_is_connect_database)
		QMessageBox::critical(this, "Fail", "Cannot connect to game database.");
	return m_is_connect_database;
}

void DialogSignIn::playClickSound()
{
	m_player_click.stop();
	m_player_click.play();
}


DialogSignIn::~DialogSignIn()
{

}

