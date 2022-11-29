#ifndef SERVER_RPC_H
#define SERVER_RPC_H
#include "socket_rpc.h"


class RPC_server_SLOT_Object : public RPC_SLOT_Object
{
	Q_OBJECT
public:
	RPC_server_SLOT_Object(QString _addr, int _port) : RPC_SLOT_Object(_addr, _port) {this->QObject::setObjectName("server_slot_obj");}
	////////////////////////////////////
public slots:
	   void runServer(const QString& _ipAddress);
	   int PODKL_14N736(int KR, int main_MKO, const QString& MKO);
	   int OTKL_14N736();
	   int PODKL_14N737(int KR, const QString& MKO);
	   int OTKL_14N737(int KR, QString MKO);
	   int VYDAT_KMD_SH(const QString& device, int KR, const QString& command);
	   int SNYAT_KMD_SH(QString address, int KR, QString command);
	   QString getXML();
	////////////////////////////////////
};

class RPC_server_SLOT_Thread : public RPC_SLOT_Thread
{
	Q_OBJECT
public:
	RPC_server_SLOT_Thread() : RPC_SLOT_Thread() {this->QObject::setObjectName("server_slot_thr");}
	void run();
	SLOT_OBJ_PTR get_obj() {return std::static_pointer_cast<RPC_SLOT_Object, RPC_server_SLOT_Object>(rpc_obj);}
	std::shared_ptr<RPC_server_SLOT_Object> get_server_obj() {return rpc_obj;}
private:
	std::shared_ptr<RPC_server_SLOT_Object> rpc_obj;

};

class RPC_server_SIGNAL_Object : public RPC_SIGNAL_Object
{
	Q_OBJECT
public:
	RPC_server_SIGNAL_Object(QString _addr, int _port) : RPC_SIGNAL_Object(_addr, _port)
	{
		this->QObject::setObjectName("server_signal_obj");
	}
public slots:
	void read_data();
protected:
	void connectNotify(const QMetaMethod & signal);
	void disconnectNotify(const QMetaMethod & signal);
signals:
	   void toLog(QString message);
	   void toProtocol(QString message);
};

class RPC_server_SIGNAL_Thread : public RPC_SIGNAL_Thread
{
	Q_OBJECT
public:
	RPC_server_SIGNAL_Thread() : RPC_SIGNAL_Thread() {this->QObject::setObjectName("server_signal_thr");}
	void run();
	SIGNAL_OBJ_PTR get_obj() {return std::static_pointer_cast<RPC_SIGNAL_Object, RPC_server_SIGNAL_Object>(rpc_obj);}
private:
	std::shared_ptr<RPC_server_SIGNAL_Object> rpc_obj;
};

#endif
