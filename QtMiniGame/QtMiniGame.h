#pragma once
// Right click for button
//https://stackoverflow.com/questions/15658464/qt-rightclick-qpushbutton

#include <QtWidgets/QMainWindow>
#include "ui_QtMiniGame.h"
#include "QPushButtonRightClick.h"

#include <cmath>   // for std::sqrt


class QtMiniGame : public QMainWindow
{
    Q_OBJECT

public:
    QtMiniGame(QWidget *parent = nullptr);
    ~QtMiniGame();

private:
    Ui::QtMiniGameClass ui;

// USER DEFINE MEMBER VARIABLES AND MEMBER FUNCTION
private:
    QWidget* m_central = nullptr; // container
    QVBoxLayout* m_wrapper_align = nullptr;

    // layouts for alignment
    QVBoxLayout* m_layout_v = nullptr;
    QHBoxLayout* m_layout_h = nullptr;

    // function buttons
    QLabel* m_label_win_lose = nullptr;
    QLabel* m_label_score = nullptr;
    QPushButton* m_btn_new = nullptr;
    QPushButton* m_btn_restart = nullptr;
    QPushButton* m_btn_back = nullptr;
    
    
    QGridLayout* m_grid_layout = nullptr; // manage row col
    
    int m_button_level = 100;
    QVector<QPushButtonRightClick*> m_buttons; // for buttons


public:
    void setCentralWidgetandGridLayout();
    void setButtonGridLayout();
};

