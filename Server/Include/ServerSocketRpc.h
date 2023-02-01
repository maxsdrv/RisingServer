#pragma once

#include <QObject>
#include <QThread>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QTextEdit>
#include <QWaitCondition>
#include <utility>

#include "MKOServer.h"
//#include "rpc_loger.h"
//#include "socket_rpc.h"

namespace ServerMKOSocketRPC {
namespace Slots {
	class SlotObject : public QObject
	{
	Q_OBJECT
	public:
		SlotObject(MKOServer* _app, int socketDescriptor);
		~SlotObject() override = default;
		typedef QVariant (SlotObject::*OPERATOR_EXECUTOR)(QVariantList&);
		typedef QMap<QString, OPERATOR_EXECUTOR> OPERATORS_MAP;
	public:
		QVariant QuerySlots(QVariantList& _values);
		QVariant VYDAT_KMD_SH(QVariantList& _values);
		QVariant SNYAT_KMD_SH(QVariantList& _values);
		QVariant getXML(QVariantList& _values);
	public slots:
		void read_data();
		void sock_error(QAbstractSocket::SocketError _err);
	private:
		OPERATORS_MAP operators_map;
		QTcpSocket* rpc_socket;
		MKOServer* app;
		bool with_return;
		static int obj_num;
	};

	class SlotThread : public QThread
	{
	Q_OBJECT
	public:
		SlotThread(MKOServer* _app, size_t socket_descriptor);
		void run() override;
		std::shared_ptr<SlotObject> get_obj(){ return rpc_obj; }
	private:
		std::shared_ptr<SlotObject> rpc_obj;
		MKOServer* app;
		int socket_descriptor;
		static int obj_num;
	};

	class SlotServer : public QTcpServer
	{
	Q_OBJECT
	public:
		SlotServer(QString _conn_ip, int _conn_port, MKOServer* _app);
	protected:
		void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
	private:
		MKOServer* app;
		QList<std::shared_ptr<SlotThread> > rpc_objects;
	};
}
namespace Signals {
	class SignalObject  : public QObject
	{
	Q_OBJECT
	public:
		SignalObject();
		~SignalObject() override = default;
		void set_app(MKOServer* _app);
		void set_socket(QTcpSocket* _rpc_socket);
	public slots:
		void string_msg(const QString& _msg);
		void int_msg(int _msg);
		void int_return_signal(int& ret_int);
		void send_signal_slot(QByteArray* _arr);
		void read_data();
		void sock_error(QAbstractSocket::SocketError _err);
	private:
		void send_signal_func(QByteArray* _arr);
		QTcpSocket* rpc_socket {};
		QMutex signal_mutex {};
		MKOServer* app {};
		static int obj_num;
		static int call_number;
//    std::map<QString, std::shared_ptr<SignalData> > data_map;
	signals:
		void send_signal(QByteArray* _arr);
	};
/*                                                               */
	class SignalServer : public QObject
	{
	Q_OBJECT
	public:
		SignalServer(const QString& _conn_ip, int _conn_port);
		void set_app(MKOServer* _app)
		{
			app = _app;
		}
	public slots:
		void tcp_slot();
	private:
		std::unique_ptr<QTcpServer> rpc_server;
		MKOServer* app {};
		QList<std::shared_ptr<Signals::SignalObject> > rpc_objects;
	};

	class SignalThread : public QThread {
	Q_OBJECT
	public:
		SignalThread();
		void set_app(MKOServer* _app) {
			app = _app;
		}
		void set_params(QString&& _conn_ip, int _conn_port) {
			conn_ip = std::move(_conn_ip);
			conn_port = _conn_port;
		}
		void run() override;
	private:
		std::unique_ptr<SignalServer> rpc_srv {};
		MKOServer* app {};
		QString conn_ip;
		int conn_port;
	};
}

class ServerThread : public QThread
{
Q_OBJECT
public:
    ServerThread();
    void set_app(MKOServer* _app)
    {
        app = _app;
    }
    void set_params(QString&& _conn_ip, int _conn_port)
    {
        conn_ip = std::move(_conn_ip);
        conn_port = _conn_port;
    }
    void run() override;
private:
    std::unique_ptr<Slots::SlotServer> rpc_srv;

    MKOServer* app {};
    QString conn_ip;
    int conn_port;

};
}
