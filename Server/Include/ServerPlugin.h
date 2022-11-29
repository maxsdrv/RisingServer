#ifndef SERVERPLUGIN_H
#define SERVERPLUGIN_H


#include <QObject>
#include "ServerPluginInterface.hpp"

class ServerPlugin : public QObject, public ServerPluginInterface
{
Q_OBJECT
    Q_PLUGIN_METADATA(IID "TestServerPlugin");
    Q_INTERFACES(ServerPluginInterface)

public:
    virtual ~ServerPlugin() { if (_interface) delete _interface; }
    virtual void connect(const QString& ip);
    virtual QString get_name() { return "mezonin_server"; }
};


#endif //SERVERPLUGIN_H
