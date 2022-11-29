#pragma once

#include <QDialog>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class DialogSettings : public QDialog
{
    Q_OBJECT
public:
    explicit DialogSettings(QWidget *parent = nullptr);
    ~DialogSettings() override { qDebug() << "~DialogSettings"; }
public:
    QLineEdit *nameLineEdit;
    QLineEdit *hostLineEdit;
private:
    QLabel *nameLabel;
    QLabel *hostLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

