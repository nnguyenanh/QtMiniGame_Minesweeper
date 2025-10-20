#pragma once
#include <QDialog>
#include "QPushButtonStyled.h"

namespace Ui {
    class DialogLevel;
}

class DialogLevel : public QDialog
{
    Q_OBJECT
public:
    explicit DialogLevel(QWidget* parent = nullptr);
    ~DialogLevel();

private:
    Ui::DialogLevel* ui;
    QRadioButton* m_easy = nullptr;
    QRadioButton* m_medium = nullptr;
    QRadioButton* m_hard = nullptr;
    QRadioButton* m_custom = nullptr;
    QButtonGroup* m_group = nullptr;

    QLineEdit* m_edit_size = nullptr;
    QLineEdit* m_edit_bombcount = nullptr;
};
