#include "ServerVisualPlugin.h"

#include <QDateTime>
#include <QDataStream>
#include <QBoxLayout>

QString ServerVisualPlugin::GreySt = "QLabel {"
                                      "border-style: solid;"
                                      "border-width: 1px;"
                                      "border-color: black; "
                                      "qproperty-alignment: AlignCenter;"
                                      "background-color : lightGray"
                                      "}";


QString ServerVisualPlugin::GreenSt = "QLabel { background-color : qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(172, 209, 156), stop: 1 rgb(138, 191, 115)); color : black;}";


QWidget* TestServerPlugin::getWidget(const QString& panel_name, QWidget* parent)
{
    widg = new ServerVisualPlugin(parent);

    return widg;
}

ServerVisualPlugin::ServerVisualPlugin(QWidget* parent) : QWidget(parent), db_th("ТМ ТЕСТ test")
{
    auto* v_lay = new QGridLayout(this);
    label1 = new QLabel("Генератор");
    label2 = new QLabel("Анализатор");
    label1->setStyleSheet(GreySt);
    label2->setStyleSheet(GreySt);
    label1->setFixedSize(300, 200);
    label2->setFixedSize(300, 200);
    v_lay->addWidget(label1);
    v_lay->addWidget(label2);
    v_lay->setAlignment(Qt::AlignCenter);

    DBCallback cr_f = std::bind(&DBCreator::convertData, &db_cr, std::placeholders::_1);
    db_th.addCallBackFunction(cr_f);
    db_th.start();
    connect(&db_cr, &DBCreator::needProcessData, this, &ServerVisualPlugin::MsgFromDB);
    QThread::currentThread()->sleep(2);
    db_th.startRead();
}


void DBCreator::convertData(const std::vector<QVariant>& msg_list)
{
    std::list<MsgFromTMDB> templist;
        foreach(const QVariant& msg_q, msg_list)
        {
            auto msg = qvariant_cast<MsgFromTMDB>(msg_q);
            templist.push_back(msg);
        }
    emit needProcessData(templist);
}

int ServerVisualPlugin::MsgFromDB(const std::list<MsgFromTMDB>& msg_list)
{
        foreach(const MsgFromTMDB& msg, msg_list)
        {
            int tmp_code = msg.tm_code;
            QVariant data = msg.value;

            switch (tmp_code)
            {
            case 1:
                switch (data.toInt())
                {
                case 1:
                    label1->setStyleSheet(GreenSt);
                    break;
                default:
                    label1->setStyleSheet(GreySt);
                    break;
                }
                break;
            case 2:
                switch (data.toInt())
                {
                case 1:
                    label2->setStyleSheet(GreenSt);
                    break;
                default:
                    label2->setStyleSheet(GreySt);
                    break;
                }
                break;
            default:
                break;
            }

        }

    return 0;
}

void TestServerPlugin::clearWidgets()
{
    if (widg != NULL)
        delete widg;
}