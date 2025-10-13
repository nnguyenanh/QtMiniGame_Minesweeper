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

}

// SET WIDGET LAYOUT
void QtMiniGame::setCentralWidgetandGridLayout()
{
    // create a container for grid layout
    m_central = new QWidget();
    // align grid and button
    m_layout_h = new QHBoxLayout();
    // create a grid layout
    m_grid_layout = new QGridLayout();
    m_grid_layout->setSpacing(0); // no space between cells

    QWidget* container_grid = new QWidget();
    container_grid->setLayout(m_grid_layout);
    container_grid->setFixedSize(550, 550);
    m_layout_h->addWidget(container_grid, 1);

    // align buttons
    m_layout_v = new QVBoxLayout();
        // function button 
    m_label_win_lose = new QLabel("CLICK TO START");
    m_label_win_lose->setAlignment(Qt::AlignCenter);
    
    m_label_score = new QLabel("BOMB: 0");
    m_label_score->setAlignment(Qt::AlignCenter);
    
    m_btn_new = new QPushButton(QString("New Game"));
    m_btn_new->setFixedSize(100, 50);

    m_btn_restart = new QPushButton(QString("Restart"));
    m_btn_restart->setFixedSize(100, 50);

    m_btn_back = new QPushButton(QString("Back"));
    m_btn_back->setFixedSize(100, 50);

    //m_layout_v->addWidget(m_label_win_lose, 0, Qt::AlignHCenter | Qt::AlignTop);
    m_layout_v->addWidget(m_label_win_lose);
    m_layout_v->addWidget(m_label_score);
    m_layout_v->addWidget(m_btn_new);
    m_layout_v->addWidget(m_btn_restart);
    m_layout_v->addWidget(m_btn_back);

    QWidget* container_buttons = new QWidget();
    container_buttons->setLayout(m_layout_v);
    m_layout_h->addWidget(container_buttons);
  

    // set layout to widget container
    m_central->setLayout(m_layout_h);
    // Parent-Child ownership:
    // m_central use 'this' because it is belong to the widget
    // m_grid use 'm_central' because it belongs to m_central
    setFixedSize(700, 620);

    // wrapper widget + layout
    QWidget* wrapper = new QWidget(this);
    QVBoxLayout* wrapperLayout = new QVBoxLayout(wrapper);
    wrapperLayout->addWidget(m_central, 0, Qt::AlignCenter);
    // tell QMainWindow to use it as central area
    setCentralWidget(wrapper);
}

// SET BUTTON TO LAYOUT
void QtMiniGame::setButtonGridLayout()
{
    int row = std::sqrt(m_button_level);
    int col = row;
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            QPushButtonRightClick* btn = new QPushButtonRightClick();
            m_grid_layout->addWidget(btn, r, c);  // row r, col c
            m_buttons.push_back(btn);
        }
    }
}



QtMiniGame::~QtMiniGame()
{}

