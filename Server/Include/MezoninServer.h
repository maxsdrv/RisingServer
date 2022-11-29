#pragma once

#ifdef WIN32
#include "winsock2.h"
#endif
#include <QObject>
#include <filesystem>
#include <utility>

#include "TMDBController.hpp"
#include "enums.h"
#include "HWModule.h"

class MezoninServer : public QObject
{
Q_OBJECT
public:
    explicit MezoninServer(QObject *parent = nullptr/*int slot_port, int signal_port*/);
    ~MezoninServer() override;

public slots:
    void runServer(const QString& _ipAddress);
public:
    /**
	*	\brief Добавление модуля к списку подключенных модулей
	*
	*	Каждый подлючаемый модуль является синглтоном, поэтому в списке модулей хранится укзатель но глобальный объект
	*	\param str - Описатель модуля
	*/
    template <class T>
    T* addModule(bool _show = true)
    {
        try
        {
            T* ptr = &T::Instance();
            lst_modules[T::getNamePrefix()] = ptr;
            ptr->setTestShow(_show);
            return ptr;
        }
        catch (const std::exception& e)
        {
            //startupErrors.push_back(QString(e.what()));
        }

        return NULL;
    }
    /**
    *	\brief Получение указателя на модуль с именем obj
    *
    *	При отсутствии искомого модуля выдается соответствующее исключение
    *	\param obj имя модуля
    */
    template <class T>
    T& getModuleReference() const
    {
        MODULE_LIST::const_iterator itr = lst_modules.find(T::getNamePrefix());
        if (itr == lst_modules.end())
            throw std::runtime_error(QString("Модуль %1 не присоединен").arg(T::getNamePrefix()).toStdString().c_str());
        if (itr.value()->lst_device.isEmpty())
            throw std::runtime_error(QString("Список устройств модуля %1 пуст").arg(T::getNamePrefix()).toStdString().c_str());
        return *static_cast<T*>(itr.value());
    }

    void toProtocol_send(QString message)
    {
        emit toProtocol(std::move(message));
    }

public slots:
    int PODKL_14N736(int KR, int main_MKO, const QString& MKO);
    int OTKL_14N736();
    int PODKL_14N737(int KR, const QString& MKO);
    int OTKL_14N737(int KR, QString MKO);
    int VYDAT_KMD_SH(const QString& device, int KR, const QString& command);
    int SNYAT_KMD_SH(QString address, int KR, QString command);
    QString getXML();
private:
    //The type of list connected modules
    using MODULE_LIST = QMap<QString, HWModule*>;
    //List of modules
    MODULE_LIST lst_modules;
    std::shared_ptr<TMDBController> db_ctrl;
signals:
    /**
    *	\brief Àñèíõðîííûé ñèãíàë, ïåðåäàþùèé êëèåíòó ñîîáùåíèå â æóðíàë
    *	\param message - òåêñò ñîîáùåíèÿ
    */
    void toLog(QString message);
    //exception
    void toProtocol(QString message);

public slots:

};










