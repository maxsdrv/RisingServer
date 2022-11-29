	#include "server_socket_rpc.h"

int server_Socket_RPC_SLOT_Object::obj_num = 0;
int server_Socket_RPC_SIGNAL_Object::obj_num = 0;
int server_Socket_RPC_SIGNAL_Object::call_number = 0;
int server_Socket_RPC_SLOT_Thread::obj_num = 0;

	server_Socket_RPC_SIGNAL_Thread::server_Socket_RPC_SIGNAL_Thread() : QThread()
	{
		setObjectName("server_Socket_RPC_SIGNAL_Thread");
	}

	void server_Socket_RPC_SIGNAL_Thread::run()
	{
		rpc_srv = new server_Socket_RPC_SIGNAL_Server(conn_ip, conn_port);
		rpc_srv->set_app(app);
		SRPCSignalClass::Instance().toLog("server signal thread started");
		exec();
	}

	server_Socket_RPC_SIGNAL_Server::server_Socket_RPC_SIGNAL_Server(QString _conn_ip, int _conn_port)
	{
		rpc_server = new QTcpServer;
		connect(rpc_server, SIGNAL(newConnection()), this, SLOT(tcp_slot()));
		rpc_server->listen(((_conn_ip == "") ? QHostAddress::Any : QHostAddress(_conn_ip)), _conn_port);
		SRPCSignalClass::Instance().toLog(QString("signal server started listen ip %1 port %2").arg(_conn_ip).arg(_conn_port));

	}

	void server_Socket_RPC_SIGNAL_Server::tcp_slot()
	{
		SRPCSignalClass::Instance().toLog("server signal client connected");
		std::shared_ptr<server_Socket_RPC_SIGNAL_Object> tmp_obj(new server_Socket_RPC_SIGNAL_Object);
		tmp_obj->set_app(app);
		tmp_obj->set_socket(rpc_server->nextPendingConnection());
		rpc_objects << tmp_obj;
	}

	server_Socket_RPC_SLOT_Server_Thread::server_Socket_RPC_SLOT_Server_Thread() : QThread()
	{
		setObjectName("Socket_RPC_SLOT_Server_Thread");
	}

	server_Socket_RPC_SLOT_Server::server_Socket_RPC_SLOT_Server(QString _conn_ip, int _conn_port, MezoninServer* _app) : QTcpServer(), app(_app)
	{
		listen(((_conn_ip == "") ? QHostAddress::Any : QHostAddress(_conn_ip)), _conn_port);
		SRPCSignalClass::Instance().toLog(QString("slot server started listen ip %1 port %2").arg(_conn_ip).arg(_conn_port));
	}


	void server_Socket_RPC_SLOT_Server_Thread::run()
	{
		rpc_srv = new server_Socket_RPC_SLOT_Server(conn_ip, conn_port, app);
		SRPCSignalClass::Instance().toLog("server slot thread started");
		exec();
	}

	void server_Socket_RPC_SLOT_Thread::run()
	{
		rpc_obj = std::shared_ptr<server_Socket_RPC_SLOT_Object>(new server_Socket_RPC_SLOT_Object(app, socketDescriptor));
		exec();
	}

	server_Socket_RPC_SLOT_Thread::server_Socket_RPC_SLOT_Thread(MezoninServer* _app, int _socketDescriptor) : app(_app), socketDescriptor(_socketDescriptor)
	{
	setObjectName(QString("server_Socket_RPC_SLOT_Thread_%1").arg(obj_num++));
	}

	void server_Socket_RPC_SLOT_Server::incomingConnection(qintptr socketDescriptor)
	{
		SRPCSignalClass::Instance().toLog("server slot client connected");
		std::shared_ptr<server_Socket_RPC_SLOT_Thread> tmp_obj(new server_Socket_RPC_SLOT_Thread(app, socketDescriptor));
		tmp_obj->start();
		rpc_objects << tmp_obj;
	}

	server_Socket_RPC_SLOT_Object::server_Socket_RPC_SLOT_Object(MezoninServer* _app, int socketDescriptor) : QObject(), with_return(false), app(_app)
	{
	setObjectName(QString("server_SLOT_Object_%1").arg(obj_num++));
		operators_map["QuerySlots()"] = &server_Socket_RPC_SLOT_Object::QuerySlots;
		///////////////////////////////////////////////////////////////////////
		operators_map["  void runServer(QString&)"] = &server_Socket_RPC_SLOT_Object::  void runServer;
		operators_map["  int PODKL_14N736(int, int, QString&)"] = &server_Socket_RPC_SLOT_Object::  int PODKL_14N736;
		operators_map["  int OTKL_14N736()"] = &server_Socket_RPC_SLOT_Object::  int OTKL_14N736;
		operators_map["  int PODKL_14N737(int, QString&)"] = &server_Socket_RPC_SLOT_Object::  int PODKL_14N737;
		operators_map["  int OTKL_14N737(int, QString)"] = &server_Socket_RPC_SLOT_Object::  int OTKL_14N737;
		operators_map["  int VYDAT_KMD_SH(QString&, int, QString&)"] = &server_Socket_RPC_SLOT_Object::  int VYDAT_KMD_SH;
		operators_map["  int SNYAT_KMD_SH(QString, int, QString)"] = &server_Socket_RPC_SLOT_Object::  int SNYAT_KMD_SH;
		operators_map["  QString getXML()"] = &server_Socket_RPC_SLOT_Object::  QString getXML;
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		rpc_socket = new QTcpSocket();
		rpc_socket->setSocketDescriptor(socketDescriptor);
		connect(rpc_socket, SIGNAL(readyRead()), this, SLOT(read_data()));
		connect(rpc_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sock_error(QAbstractSocket::SocketError)));
	}

	server_Socket_RPC_SIGNAL_Object::server_Socket_RPC_SIGNAL_Object() : QObject()
	{
		setObjectName(QString("server_SIGNAL_Object_%1").arg(obj_num++));
		connect(this, SIGNAL(send_signal(QByteArray*)), this, SLOT(send_signal_slot(QByteArray*)), Qt::BlockingQueuedConnection);
	}

	void server_Socket_RPC_SIGNAL_Object::send_signal_func(QByteArray* _arr)
	{
		QMutexLocker locker(&signal_mutex);
		emit send_signal(_arr);
	}

	void server_Socket_RPC_SLOT_Object::sock_error(QAbstractSocket::SocketError _err)
	{
		SRPCSignalClass::Instance().toLog(QString("%1 SLOT SOCK ERROR!!! %2").arg(this->objectName()).arg(_err));
	}

	void server_Socket_RPC_SIGNAL_Object::set_socket(QTcpSocket* _rpc_socket)
	{
		rpc_socket = _rpc_socket;
		connect(rpc_socket, SIGNAL(readyRead()), this, SLOT(read_data()));
		connect(rpc_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sock_error(QAbstractSocket::SocketError)));
	}

	void server_Socket_RPC_SIGNAL_Object::sock_error(QAbstractSocket::SocketError _err)
	{
		SRPCSignalClass::Instance().toLog(QString("%1 SIGNAL SOCK ERROR!!! %2").arg(this->objectName()).arg(_err));
		if (_err == QAbstractSocket::SocketError::SocketTimeoutError)
			return;
		disconnect(app, SIGNAL(  void toLog(QString)), this, SLOT(  void toLog(QString)));
		disconnect(app, SIGNAL(  void toProtocol(QString)), this, SLOT(  void toProtocol(QString)));
	}
	void server_Socket_RPC_SIGNAL_Object::set_app(MezoninServer* _app)
	{
		app = _app;
		connect(app, SIGNAL(  void toLog(QString)), this, SLOT(  void toLog(QString)), Qt::DirectConnection);
		data_map.insert("  void toLog(QString)", std::shared_ptr<SignalData>(new SignalData()));
		connect(app, SIGNAL(  void toProtocol(QString)), this, SLOT(  void toProtocol(QString)), Qt::DirectConnection);
		data_map.insert("  void toProtocol(QString)", std::shared_ptr<SignalData>(new SignalData()));

	}

	void server_Socket_RPC_SLOT_Object::read_data()
	{
		//LARGE_INTEGER _freq;
		//LARGE_INTEGER tmp1;
		//LARGE_INTEGER tmp2;
		int tmp_size;
		int tmp_bytes = rpc_socket->bytesAvailable();
		if (tmp_bytes < 4)
			return;
		QByteArray tmp_size_arr = rpc_socket->read(4);
		QDataStream tmp_size_stream(&tmp_size_arr, QIODevice::ReadOnly);
		tmp_size_stream >> tmp_size;
		while (1)
		{
			tmp_bytes = rpc_socket->bytesAvailable();
			if (tmp_bytes >= tmp_size)
			break;
			rpc_socket->waitForReadyRead(500);
		}
		SRPCSignalClass::Instance().toLog(QString(" %1 new data %2 bytes").arg(objectName()).arg(tmp_size));
		QByteArray tmp_arr = rpc_socket->read(tmp_size);
		QDataStream tmp_stream(&tmp_arr, QIODevice::ReadOnly);
		int call_n;
		tmp_stream >> call_n;
		QString op_name;
		tmp_stream >> op_name;
		SRPCSignalClass::Instance().toLog(QString("%1 op_name %2 call_n %3").arg(objectName()).arg(op_name).arg(call_n));
		OPERATORS_MAP::iterator op_itr = operators_map.find(op_name);
		QVariant res = 1;
		with_return = false;
		QVariantList var_list;
		tmp_stream >> var_list;
		if (op_itr != operators_map.end())
			res = (this->*op_itr.value())(var_list);
		//QueryPerformanceCounter(&tmp2);
		//double tmp_time = (tmp2.QuadPart-tmp1.QuadPart)*1e6/_freq.QuadPart;
		//qDebug() << tmp_time;
		QByteArray tmp_arr2;
		QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
		if (!with_return)
		{
			tmp_stream2 << QString("response");
			tmp_stream2 << res;
		}
		else
		{
			tmp_stream2 << QString("response_return");
			tmp_stream2 << res;
			tmp_stream2 << var_list;
		}
		QByteArray tmp_arr3;
		QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
		tmp_stream3 << tmp_arr2.size();
		rpc_socket->write(tmp_arr3+tmp_arr2);
		for (int i = 0; i<3; ++i)
		{
			if (rpc_socket->waitForBytesWritten(3000))
				break; 
			else
				SRPCSignalClass::Instance().toLog(QString(" == == == == == == == == == == == == == = %1 response wait failed %2").arg(objectName()).arg(rpc_socket->errorString()));
		}
		SRPCSignalClass::Instance().toLog(QString(" %1 %2 call_n %3 response sent %4 %5 %6").arg(objectName()).arg(op_name).arg(call_n).arg(tmp_arr2.size()).arg(tmp_arr3.size()).arg(tmp_arr3.data())); 
	}

	void server_Socket_RPC_SIGNAL_Object::send_signal_slot(QByteArray* _arr)
	{
		rpc_socket->write(*_arr);
		rpc_socket->waitForBytesWritten(3000);
	}

	void server_Socket_RPC_SIGNAL_Object::read_data()
	{
		int tmp_size;
		while (rpc_socket->bytesAvailable())
		{
			int tmp_bytes = rpc_socket->bytesAvailable();
			while (tmp_bytes < 4)
			{
				rpc_socket->waitForReadyRead(100);
				tmp_bytes = rpc_socket->bytesAvailable();
			}
			QByteArray tmp_size_arr = rpc_socket->read(4);
			QDataStream tmp_size_stream(&tmp_size_arr, QIODevice::ReadOnly);
			tmp_size_stream >> tmp_size;
			while (1)
			{
				tmp_bytes = rpc_socket->bytesAvailable();
				if (tmp_bytes >= tmp_size)
					break;
				rpc_socket->waitForReadyRead(100);
			}
			QByteArray tmp_arr = rpc_socket->read(tmp_size);
			QDataStream tmp_stream(&tmp_arr, QIODevice::ReadOnly);
			QVariantList signal_data;
			QString signal_name;
			tmp_stream >> signal_name;
			if (signal_name == "connect")
			{
				tmp_stream >> signal_name;
				if (!data_map.contains(signal_name))
					return;
				SRPCSignalClass::Instance().toLog(QString("%1 connect signal %2").arg(objectName()).arg(signal_name));
				data_map[signal_name]->signal_needed = true;
			}
			else
			if (signal_name == "disconnect")
			{
				tmp_stream >> signal_name;
				if (!data_map.contains(signal_name))
					return;
				SRPCSignalClass::Instance().toLog(QString("%1 disconnect signal %2").arg(objectName()).arg(signal_name));
				data_map[signal_name]->signal_needed = false;
			}
			else
			{
				if (!data_map.contains(signal_name))
					return;
				auto& descriptor = *data_map[signal_name].get();
				SRPCSignalClass::Instance().toLog(QString("%1 signal %2 received data").arg(objectName()).arg(signal_name));
				if (signal_name.toLocal8Bit().size() != tmp_size)
					tmp_stream >> signal_data;
				descriptor.signal_data = signal_data;
//				data_map[signal_name]->cond.wakeAll();
				descriptor.mutex.unlock();
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void server_Socket_RPC_SIGNAL_Object::  void toLog(QString message)
	{
		auto& descriptor = *data_map["  void toLog(QString)"].get();
		if (!descriptor.signal_needed)
			return;
		QByteArray tmp_arr;
		QDataStream tmp_stream(&tmp_arr, QIODevice::WriteOnly);
		tmp_stream << QString("  void toLog(QString)");
		tmp_stream << (++call_number);
		SRPCSignalClass::Instance().toLog(QString("%1 from thread %2 send_signal   void toLog  call_number %3").arg(objectName()).arg(QThread::currentThread()->objectName()).arg(call_number));
		tmp_stream << message;
		SRPCSignalClass::Instance().toLog(QString("  void toLog  call_number %2 message =  %1").arg(RPCSignalClass::QVariantToString(message)).arg(call_number));
		QByteArray tmp_arr2;
		QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
		tmp_stream2 << tmp_arr.size();
		tmp_arr2 += tmp_arr;
		descriptor.mutex.lock();
		send_signal_func(&tmp_arr2);
		SRPCSignalClass::Instance().toLog(QString("%1 send_signal   void toLog sended").arg(objectName()));
		descriptor.mutex.lock();
		descriptor.mutex.unlock();
		SRPCSignalClass::Instance().toLog(QString("%1 send_signal   void toLog finished").arg(objectName()));
	}
	void server_Socket_RPC_SIGNAL_Object::  void toProtocol(QString message)
	{
		auto& descriptor = *data_map["  void toProtocol(QString)"].get();
		if (!descriptor.signal_needed)
			return;
		QByteArray tmp_arr;
		QDataStream tmp_stream(&tmp_arr, QIODevice::WriteOnly);
		tmp_stream << QString("  void toProtocol(QString)");
		tmp_stream << (++call_number);
		SRPCSignalClass::Instance().toLog(QString("%1 from thread %2 send_signal   void toProtocol  call_number %3").arg(objectName()).arg(QThread::currentThread()->objectName()).arg(call_number));
		tmp_stream << message;
		SRPCSignalClass::Instance().toLog(QString("  void toProtocol  call_number %2 message =  %1").arg(RPCSignalClass::QVariantToString(message)).arg(call_number));
		QByteArray tmp_arr2;
		QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
		tmp_stream2 << tmp_arr.size();
		tmp_arr2 += tmp_arr;
		descriptor.mutex.lock();
		send_signal_func(&tmp_arr2);
		SRPCSignalClass::Instance().toLog(QString("%1 send_signal   void toProtocol sended").arg(objectName()));
		descriptor.mutex.lock();
		descriptor.mutex.unlock();
		SRPCSignalClass::Instance().toLog(QString("%1 send_signal   void toProtocol finished").arg(objectName()));
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	QVariant server_Socket_RPC_SLOT_Object::QuerySlots(QVariantList& _values)
	{
		QString tmp_string;
		int _count = operators_map.keys().count();
		for (int i = 0; i < _count; ++i)
			tmp_string += operators_map.keys().at(i);
		return tmp_string;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	QVariant server_Socket_RPC_SLOT_Object::  void runServer(QVariantList& _values)
	{
		try
		{
			SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values)));
			QString _ipAddress = _values.at(0).value<QString>();
			 res = app->  void runServer(_ipAddress);
			_values[0] = _ipAddress;
			SRPCSignalClass::Instance().toLog(QString("%1 _ipAddress = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values[0])));
			with_return = true;
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  int PODKL_14N736(QVariantList& _values)
	{
		try
		{
			SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values)));
			int KR = _values.at(0).value<int>();
			int main_MKO = _values.at(1).value<int>();
			QString MKO = _values.at(2).value<QString>();
			 res = app->  int PODKL_14N736(KR, main_MKO, MKO);
			_values[2] = MKO;
			SRPCSignalClass::Instance().toLog(QString("%1 MKO = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values[2])));
			with_return = true;
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  int OTKL_14N736(QVariantList& _values)
	{
		try
		{
			 res = app->  int OTKL_14N736();
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  int PODKL_14N737(QVariantList& _values)
	{
		try
		{
			SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values)));
			int KR = _values.at(0).value<int>();
			QString MKO = _values.at(1).value<QString>();
			 res = app->  int PODKL_14N737(KR, MKO);
			_values[1] = MKO;
			SRPCSignalClass::Instance().toLog(QString("%1 MKO = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values[1])));
			with_return = true;
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  int OTKL_14N737(QVariantList& _values)
	{
		try
		{
			SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values)));
			int KR = _values.at(0).value<int>();
			QString MKO = _values.at(1).value<QString>();
			 res = app->  int OTKL_14N737(KR, MKO);
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  int VYDAT_KMD_SH(QVariantList& _values)
	{
		try
		{
			SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values)));
			QString device = _values.at(0).value<QString>();
			int KR = _values.at(1).value<int>();
			QString command = _values.at(2).value<QString>();
			 res = app->  int VYDAT_KMD_SH(device, KR, command);
			_values[0] = device;
			SRPCSignalClass::Instance().toLog(QString("%1 device = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values[0])));
			_values[2] = command;
			SRPCSignalClass::Instance().toLog(QString("%1 command = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values[2])));
			with_return = true;
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  int SNYAT_KMD_SH(QVariantList& _values)
	{
		try
		{
			SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(_values)));
			QString address = _values.at(0).value<QString>();
			int KR = _values.at(1).value<int>();
			QString command = _values.at(2).value<QString>();
			 res = app->  int SNYAT_KMD_SH(address, KR, command);
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
	QVariant server_Socket_RPC_SLOT_Object::  QString getXML(QVariantList& _values)
	{
		try
		{
			 res = app->  QString getXML();
			SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
			return res;
		}
		catch(const std::exception &err)
		{
			app->  void toProtocol_send(err.what());
			return ;
		}
		catch(...)
		{
			app->  void toProtocol_send("Неизвестное исключение");
			return ;
		}
	}
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

