#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    
    //QString myStr;
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    //socket->bind(QHostAddress::AnyIPv4,1);
    socket->bind(QHostAddress("192.168.43.221"),4210);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    //parsing();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_getvaluesbutton_clicked()
{
    if(ui->startbutton->text()=="شروع")
    {
        gettingValue();
    }



}


void MainWindow::gettingValue()
{

    ui->getvaluesbutton->setText("آماده به کار/فراخوانی مجدد");
    ui->startbutton->setEnabled(true);
    ui->statusStrValue->setText("آماده برای شروع فرآیند");

    QFile file_obj("C:/Users/mahdi-nnc/Documents/QtArchivePrj/trashv1/myfile.json");

    if(!file_obj.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Failed to open "<<"myfile.json";
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();
    //////////////////////////
    //auto json_doc=QJsonDocument::fromJSON(json_bytes);
    auto json_doc=QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        exit(2);
    }
    if(!json_doc.isObject()){
        qDebug()<<"JSON is not an object.";
        exit(3);
    }

    QJsonObject json_obj=json_doc.object();

    if(json_obj.isEmpty()){
        qDebug()<<"JSON object is empty.";
        exit(4);
    }
    /////////////////////////////////////
    QVariantMap json_map = json_obj.toVariantMap();
    QString j1 = json_obj["name"].toString();
    //qDebug()<<"j1:"+j1;

    qDebug()<< json_map["name"].toString();

    //qDebug()<< json_map["name"].toString();
    qDebug()<< json_map["str"].toInt();
    qDebug()<< json_map["enemy"].toString();


    //ui->label_6->setText(json_obj[0].toString());
    ///////////////////
    QString name ="name";

    ui->sickselectedlable->setNum(ui->comboBox->currentIndex());
    switch (ui->sickselectedlable->text().toInt()) {
    case 0:  qDebug()<<"0000";
        ui->label_4->setText(json_map["name1"].toString());
        ui->time1value->setNum(json_map["time10"].toInt());
        ui->temp1value->setNum(json_map["temp10"].toInt());
        ui->time2value->setNum(json_map["time11"].toInt());
        ui->temp2value->setNum(json_map["temp11"].toInt());
        ui->time3value->setNum(json_map["time12"].toInt());
        ui->temp3value->setNum(json_map["temp12"].toInt());
        break;
    case 1: qDebug()<<"11111";
        ui->label_4->setText(json_map["name2"].toString());
        ui->time1value->setNum(json_map["time20"].toInt());
        ui->temp1value->setNum(json_map["temp20"].toInt());
        ui->time2value->setNum(json_map["time21"].toInt());
        ui->temp2value->setNum(json_map["temp21"].toInt());
        ui->time3value->setNum(json_map["time22"].toInt());
        ui->temp3value->setNum(json_map["temp22"].toInt());
        break;
    case 2: qDebug()<<"2222";
        ui->label_4->setText(json_map["name3"].toString());
        ui->time1value->setNum(json_map["time30"].toInt());
        ui->temp1value->setNum(json_map["temp30"].toInt());
        ui->time2value->setNum(json_map["time31"].toInt());
        ui->temp2value->setNum(json_map["temp31"].toInt());
        ui->time3value->setNum(json_map["time32"].toInt());
        ui->temp3value->setNum(json_map["temp32"].toInt());
        break;
    case 3: qDebug()<<"3333";
        ui->label_4->setText(json_map["name4"].toString());
        ui->time1value->setNum(json_map["time40"].toInt());
        ui->temp1value->setNum(json_map["temp40"].toInt());
        ui->time2value->setNum(json_map["time41"].toInt());
        ui->temp2value->setNum(json_map["temp41"].toInt());
        ui->time3value->setNum(json_map["time42"].toInt());
        ui->temp3value->setNum(json_map["temp42"].toInt());
        break;;
    }
    switch (ui->sickselectedlable->text().toInt()) {
    case 0:
        name="name1";
        qDebug()<<"name1";
        break;

        ui->label_4->setText(json_map[name].toString());
    case 1:
        name="name2";
        ui->label_4->setText(json_map[name].toString());
        qDebug()<<"name2";

        break;;
    }
}


void MainWindow::on_startbutton_clicked()
{
    if (ui->startbutton->text()=="شروع")
    {


        if(ui->getvaluesbutton->text()=="آماده به کار/فراخوانی مجدد")
        {
            ui->nextStep->setEnabled(true);

            if (ui->autoRun->isChecked())
            {
                auto_manual_run=1;
            }
            else {
                auto_manual_run=0;

            }
            ui->autoRun->setEnabled(false);
            ui->manualRun->setEnabled(false);
            ui->endbutton->setEnabled(true);

            //timeremain=ui->time1value->text().toInt();
            //counter1();
            stepsRuning();
            ui->comboBox->setEnabled(false);
            ui->getvaluesbutton->setEnabled(false);
            ui->startbutton->setText("توقف");
            ui->statusStrValue->setText("در حال کار");


        }
    }
    else if (ui->startbutton->text()=="توقف") {
        timer->stop();
        ui->startbutton->setText("ادامه");
        ui->statusStrValue->setText("فرآیند متوقف شده است");

    }

    else if (ui->startbutton->text()=="ادامه") {
        timer->start();
        ui->startbutton->setText("توقف");
        ui->statusStrValue->setText("در حال کار");

    }

}
void MainWindow::counter1()
{
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeReduce()));
    timer->start(1000); //time specified in ms
}
void MainWindow::timeReduce()
{
    timeremain--;
    ui->digitdot->setEnabled(digitflag);
    digitflag=!digitflag;
    if ((timeremain/60)<10)
    {
        ui->minHdigit->display(0);
        ui->minLdigit->display(timeremain/60);

    }
    else if ((timeremain/60)>=10)
    {
        ui->minHdigit->display(timeremain/600);
        ui->minLdigit->display((timeremain/60)%10);

    }

    if ((timeremain%60)<10)
    {
        ui->secHdigit->display(0);
        ui->secLdigit->display(timeremain%60);

    }
    else if ((timeremain%60)>=10)
    {
        ui->secHdigit->display((timeremain%60)/10);
        ui->secLdigit->display((timeremain%60)%10);

    }

    if (timeremain<=0)
    {
        timer->stop();
        stepstatus++;
        stepsRuning();



    }
}

void MainWindow::on_endbutton_clicked()
{
    ui->endbutton->setEnabled(false);
    ui->startbutton->setText("شروع");
    ui->startbutton->setEnabled(false);
    ui->autoRun->setEnabled(true);
    ui->manualRun->setEnabled(true);
    ui->statusStrValue->setText("بیماری را فراخوانی کنید");
    ui->nextStep->setEnabled(false);
    stepstatus=0;
    ui->comboBox->setEnabled(true);

    ui->getvaluesbutton->setEnabled(true);
    ui->getvaluesbutton->setText("فراخوانی");
    timer->stop();
    ui->minHdigit->display(0);
    ui->minLdigit->display(0);

    ui->secHdigit->display(0);
    ui->secLdigit->display(0);
}

void MainWindow::on_nextStep_clicked()
{
    timer->stop();
    ui->startbutton->setText("توقف");
    ui->statusStrValue->setText("در حال کار");
    stepstatus++;
    stepsRuning();
    if(stepstatus==2)
    {
        ui->nextStep->setEnabled(false);
    }
}
void MainWindow::stepsRuning()
{
    if (auto_manual_run==1)
    {
        if(stepstatus==0)
        {
            //stepstatus++;
            timeremain=ui->time1value->text().toInt();
           counter1();
        }
       else if(stepstatus==1)
        {
            //stepstatus++;
            timeremain=ui->time2value->text().toInt();
           counter1();
        }
        else if(stepstatus==2)
        {
            //stepstatus++;
            timeremain=ui->time3value->text().toInt();
           counter1();
        }
        else if(stepstatus==3)
        {
               ui->endbutton->click();
        }
    }
}
void MainWindow::SeyHello()
{
    QJsonDocument Jdata;
    QByteArray Data;
    readyRead();
    Data.append("Hello From UDP land");
    //socket->writeDatagram(Data,QHostAddress("192.168.137.110"),4210);
    //socket->writeDatagram(Data,QHostAddress::AnyIPv4,1);
   // socket->writeDatagram(Data,QHostAddress("192.168.43.207"),4210);
    socket->writeDatagram(Data,QHostAddress(IPArduino),4210);

}
QByteArray MainWindow::readyRead()
{

    Buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);
        //qDebug() << "Message from: " << sender.toString();
        //qDebug() << "Message port: " << senderPort;
        //qDebug() << "Message: " << Buffer;
        bool ok=1;
        QtJson::JsonObject result = QtJson::parse(Buffer,ok).toMap();
        if(!ok) {
            qDebug() << "not OK";

          //qFatal("An error occurred during parsing");
        }
        else{
            IPArduino=result["Ip"].toString();
            SirculatorArduino=result["motor"].toInt();
            TempArduino=result["onlineTemp"].toInt();
            HCStateArduino=result["HCstate"].toInt();

            qDebug()<<"OK:"<< Buffer;
            qDebug() << "IP:" << result["Ip"].toString();
            qDebug() << "motor:" << result["motor"].toInt();
            qDebug() << "OnlineTemp:" << result["onlineTemp"].toInt();
            qDebug() << "HCstate:" << result["HCstate"].toInt();
            //qDebug() << "Time:" << result["time"].toInt();
            ///////////
            ui->IPLable->setText(IPArduino);
            ui->tempSetLable->setNum(setpointTemp);
            ui->tempOnlineLable->setNum(TempArduino);
            ui->HCstateLable->setText(HCStateArduino?"ON":"OFF");
            ui->SirculatorLable->setText(SirculatorArduino?"ON":"OFF");
        }
        return (Buffer);
}

void MainWindow::on_SendJsonButton_clicked()
{
    SeyHello();
    parsing();
}
void MainWindow::parsing()
{

}
