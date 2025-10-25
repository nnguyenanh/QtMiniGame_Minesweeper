#pragma once
#include <QSqlDatabase>

class UserLogInData
{
private:
	QSqlDatabase m_connection;
	QString m_username = "none";
	QString m_role = "stupid guest";
	bool m_is_user = false;

public:
	void setDatabaseConnection(QSqlDatabase connection) { m_connection = connection; }
	void setUsername(QString username) { m_username = username; }
	void setRole(QString role) { m_role = role; }
	void setIsUser(bool is_user) { m_is_user = is_user; }

	QSqlDatabase getDatabaseConnection() { return m_connection; }
	QString getUsername() { return m_username; }
	QString getRole() { return m_role; }
	bool getIsUser() { return m_is_user; }

	// Overload operator=
	UserLogInData& operator=(const UserLogInData& other)
	{
		if (this != &other)
		{
			m_connection = other.m_connection;
			m_username = other.m_username;
			m_role = other.m_role;
			m_is_user = other.m_is_user;
		}
		return *this;
	}
};