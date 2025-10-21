#include "stdafx.h"
#include "QtMiniGame.h"

QtMiniGame::QtMiniGame(QWidget* parent)
	: QMainWindow(parent)
{
	// DEFAULT Qt .ui
	ui.setupUi(this);
	QFont font("Courier New", 11, QFont::Bold);
	setFont(font);

	// ICONS
	m_icon_1_red_flag = QIcon(":/QtMiniGame/icons/icon_1_red_flag.ico");
	m_icon_2_question_mark = QIcon(":/QtMiniGame/icons/icon_2_question_mark.ico");
	m_icon_3_mine = QIcon(":/QtMiniGame/icons/icon_3_mine.ico");
	m_icon_4_blasting = QIcon(":/QtMiniGame/icons/icon_4_blasting.ico");
	m_icon_5_pause = QIcon(":/QtMiniGame/icons/icon_5_pause.ico");
	m_icon_6_play = QIcon(":/QtMiniGame/icons/icon_6_play.ico");
	m_icon_7_sound_off = QIcon(":/QtMiniGame/icons/icon_7_sound_off.ico");
	m_icon_7_sound_on = QIcon(":/QtMiniGame/icons/icon_7_sound_on.ico");
	m_icon_8_level = QIcon(":/QtMiniGame/icons/icon_8_level.ico");

	m_icon_number_1 = QIcon(":/QtMiniGame/icons/number_1.ico");
	m_icon_number_2 = QIcon(":/QtMiniGame/icons/number_2.ico");
	m_icon_number_3 = QIcon(":/QtMiniGame/icons/number_3.ico");
	m_icon_number_4 = QIcon(":/QtMiniGame/icons/number_4.ico");
	m_icon_number_5 = QIcon(":/QtMiniGame/icons/number_5.ico");
	m_icon_number_6 = QIcon(":/QtMiniGame/icons/number_6.ico");
	m_icon_number_7 = QIcon(":/QtMiniGame/icons/number_7.ico");
	m_icon_number_8 = QIcon(":/QtMiniGame/icons/number_8.ico");

	setWindowIcon(m_icon_3_mine);
	setWindowTitle("Minesweeper Vietnam");

	// SOUNDS
	m_player_1_step.setAudioOutput(&m_audio_1_step);
	m_player_1_step.setSource(QUrl("qrc:/QtMiniGame/sounds/sound_1_step.mp3"));
	m_audio_1_step.setVolume(0.8);

	m_player_2_flag.setAudioOutput(&m_audio_2_flag);
	m_player_2_flag.setSource(QUrl("qrc:/QtMiniGame/sounds/sound_2_flag.mp3"));
	m_audio_2_flag.setVolume(0.8);

	m_player_3_mine.setAudioOutput(&m_audio_3_mine);
	m_player_3_mine.setSource(QUrl("qrc:/QtMiniGame/sounds/sound_3_explode.mp3"));
	m_audio_3_mine.setVolume(0.8);

	m_player_4_click.setAudioOutput(&m_audio_4_click);
	m_player_4_click.setSource(QUrl("qrc:/QtMiniGame/sounds/sound_4_click.mp3"));
	m_audio_4_click.setVolume(0.8);



	// Set central widget and grid layout
	setCentralWidgetandGridLayout();
	// Set buttons to layout
	setButtonGridLayout();
	qApp->processEvents();
	setFixGridButtonsSize();
	setGameIconSize();
	initGame();

}

// SET WIDGET LAYOUT
void QtMiniGame::setCentralWidgetandGridLayout()
{
	m_central = new QWidget(this);

	// === GRID ===
	m_layout_grid = new QGridLayout();
	m_layout_grid->setSpacing(0);

	QWidget* container_grid = new QWidget();
	container_grid->setLayout(m_layout_grid);
	container_grid->setFixedSize(m_grid_size, m_grid_size);

	QWidget* gridHolder = new QWidget();
	QVBoxLayout* gridLayout = new QVBoxLayout(gridHolder);
	gridLayout->addStretch();
	gridLayout->addWidget(container_grid, 0, Qt::AlignCenter);
	gridLayout->addStretch();

	// === BUTTONS ===
	m_btn_pause_resume = new QPushButton(this);
	m_btn_pause_resume->setFixedSize(50, 50);
	m_btn_pause_resume->setIcon(m_icon_5_pause);
	m_btn_pause_resume->setIconSize(QSize(m_icon_pause_sound_wid, m_icon_pause_sound_wid));
	m_btn_pause_resume->setDisabled(true);
	m_btn_sound = new QPushButton(this);
	m_btn_sound->setFixedSize(50, 50);
	m_btn_sound->setIcon(m_icon_7_sound_off);
	m_btn_sound->setIconSize(QSize(m_icon_pause_sound_wid, m_icon_pause_sound_wid));
	m_btn_level = new QPushButton("Level", this);
	m_btn_level->setFixedSize(110, 50);
	m_btn_restart = new QPushButton("Restart", this);
	m_btn_restart->setFixedSize(110, 50);
	m_btn_logout = new QPushButton("Sign Out", this);
	m_btn_logout->setFixedSize(110, 50);

	// WIN screen 
	m_label_win_lose = new QLabel(this);
	m_label_win_lose->setFixedSize(110, 180);
	m_label_win_lose->setAlignment(Qt::AlignCenter);
	m_label_win_lose->setTextFormat(Qt::PlainText);
	m_label_win_lose->setWordWrap(true);
	m_label_win_lose->setText("PLAY");  // default text
	m_label_win_lose->setStyleSheet(
		"QLabel {"
		" background-color: black;"
		" color: red;"
		" border: 2px solid grey;"
		" border-radius: 5px;"
		" font: bold 20px 'Courier New';"
		"}"
	);

	// bomb screen 
	m_label_bombcount = new QLabel(this);
	m_label_bombcount->setFixedSize(110, 50);
	m_label_bombcount->setAlignment(Qt::AlignCenter);
	m_label_bombcount->setText("0");  // default text
	m_label_bombcount->setStyleSheet(
		"QLabel {"
		" background-color: black;"
		" color: red;"
		" border: 2px solid grey;"
		" border-radius: 5px;"
		" font: bold 20px 'Courier New';"
		"}"
	);

	// clock screen
	m_label_clock = new QLabel(this);
	m_label_clock->setFixedSize(110, 50);
	m_label_clock->setAlignment(Qt::AlignCenter);
	m_label_clock->setText("00:00");  // default text
	m_label_clock->setStyleSheet(
		"QLabel {"
		" background-color: black;"
		" color: red;"
		" border: 2px solid grey;"
		" border-radius: 5px;"
		" font: bold 20px 'Courier New';"
		"}"
	);


	QHBoxLayout* layout_pause_sound = new QHBoxLayout();
	layout_pause_sound->addStretch();
	layout_pause_sound->addWidget(m_btn_pause_resume);
	layout_pause_sound->addSpacing(4);
	layout_pause_sound->addWidget(m_btn_sound);
	layout_pause_sound->addStretch();


	QVBoxLayout* layout_control_panel = new QVBoxLayout();
	//layout_control_panel->addStretch();
	layout_control_panel->addSpacing(20);
	layout_control_panel->addWidget(m_label_win_lose, 0, Qt::AlignHCenter);
	layout_control_panel->addSpacing(20);
	layout_control_panel->addWidget(m_label_bombcount, 0, Qt::AlignHCenter);
	layout_control_panel->addSpacing(20);
	layout_control_panel->addWidget(m_label_clock, 0, Qt::AlignHCenter);
	layout_control_panel->addLayout(layout_pause_sound);
	layout_control_panel->addSpacing(20);
	layout_control_panel->addWidget(m_btn_level, 0, Qt::AlignHCenter);
	layout_control_panel->addWidget(m_btn_restart, 0, Qt::AlignHCenter);
	layout_control_panel->addStretch();
	layout_control_panel->addWidget(m_btn_logout, 0, Qt::AlignHCenter);

	QWidget* container_buttons = new QWidget();
	container_buttons->setLayout(layout_control_panel);


	// SPLITTER
	m_split_screen = new QSplitter(Qt::Horizontal, m_central);
	m_split_screen->addWidget(gridHolder);
	m_split_screen->addWidget(container_buttons);/*
	m_split_screen->setStretchFactor(0, 1);
	m_split_screen->setStretchFactor(1, 1);*/
	//m_split_screen->setSizes({ 550, 200 });

	m_split_screen->setHandleWidth(2);
	m_split_screen->setStyleSheet(
		"QSplitter::handle {"
		"  background-color: #696969;"
		"  border: none;"
		"}"
	);

	QSplitterHandle* handle = m_split_screen->handle(1);
	if (handle)
	{
		handle->setEnabled(false);
		handle->setCursor(Qt::ArrowCursor);
	}

	// CENTRAL
	QVBoxLayout* wrapperLayout = new QVBoxLayout(m_central);
	wrapperLayout->addWidget(m_split_screen);
	m_central->setLayout(wrapperLayout);

	setCentralWidget(m_central);
	//setMinimumSize(900, 720);
	setFixedSize(900, 720);

	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, [=]() {
		int total = (m_paused_ms + m_elapsed.elapsed()) / 1000;
		int min = total / 60;
		int sec = total % 60;
		// Store formatted string
		m_str_time = QString("%1:%2")
			.arg(min, 2, 10, QChar('0'))
			.arg(sec, 2, 10, QChar('0'));
		// Display
		m_label_clock->setText(m_str_time);
		});


	connect(m_btn_pause_resume, &QPushButton::clicked, this, [=]() {
		if (m_is_playing) {
			m_timer->stop();
			m_paused_ms += m_elapsed.elapsed();  // store elapsed before pause
			m_btn_pause_resume->setIcon(m_icon_6_play);
			m_is_playing = false;
			disableAllGrid(true);
		}
		else {
			m_elapsed.restart();  // reset for resumed interval
			m_timer->start(1000);
			m_is_playing = true;
			m_btn_pause_resume->setIcon(m_icon_5_pause);
			disableAllGrid(false);
		}
		});

	m_revealTimer = new QTimer(this);
	m_revealTimer->setInterval(m_revealIntervalMs);
	connect(m_revealTimer, &QTimer::timeout, this, [=]() {
		if (m_revealIndex >= m_revealList.size()) {
			m_revealTimer->stop();
			disableAllGrid(false);          // allow input after reveal finishes
			return;
		}
		auto* b = m_revealList[m_revealIndex++];
		b->setVisible(true);                // show next tile
		b->update();
		});

	connect(m_btn_level, &QPushButton::clicked, this, [=]() {
		DialogLevel dlg(this);
		dlg.setWindowIcon(m_icon_8_level);
		// pass control
		dlg.setSoundControl(&m_is_sound, [=]() {
			m_player_4_click.stop();
			m_player_4_click.play();
			});
		if (dlg.exec() == QDialog::Accepted) {
			// get values from level dialog
			m_rows = dlg.setSize();
			m_cols = dlg.setSize();
			m_bomb_count = dlg.setBombCount();
			m_grid_size = dlg.setGridSize();


			QProgressDialog loading("Loading...", QString(), 0, m_rows * m_cols * 2, this);
			loading.setWindowTitle("Create Game Board");
			loading.setWindowModality(Qt::ApplicationModal);
			loading.setCancelButton(nullptr);
			loading.setMinimumDuration(0);
			loading.setAutoClose(false);
			loading.setAutoReset(false);
			//loading.setMaximum(10000);
			loading.setStyleSheet(
				"QProgressDialog { background-color: #222; color: white; font: bold 11px 'Courier New'; }"
				"QLabel { color: white; font: bold 15px 'Courier New'; }"
				"QProgressBar {"
				"  border: 1px solid #555;"
				"  border-radius: 5px;"
				"  text-align: center;"
				"  color: white;"
				"  background-color: #333;"
				"}"
				"QProgressBar::chunk {"
				"  background-color: #00cc66;"
				"  width: 20px;"
				"}"
			);

			loading.show();
			//qApp->processEvents();

			recreateGridWithProgress(&loading);
			initGame();
			loading.setValue(loading.maximum() - 1);
			loading.close();
			m_revealIndex = 0;
			m_revealTimer->start();

		}
		});
	connect(m_btn_restart, &QPushButton::clicked, this, &QtMiniGame::initGame);
	connect(m_btn_sound, &QPushButton::clicked, this, [=] {
		if (m_is_sound)
		{
			m_is_sound = false;
			m_btn_sound->setIcon(m_icon_7_sound_off);
			m_btn_sound->setIconSize(QSize(m_icon_pause_sound_wid, m_icon_pause_sound_wid));
		}
		else
		{
			m_is_sound = true;
			m_btn_sound->setIcon(m_icon_7_sound_on);
			m_btn_sound->setIconSize(QSize(m_icon_pause_sound_wid, m_icon_pause_sound_wid));
		}
		});

	// CLICK SOUND FOR NORMAL BUTTONS
	auto connectButtonClickSound = [&](QPushButton* btn) {
		connect(btn, &QPushButton::pressed, this, [=]() {
			if (m_is_sound) {
				m_player_4_click.stop();  // reset position
				m_player_4_click.play();  // play sound
			}
			});
		};
	auto connectButtonClickSoundAlways = [&](QPushButton* btn) {
		connect(btn, &QPushButton::pressed, this, [=]() {
			m_player_4_click.stop();  // reset position
			m_player_4_click.play();  // play sound
			});
		};

	connectButtonClickSound(m_btn_level);
	connectButtonClickSound(m_btn_restart);
	connectButtonClickSound(m_btn_logout);
	connectButtonClickSound(m_btn_pause_resume);
	connectButtonClickSoundAlways(m_btn_sound);
}

void QtMiniGame::initGame()
{
	this->grabMouse();
	m_count_revealed_btn = 0;
	m_timer->stop();
	m_elapsed.invalidate();          // clear old time
	m_label_clock->setText("00:00");

	m_label_bombcount->setText(QString("%1").arg(m_bomb_count));

	m_paused_ms = 0;
	m_is_playing = false;
	m_is_win = false;
	m_btn_pause_resume->setDisabled(true);
	// clear hover/pressed state from any button under cursor
	for (int r = 0; r < m_rows; ++r)
		for (int c = 0; c < m_cols; ++c)
		{
			QEvent leaveEvent(QEvent::Leave);
			QCoreApplication::sendEvent(m_buttons_grid[r][c], &leaveEvent);
		}
	// clear old button states
	for (int r = 0; r < m_rows; ++r)
		for (int c = 0; c < m_cols; ++c)
		{
			auto* btn = m_buttons_grid[r][c];
			btn->setIcon(QIcon());
			btn->setProperty("isRedFlag", false);
			btn->setProperty("isBomb", false);
			btn->setProperty("AdjacentBombCount", 0);
			btn->setProperty("hiddenIcon", QVariant());
			btn->setProperty("isNumber", false);
			btn->setProperty("isRevealed", false);
			btn->setAttribute(Qt::WA_TransparentForMouseEvents, false);
			btn->setStyleSheet(
				"QPushButton { background-color: #696969; border: 0.5px solid #222; border-radius: 0; }"
				"QPushButton:hover { background-color: #3e3e3e; }"
				"QPushButton:pressed { background-color: #222; }"
			);
			btn->repaint();
		}

	// regenerate bombs and icons
	setGridButtonsProperty(m_bomb_count);
	setGameIconSize();
	m_label_win_lose->setText("CLICK\nTO\nBEGIN");
	this->releaseMouse();
}


// SET BUTTON TO LAYOUT
void QtMiniGame::setButtonGridLayout()
{
	m_buttons_grid.resize(m_rows);
	for (int r = 0; r < m_rows; ++r) m_buttons_grid[r].resize(m_cols);

	for (int r = 0; r < m_rows; ++r) {
		for (int c = 0; c < m_cols; ++c) {
			QPushButtonRightClick* btn = new QPushButtonRightClick();
			m_layout_grid->addWidget(btn, r, c);  // row r, col c
			//m_buttons.push_back(btn);
			// add signal connections here
			connect(btn, &QPushButton::clicked, this, [=]() {
				onLeftClickGrid(r, c);
				});
			connect(btn, &QPushButtonRightClick::clickedRight, this, [=]() {
				onRightClickGrid(r, c);
				});
			m_buttons_grid[r][c] = btn;
		}
	}
}

void QtMiniGame::onLeftClickGrid(int row, int col)
{
	if (!m_buttons_grid[row][col]) return;
	if (m_buttons_grid[row][col]->property("isRedFlag").toBool()) return;
	if (!m_is_playing)
	{
		m_is_playing = true;
		m_elapsed.start();
		m_timer->start(1000);
		m_label_win_lose->setText("FOCUS");
	}
	if (!m_btn_pause_resume->isEnabled())
		m_btn_pause_resume->setDisabled(false);
	// Check if this button has a bomb
	bool isBomb = m_buttons_grid[row][col]->property("isBomb").toBool();
	if (isBomb) {
		if (m_is_sound) m_player_3_mine.play();
		m_label_win_lose->setText("BOOM");
		m_btn_pause_resume->setDisabled(true);

		m_timer->stop();
		m_is_playing = false;
		disableAllGrid(true);

		static QIcon blast(m_icon_4_blasting);
		m_buttons_grid[row][col]->setIcon(blast);
		m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid, m_icon_wid));
		m_buttons_grid[row][col]->setStyleSheet(
			"QPushButton { background-color: orange; border: 1px solid #222; }"
		);

		revealBomb(row, col);
	}
	else {
		if (m_is_sound) m_player_1_step.play();
		bool isNumber = m_buttons_grid[row][col]->property("isNumber").toBool();
		m_buttons_grid[row][col]->setProperty("isRevealed", true);
		m_count_revealed_btn++;

		if (isNumber)
		{
			QIcon icon = m_buttons_grid[row][col]->property("hiddenIcon").value<QIcon>();
			m_buttons_grid[row][col]->setIcon(icon);
			m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid_number, m_icon_wid_number));
			m_buttons_grid[row][col]->setStyleSheet(
				"QPushButton { background-color: #3e3e3e; border: 1px solid #222; }"
			);
		}
		else
		{
			m_buttons_grid[row][col]->setIcon(QIcon());
			m_buttons_grid[row][col]->setStyleSheet(
				"QPushButton { background-color: #3e3e3e; border: 1px solid #222; }"
			);
			QQueue<QPair<int, int>> blank_coords;
			blank_coords.enqueue({ row, col });
			expandClickedBreadthFirstSearch(blank_coords);
		}
	}

	m_buttons_grid[row][col]->setAttribute(Qt::WA_TransparentForMouseEvents);
	if (m_count_revealed_btn == m_number_revealed_btn) {
		QString msg = QString("YOU WASTED %1\nOF\nYOUR LIFE").arg(m_str_time);
		m_label_win_lose->setText(msg);
		m_timer->stop();
		m_is_playing = false;
		m_is_win = true;
		m_btn_pause_resume->setDisabled(true);
		m_label_bombcount->setText("0");
		m_label_clock->setText("WIN");
		revealBomb(row, col);
		disableAllGrid(true);
	}
}

void QtMiniGame::onRightClickGrid(int row, int col)
{
	if (!m_is_playing)
		return;

	if (m_buttons_grid[row][col]->icon().isNull())
	{
		if (m_is_sound)
			m_player_2_flag.play();
		m_player_2_flag.play();
		m_buttons_grid[row][col]->setIcon(m_icon_1_red_flag);
		m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid, m_icon_wid));
		m_buttons_grid[row][col]->setProperty("isRedFlag", true);
		int flagged = 0;
		for (auto& row : m_buttons_grid)
			for (auto* btn : row)
				if (btn->property("isRedFlag").toBool())
					flagged++;

		m_label_bombcount->setText(QString("%1").arg(m_bomb_count - flagged));

	}
	else
	{
		if (m_is_sound) m_player_2_flag.play();
		if (m_buttons_grid[row][col]->property("isRedFlag").toBool())
		{
			m_buttons_grid[row][col]->setIcon(m_icon_2_question_mark);
			m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid, m_icon_wid));
			m_buttons_grid[row][col]->setProperty("isRedFlag", false);
			int flagged = 0;
			for (auto& row : m_buttons_grid)
				for (auto* btn : row)
					if (btn->property("isRedFlag").toBool())
						flagged++;

			m_label_bombcount->setText(QString("%1").arg(m_bomb_count - flagged));

		}
		else
		{
			m_buttons_grid[row][col]->setIcon(QIcon());  // delete icon

		}
	}


}


void QtMiniGame::setGridButtonsProperty(int BombsCount)
{
	generateRandomBombs(BombsCount);
	int number_adjacent_bombs = 0;

	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			if (isBomb(r, c))
			{
				m_buttons_grid[r][c]->setProperty("AdjacentBombCount", -1); // mark as mine
				continue;
			}

			number_adjacent_bombs = countAdjacentBombs(r, c);
			if (number_adjacent_bombs > 0)
			{
				QIcon icon = chooseHiddenIconNumber(number_adjacent_bombs);
				m_buttons_grid[r][c]->setProperty("hiddenIcon", icon);
				m_buttons_grid[r][c]->setProperty("isNumber", true);
			}
		}
	}
}

int QtMiniGame::countAdjacentBombs(int row, int col)
{
	int count = 0;
	for (int ir = -1; ir <= 1; ir++) // ir = interval row
		for (int ic = -1; ic <= 1; ic++) // ic = interval column
		{
			if (ic == 0 && ir == 0) continue;
			int adr = row + ir, adc = col + ic; // adjacent row, column
			if (adr >= 0 && adr < m_rows && adc >= 0 && adc < m_cols)
				if (isBomb(adr, adc))
					count++;
		}
	return count;
}

QIcon QtMiniGame::chooseHiddenIconNumber(int number)
{
	switch (number)
	{
	case 1: return m_icon_number_1;
	case 2: return m_icon_number_2;
	case 3: return m_icon_number_3;
	case 4: return m_icon_number_4;
	case 5: return m_icon_number_5;
	case 6: return m_icon_number_6;
	case 7: return m_icon_number_7;
	case 8: return m_icon_number_8;
	default: return QIcon(); // 0 or invalid
	}
}


void QtMiniGame::generateRandomBombs(int bombCount)
{
	if (!m_bombs_coords.isEmpty())
		m_bombs_coords.clear();

	QVector<QPair<int, int>> all;
	for (int r = 0; r < m_rows; ++r)
		for (int c = 0; c < m_cols; ++c)
			all.append({ r, c });

	std::shuffle(all.begin(), all.end(), std::mt19937(std::random_device{}()));

	for (int i = 0; i < bombCount; ++i) {
		auto [r, c] = all[i];
		m_buttons_grid[r][c]->setProperty("isBomb", true);
		m_bombs_coords.append({ r, c }); // save bomb coords only
	}
}

bool QtMiniGame::isBomb(int row, int col)
{
	return m_buttons_grid[row][col]->property("isBomb").toBool();
}


void QtMiniGame::expandClickedBreadthFirstSearch(QQueue<QPair<int, int>>& blank_coords)
{
	while (!blank_coords.isEmpty())
	{
		auto [row, col] = blank_coords.dequeue();
		if (!m_buttons_grid[row][col]->property("isRevealed").toBool()) {
			m_buttons_grid[row][col]->setProperty("isRevealed", true);
			m_count_revealed_btn++;
		}
		for (int ir = -1; ir <= 1; ++ir)
		{
			for (int ic = -1; ic <= 1; ++ic)
			{
				int adr = row + ir, adc = col + ic;
				if (adr == row && adc == col) continue;
				if (adr >= 0 && adr < m_rows && adc >= 0 && adc < m_cols)
				{
					if (m_buttons_grid[adr][adc]->property("isRevealed").toBool())
						continue;
					m_buttons_grid[adr][adc]->setProperty("isRevealed", true);
					m_count_revealed_btn++;
					if (m_buttons_grid[adr][adc]->property("isNumber").toBool())
					{
						QIcon icon = m_buttons_grid[adr][adc]->property("hiddenIcon").value<QIcon>();
						m_buttons_grid[adr][adc]->setIcon(icon);
						m_buttons_grid[adr][adc]->setIconSize(QSize(m_icon_wid_number, m_icon_wid_number));
						m_buttons_grid[adr][adc]->setStyleSheet(
							"QPushButton { background-color: #3e3e3e; border: 1px solid #222; }"
						);
						m_buttons_grid[adr][adc]->setAttribute(Qt::WA_TransparentForMouseEvents);
					}
					else
					{
						m_buttons_grid[adr][adc]->setStyleSheet(
							"QPushButton { background-color: #3e3e3e; border: 1px solid #222; }"
						);
						m_buttons_grid[adr][adc]->setAttribute(Qt::WA_TransparentForMouseEvents);
						blank_coords.enqueue({ adr, adc });
					}
				}
			}
		}

		// Force the UI to repaint during the loop
		m_buttons_grid[row][col]->repaint();
	}
}

void QtMiniGame::revealBomb(int row, int col)
{
	int r = 0, c = 0;
	for (int i = 0; i < m_bomb_count; i++)
	{
		r = m_bombs_coords[i].first;
		c = m_bombs_coords[i].second;
		if (r == row && c == col) continue;
		m_buttons_grid[r][c]->setIcon(m_icon_3_mine);
		m_buttons_grid[r][c]->setIconSize(QSize(m_icon_wid, m_icon_wid));
		if (m_buttons_grid[r][c]->property("isRedFlag").toBool() || m_is_win == true)
			m_buttons_grid[r][c]->setStyleSheet(
				"QPushButton { background-color: #2D68C4; border: 1px solid #222; }"
			);
		else
			m_buttons_grid[r][c]->setStyleSheet(
				"QPushButton { background-color: red; border: 1px solid #222; }"
			);
		m_buttons_grid[r][c]->setAttribute(Qt::WA_TransparentForMouseEvents);
		m_buttons_grid[r][c]->repaint();
	}
}

void QtMiniGame::disableAllGrid(bool status)
{
	for (auto& btn : m_buttons_grid)
		for (auto* b : btn)
			b->setAttribute(Qt::WA_TransparentForMouseEvents, status);
}

void QtMiniGame::setGameIconSize()
{
	m_icon_wid = m_buttons_grid[0][0]->width() * 0.85;
	m_icon_wid_number = m_buttons_grid[0][0]->width() * 0.65;
	m_number_revealed_btn = (m_rows * m_cols) - m_bomb_count;
}

void QtMiniGame::setFixGridButtonsSize()
{
	if (m_rows == 0 || m_cols == 0) return;

	int tile = m_grid_size / std::min(m_rows, m_cols);

	for (auto& row : m_buttons_grid)
		for (auto* b : row) {
			b->setFixedSize(tile, tile);
			b->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		}

	m_layout_grid->setSizeConstraint(QLayout::SetFixedSize);
}

void QtMiniGame::recreateGridWithProgress(QProgressDialog* progress)
{
	// freeze painting
	this->setUpdatesEnabled(false);
	disableAllGrid(true);            // block input during rebuild

	// clear old grid
	QLayoutItem* item;
	while ((item = m_layout_grid->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}
	m_buttons_grid.clear();
	m_revealList.clear();
	m_revealIndex = 0;

	// progress range = total cells
	const int total = m_rows * m_cols;
	if (progress) progress->setRange(0, total);

	// create new grid invisibly
	m_buttons_grid.resize(m_rows);
	int made = 0;
	for (int r = 0; r < m_rows; ++r) {
		m_buttons_grid[r].resize(m_cols);
		for (int c = 0; c < m_cols; ++c) {
			auto* btn = new QPushButtonRightClick();
			btn->setVisible(false);                     // keep hidden
			m_layout_grid->addWidget(btn, r, c);

			connect(btn, &QPushButton::clicked, this, [=]() { onLeftClickGrid(r, c); });
			connect(btn, &QPushButtonRightClick::clickedRight, this, [=]() { onRightClickGrid(r, c); });

			m_buttons_grid[r][c] = btn;
			m_revealList.push_back(btn);                // order to reveal

			// update progress per button
			if (progress) {
				progress->setValue(++made);
				QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
			}
		}
	}

	setFixGridButtonsSize();
	setGameIconSize();

	// unfreeze painting
	this->setUpdatesEnabled(true);
	this->update();                                      // layout recalculated

	// progress dialog closes in caller; we start reveal afterward
}

QtMiniGame::~QtMiniGame()
{
}

