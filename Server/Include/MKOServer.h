#pragma once

#include <QObject>
#include <filesystem>
#include <utility>
#include <iostream>

#include "enums.h"
#include "MmkoModule.h"

class MKOServer : public QObject
{
	Q_OBJECT
public:
    explicit MKOServer(QObject *parent = nullptr/*int slot_port, int signal_port*/);
    ~MKOServer() override;

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
			std::cerr << e.what();
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
        const auto itr = lst_modules.find(T::getNamePrefix());
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
    int VYDAT_KMD_SH(const QString& device, int KR, const QString& command);
    int SNYAT_KMD_SH(QString address, int KR, QString command);
    QString getXML();
private:
    //The type of list connected modules
    std::map<QString, MKOModule*> lst_modules;
    //List of modules

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










