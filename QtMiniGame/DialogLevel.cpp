#include "stdafx.h"
#include "DialogLevel.h"
#include "ui_DialogLevel.h"

DialogLevel::DialogLevel(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::DialogLevel)
{
    ui->setupUi(this);
    QFont font("Courier New", 11, QFont::Bold);
    setFont(font);
    setWindowTitle("Select Level");
    setFixedSize(320, 280);

    // Style Apply
    ui->okButton->setFixedSize(100, 30);
    ui->okButton->setText("Apply");


    // LABEL
    QLabel* title = new QLabel("Choose difficulty:");

    // RADIO BUTTONS
    m_easy   = new QRadioButton("[ EASY ]   (05|06)");
    m_medium = new QRadioButton("[MEDIUM]   (10|15)");
    m_hard   = new QRadioButton("[ HARD ]   (15|28)");
    m_custom = new QRadioButton("[CUSTOM] maximum (30|899)");

    // GROUP
    m_group = new QButtonGroup(this);
    m_group->addButton(m_easy);
    m_group->addButton(m_medium);
    m_group->addButton(m_hard);
    m_group->addButton(m_custom);
    m_medium->setChecked(true);

    // EDIT 
    m_edit_size = new QLineEdit();
    m_edit_size->setFixedWidth(60);
    m_edit_size->setPlaceholderText("size");
    m_edit_bombcount = new QLineEdit();
    m_edit_bombcount->setFixedWidth(60);
    m_edit_bombcount->setPlaceholderText("mine");


    // LAYOUT
    QVBoxLayout* layout_emh = new QVBoxLayout();
    layout_emh->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout_emh->setContentsMargins(0, 20, 0, 0);
    layout_emh->setSpacing(5);
    layout_emh->addWidget(m_easy);
    layout_emh->addWidget(m_medium);
    layout_emh->addWidget(m_hard);

    QVBoxLayout* layout_cus = new QVBoxLayout();
    layout_cus->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout_cus->setContentsMargins(0, 20, 0, 0);
    layout_cus->addWidget(m_custom);


    QLabel* label_enter = new QLabel("Enter:");
    QHBoxLayout* layout_edit = new QHBoxLayout();
    layout_edit->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout_edit->addStretch();
    layout_edit->addWidget(label_enter);
    layout_edit->addWidget(m_edit_size);
    layout_edit->addWidget(m_edit_bombcount);
    layout_edit->addStretch();


    layout_cus->addLayout(layout_edit);

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
    layout_main->addLayout(layout_cus_center);
    layout_main->addStretch();                // push buttons to the bottom
    layout_main->addLayout(layout_button);

    setLayout(layout_main);
}

DialogLevel::~DialogLevel()
{
    delete ui;
}