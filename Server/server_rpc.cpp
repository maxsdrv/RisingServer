#include "server_rpc.h"

void RPC_server_SLOT_Thread::run()
{
	rpc_obj = std::shared_ptr<RPC_server_SLOT_Object>(new RPC_server_SLOT_Object(addr, port));
	rpc_obj->connect_to_server();
	exec();
}

void RPC_server_SIGNAL_Thread::run()
{
	rpc_obj = std::shared_ptr<RPC_server_SIGNAL_Object>(new RPC_server_SIGNAL_Object(addr, port));
	rpc_obj->connect_to_server();
	exec();
}

void RPC_server_SIGNAL_Object::connectNotify(const QMetaMethod & signal)
{
	if (signal == QMetaMethod::fromSignal(&RPC_server_SIGNAL_Object::  void toLog)) {
		connect_signal("  void toLog(QString)", true);
	}
	else
	if (signal == QMetaMethod::fromSignal(&RPC_server_SIGNAL_Object::  void toProtocol)) {
		connect_signal("  void toProtocol(QString)", true);
	}
}

void RPC_server_SIGNAL_Object::disconnectNotify(const QMetaMethod & signal)
{
	if (signal == QMetaMethod::fromSignal(&RPC_server_SIGNAL_Object::  void toLog)) {
		connect_signal("  void toLog(QString)", false);
	}
	else
	if (signal == QMetaMethod::fromSignal(&RPC_server_SIGNAL_Object::  void toProtocol)) {
		connect_signal("  void toProtocol(QString)", false);
	}
}

void RPC_server_SIGNAL_Object::read_data()
{
	int tmp_size;
	while (_sock->bytesAvailable())
	{
		int tmp_bytes = _sock->bytesAvailable();
		while (tmp_bytes < 4)
		{
			_sock->waitForReadyRead(100);
			tmp_bytes = _sock->bytesAvailable();
		}
		QByteArray tmp_size_arr = _sock->read(4);
		QDataStream tmp_size_stream(&tmp_size_arr, QIODevice::ReadOnly);
		tmp_size_stream >> tmp_size;
		while (1)
		{
			tmp_bytes = _sock->bytesAvailable();
			if (tmp_bytes >= tmp_size)
				break;
			_sock->waitForReadyRead(500);
		}
		SRPCSignalClass::Instance().toLog(QString("%1 signal new data %2 bytes").arg(objectName()).arg(tmp_size));
		QByteArray tmp_arr = _sock->read(tmp_size);
		QDataStream tmp_stream(&tmp_arr, QIODevice::ReadOnly);
		while(!tmp_stream.atEnd())
		{
			QString op_name;
			tmp_stream >> op_name;
			int call_number;
			tmp_stream >> call_number;

			SRPCSignalClass::Instance().toLog("server new signal " + op_name);

			if (op_name == "  void toLog(QString)")
			{
				QString message;
				tmp_stream >> message;
				SRPCSignalClass::Instance().toLog("server " + op_name +" call_number "+ QString::number(call_number) + " message = "+RPCSignalClass::QVariantToString(message));
				emit   void toLog(message);
				QByteArray tmp_arr2;
				QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
				tmp_stream2 << op_name;
				QByteArray tmp_arr3;
				QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
				tmp_stream3 << tmp_arr2.size();
				_sock->write(tmp_arr3 + tmp_arr2);
				_sock->waitForBytesWritten(3000);
				SRPCSignalClass::Instance().toLog("server signal finished " + op_name +" call_number "+ QString::number(call_number));
			}
			if (op_name == "  void toProtocol(QString)")
			{
				QString message;
				tmp_stream >> message;
				SRPCSignalClass::Instance().toLog("server " + op_name +" call_number "+ QString::number(call_number) + " message = "+RPCSignalClass::QVariantToString(message));
				emit   void toProtocol(message);
				QByteArray tmp_arr2;
				QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
				tmp_stream2 << op_name;
				QByteArray tmp_arr3;
				QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
				tmp_stream3 << tmp_arr2.size();
				_sock->write(tmp_arr3 + tmp_arr2);
				_sock->waitForBytesWritten(3000);
				SRPCSignalClass::Instance().toLog("server signal finished " + op_name +" call_number "+ QString::number(call_number));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

 RPC_server_SLOT_Object::  void runServer(const QString& _ipAddress)
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	tmp_list << QVariant(_ipAddress);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   void runServer %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  void runServer(QString&)", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   void runServer %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  int PODKL_14N736(int KR, int main_MKO, const QString& MKO)
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	tmp_list << QVariant(KR);
	tmp_list << QVariant(main_MKO);
	tmp_list << QVariant(MKO);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   int PODKL_14N736 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  int PODKL_14N736(int, int, QString&)", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   int PODKL_14N736 %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  int OTKL_14N736()
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   int OTKL_14N736 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  int OTKL_14N736()", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   int OTKL_14N736 %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  int PODKL_14N737(int KR, const QString& MKO)
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	tmp_list << QVariant(KR);
	tmp_list << QVariant(MKO);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   int PODKL_14N737 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  int PODKL_14N737(int, QString&)", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   int PODKL_14N737 %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  int OTKL_14N737(int KR, QString MKO)
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	tmp_list << QVariant(KR);
	tmp_list << QVariant(MKO);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   int OTKL_14N737 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  int OTKL_14N737(int, QString)", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   int OTKL_14N737 %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  int VYDAT_KMD_SH(const QString& device, int KR, const QString& command)
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	tmp_list << QVariant(device);
	tmp_list << QVariant(KR);
	tmp_list << QVariant(command);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   int VYDAT_KMD_SH %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  int VYDAT_KMD_SH(QString&, int, QString&)", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   int VYDAT_KMD_SH %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  int SNYAT_KMD_SH(QString address, int KR, QString command)
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	tmp_list << QVariant(address);
	tmp_list << QVariant(KR);
	tmp_list << QVariant(command);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   int SNYAT_KMD_SH %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  int SNYAT_KMD_SH(QString, int, QString)", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   int SNYAT_KMD_SH %1").arg(tmp_ret_params));
	return res;
}
 RPC_server_SLOT_Object::  QString getXML()
{
	QVariantList tmp_list;
	QString tmp_ret_params;
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call   QString getXML %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
	dynamic_call("  QString getXML()", tmp_list);
	tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
	SRPCSignalClass::Instance().toLog(QString("server dynamic_call finished   QString getXML %1").arg(tmp_ret_params));
	return res;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

