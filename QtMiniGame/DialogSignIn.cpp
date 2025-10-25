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
	setFixedSize(360, 190);
	setupLayout();

	connect(m_btn_login, &QPushButton::pressed, this, &DialogSignIn::clickSignIn);
	connect(m_btn_create_account, &QPushButton::pressed, this, &DialogSignIn::clickCreate);
	connect(m_btn_guest, &QPushButton::pressed, this, &DialogSignIn::clickGuest);
	/*connect(m_edit_username, &QLineEdit::selectionChanged, this, play_click);
	connect(m_edit_password, &QLineEdit::selectionChanged, this, play_click);*/
}


void DialogSignIn::setupLayout()
{
	m_label_error = new QLabel("");
	m_label_error->setFixedHeight(11);
	m_edit_username = new QLineEdit(this);
	m_edit_username->setFixedHeight(25);
	m_edit_password = new QLineEdit(this);
	m_edit_password->setFixedHeight(25);
	m_edit_password->setEchoMode(QLineEdit::Password);

	m_btn_login = new QPushButton("LOG IN", this);
	m_btn_login->setFixedSize(100, 50);
	m_btn_create_account = new QPushButton("CREATE", this);
	m_btn_create_account->setFixedSize(100, 50);
	m_btn_guest = new QPushButton("GUEST", this);
	m_btn_guest->setFixedSize(100, 50);

	QFormLayout* layout_form = new QFormLayout();
	layout_form->addRow(new QLabel("USERNAME", this), m_edit_username);
	layout_form->addRow(new QLabel("PASSWORD", this), m_edit_password);
	layout_form->addRow(nullptr, m_label_error);
	layout_form->addRow(makeLine());
	layout_form->setContentsMargins(14, 10, 14, 5);

	QHBoxLayout* layout_btn = new QHBoxLayout();
	layout_btn->addStretch();
	layout_btn->addWidget(m_btn_login);
	layout_btn->addWidget(m_btn_create_account);
	layout_btn->addWidget(m_btn_guest);
	layout_btn->addStretch();
	layout_btn->setContentsMargins(0, 5, 0, 10);


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
		"PORT=3306;"
		"DATABASE=minesweeper;"
		"USER=admin;"
		"PASSWORD=141103n@N6565;";   // password

	m_database_connection = QSqlDatabase::addDatabase("QODBC", "MainConnection");
	m_database_connection.setDatabaseName(connect_str);
	m_is_connect_database = m_database_connection.open();

	//QStringList drivers = QSqlDatabase::drivers();
	//QString msg = "Available SQL drivers:\n" + drivers.join("\n");
	//QMessageBox::information(this, "Qt SQL", msg);

	//try
	//{
	//	m_driver = get_driver_instance();
	//	if (!m_driver) {
	//		QMessageBox::critical(this, "Error", "get_driver_instance() returned null");
	//		return;
	//	}
	//	m_database_connection = std::unique_ptr<sql::Connection>(
	//		m_driver->connect("tcp://localhost:3306", "admin", "111111")
	//	);
	//	if (!m_database_connection || !m_database_connection->isValid())
	//		throw std::runtime_error("Failed to connect to MySQL server.");
	//	m_database_connection->setSchema("minesweeper");
	//}
	//catch (sql::SQLException& e)
	//{
	//	m_string_error_database_connection = QString::fromStdString(e.what());
	//}
	//m_is_connect_database = (m_database_connection && m_database_connection->isValid());
}

void DialogSignIn::clickSignIn()
{
	playClickSound();
	if (!isConnectedDatabase()) return;

	QString username = m_edit_username->text().trimmed();
	QString password = m_edit_password->text();

	if (username.isEmpty() || password.isEmpty())
	{
		m_label_error->setStyleSheet(m_sheetstyle_error);
		m_label_error->setText("Invalid username or password.");
		return;
	}
	else
	{
		//std::unique_ptr<sql::PreparedStatement> query(
		//	m_database_connection->prepareStatement("SELECT role FROM accounts WHERE username = ? AND password = ?")
		//);

		//query->setString(1, username.toStdString());
		//query->setString(2, password.toStdString());

		//std::unique_ptr<sql::ResultSet> exec_query_result(query->executeQuery());

		//if (exec_query_result->next())
		//{
		//	accept();
		//}
		//else
		//{
		//	QMessageBox::warning(this, "Sign In", "Invalid USERNAME or PASSWORD.");
		//	return;
		//}

		QSqlQuery query(m_database_connection);
		query.prepare("SELECT role FROM accounts WHERE username = ? AND password = ?");
		query.addBindValue(username);
		query.addBindValue(password);
		query.exec();

		if (query.next())
		{
			QString role = query.value("role").toString();
			m_user_data.setDatabaseConnection(QSqlDatabase::database("MainConnection"));
			m_user_data.setUsername(username);
			m_user_data.setRole(role);
			m_user_data.setIsUser(true);
			accept();
		}
		else
		{
			m_label_error->setStyleSheet(m_sheetstyle_error);
			m_label_error->setText("Invalid username or password.");
			return;
		}
	}
}


void DialogSignIn::clickCreate()
{
	playClickSound();
	if (!isConnectedDatabase()) return;

	QString username = m_edit_username->text().trimmed();
	QString password = m_edit_password->text();

	if (username.isEmpty() || password.isEmpty())
	{
		m_label_error->setStyleSheet(m_sheetstyle_error);
		m_label_error->setText("Username and password cannot be empty.");
		return;
	}
	if (username.contains(" "))
	{
		m_label_error->setStyleSheet(m_sheetstyle_error);
		m_label_error->setText("Username cannot contain space.");
		return;
	}
	else
	{
		//try
		//{
		//	std::unique_ptr < sql::PreparedStatement> query(
		//		m_database_connection->prepareStatement("SELECT COUNT(*) FROM accounts WHERE username = ?")
		//	);

		//	query->setString(1, username.toStdString());
		//	std::unique_ptr<sql::ResultSet> exec_query_result(query->executeQuery());

		//	exec_query_result->next();
		//	int count = exec_query_result->getInt(1);

		//	if (count > 0)
		//	{
		//		QMessageBox::warning(this, "Create Account", "USERNAME has been taken.");
		//		return;
		//	}
		//	else
		//	{
		//		QString str_pass_default = "1";
		//		if (password.isEmpty())
		//		{
		//			password = str_pass_default;
		//		}

		//		query = std::unique_ptr < sql::PreparedStatement>(
		//			m_database_connection->prepareStatement("INSERT INTO accounts (username, password, role) VALUES (?, ?, 'user')")

		//		);
		//		query->setString(1, username.toStdString());
		//		query->setString(2, password.toStdString());
		//		query->executeUpdate();

		//		QString msg = "Account created successfully.";
		//		if (password == str_pass_default)
		//			msg += "\nDefault PASSWORD is 1.";
		//		QMessageBox::information(this, "Create Account", msg);

		//	}

		//}
		//catch (sql::SQLException& e)
		//{
		//	return;
		//}

		QSqlQuery query(m_database_connection);
		query.prepare("SELECT COUNT(*) FROM accounts WHERE username = ?");
		query.addBindValue(username);
		query.exec();

		if (query.next() && query.value(0).toInt() > 0) {
			m_label_error->setStyleSheet(m_sheetstyle_error);
			m_label_error->setText("Username is already taken.");
			return;
		}
		else
		{
			m_label_error->setStyleSheet(m_sheetstyle_success);
			query.prepare("INSERT INTO accounts (username, password, role) VALUES (?, ?, 'user')");
			query.addBindValue(username);
			query.addBindValue(password);
			query.exec();
			m_label_error->setText("Account created successfully.");
		}
	}
}

bool DialogSignIn::isConnectedDatabase()
{
	if (!m_is_connect_database)
	{
		m_label_error->setStyleSheet(m_sheetstyle_error);
		m_label_error->setText("Cannot connect to game database.");
		return false;
	}
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

