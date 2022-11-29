#include <QDateTime>
#include <QFileInfo>
#include <QDataStream>

#include "ServerPlugin.h"
#include <memory>
#include "ServerRpc.h"
#include "enums.h"


typedef RPC_mezonin_server_SLOT_Thread RMS_SLOT;
typedef RPC_mezonin_server_SIGNAL_Thread RMS_SIGNAL;

void ServerPlugin::connect(const QString& ip)
{
    _interface = new ServerInterface(std::make_shared<RMS_SLOT>(),
                                     std::make_shared<RMS_SLOT>(),
                                     std::make_shared<RMS_SIGNAL>());
    _interface->connect_to_srv(ip, static_cast<int>(PORTS::SLOT_PORT),
                                static_cast<int>(PORTS::SIGNAL_PORT));
}