#pragma once
// Right click for button
//https://stackoverflow.com/questions/15658464/qt-rightclick-qpushbutton

#include <QtWidgets/QMainWindow>
#include "ui_QtMiniGame.h"
#include "QPushButtonRightClick.h"
//#include "QPushButtonStyled.h"
//#include "QLabelStyled.h"
#include "DialogLevel.h"


//#include <cmath>   // for std::sqrt


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
    QWidget* m_central = nullptr; // 

    QSplitter* m_split_screen = nullptr;
    QVBoxLayout* m_wrapper_align = nullptr;

    // layouts for alignment
    QVBoxLayout* m_layout_v = nullptr;
    QHBoxLayout* m_layout_main = nullptr;
    QGridLayout* m_layout_grid = nullptr; // manage row col
    QGridLayout* m_grid_layout = nullptr; // manage row col


    // function buttons
    QLabel* m_label_win_lose = nullptr;
    QLabel* m_label_bombcount = nullptr;

    QPushButton* m_btn_level = nullptr;
    QPushButton* m_btn_restart = nullptr;

    QPushButton* m_btn_logout = nullptr;
    
    
    
    int m_button_level = 100; // for level
    int m_rows = 25;
    int m_cols = 25;
    int m_bomb_count = 120;
    QVector<QPair<int, int>> m_bombs_coords;
    //QVector<QPushButtonRightClick*> m_buttons; // for buttons

    QVector<QVector<QPushButtonRightClick*>> m_buttons_grid; // for buttons

    int m_icon_wid_number = 0;
    int m_icon_wid = 0;

public:
    void setCentralWidgetandGridLayout();
    void setButtonGridLayout();
    void setGameIconSize();

    void setGridButtonsProperty(int BombsCount);
    int countAdjacentBombs(int row, int col);
    QString chooseHiddenIconNumber(int number);
    //void setClickedButtonIcon(int row, int col, int wid);

    void generateRandomBombs(int BombsCount);
    bool isBomb(int row, int col);

    
    void expandClickedBreadthFirstSearch(QQueue<QPair<int, int>>& blank_coords);


//private slots:
private slots:
    void onLeftClickGrid(int row, int col);
    void onRightClickGrid(int row, int col);
    void initGame();

};

