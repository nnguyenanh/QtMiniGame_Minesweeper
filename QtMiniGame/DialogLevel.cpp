#include "stdafx.h"
#include "DialogLevel.h"
#include "ui_DialogLevel.h"

DialogLevel::DialogLevel(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::DialogLevel)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/QtMiniGame/icons/icon_8_level.ico"));
    setFont(QFont("Courier New", 11, QFont::Bold));
    setWindowTitle("Level");
    setFixedSize(320, 380);

    //connect(ui->okButton, &QPushButton::clicked, this, &DialogLevel::accept);

    // Style Apply
    ui->okButton->setFixedSize(110, 50);
    ui->okButton->setText("Apply");


    // LABEL
    QLabel* title = new QLabel("Choose difficulty:");

    // RADIO BUTTONS
    m_easy   = new QRadioButton("[ EASY ]   (10|12)");
    m_medium = new QRadioButton("[MEDIUM]   (16|40)");
    m_hard   = new QRadioButton("[ HARD ]   (22|99)");
    m_custom = new QRadioButton("[CUSTOM]   (??|??)");

    // GROUP
    m_group = new QButtonGroup(this);
    m_group->addButton(m_easy);
    m_group->addButton(m_medium);
    m_group->addButton(m_hard);
    m_group->addButton(m_custom);
    m_easy->setChecked(true);

    // EDIT 
    m_edit_size = new QLineEdit();
    m_edit_size->setFixedWidth(60);
    m_edit_size->setPlaceholderText("size");
    m_edit_bombcount = new QLineEdit();
    m_edit_bombcount->setFixedWidth(60);
    m_edit_bombcount->setPlaceholderText("mine");


    // LAYOUT
    QVBoxLayout* layout_emh = new QVBoxLayout();
    layout_emh->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
    //layout_emh->setSpacing(5);
    layout_emh->addWidget(m_easy);
    layout_emh->addWidget(m_medium);
    layout_emh->addWidget(m_hard);

    QVBoxLayout* layout_cus = new QVBoxLayout();
    QVBoxLayout* layout_c = new QVBoxLayout();
    layout_c->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout_c->setContentsMargins(0, 0, 0, 15);
    layout_c->addWidget(m_custom);

    layout_cus->addLayout(layout_c);


    QLabel* label_enter = new QLabel("Enter:");
    QHBoxLayout* layout_edit = new QHBoxLayout();
    layout_edit->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout_edit->addStretch();
    layout_edit->addWidget(label_enter);
    layout_edit->addWidget(m_edit_size);
    layout_edit->addWidget(m_edit_bombcount);
    layout_edit->addStretch();

    QLabel* label_note = new QLabel("\NOTE:\n- Maximum (35|1224)\n- Minimum (05|24)\n- (total cells) > (mine) > 0.");
    label_note->setFont(QFont("Courier New", 11, QFont::Normal, true));
    QHBoxLayout* layout_note = new QHBoxLayout();
    label_note->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout_note->addStretch();
    layout_note->addWidget(label_note);
    layout_note->addStretch();


    layout_cus->addLayout(layout_edit);
    layout_cus->addSpacing(10);
    layout_cus->addLayout(layout_note);

    QHBoxLayout* layout_cus_center = new QHBoxLayout();
    layout_cus_center->addStretch();
    layout_cus_center->addLayout(layout_cus);
    layout_cus_center->addStretch();

    QHBoxLayout* layout_button = new QHBoxLayout();
    layout_button->addStretch();              
    layout_button->addWidget(ui->okButton);
    layout_button->addStretch();             

    QVBoxLayout* layout_main = new QVBoxLayout();
    layout_main->addLayout(layout_emh);
    layout_main->addSpacing(10);     
    layout_main->addWidget(makeLine());
    layout_main->addSpacing(10);   

    layout_main->addLayout(layout_cus_center);
    layout_main->addSpacing(10);      
    layout_main->addWidget(makeLine());
    layout_main->addSpacing(10);  

    layout_main->addLayout(layout_button);
    //layout_main->setSpacing(5);      
    layout_main->setContentsMargins(20, 0, 20, 20);



    setLayout(layout_main);

    // disable input at first
    m_edit_size->setEnabled(false);
    m_edit_bombcount->setEnabled(false);

    // if CUSTOM selected -> enable inputs
    connect(m_custom, &QRadioButton::toggled, this, [=]() {
        m_edit_size->setEnabled(true);
        m_edit_bombcount->setEnabled(true);
        });

    // if other radio buttons selected disable inputs
    connect(m_easy, &QRadioButton::toggled, this, [=]() {
        m_edit_size->setEnabled(false);
        m_edit_bombcount->setEnabled(false);
        });
    connect(m_medium, &QRadioButton::toggled, this, [=]() {
        m_edit_size->setEnabled(false);
        m_edit_bombcount->setEnabled(false);
        });
    connect(m_hard, &QRadioButton::toggled, this, [=]() {
        m_edit_size->setEnabled(false);
        m_edit_bombcount->setEnabled(false);
        });
    connect(ui->okButton, &QPushButton::pressed, this, [=]() {
        if (m_ptr_is_sound && *m_ptr_is_sound && m_playClickSound)
            m_playClickSound();
        });

    // SOUND
    auto connectRadioClickSound = [&](QAbstractButton* btn) {
        connect(btn, &QAbstractButton::pressed, this, [=]() {
            if (m_ptr_is_sound && *m_ptr_is_sound && m_playClickSound)
                m_playClickSound();
            });
        };

    connectRadioClickSound(m_easy);
    connectRadioClickSound(m_medium);
    connectRadioClickSound(m_hard);
    connectRadioClickSound(m_custom);
}


int DialogLevel::setSize() const {
    if (m_easy->isChecked()) return 10;
    if (m_medium->isChecked()) return 16;
    if (m_hard->isChecked()) return 22;
    if (m_custom->isChecked())
        return m_edit_size->text().toInt();
    return 10;
}

int DialogLevel::setBombCount() const {
    if (m_easy->isChecked()) return 12;
    if (m_medium->isChecked()) return 40;
    if (m_hard->isChecked()) return 99;
    if (m_custom->isChecked())
        return m_edit_bombcount->text().toInt();
    return 15;
}

int DialogLevel::setGridSize() const {
    if (m_easy->isChecked()) return 550;
    if (m_medium->isChecked()) return 600;
    if (m_hard->isChecked()) return 650;
    if (m_custom->isChecked())
    {
        int n = m_edit_size->text().toInt();
        if (n < 15) return 550;
        else if (n < 25) return 600;
        else return 650;
    }
    return 550;
}

void DialogLevel::accept()
{
    if (m_custom->isChecked()) {
        bool check_size, check_mine;
        int size = m_edit_size->text().toInt(&check_size);
        int bombs = m_edit_bombcount->text().toInt(&check_mine);

        QStringList errors;

        if (!check_size || !check_mine)
            errors << "Inputs must be integers.";
        if (check_size && (size < 5 || size > 35))
            errors << "Size must be between 5 and 35.";
        if (check_mine && (bombs < 1 || bombs >= size * size))
            errors << "Mines must be:\n- At least 1.\n- Less than total cells.";

        if (!errors.isEmpty()) {
            QMessageBox::critical(this, "ERROR", errors.join("\n"));
            return;
        }
    }

    QDialog::accept();
}

void DialogLevel::setSoundControl(bool* soundFlag, std::function<void()> playClick)
{
    m_ptr_is_sound = soundFlag;
    m_playClickSound = playClick;
}


DialogLevel::~DialogLevel()
{
    delete ui;
}