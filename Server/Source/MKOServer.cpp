#include <QTextCodec>
#include <QtNetwork/QtNetwork>

#include "MKOServer.h"
#include "ServerSocketRpc.h"

MKOServer::MKOServer(QObject* parent)
		: QObject(parent) { }

void MKOServer::runServer(const QString& _ipAddress)
{
    auto* rpc_slot_srv = new mezonin_server_Socket_RPC_SLOT_Server_Thread;
    rpc_slot_srv->set_app(this);
    rpc_slot_srv->set_params(_ipAddress,
                             static_cast<int>(PORTS::SLOT_PORT));
    rpc_slot_srv->start();
    auto* rpc_signal_srv = new mezonin_server_Socket_RPC_SIGNAL_Thread;
    rpc_signal_srv->set_app(this);
    rpc_signal_srv->set_params(_ipAddress,
                               static_cast<int>(PORTS::SIGNAL_PORT));
    rpc_signal_srv->start();

    /*db_ctrl = std::dynamic_pointer_cast<TMDBController>(std::make_shared<MongoTMDBController_v3>("tm_test_db", "ÒÌ ÒÅÑÒ"));
    db_ctrl->tryConnect("", instr::GetIpFromSettings("tm_test_db"), false);*/
}

QString MKOServer::getXML()
{
    QFile file(":/directives.xml");

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "FILE::OPEN::SUCCESSFULLY";
        return file.readAll();
    }
    else
    {
        qDebug() << "FILE::OPEN::ERROR";
        return "";
    }

}

MKOServer::~MKOServer()
{
    qDebug() << __FUNCTION__ ;
}



















