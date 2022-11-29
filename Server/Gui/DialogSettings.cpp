#include "DialogSettings.h"

#include <QtWidgets>

DialogSettings::DialogSettings(QWidget *parent) : QDialog(parent)
{
    nameLabel = new QLabel(tr("Name"));
    nameLineEdit = new QLineEdit;
    hostLabel = new QLabel(tr("Host"));
    hostLineEdit = new QLineEdit;
    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameLineEdit, 0, 1);

    gLayout->addWidget(hostLabel, 1, 0);
    gLayout->addWidget(hostLineEdit, 1, 1);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &DialogSettings::accept);
    connect(cancelButton, &QPushButton::clicked, this, &DialogSettings::reject);

    setWindowTitle(tr("Add an address"));

}
