#pragma once

#include <QWidget>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <QElapsedTimer>
#include <QSettings>
#include <memory>

QT_BEGIN_NAMESPACE
class QGridLayout;
class QTextCursor;
class QCheckBox;
class QTextEdit;
class QGroupBox;
class QComboBox;
class QPushButton;
class QLabel;
class QListView;
class QScrollBar;
class QTextDocument;
class QStringListModel;
class MKOServer;
class CustomTableModel;
class DialogSettings;
class QTableView;
class QStandardItemModel;
QT_END_NAMESPACE

class MServerWindow : public QWidget
{
    Q_OBJECT
public:
    MServerWindow() = default;
    explicit MServerWindow(const QString &title, QWidget *parent = nullptr);
    ~MServerWindow() override { qDebug() << "~MServerWindow()"; };
private:
    void createServerGroupBox(); //base part for mapping logs of server
    void createSettingManagerGroupBox(); // properties for configure file SPO_AIK.conf and options for connection
    void logSettings();
    void loadSettings();

    QGroupBox *serverGroupBox;
    QGridLayout *serverGridLayout;
    QTextEdit *serverTextEdit;
    QCheckBox *autoScrollBox;
    QCheckBox *saveTimeWorkBox;
    QScrollBar *serverScrollBar;
    QTextDocument *serverTextDocument;
    QTextCursor *serverTextCursor;

    QGroupBox *settingManagerGroupBox;
    QComboBox *hostBox;
    QLabel *hostLabel;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QListView *settingManagerView;
    QStringListModel *strModel;
    QStringList listAddresses;
    QSettings settingsValue;
    QString ipAddress;

    QString logFileName;
    QString timeFileName;
    QStringList logBuffer;
    QMutex logMutex;
    QTimer logTimer;
    QElapsedTimer workTimer;

    std::shared_ptr<MKOServer> mezoninServer;
    std::shared_ptr<DialogSettings> dSettings;
public:
    QString startTime;

signals:
    void sendIp(const QString &ipAddr);
public slots:
    void log_append(const QString &_msg);
    void logTimerOntimer();
    void addAddress();
    void deleteAddress();
    void hostBoxChanged();
    void startServer();
};

