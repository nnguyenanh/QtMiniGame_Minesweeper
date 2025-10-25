#pragma once
#include <QDialog>
#include <QMessageBox>

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

    bool* m_ptr_is_sound = nullptr;
    std::function<void()> m_playClickSound;


protected:
    void accept() override;

public:
    int setSize() const;
    int setBombCount() const;
    int setGridSize() const;
    void setSoundControl(bool* soundFlag, std::function<void()> playClick);

    QFrame* makeLine(QWidget* parent = nullptr) {
        QFrame* line = new QFrame(parent);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setStyleSheet("color: #696969;");
        return line;
    }
};
