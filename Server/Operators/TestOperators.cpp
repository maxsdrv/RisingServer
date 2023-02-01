#include "../MezoninServer.h"

#include <QVariantList>
#include <QFile>
#include <QThread>
#include <qcoreapplication.h>
#include "rpc_loger.h"

int MezoninServer::SLOZHENIE_CELOE(int A, int B)
{
    int res = A + B;
    toProtocol(QString("%1 + %2 = %3").arg(A).arg(B).arg(res));
    db_ctrl->insertTMData(1, res);
    return SUCCESS;
}

int MezoninServer::SLOZHENIE_VESSHESTVENNOE(double A, double B, double& C)
{
    C = A + B;
    toProtocol(QString("%1 + %2 = %3").arg(A).arg(B).arg(C));
    db_ctrl->insertTMData(2, C);
    QVariantList tmp_list;
    tmp_list << A << B;
    db_ctrl->insertTMData(3, tmp_list);
    return SUCCESS;
}

int MezoninServer::MASSIV_CELYX(QVariantList arr, double& result)
{
    result = 0;
    for (int i = 0; i < arr.count(); i++)
        result += arr.at(i).toInt();
    toProtocol(QString("��������� ��������: %1").arg(result));
    return SUCCESS;
}

int MezoninServer::OZHIDANIE(int MS)
{
    int packs = MS / 100;
    for (int i = 0; i < packs; i++)
        QThread::msleep(100);
    return SUCCESS;
}


int MezoninServer::get_tm_data(int tm_code, QVariant& tm_data)
{
    tm_data = db_ctrl->getTMData(tm_code);
    SRPCSignalClass::Instance().toLog(QString("������ ������ %1: %2").arg(tm_code).arg(RPCSignalClass::QVariantToString(tm_data)));
    return SUCCESS;
}

int MezoninServer::ZAPISAT_TM(int tm_code, int value)
{
    return !db_ctrl->insertTMData(tm_code, value);
}

int MezoninServer::CHTENIE_AB_NEP(int ab_address, int ab_sub_address, int number_data_word)
{
    ab_address = 0;
    ab_sub_address = 1;
    number_data_word = 11;
    QVariantList tmp_list {};
    toProtocol(QString("%1: %2: %3").arg(ab_address, ab_sub_address, number_data_word));
    tmp_list << ab_address << ab_sub_address << number_data_word;
    db_ctrl->insertTMData(3, tmp_list);

    return SUCCESS;
}

QString MezoninServer::getXML()
{
    namespace fs = std::filesystem;
    fs::path path_to_xml(fs::current_path());
    qDebug() << "getXML() MKOServer";
    path_to_xml /= "../../servers/mezonin_server/mezonin_server_directives.xml";
    qDebug() << path_to_xml.c_str();

    QFile file(path_to_xml.c_str());

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "FILE::OPEN::SUCCESSFULL";
        return file.readAll();
    }
    else
    {
        qDebug() << "FILE::OPEN::ERROR";
        return "";
    }
}