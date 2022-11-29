#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "VisualizePluginInterface.hpp"
#include "TMDBController.hpp"
#include "DBThread.h"

class DBCreator : public QObject
{
Q_OBJECT
public:

    void convertData(const std::vector<QVariant>& msg_list);
signals:
    void needProcessData(const std::list<MsgFromTMDB>& msg_list);
};

class ServerVisualPlugin : public QWidget
{
Q_OBJECT

public:
    static QString GreySt;
    static QString GreenSt;

    ServerVisualPlugin(QWidget* parent = 0);
    int MsgFromDB(const std::list<MsgFromTMDB>& msg_list);
    void convertData(const std::vector<QVariant>& msg_list);
private:
    DBCreator db_cr;
    DBReaderThread db_th;
    QLabel *label1;
    QLabel *label2;

};


class TestServerPlugin : public QObject, public VisualizePluginInterface
{
Q_OBJECT
    Q_PLUGIN_METADATA(IID "TestServerPlugin");
    Q_INTERFACES(VisualizePluginInterface)

public:
    virtual QWidget* getWidget(const QString& panel_name, QWidget* parent = 0);
    virtual QStringList getPanels() { return QStringList() << "mezonin_server_panel_1"; }
    virtual QString getName() { return "mezonin_server"; }
    virtual void clearWidgets();
private:
    ServerVisualPlugin* widg;
};
