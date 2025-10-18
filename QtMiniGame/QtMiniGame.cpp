#include "stdafx.h"
#include "QtMiniGame.h"

QtMiniGame::QtMiniGame(QWidget *parent)
    : QMainWindow(parent)
{
    // DEFAULT Qt .ui
    ui.setupUi(this);

    // USER DEFINED 
    
    // Set central widget and grid layout
    setCentralWidgetandGridLayout();
    // Set buttons to layout
    setButtonGridLayout();
    initGame(m_bomb_count);

    QTimer::singleShot(0, this, [this]() {
        setGameIconSize();   // calculate icon width right after constructor done
        });
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
    container_grid->setFixedSize(550, 550); 

    QWidget* gridHolder = new QWidget();    
    QVBoxLayout* gridLayout = new QVBoxLayout(gridHolder);
    gridLayout->addStretch();
    gridLayout->addWidget(container_grid, 0, Qt::AlignCenter);
    gridLayout->addStretch();

    // === BUTTONS ===
    m_label_win_lose = new QLabel("CLICK TO START");
    m_label_win_lose->setAlignment(Qt::AlignCenter);
    m_label_score = new QLabel("BOMB: 0");
    m_label_score->setAlignment(Qt::AlignCenter);

    m_btn_easy = new QPushButton("Easy");
    m_btn_easy->setFixedSize(100, 50);
    m_btn_medium = new QPushButton("Medium");
    m_btn_medium->setFixedSize(100, 50);
    m_btn_hard = new QPushButton("Hard");
    m_btn_hard->setFixedSize(100, 50);
    m_btn_custom = new QPushButton("Custom");
    m_btn_custom->setFixedSize(100, 50);


    m_btn_new = new QPushButton("New Game");
    m_btn_new->setFixedSize(100, 50);

    m_btn_logout = new QPushButton("Log out");
    m_btn_logout->setFixedSize(100, 50);

    m_layout_v = new QVBoxLayout();
    m_layout_v->addStretch();
    m_layout_v->addWidget(m_label_win_lose, 0, Qt::AlignHCenter);
    m_layout_v->addSpacing(20);
    m_layout_v->addWidget(m_label_score, 0, Qt::AlignHCenter);
    m_layout_v->addSpacing(30);
    m_layout_v->addWidget(m_btn_easy, 0, Qt::AlignHCenter);
    m_layout_v->addWidget(m_btn_medium, 0, Qt::AlignHCenter);
    m_layout_v->addWidget(m_btn_hard, 0, Qt::AlignHCenter);
    m_layout_v->addWidget(m_btn_custom, 0, Qt::AlignHCenter);
    m_layout_v->addWidget(m_btn_new, 0, Qt::AlignHCenter);
    m_layout_v->addStretch();
    m_layout_v->addWidget(m_btn_logout, 0, Qt::AlignHCenter);

    QWidget* container_buttons = new QWidget();
    container_buttons->setLayout(m_layout_v);

    // === SPLITTER ===
    m_split_screen = new QSplitter(Qt::Horizontal, m_central);
    m_split_screen->addWidget(gridHolder);        
    m_split_screen->addWidget(container_buttons);
    m_split_screen->setStretchFactor(0, 1);      
    m_split_screen->setStretchFactor(1, 1);
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

    // === CENTRAL ===
    QVBoxLayout* wrapperLayout = new QVBoxLayout(m_central);
    wrapperLayout->addWidget(m_split_screen);
    m_central->setLayout(wrapperLayout);

    setCentralWidget(m_central);
    setMinimumSize(900, 700);
}

void QtMiniGame::initGame(int bombCount)
{
    // initialize buttons attributes
    // clear old properties
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
        {
            auto* btn = m_buttons_grid[r][c];
            btn->setIcon(QIcon());
            btn->setProperty("isBomb", false);
            btn->setProperty("AdjacentBombCount", 0);
            btn->setProperty("hiddenIcon", QVariant());
        }

    // generate bombs and assign numbers/icons
    setGridButtonsProperty(bombCount);
    setGameIconSize();

    m_label_win_lose->setText("CLICK TO START");
    m_label_win_lose->setText("PLAY");
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

    // Check if this button has a bomb
    bool isBomb = m_buttons_grid[row][col]->property("isBomb").toBool();
    if (isBomb) {
        static QIcon blast(":/QtMiniGame/icons/icon_4_blasting.ico");
        m_buttons_grid[row][col]->setIcon(blast);
        m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid, m_icon_wid));
        m_buttons_grid[row][col]->setStyleSheet(
            "QPushButton { background-color: orange; border: 1px solid #222; }"
        );

        static QIcon bomb(":/QtMiniGame/icons/icon_3_mine.ico");
        int r = 0, c = 0;
        for (int i = 0; i < m_bomb_count; i++)
        {
            r = m_bombs_coords[i].first;
            c = m_bombs_coords[i].second;
            if (r == row && c == col) continue;
            m_buttons_grid[r][c]->setIcon(bomb);
            m_buttons_grid[r][c]->setIconSize(QSize(m_icon_wid, m_icon_wid));
            m_buttons_grid[r][c]->setStyleSheet(
                "QPushButton { background-color: red; border: 1px solid #222; }"
            );
            m_buttons_grid[r][c]->setAttribute(Qt::WA_TransparentForMouseEvents);
        }
    }
    else {
        bool isNumber = m_buttons_grid[row][col]->property("isNumber").toBool();
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
            m_buttons_grid[row][col]->setStyleSheet(
                "QPushButton { background-color: #3e3e3e; border: 1px solid #222; }"
            );
            QQueue<QPair<int, int>> blank_coords;
            blank_coords.enqueue({ row, col });
            expandClickedBreadthFirstSearch(blank_coords);
        }
    }

    m_buttons_grid[row][col]->setAttribute(Qt::WA_TransparentForMouseEvents);
}


void QtMiniGame::onRightClickGrid(int row, int col)
{
    // handle flag marking logic
    static QIcon red_flag(":/QtMiniGame/icons/icon_1_red_flag.ico");
    static QIcon question_mark(":/QtMiniGame/icons/icon_2_question_mark.ico");
    

    if (m_buttons_grid[row][col]->icon().isNull())
    {
        m_buttons_grid[row][col]->setIcon(red_flag);
        m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid, m_icon_wid));
        m_buttons_grid[row][col]->setProperty("is_red_flag", true);
    }
    else
    {
        if (m_buttons_grid[row][col]->property("is_red_flag").toBool())
        {
            m_buttons_grid[row][col]->setIcon(question_mark);
            m_buttons_grid[row][col]->setIconSize(QSize(m_icon_wid, m_icon_wid));
            m_buttons_grid[row][col]->setProperty("is_red_flag", false);
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
                QString iconPath = chooseHiddenIconNumber(number_adjacent_bombs);
                m_buttons_grid[r][c]->setProperty("hiddenIcon", QIcon(iconPath));
                m_buttons_grid[r][c]->setProperty("isNumber", true);
            }
            //if (!iconPath.isEmpty())
            //{
            //    QIcon icon(iconPath);
            //    m_buttons_grid[r][c]->setProperty("hiddenIcon", icon);

            //    // === DEBUG DISPLAY ===
            //    m_buttons_grid[r][c]->setIcon(icon);
            //    m_buttons_grid[r][c]->setIconSize(QSize(m_icon_wid, m_icon_wid));
            //    // remove the two lines above after testing
            //    // === END DEBUG ===
            //}
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

QString QtMiniGame::chooseHiddenIconNumber(int number)
{
    switch (number)
    {
    case 1: return ":/QtMiniGame/icons/number_1.ico";
    case 2: return ":/QtMiniGame/icons/number_2.ico";
    case 3: return ":/QtMiniGame/icons/number_3.ico";
    case 4: return ":/QtMiniGame/icons/number_4.ico";
    case 5: return ":/QtMiniGame/icons/number_5.ico";
    case 6: return ":/QtMiniGame/icons/number_6.ico";
    case 7: return ":/QtMiniGame/icons/number_7.ico";
    case 8: return ":/QtMiniGame/icons/number_8.ico";
    default: return ""; // 0 or invalid
    }
}


void QtMiniGame::generateRandomBombs(int bombCount)
{
    //QVector<int> indices(m_button_level);
    //std::iota(indices.begin(), indices.end(), 0);
    //std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device{}()));

    //for (int i = 0; i < bombCount; i++)
    //{
    //    int idx = indices[i]; // use shuffled index
    //    //m_buttons[idx]->setProperty("isBomb", true);
    //    m_buttons[i]->setProperty("isBomb", true);
    //    // during setup or bomb generation

    //    m_buttons[i]->setProperty("hiddenIcon", QIcon(":/icons/icon_3_mine.ico"));

    //}

    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            m_bombs_coords.append({ r, c });

    std::shuffle(m_bombs_coords.begin(), m_bombs_coords.end(), std::mt19937(std::random_device{}()));

    for (int i = 0; i < bombCount; ++i)
    {
        int r = m_bombs_coords[i].first;
        int c = m_bombs_coords[i].second;
        m_buttons_grid[r][c]->setProperty("isBomb", true);
        //m_buttons_grid[r][c]->setProperty("hiddenIcon", QIcon(":/QtMiniGame/icons/icon_3_mine.ico"));
        //QIcon icon = m_buttons_grid[r][c]->property("hiddenIcon").value<QIcon>();
        //m_buttons_grid[r][c]->setIcon(icon);
        //m_buttons_grid[r][c]->setIconSize(QSize(m_icon_wid, m_icon_wid));
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
        m_buttons_grid[row][col]->setProperty("isRevealed", true);
        for (int ir = -1; ir <= 1; ir++)
        {
            for (int ic = -1; ic <= 1; ic++)
            {
                int adr = row + ir, adc = col + ic;
                if (adr == row && adc == col) continue;
                if (adr >= 0 && adr < m_rows && adc >= 0 && adc < m_cols)
                {
                    if (m_buttons_grid[adr][adc]->property("isRevealed").toBool()) continue;
                    else m_buttons_grid[adr][adc]->setProperty("isRevealed", true);

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
                        blank_coords.enqueue({ adr , adc });
                    }

                }
            }
        }
    }
}


void QtMiniGame::setGameIconSize()
{
    m_icon_wid = m_buttons_grid[0][0]->width() * 0.85;
    m_icon_wid_number = m_buttons_grid[0][0]->width() * 0.65;
}


QtMiniGame::~QtMiniGame()
{}

