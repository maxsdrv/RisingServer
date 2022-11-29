#include "MezoninServer.h"
#include "rpc_loger.h"

#include <QThread>
#include <utility>
#include <qcoreapplication.h>
#include "14N737_14N736/14N73_Module.h"

struct CmdData
{
    CmdData(int _KR, int _cmd, const QString& _dev_name, const QString& _aik_name,
            const QString& _sig_txt, const QString& _cmd_txt, int _wait_time = 0)
        : KR(_KR), dev_name(_dev_name), aik_name(_aik_name), sig_txt(_sig_txt),
          cmd_txt(_cmd_txt), wait_time(_wait_time), cmd(_cmd)
    {}
    int KR;
    QString dev_name;
    QString aik_name;
    QString sig_txt;
    QString cmd_txt;
    int wait_time;
    int cmd;
};

namespace CONTROL_FUNCTION_14N
{
void execCmd(MezoninServer *appl, const CmdData &cmd_data, bool inverse_cond = false)
{
    (*appl->getModuleReference<Module_14N73_>())->sendCmd(cmd_data.cmd);

    QTime time;
    time.start();
    while (time.elapsed() < cmd_data.wait_time)
    {
        QThread::msleep(1);
        QCoreApplication::processEvents(QEventLoop::EventLoopExec);
    }
    bool res = STmDBCtrl::Instance().getTMData(cmd_data.aik_name).toBool();
    if (inverse_cond)
    {
        if (res)
            throw std::runtime_error(QString("Ошибка! Зафиксирован cигнал \"%1\" на КР%2 %3")
                                         .arg(cmd_data.sig_txt).arg(cmd_data.KR).arg(cmd_data.dev_name).toLocal8Bit());

        appl->toProtocol(QString("Команда \"%1\" успешно снята на КР%2 %3")
                             .arg(cmd_data.cmd_txt).arg(cmd_data.KR).arg(cmd_data.dev_name));
    }
    else
    {
        if (!res)
            throw std::runtime_error(QString("Ошибка! Сигнал \"%1\" не зафиксирован на КР%2 %3")
                                         .arg(cmd_data.sig_txt).arg(cmd_data.KR)
                                         .arg(cmd_data.dev_name).toLocal8Bit());

        appl->toProtocol(QString("Команда \"%1\" успешно установлена на КР%2 %3")
                             .arg(cmd_data.cmd_txt).arg(cmd_data.KR).arg(cmd_data.dev_name));
    }

}
int PODKL_14N73_(MezoninServer *appl, const QString &dev_name, int KR, const QString& MKO)
{
    qDebug() << QString(__func__) << "was invoked";
    qDebug() << "dev_name = " << dev_name << "MKO = " << MKO;

    QString state_aik_num = QString("%1_КР#%2_СТАТУС").arg(dev_name).arg(KR);
    using MD = Module_14N73_Device;
    auto &mod = appl->getModuleReference<Module_14N73_>();
    if (!mod.switchDevice(dev_name))
        throw std::runtime_error("CONNECT::ERROR::DEVICE " + dev_name.toLocal8Bit());
    (*mod)->setKR(KR);
    (*mod)->setMKO((MKO == "О") ? MD::MAIN : MD::RESERVE);

    if (appl->VYDAT_KMD_SH(dev_name, KR, "БЛОКИРОВКА") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    if (appl->VYDAT_KMD_SH(dev_name, KR, "ВКЛЮЧИТЬ") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    STmDBCtrl::Instance().insertTMData(state_aik_num, 2);

    if (appl->VYDAT_KMD_SH(dev_name, KR, "ПОДКЛЮЧИТЬ") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    if (appl->VYDAT_KMD_SH(dev_name, KR, "РАБОТА") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    STmDBCtrl::Instance().insertTMData(state_aik_num, 1);

    return SUCCESS;
}

int OTKL_14N73_(MezoninServer *appl, const QString &dev_name)
{

    auto &mod = appl->getModuleReference<Module_14N73_>();
    if (!mod.switchDevice(dev_name))
        throw std::runtime_error("Ошибка переключения на устройство " + dev_name.toLocal8Bit());

    int KR = (*mod)->getKR();

    QString state_aik_num = QString("%1_КР#%2_СТАТУС").arg(dev_name).arg(KR);

    if (appl->SNYAT_KMD_SH(dev_name, KR, "РАБОТА") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    if (appl->SNYAT_KMD_SH(dev_name, KR, "ПОДКЛЮЧИТЬ") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    STmDBCtrl::Instance().insertTMData(state_aik_num, 2);

    if (appl->SNYAT_KMD_SH(dev_name, KR, "БЛОКИРОВКА") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    if (appl->SNYAT_KMD_SH(dev_name, KR, "ВКЛЮЧИТЬ") != SUCCESS)
        throw std::runtime_error("Ошибка! Устройство 14Н736 не подключено");

    STmDBCtrl::Instance().insertTMData(state_aik_num, 0);

    return SUCCESS;
}
}

int MezoninServer::PODKL_14N736(int KR, int main_MKO, const QString& MKO)
{
    qDebug() << QString(__func__) << "was invoked";
    return CONTROL_FUNCTION_14N::PODKL_14N73_(this, "14Н736", KR, MKO);
}
int MezoninServer::OTKL_14N736()
{
    return CONTROL_FUNCTION_14N::OTKL_14N73_(this, "14H736");
}
int MezoninServer::PODKL_14N737(int KR, const QString& MKO)
{
    return CONTROL_FUNCTION_14N::PODKL_14N73_(this, "14H737", KR, MKO);
}
int MezoninServer::OTKL_14N737(int KR, QString MKO)
{
    return CONTROL_FUNCTION_14N::OTKL_14N73_(this, "14H737");
}
int MezoninServer::VYDAT_KMD_SH(const QString& device, int KR, const QString& command)
{

    if ((device != "14Н736") && (device != "14Н737"))
        throw std::runtime_error("Ошибка! Неверное имя устройства!");

    if ((KR != 1) && (KR != 2))
        throw std::runtime_error("Ошибка! Неверный комплект резервирования. "\
		"Допустимые значение: 1 или 2");

    if ((device == "14Н736") && (command.toUpper() == "РАБОТА ФК"))
        throw std::runtime_error("Ошибка! Команда \"РАБОТА ФК\" только для 14Н737");

    if (!getModuleReference<Module_14N73_>().switchDevice(device))
        throw std::runtime_error("Ошибка переключения на устройство " + device.toLocal8Bit());

    typedef Module_14N73_Device MD;

    if (command.toUpper() == "БЛОКИРОВКА")
    {
        QString aik_name = QString("%1_КР#%2_ГОТОВ_К_ЦУ").arg(device).arg(KR);

        if (!STmDBCtrl::Instance().getTMData(aik_name).toBool())
            throw std::runtime_error(QString("Ошибка! Сигнал \"Готов к ЦУ\" не зафиксирован "\
								"на КР%1 %2").arg(KR).arg(device).toLocal8Bit());

        toProtocol(QString("Сигнал \"Готов к ЦУ\" зафиксирован на КР%1 %2")
                       .arg(KR).arg(device));

        aik_name = QString("%1_КР#%2_БЛОКИРОВКА").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::BLOCK, device, aik_name,
                              "Блокировка", "Блокировка"));

        return SUCCESS;
    }

    if (command.toUpper() == "ВКЛЮЧИТЬ")
    {
        QString aik_name = QString("%1_КР#%2_ВКЛЮЧЕНО").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::ON, device, aik_name,
                              "Включено", "Включить", 5000));
        return SUCCESS;
    }

    if (command.toUpper() == "ПОДКЛЮЧИТЬ")
    {
        QString aik_name = QString("%1_КР#%2_ПОДКЛЮЧЕНО").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::CONNECT, device, aik_name,
                              "Подключено", "Подключить", 100));
        return SUCCESS;
    }

    if (command.toUpper() == "РАБОТА")
    {
        QString aik_name = QString("%1_КР#%2_ИСПРАВНО").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::WORK, device, aik_name,
                              "Исправно", "Исправно", 30000));

        aik_name = QString("%1_КР#%2_РАБОТА").arg(device).arg(KR);
        if (!STmDBCtrl::Instance().getTMData(aik_name).toBool())
            throw std::runtime_error(QString("Ошибка! Сигнал \"Работа установлена\" "\
			"не зафиксирован на КР%1 %2").arg(KR).arg(device).toLocal8Bit());
        toProtocol(QString("Команда \"Работа установлена\" установлена на КР%1 %2")
                       .arg(KR).arg(device));

        return SUCCESS;
    }

    if (command.toUpper() == "РАБОТА ФК")
    {
        QString aik_name = QString("%1_КР#%2_РАБОТА_ФК").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::CONNECT, device, aik_name,
                              "Работа ФК установлена", "Работа ФК установлена", 100));
        return SUCCESS;
    }

    toProtocol("Ошибка! Неизвестная команда " + command);

    return LOGIC_ERROR;
}

int MezoninServer::SNYAT_KMD_SH(QString device, int KR, QString command)
{
    if ((device != "14Н736") && (device != "14Н737"))
        throw std::runtime_error("Ошибка! Неверное имя устройства!");

    if ((KR != 1) && (KR != 2))
        throw std::runtime_error("Ошибка! Неверный комплект резервирования. "\
											"Допустимые значение: 1 или 2");

    if ((device == "14Н736") && (command.toUpper() == "РАБОТА ФК"))
        throw std::runtime_error("Ошибка! Команда \"РАБОТА ФК\" только для 14Н737");

    if (!getModuleReference<Module_14N73_>().switchDevice(device))
        throw std::runtime_error("Ошибка переключения на устройство " + device.toLocal8Bit());

    typedef Module_14N73_Device MD;

    if (command.toUpper() == "БЛОКИРОВКА")
    {
        QString aik_name = QString("%1_КР#%2_БЛОКИРОВКА").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::REM_BLOCK, device, aik_name,
                              "Блокировка", "Блокировка"), true);
        return SUCCESS;
    }

    if (command.toUpper() == "ВКЛЮЧИТЬ")
    {
        QString aik_name = QString("%1_КР#%2_ВКЛЮЧЕНО").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, Module_14N73_Device::REM_ON, device, aik_name,
                              "Включено", "Включить", 5000), true);
        return SUCCESS;
    }

    if (command.toUpper() == "ПОДКЛЮЧИТЬ")
    {
        QString aik_name = QString("%1_КР#%2_ПОДКЛЮЧЕНО").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::REM_CONNECT, device, aik_name,
                              "Подключено", "Подключить"), true);
        return SUCCESS;
    }

    if (command.toUpper() == "РАБОТА")
    {
        QString aik_name = QString("%1_КР#%2_ГОТОВ_К_ЦУ").arg(device).arg(KR);

        aik_name = QString("%1_КР#%2_РАБОТА").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::REM_WORK, device, aik_name,
                              "Работа установлена", "Работа установлена"), true);

        aik_name = QString("%1_КР#%2_ИСПРАВНО").arg(device).arg(KR);

        if (STmDBCtrl::Instance().getTMData(aik_name).toBool())
            throw std::runtime_error(QString("Ошибка! Зафиксирован сигнал \"Исправно\" "\
							"на КР%1 %2").arg(KR).arg(device).toLocal8Bit());

        toProtocol(QString("Команда \"Работа\" успешно снята на КР%1 %2")
                       .arg(KR).arg(device));
        return SUCCESS;
    }

    if (command.toUpper() == "РАБОТА ФК")
    {
        QString aik_name = QString("%1_КР#%2_РАБОТА_ФК").arg(device).arg(KR);
        CONTROL_FUNCTION_14N::execCmd(this, CmdData(KR, MD::REM_CONNECT, device, aik_name,
                              "Работа ФК установлена", "Работа ФК установлена"), true);
        return SUCCESS;
    }

    toProtocol("Ошибка! Неизвестная команда " + command);
    return LOGIC_ERROR;
}





















