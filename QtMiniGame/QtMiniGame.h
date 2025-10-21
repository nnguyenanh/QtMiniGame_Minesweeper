#pragma once
// Right click for button
//https://stackoverflow.com/questions/15658464/qt-rightclick-qpushbutton

#include <QtWidgets/QMainWindow>
#include "ui_QtMiniGame.h"
#include "QPushButtonRightClick.h"
#include "DialogLevel.h"
#include <QMediaPlayer>
#include <QAudioOutput>


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
    bool m_is_sound = false;
    qint64 m_paused_ms = 15;
    QString m_str_time = "00:00";


    // reveal sequence
    QTimer* m_reveal_timer = nullptr;
    QVector<QPushButton*> m_reveal_list;
    int m_reveal_index = 0;
    int m_reveal_iterval_ms = 1; // tweak for speed


    // QIcon 
    QIcon m_icon_1_red_flag;
    QIcon m_icon_2_question_mark;
    QIcon m_icon_3_mine;
    QIcon m_icon_4_blasting;
    QIcon m_icon_5_pause;
    QIcon m_icon_6_play;
    QIcon m_icon_7_sound_off;
    QIcon m_icon_7_sound_on;
    QIcon m_icon_8_level;

    QIcon m_icon_number_1;
    QIcon m_icon_number_2;
    QIcon m_icon_number_3;
    QIcon m_icon_number_4;
    QIcon m_icon_number_5;
    QIcon m_icon_number_6;
    QIcon m_icon_number_7;
    QIcon m_icon_number_8;

    // QSoundEffect
    QMediaPlayer m_player_1_step;
    QAudioOutput m_audio_1_step;

    QMediaPlayer m_player_2_flag;
    QAudioOutput m_audio_2_flag;

    QMediaPlayer m_player_3_mine;
    QAudioOutput m_audio_3_mine;

    QMediaPlayer m_player_4_click;
    QAudioOutput m_audio_4_click;

    QMediaPlayer m_player_5_win;
    QAudioOutput m_audio_5_win;

    QMediaPlayer m_player_6_reload;
    QAudioOutput m_audio_6_reload;


public:
    void setCentralWidgetandGridLayout();
    void setButtonGridLayout();
    void setGameIconSize();

    void setGridButtonsProperty(int BombsCount);
    int countAdjacentBombs(int row, int col);
    QIcon chooseHiddenIconNumber(int number);
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


signals:
    void revealFinished();


};

