#pragma once


class ServerSocketRpc
{

};
#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include "MezoninServer.h"

#include <QWidget>
#include <QTextEdit>
#include <QWaitCondition>

#include "rpc_loger.h"
#include "socket_rpc.h"


class mezonin_server_Socket_RPC_SIGNAL_Object : public QObject
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SIGNAL_Object();
    ~mezonin_server_Socket_RPC_SIGNAL_Object()
    {
    }
    void set_app(MezoninServer* _app);

    void set_socket(QTcpSocket* _rpc_socket);
signals:
    void send_signal(QByteArray* _arr);
public slots:
    void string_msg(QString _msg);
    void int_msg(int _msg);
    void int_return_signal(int& ret_int);
    void toLog(QString message);
    void toProtocol(QString message);

    void send_signal_slot(QByteArray* _arr);
    void read_data();
    void sock_error(QAbstractSocket::SocketError _err);
private:
    void send_signal_func(QByteArray* _arr);
    QTcpSocket* rpc_socket;
    QMutex signal_mutex;
    MezoninServer* app;
    static int obj_num;
    static int call_number;
    QMap<QString, std::shared_ptr<SignalData> > data_map;
};


class mezonin_server_Socket_RPC_SIGNAL_Server : public QObject
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SIGNAL_Server(QString _conn_ip, int _conn_port);
    void set_app(MezoninServer* _app)
    {
        app = _app;
    }
public slots:
    void tcp_slot();
private:
    QTcpServer* rpc_server;
    MezoninServer* app;
    QList<std::shared_ptr<mezonin_server_Socket_RPC_SIGNAL_Object> > rpc_objects;
};

class mezonin_server_Socket_RPC_SIGNAL_Thread : public QThread
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SIGNAL_Thread();
    void set_app(MezoninServer* _app)
    {
        app = _app;
    }
    void set_params(QString _conn_ip, int _conn_port)
    {
        conn_ip = _conn_ip;
        conn_port = _conn_port;
    }
    void run();
private:
    mezonin_server_Socket_RPC_SIGNAL_Server* rpc_srv;
    MezoninServer* app;
    QString conn_ip;
    int conn_port;
};

class mezonin_server_Socket_RPC_SLOT_Object : public QObject
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SLOT_Object(MezoninServer* _app, int socketDescriptor);
    ~mezonin_server_Socket_RPC_SLOT_Object()
    {
    }
    typedef QVariant (mezonin_server_Socket_RPC_SLOT_Object::*OPERATOR_EXECUTOR)(QVariantList&);
    typedef QMap<QString, OPERATOR_EXECUTOR> OPERATORS_MAP;
public:
    QVariant QuerySlots(QVariantList& _values);
    QVariant PODKL_14N736(QVariantList& _values);
    QVariant OTKL_14N736(QVariantList& _values);
    QVariant PODKL_14N737(QVariantList& _values);
    QVariant OTKL_14N737(QVariantList& _values);
    QVariant VYDAT_KMD_SH(QVariantList& _values);
    QVariant SNYAT_KMD_SH(QVariantList& _values);
    QVariant getXML(QVariantList& _values);
public slots:
    void read_data();
    void sock_error(QAbstractSocket::SocketError _err);
private:
    OPERATORS_MAP operators_map;
    QTcpSocket* rpc_socket;
    MezoninServer* app;
    bool with_return;
    static int obj_num;
};

class mezonin_server_Socket_RPC_SLOT_Thread : public QThread
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SLOT_Thread(MezoninServer* _app, int _socketDescriptor);
    void run();
    std::shared_ptr<mezonin_server_Socket_RPC_SLOT_Object> get_obj(){ return rpc_obj; }
private:
    std::shared_ptr<mezonin_server_Socket_RPC_SLOT_Object> rpc_obj;
    MezoninServer* app;
    int socketDescriptor;
    static int obj_num;
};

class mezonin_server_Socket_RPC_SLOT_Server : public QTcpServer
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SLOT_Server(QString _conn_ip, int _conn_port, MezoninServer* _app);
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
private:
    MezoninServer* app;
    QList<std::shared_ptr<mezonin_server_Socket_RPC_SLOT_Thread> > rpc_objects;
};

class mezonin_server_Socket_RPC_SLOT_Server_Thread : public QThread
{
Q_OBJECT
public:
    mezonin_server_Socket_RPC_SLOT_Server_Thread();
    void set_app(MezoninServer* _app)
    {
        app = _app;
    }
    void set_params(QString _conn_ip, int _conn_port)
    {
        conn_ip = _conn_ip;
        conn_port = _conn_port;
    }
    void run();
private:
    mezonin_server_Socket_RPC_SLOT_Server* rpc_srv;
    MezoninServer* app;
    QString conn_ip;
    int conn_port;

};

