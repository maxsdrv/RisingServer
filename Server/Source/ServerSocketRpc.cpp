#include <QMutexLocker>
#include <memory>

#include "ServerSocketRpc.h"

using namespace ServerMKOSocketRPC;

int Signals::SignalObject::obj_num = 0;
int Slots::SlotObject::obj_num = 0;
int Signals::SignalObject::call_number = 0;
int Slots::SlotThread::obj_num = 0;

Signals::SignalThread::SignalThread() : conn_ip(), conn_port() {
	setObjectName("MKOServer_Socket_RPC_SIGNAL_Thread");
}

void Signals::SignalThread::run()
{
	rpc_srv = std::make_unique<SignalServer>(conn_ip, conn_port);
    rpc_srv->set_app(app);
//    SRPCSignalClass::Instance().toLog("mezonin_server signal thread started");
    exec();
}

Signals::SignalServer::SignalServer(const QString& _conn_ip, int _conn_port)
{
    qDebug() << QString(__func__) << "ip: " << _conn_ip << " port: " << _conn_port;
	rpc_server = std::make_unique<QTcpServer>(this);
    connect(rpc_server.get(), SIGNAL(newConnection()), this, SLOT(tcp_slot()));
    rpc_server->listen(((_conn_ip == "") ? QHostAddress::Any : QHostAddress(_conn_ip)), _conn_port);

//    SRPCSignalClass::Instance().toLog(QString("signal server started listen ip %1 port %2").arg(_conn_ip).arg(_conn_port));
}

void Signals::SignalServer::tcp_slot()
{
//    SRPCSignalClass::Instance().toLog("mezonin_server signal client connected");
    std::shared_ptr<Signals::SignalObject> tmp_obj(new Signals::SignalObject);
    tmp_obj->set_app(app);
    tmp_obj->set_socket(rpc_server->nextPendingConnection());
    rpc_objects << tmp_obj;
}

ServerThread::ServerThread() : conn_ip(), conn_port(), QThread()
{
    setObjectName("Socket_RPC_SLOT_Server_Thread");
}

Slots::SlotServer::SlotServer(QString _conn_ip, int _conn_port, MKOServer* _app) : QTcpServer(), app(_app)
{
    qDebug() << QString(__func__) << "ip: " << _conn_ip << " port: " << _conn_port;
    listen(((_conn_ip == "") ? QHostAddress::Any : QHostAddress(_conn_ip)), _conn_port);
//    SRPCSignalClass::Instance().toLog(QString("slot server started listen ip %1 port %2").arg(_conn_ip).arg(_conn_port));
}


void ServerThread::run()
{
	rpc_srv = std::make_unique<Slots::SlotServer>(conn_ip, conn_port, app);
//    SRPCSignalClass::Instance().toLog("mezonin_server slot thread started");
    exec();
}

void Slots::SlotThread::run()
{
    rpc_obj = std::make_shared<Slots::SlotObject>(app, socket_descriptor);
    exec();
}

Slots::SlotThread::SlotThread(MKOServer* _app, size_t _socket_descriptor) : app(_app), socket_descriptor(_socket_descriptor)
{
    setObjectName(QString("mezonin_server_Socket_RPC_SLOT_Thread_%1").arg(obj_num++));
}

void Slots::SlotServer::incomingConnection(qintptr socketDescriptor)
{
//    SRPCSignalClass::Instance().toLog("mezonin_server slot client connected");
    std::shared_ptr<Slots::SlotThread> tmp_obj(new Slots::SlotThread(app, socketDescriptor));
    tmp_obj->start();
    rpc_objects << tmp_obj;
}
Slots::SlotObject::SlotObject(MKOServer* _app, int socketDescriptor) :QObject(), with_return(false), app(_app)
{
    qDebug() << QString(__func__) << " was invoked";
    setObjectName(QString("mezonin_server_SLOT_Object_%1").arg(obj_num++));
    operators_map["QuerySlots()"] = &SlotObject::QuerySlots;
    operators_map["getXML()"] = &SlotObject::getXML;
    operators_map["VYDAT_KMD_SH(QString, int, QString)"] = &SlotObject::VYDAT_KMD_SH;
    operators_map["SNYAT_KMD_SH(QString, int, QString"] = &SlotObject::SNYAT_KMD_SH;

    rpc_socket = new QTcpSocket();
    rpc_socket->setSocketDescriptor(socketDescriptor);
    connect(rpc_socket, SIGNAL(readyRead()), this, SLOT(read_data()));
    connect(rpc_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sock_error(QAbstractSocket::SocketError)));
}

Signals::SignalObject::SignalObject() : QObject(nullptr)
{
    setObjectName(QString("MKOServer_SIGNAL_Object_%1").arg(obj_num++));
    connect(this, SIGNAL(send_signal(QByteArray*)), this, SLOT(send_signal_slot(QByteArray*)), Qt::BlockingQueuedConnection);
}

void Signals::SignalObject::send_signal_func(QByteArray* _arr)
{
    QMutexLocker locker(&signal_mutex);
    emit send_signal(_arr);
}

void Slots::SlotObject::sock_error(QAbstractSocket::SocketError _err)
{
//    SRPCSignalClass::Instance().toLog(QString("%1 SLOT SOCK ERROR!!! %2").arg(this->objectName()).arg(_err));
}

void Signals::SignalObject::set_socket(QTcpSocket* _rpc_socket)
{
    rpc_socket = _rpc_socket;
    connect(rpc_socket, SIGNAL(readyRead()), this, SLOT(read_data()));
    connect(rpc_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sock_error(QAbstractSocket::SocketError)));
}

void Signals::SignalObject::sock_error(QAbstractSocket::SocketError _err)
{
//    SRPCSignalClass::Instance().toLog(QString("%1 SIGNAL SOCK ERROR!!! %2").arg(this->objectName()).arg(_err));
    if (_err == QAbstractSocket::SocketError::SocketTimeoutError)
        return;
    disconnect(app, SIGNAL(toLog(QString)), this, SLOT(toLog(QString)));
    disconnect(app, SIGNAL(toProtocol(QString)), this, SLOT(toProtocol(QString)));
}
void Signals::SignalObject::set_app(MKOServer* _app) {
	app = _app;
	connect(app, SIGNAL(toLog(QString)), this, SLOT(toLog(QString)), Qt::DirectConnection);
	data_map.insert("toLog(QString)", std::shared_ptr<SignalData>(new SignalData()));
	connect(app, SIGNAL(toProtocol(QString)), this, SLOT(toProtocol(QString)), Qt::DirectConnection);
	data_map.insert("toProtocol(QString)", std::shared_ptr<SignalData>(new SignalData()));
}

void Slots::SlotObject::read_data()
{
    int tmp_size;
    size_t tmp_bytes = rpc_socket->bytesAvailable();
    if (tmp_bytes < 4)
        return;
    QByteArray tmp_size_arr = rpc_socket->read(4);
    QDataStream tmp_size_stream(&tmp_size_arr, QIODevice::ReadOnly);
    tmp_size_stream >> tmp_size;
    while (true)
    {
        tmp_bytes = rpc_socket->bytesAvailable();
        if (tmp_bytes >= tmp_size)
            break;
        rpc_socket->waitForReadyRead(500);
    }
//    SRPCSignalClass::Instance().toLog(QString(" %1 new data %2 bytes").arg(objectName(),tmp_size));
    QByteArray tmp_arr = rpc_socket->read(tmp_size);
    QDataStream tmp_stream(&tmp_arr, QIODevice::ReadOnly);
    int call_n;
    tmp_stream >> call_n;
    QString op_name;
    tmp_stream >> op_name;
//    SRPCSignalClass::Instance().toLog(QString("%1 op_name %2 call_n %3").arg(objectName(),op_name).arg(call_n));
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
			std::cout << "???";
//            SRPCSignalClass::Instance().toLog(QString(" == == == == == == == == == == == == == = %1 response wait failed %2").arg(objectName()).arg(rpc_socket->errorString()));
    }
//    SRPCSignalClass::Instance().toLog(QString(" %1 %2 call_n %3 response sent %4 %5 %6").arg(objectName()).arg(op_name).arg(call_n).arg(tmp_arr2.size()).arg(tmp_arr3.size()).arg(tmp_arr3.data()));
}

void Signals::SignalObject::send_signal_slot(QByteArray* _arr)
{
    rpc_socket->write(*_arr);
    rpc_socket->waitForBytesWritten(3000);
}

void Signals::SignalObject::read_data()
{
    int tmp_size;
    while (rpc_socket->bytesAvailable())
    {
        size_t tmp_bytes = rpc_socket->bytesAvailable();
        while (tmp_bytes < 4)
        {
            rpc_socket->waitForReadyRead(100);
            tmp_bytes = rpc_socket->bytesAvailable();
        }
        QByteArray tmp_size_arr = rpc_socket->read(4);
        QDataStream tmp_size_stream(&tmp_size_arr, QIODevice::ReadOnly);
        tmp_size_stream >> tmp_size;
        while (true)
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
//            SRPCSignalClass::Instance().toLog(QString("%1 connect signal %2").arg(objectName()).arg(signal_name));
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
//            SRPCSignalClass::Instance().toLog(QString("%1 signal %2 received data").arg(objectName()).arg(signal_name));
            if (signal_name.toLocal8Bit().size() != tmp_size)
                tmp_stream >> signal_data;
            descriptor.signal_data = signal_data;
//				data_map[signal_name]->cond.wakeAll();
            descriptor.mutex.unlock();
        }
    }
}

void Signals::SignalObject::string_msg(const QString& _msg)
{
    auto& descriptor = *data_map["string_msg(QString)"].get();
    if (!descriptor.signal_needed)
        return;
    QByteArray tmp_arr;
    QDataStream tmp_stream(&tmp_arr, QIODevice::WriteOnly);
    tmp_stream << QString("string_msg(QString)");
    tmp_stream << (++call_number);
//    SRPCSignalClass::Instance().toLog(QString("%1 from thread %2 send_signal string_msg  call_number %3").arg(objectName()).arg(QThread::currentThread()->objectName()).arg(call_number));
    tmp_stream << _msg;
//    SRPCSignalClass::Instance().toLog(QString("string_msg  call_number %2 _msg =  %1").arg(RPCSignalClass::QVariantToString(_msg)).arg(call_number));
    QByteArray tmp_arr2;
    QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
    tmp_stream2 << tmp_arr.size();
    tmp_arr2 += tmp_arr;
    descriptor.mutex.lock();
    send_signal_func(&tmp_arr2);
//    SRPCSignalClass::Instance().toLog(QString("%1 send_signal string_msg sended").arg(objectName()));
    descriptor.mutex.lock();
    descriptor.mutex.unlock();
//    SRPCSignalClass::Instance().toLog(QString("%1 send_signal string_msg finished").arg(objectName()));
}
void Signals::SignalObject::int_msg(int _msg)
{
    auto& descriptor = *data_map["int_msg(int)"].get();
    if (!descriptor.signal_needed)
        return;
    QByteArray tmp_arr;
    QDataStream tmp_stream(&tmp_arr, QIODevice::WriteOnly);
    tmp_stream << QString("int_msg(int)");
    tmp_stream << (++call_number);
//    SRPCSignalClass::Instance().toLog(QString("%1 from thread %2 send_signal int_msg  call_number %3").arg(objectName()).arg(QThread::currentThread()->objectName()).arg(call_number));
    tmp_stream << _msg;
//    SRPCSignalClass::Instance().toLog(QString("int_msg  call_number %2 _msg =  %1").arg(RPCSignalClass::QVariantToString(_msg)).arg(call_number));
    QByteArray tmp_arr2;
    QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
    tmp_stream2 << tmp_arr.size();
    tmp_arr2 += tmp_arr;
    descriptor.mutex.lock();
    send_signal_func(&tmp_arr2);
//    SRPCSignalClass::Instance().toLog(QString("%1 send_signal int_msg sended").arg(objectName()));
    descriptor.mutex.lock();
    descriptor.mutex.unlock();
//    SRPCSignalClass::Instance().toLog(QString("%1 send_signal int_msg finished").arg(objectName()));
}
void Signals::SignalObject::int_return_signal(int& ret_int)
{
    auto& descriptor = *data_map["int_return_signal(int&)"].get();
    if (!descriptor.signal_needed)
        return;
    QByteArray tmp_arr;
    QDataStream tmp_stream(&tmp_arr, QIODevice::WriteOnly);
    tmp_stream << QString("int_return_signal(int&)");
    tmp_stream << (++call_number);
//    SRPCSignalClass::Instance().toLog(QString("%1 from thread %2 send_signal int_return_signal  call_number %3").arg(objectName()).arg(QThread::currentThread()->objectName()).arg(call_number));
    tmp_stream << ret_int;
//    SRPCSignalClass::Instance().toLog(QString("int_return_signal  call_number %2 ret_int =  %1").arg(RPCSignalClass::QVariantToString(ret_int)).arg(call_number));
    QByteArray tmp_arr2;
    QDataStream tmp_stream2(&tmp_arr2, QIODevice::WriteOnly);
    tmp_stream2 << tmp_arr.size();
    tmp_arr2 += tmp_arr;
    descriptor.mutex.lock();
    send_signal_func(&tmp_arr2);
//    SRPCSignalClass::Instance().toLog(QString("%1 send_signal int_return_signal sended").arg(objectName()));
    descriptor.mutex.lock();
    descriptor.mutex.unlock();
    ret_int = data_map["int_return_signal(int&)"]->signal_data.at(0).toInt();
//    SRPCSignalClass::Instance().toLog(QString("%1 send_signal int_return_signal finished").arg(objectName()));
}

QVariant Slots::SlotObject::QuerySlots(QVariantList& _values)
{
    QString tmp_string;
    int _count = operators_map.keys().count();
    for (int i = 0; i < _count; ++i)
        tmp_string += operators_map.keys().at(i);
    return tmp_string;
}

QVariant Slots::SlotObject::getXML(QVariantList& _values)
{
    try
    {
        QString res = app->getXML();
//        SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName()).arg(RPCSignalClass::QVariantToString(res)));
        return res;
    }
    catch(const std::exception &err)
    {
        app->toProtocol_send(err.what());
        return QString();
    }
    catch(...)
    {
        app->toProtocol_send("Неизвестное исключение");
        return QString();
    }
}

QVariant Slots::SlotObject::VYDAT_KMD_SH(QVariantList &_values)
{
    try
    {
//        SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName(),RPCSignalClass::QVariantToString(_values)));
        auto USTROISTVO = _values.at(0).value<QString>();
        int KR = _values.at(1).value<int>();
        auto KOMANDA = _values.at(2).value<QString>();
        int res = app->VYDAT_KMD_SH(USTROISTVO, KR, KOMANDA);
//        SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName(),RPCSignalClass::QVariantToString(res)));
        return res;
    }
    catch(const std::exception &err)
    {
        app->toProtocol_send(err.what());
        return 1;
    }
    catch(...)
    {
        app->toProtocol_send("UNRECOGNIZED::ERROR");
        return 1;
    }
}
QVariant Slots::SlotObject::SNYAT_KMD_SH(QVariantList &_values)
{
    try
    {
//        SRPCSignalClass::Instance().toLog(QString("%1 _values = %2").arg(objectName(),RPCSignalClass::QVariantToString(_values)));
        auto USTROISTVO = _values.at(0).value<QString>();
        int KR = _values.at(1).value<int>();
        auto KOMANDA = _values.at(2).value<QString>();
        int res = app->SNYAT_KMD_SH(USTROISTVO, KR, KOMANDA);
//        SRPCSignalClass::Instance().toLog(QString("%1 return = %2").arg(objectName(),RPCSignalClass::QVariantToString(res)));
        return res;
    }
    catch(const std::exception &err)
    {
        app->toProtocol_send(err.what());
        return 1;
    }
    catch(...)
    {
        app->toProtocol_send("UNRECOGNIZED::ERROR");
        return 1;
    }
}

