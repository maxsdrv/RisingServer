#include "ServerRpc.h"


void RPC_mezonin_server_SLOT_Thread::run()
{
    rpc_obj = std::shared_ptr<RPC_mezonin_server_SLOT_Object>(new RPC_mezonin_server_SLOT_Object(addr, port));
    rpc_obj->connect_to_server();
    exec();
}

void RPC_mezonin_server_SIGNAL_Thread::run()
{
    rpc_obj = std::shared_ptr<RPC_mezonin_server_SIGNAL_Object>(new RPC_mezonin_server_SIGNAL_Object(addr, port));
    rpc_obj->connect_to_server();
    exec();
}

void RPC_mezonin_server_SIGNAL_Object::connectNotify(const QMetaMethod & signal)
{
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::string_msg)) {
        connect_signal("string_msg(QString)", true);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::int_msg)) {
        connect_signal("int_msg(int)", true);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::int_return_signal)) {
        connect_signal("int_return_signal(int&)", true);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::toLog)) {
        connect_signal("toLog(QString)", true);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::toProtocol)) {
        connect_signal("toProtocol(QString)", true);
    }
}

void RPC_mezonin_server_SIGNAL_Object::disconnectNotify(const QMetaMethod & signal)
{
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::string_msg)) {
        connect_signal("string_msg(QString)", false);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::int_msg)) {
        connect_signal("int_msg(int)", false);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::int_return_signal)) {
        connect_signal("int_return_signal(int&)", false);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::toLog)) {
        connect_signal("toLog(QString)", false);
    }
    else
    if (signal == QMetaMethod::fromSignal(&RPC_mezonin_server_SIGNAL_Object::toProtocol)) {
        connect_signal("toProtocol(QString)", false);
    }
}

void RPC_mezonin_server_SIGNAL_Object::read_data()
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

            SRPCSignalClass::Instance().toLog("mezonin_server new signal " + op_name);

            if (op_name == "string_msg(QString)")
            {
                QString _msg;
                tmp_stream >> _msg;
                SRPCSignalClass::Instance().toLog("mezonin_server " + op_name +" call_number "+ QString::number(call_number) + " _msg = "+RPCSignalClass::QVariantToString(_msg));
                emit string_msg(_msg);
                QByteArray tmp_arr2;
                QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
                tmp_stream2 << op_name;
                QByteArray tmp_arr3;
                QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
                tmp_stream3 << tmp_arr2.size();
                _sock->write(tmp_arr3 + tmp_arr2);
                _sock->waitForBytesWritten(3000);
                SRPCSignalClass::Instance().toLog("mezonin_server signal finished " + op_name +" call_number "+ QString::number(call_number));
            }
            if (op_name == "int_msg(int)")
            {
                int _msg;
                tmp_stream >> _msg;
                SRPCSignalClass::Instance().toLog("mezonin_server " + op_name +" call_number "+ QString::number(call_number) + " _msg = "+RPCSignalClass::QVariantToString(_msg));
                emit int_msg(_msg);
                QByteArray tmp_arr2;
                QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
                tmp_stream2 << op_name;
                QByteArray tmp_arr3;
                QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
                tmp_stream3 << tmp_arr2.size();
                _sock->write(tmp_arr3 + tmp_arr2);
                _sock->waitForBytesWritten(3000);
                SRPCSignalClass::Instance().toLog("mezonin_server signal finished " + op_name +" call_number "+ QString::number(call_number));
            }
            if (op_name == "int_return_signal(int&)")
            {
                int ret_int;
                tmp_stream >> ret_int;
                SRPCSignalClass::Instance().toLog("mezonin_server " + op_name +" call_number "+ QString::number(call_number) + " ret_int = "+RPCSignalClass::QVariantToString(ret_int));
                emit int_return_signal(ret_int);
                QByteArray tmp_arr2;
                QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
                tmp_stream2 << op_name;
                QVariantList return_list;
                return_list << QVariant(ret_int);
                tmp_stream2 << return_list;
                QByteArray tmp_arr3;
                QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
                tmp_stream3 << tmp_arr2.size();
                _sock->write(tmp_arr3 + tmp_arr2);
                _sock->waitForBytesWritten(3000);
                SRPCSignalClass::Instance().toLog("mezonin_server signal finished " + op_name +" call_number "+ QString::number(call_number));
            }
            if (op_name == "toLog(QString)")
            {
                QString message;
                tmp_stream >> message;
                SRPCSignalClass::Instance().toLog("mezonin_server " + op_name +" call_number "+ QString::number(call_number) + " message = "+RPCSignalClass::QVariantToString(message));
                emit toLog(message);
                QByteArray tmp_arr2;
                QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
                tmp_stream2 << op_name;
                QByteArray tmp_arr3;
                QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
                tmp_stream3 << tmp_arr2.size();
                _sock->write(tmp_arr3 + tmp_arr2);
                _sock->waitForBytesWritten(3000);
                SRPCSignalClass::Instance().toLog("mezonin_server signal finished " + op_name +" call_number "+ QString::number(call_number));
            }
            if (op_name == "toProtocol(QString)")
            {
                QString message;
                tmp_stream >> message;
                SRPCSignalClass::Instance().toLog("mezonin_server " + op_name +" call_number "+ QString::number(call_number) + " message = "+RPCSignalClass::QVariantToString(message));
                emit toProtocol(message);
                QByteArray tmp_arr2;
                QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
                tmp_stream2 << op_name;
                QByteArray tmp_arr3;
                QDataStream tmp_stream3(&tmp_arr3, QIODevice::WriteOnly);
                tmp_stream3 << tmp_arr2.size();
                _sock->write(tmp_arr3 + tmp_arr2);
                _sock->waitForBytesWritten(3000);
                SRPCSignalClass::Instance().toLog("mezonin_server signal finished " + op_name +" call_number "+ QString::number(call_number));
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

QString RPC_mezonin_server_SLOT_Object::getXML()
{
    QVariantList tmp_list;
    QString tmp_ret_params;
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call getXML %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("getXML()", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished getXML %1").arg(tmp_ret_params));
    return res.toString();
}
int RPC_mezonin_server_SLOT_Object::PODKL_14N736(int KR, int main_MKO, const QString& MKO)
{
    if(!connected) return 1;
    QVariantList tmp_list;
    QString tmp_ret_params;
    tmp_list << QVariant(KR);
    tmp_list << QVariant(MKO);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call PODKL_14N736 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("PODKL_14N736(int, QString)", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished PODKL_14N736 %1").arg(tmp_ret_params));
    return res.toInt();
}
int RPC_mezonin_server_SLOT_Object::OTKL_14N736()
{
    if(!connected) return 1;
    QVariantList tmp_list;
    QString tmp_ret_params;
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call OTKL_14N736 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("OTKL_14N736()", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished OTKL_14N736 %1").arg(tmp_ret_params));
    return res.toInt();
}
int RPC_mezonin_server_SLOT_Object::PODKL_14N737(int KR, QString MKO)
{
    if(!connected) return 1;
    QVariantList tmp_list;
    QString tmp_ret_params;
    tmp_list << QVariant(KR);
    tmp_list << QVariant(MKO);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call PODKL_14N737 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("PODKL_14N737(int, QString)", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished PODKL_14N737 %1").arg(tmp_ret_params));
    return res.toInt();
}
int RPC_mezonin_server_SLOT_Object::OTKL_14N737(int KR, QString MKO)
{
    if(!connected) return 1;
    QVariantList tmp_list;
    QString tmp_ret_params;
    tmp_list << QVariant(KR);
    tmp_list << QVariant(MKO);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call OTKL_14N737 %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("OTKL_14N737(int, QString)", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished OTKL_14N737 %1").arg(tmp_ret_params));
    return res.toInt();
}
int RPC_mezonin_server_SLOT_Object::VYDAT_KMD_SH(const QString& device, int KR, const QString& command)
{
    if(!connected) return 1;
    QVariantList tmp_list;
    QString tmp_ret_params;
    tmp_list << QVariant(device);
    tmp_list << QVariant(KR);
    tmp_list << QVariant(command);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call VYDAT_KMD_SH %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("VYDAT_KMD_SH(QString, int, QString)", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished VYDAT_KMD_SH %1").arg(tmp_ret_params));
    return res.toInt();
}
int RPC_mezonin_server_SLOT_Object::SNYAT_KMD_SH(const QString& device, int KR, const QString& command)
{
    if(!connected) return 1;
    QVariantList tmp_list;
    QString tmp_ret_params;
    tmp_list << QVariant(device);
    tmp_list << QVariant(KR);
    tmp_list << QVariant(command);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call SNYAT_KMD_SH %1").arg(RPCSignalClass::QVariantToString(tmp_list)));
    dynamic_call("SNYAT_KMD_SH(QString, int, QString)", tmp_list);
    tmp_ret_params += " return="+RPCSignalClass::QVariantToString(res);
    SRPCSignalClass::Instance().toLog(QString("mezonin_server dynamic_call finished SNYAT_KMD_SH %1").arg(tmp_ret_params));
    return res.toInt();
}

