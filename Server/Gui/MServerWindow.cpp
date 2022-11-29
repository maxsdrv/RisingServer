#include <QtWidgets/QtWidgets>
#include <QtNetwork/QtNetwork>
#include <QDir>

#include "MServerWindow.h"
#include "MezoninServer.h"
#include "rpc_loger.h"
#include "DialogSettings.h"

namespace
{
const int height = 800;

const int width = 600;
}

namespace Parser
{
const QString &parserForDelete(QString str)
{
    QString::size_type pos = str.toStdString().find('=');
    std::string key = str.toStdString().substr(0, pos);
    str.clear();
    return str.append(key.c_str());
}
}

MServerWindow::MServerWindow(const QString &title, QWidget *parent)
    : QWidget(parent),
      mezoninServer(std::make_shared<MezoninServer>()),
      settingsValue("Cometa", "СПО АИК"),
      listAddresses()
{
    workTimer.start();
    startTime = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss");

    createServerGroupBox();
    createSettingManagerGroupBox();
    logSettings();
    loadSettings();

    auto *mainLayout = new QGridLayout;
    mainLayout->addWidget(serverGroupBox, 0, 0);
    mainLayout->addWidget(settingManagerGroupBox, 0, 1);
    setLayout(mainLayout);

    setWindowTitle(title);
    this->resize(::height, ::width);

}
void MServerWindow::createSettingManagerGroupBox()
{
    settingManagerGroupBox = new QGroupBox(tr("Settings Manager"));

    hostBox = new QComboBox;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for (const auto &i : ipAddressList)
    {
        if (i == QHostAddress::LocalHost ||
            i.toIPv4Address())
        {
            hostBox->addItem(i.toString());
        }
    }
    hostLabel = new QLabel(tr("Host IP: "));
    hostLabel->setBuddy(hostBox);

    addButton = new QPushButton(tr("Add"));
    deleteButton = new QPushButton(tr("Delete"));
    startButton = new QPushButton(tr("Start Server"));
    stopButton = new QPushButton(tr("Stop"));
    settingManagerView = new QListView;

    connect(hostBox, SIGNAL(currentIndexChanged(int)), SLOT(hostBoxChanged()));
    connect(startButton, &QPushButton::clicked, this, &MServerWindow::startServer);
    connect(this, &MServerWindow::sendIp, mezoninServer.get(), &MezoninServer::runServer);
    connect(addButton, &QPushButton::clicked, this, &MServerWindow::addAddress);
    connect(deleteButton, &QPushButton::clicked, this, &MServerWindow::deleteAddress);

    auto *buttonBoxLayout = new QHBoxLayout;
    buttonBoxLayout->addWidget(addButton);
    buttonBoxLayout->addStretch();
    buttonBoxLayout->addWidget(deleteButton);

    auto *button2BoxLayout = new QHBoxLayout;
    button2BoxLayout->addWidget(startButton);
    button2BoxLayout->addStretch();
    button2BoxLayout->addWidget(stopButton);

    auto outerLayout = new QGridLayout;
    outerLayout->addWidget(hostLabel, 0, 0);
    outerLayout->addWidget(hostBox, 0, 1);
    outerLayout->addLayout(buttonBoxLayout, 1, 1);
    outerLayout->addWidget(settingManagerView, 2, 1);
    outerLayout->addLayout(button2BoxLayout, 3, 1);
    settingManagerGroupBox->setLayout(outerLayout);

    hostBoxChanged();
}
void MServerWindow::createServerGroupBox()
{
    serverGroupBox = new QGroupBox(tr("Server Logs"));

    serverTextEdit = new QTextEdit;
    serverScrollBar = serverTextEdit->verticalScrollBar();
    serverTextDocument = new QTextDocument;
    serverTextCursor = new QTextCursor(serverTextDocument);
    serverTextEdit->setDocument(serverTextDocument);
    serverTextEdit->setReadOnly(true);
    serverTextDocument->setMaximumBlockCount(1000);

    autoScrollBox = new QCheckBox(tr("Автопрокрутка"));
    autoScrollBox->setChecked(true);
    saveTimeWorkBox = new QCheckBox(tr("Сохранять время работы"));

    serverGridLayout = new QGridLayout;
    serverGridLayout->addWidget(serverTextEdit, 0, 0);
    serverGridLayout->addWidget(autoScrollBox, 1, 0);
    serverGridLayout->addWidget(saveTimeWorkBox, 2, 0);
    serverGroupBox->setLayout(serverGridLayout);
}
void MServerWindow::log_append(const QString &_msg)
{
    const_cast<QString &>(_msg) = QTime::currentTime().toString("hh:mm:ss.zzz ") + _msg;
    QMutexLocker lock(&logMutex);
    logBuffer << _msg;

}
void MServerWindow::logSettings()
{
    QSettings sett("Cometa", "СПО АИК");
#ifdef _WIN32
    QString logPath = sett.value("log_path", "d:/logs").toString();
#else
    QString logPath = sett.value("log_path", "logs/").toString();
#endif
    QString timerPath = QCoreApplication::applicationDirPath();

    logFileName = QString("%1/rpc_%2_%3.log").arg(logPath).arg(QCoreApplication::applicationName())
        .arg(QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss"));
    connect(&SRPCSignalClass::Instance(),
            &RPCSignalClass::rpc_toLog,
            this,
            &MServerWindow::log_append,
            Qt::DirectConnection);

    timeFileName = QString("%1/%2_time.log").arg(timerPath).arg(QCoreApplication::applicationName());

    QDir dir(logPath);
    if (!dir.exists())
    {
        QDir().mkdir(logPath);
    }
    connect(&logTimer, &QTimer::timeout, this, &MServerWindow::logTimerOntimer);
    logTimer.start(200);
}
void MServerWindow::logTimerOntimer()
{
    QStringList tmp_buffer;
    {
        QMutexLocker lock(&logMutex);
        tmp_buffer = logBuffer;
        logBuffer.clear();
    }
    if (tmp_buffer.isEmpty())
        return;

    QFile logFile(logFileName);
    QTextStream logStream(&logFile);
    logFile.open(QIODevice::Append);
    for (auto &itr : tmp_buffer)
    {
        serverTextCursor->insertText(itr + "\n");
        logStream << itr << "\n";
    }

    logFile.close();

    if (serverScrollBar)
        serverScrollBar->setValue(serverScrollBar->maximum());
}
void MServerWindow::loadSettings()
{
    strModel = new QStringListModel(this);
    for (const auto &i : settingsValue.allKeys())
    {
        listAddresses << i + "=" + settingsValue.value(i).toString();
    }

    strModel->setStringList(listAddresses);
    settingManagerView->setModel(strModel);
}
void MServerWindow::deleteAddress()
{
    QModelIndex index = settingManagerView->currentIndex();
    if (!index.isValid() || index.row() >= listAddresses.size())
    {
        return;
    }

    auto key = Parser::parserForDelete(index.data().toString());
    strModel->removeRow(index.row());

    if (settingsValue.contains(key))
    {
        settingsValue.remove(key);
    }
    for (int i = 0; i < listAddresses.size(); ++i)
    {
        if (listAddresses.at(i) == index.data().toString())
        {
            listAddresses.removeAt(i);
        }
    }
    settingManagerView->update();
}
void MServerWindow::hostBoxChanged()
{
    ipAddress = hostBox->currentText();
}
void MServerWindow::startServer()
{
    emit sendIp(ipAddress);
}
void MServerWindow::addAddress()
{
    dSettings = std::make_shared<DialogSettings>();
    if (dSettings->exec())
    {
        auto name = dSettings->nameLineEdit->text();
        auto host = dSettings->hostLineEdit->text();
        settingsValue.setValue(name, host);

        for (int i = 0; i < listAddresses.size(); ++i)
        {
            if (name == Parser::parserForDelete(listAddresses.at(i)))
            {
                listAddresses.removeAt(i);
                break;
            }
        }

        listAddresses << name + "=" + host;
        strModel->setStringList(listAddresses);
        settingManagerView->update();
    }
}

