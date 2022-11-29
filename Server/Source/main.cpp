#include <QApplication>
#include <QTextCodec>

#include "MezoninServer.h"
#include "ServerSocketRpc.h"
#include "MServerWindow.h"

#ifdef WIN32

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR cmdLine, int)
{
	int argc = __argc;
	char** argv = __argv;

#else

int main(int argc, char **argv)
{
#endif
    //This will be options and features for flags like --settings and --help

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);
    SMongoSingleton_v3::Instance();


    /*LogWidget widget;
    widget.show();*/
    MServerWindow window("Server Settings");
    window.show();
    MezoninServer test_server;

    return QApplication::exec();
}

