#include "stdafx.h"
#include "QPushButtonRightClick.h"


QPushButtonRightClick::QPushButtonRightClick(QWidget* parent) :
	QPushButton(parent)
{
	setStyleSheet(
		"QPushButtonRightClick {"
		"  background-color: #696969;"
		"  border: 0.5px solid #222;"
		"  border-radius: 0px;"
		"}"
		"QPushButton:hover {"
		"  background-color: #666;"
		"}"
		"QPushButton:pressed {"
		"  background-color: #222;"
		"}"
	);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void QPushButtonRightClick::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		int wid = width() * 90 /100;
		static QIcon red_flag(":/QtMiniGame/icon_1_red_flag.ico");
		static QIcon question_mark(":/QtMiniGame/icon_2_question_mark.ico");
		static bool is_red_flag = false;

		if (icon().isNull()) 
		{
			setIcon(red_flag);
			setIconSize(QSize(wid, wid));
			is_red_flag = true;
		}
		else 
		{
			if (is_red_flag)
			{
				setIcon(question_mark);
				setIconSize(QSize(wid, wid));
				is_red_flag = !is_red_flag;
			}
			else
			{
				setIcon(QIcon());  // delete icon
			}
		}

		emit clickRight();
		e->accept();
	}
	else
		QPushButton::mousePressEvent(e);
}