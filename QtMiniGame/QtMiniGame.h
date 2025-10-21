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

    int m_grid_size = 550;
    QSplitter* m_split_screen = nullptr;
    QVBoxLayout* m_wrapper_align = nullptr;

    // layouts for alignment
    QHBoxLayout* m_layout_main = nullptr;
    QGridLayout* m_layout_grid = nullptr; // manage row col
    QGridLayout* m_grid_layout = nullptr; // manage row col


    // function buttons
    QLabel* m_label_win_lose = nullptr;
    QLabel* m_label_bombcount = nullptr;
    QTimer* m_timer;
    QElapsedTimer m_elapsed;
    QLabel* m_label_clock = nullptr;

    QPushButton* m_btn_pause_resume = nullptr;
    QPushButton* m_btn_sound = nullptr;
    QPushButton* m_btn_level = nullptr;
    QPushButton* m_btn_restart = nullptr;
    QPushButton* m_btn_logout = nullptr;
    
    
    
    int m_rows = 10;
    int m_cols = 10;
    int m_bomb_count = 15;
    QVector<QPair<int, int>> m_bombs_coords;
    //QVector<QPushButtonRightClick*> m_buttons; // for buttons

    QVector<QVector<QPushButtonRightClick*>> m_buttons_grid; // for buttons

    int m_icon_wid_number = 0;
    int m_icon_wid = 0;
    int m_icon_pause_sound_wid = 25;
    int m_number_revealed_btn = 0;
    int m_count_revealed_btn = 0;
    bool m_is_win = false;
    bool m_is_playing = false;
    qint64 m_paused_ms = 0;


    // reveal sequence
    QTimer* m_revealTimer = nullptr;
    QVector<QPushButton*> m_revealList;
    int m_revealIndex = 0;
    int m_revealIntervalMs = 0; // tweak for speed


protected:
    //void showEvent(QShowEvent* e) override;


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

    void disableAllGrid(bool status=false);
    void setFixGridButtonsSize();

    void revealBomb(int row, int col);
    void recreateGridWithProgress(QProgressDialog* progress);

//private slots:
private slots:
    void onLeftClickGrid(int row, int col);
    void onRightClickGrid(int row, int col);
    void initGame();

};

