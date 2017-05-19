#include "BeaconControlCenter.h"
#include "ui_beaconcontrolcenter.h"
#include "ui_FramelessWindowCentralWidget.h"

#include "stable.h"

//iBeacon广播包参数   单位：Byte(char)
const int LENGTH_BYTE_Length=2;//AD length字节
const int TYPE_BYTE_Length=2;//AD Type字节

const int GUIDE_Length=3;//引导字符“ble”
const int FLAGS_Length=2;//标志数据
const int MIDDLE_CODE_Length=8;//公司信息等中间码
const int UUID_Length=32;//UUID数据
const int MAJOR_Length=4;//major
const int MINOR_Length=4;//minor
const int RSSI_Length=2;//RSSI
const int TEMPERATURE_Length=4;//温度数据
const int HUMIDITY_Length=4;//湿度数据
const int END_Length=1;//结束字符“#”

const int AD1_Length=6;//AD1总长
const int AD2_Length=54;//AD2总长
const int SENSOR_DATA_Length=8;//传感器数据总长
const int PACK_Length=72;//整包总长

//设备列表参数  单位：Byte(char)
const int MAC_Length=12;//MAC地址数据长度
const int IBEACON_NAME_Length=7;//ibeacon名称长度“ibeacon”

BeaconControlCenter::BeaconControlCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeaconControlCenter)
{
    ui->setupUi(this);
    QTimer *qtimer1 = new QTimer;
    connect(qtimer1,SIGNAL(timeout()),this,SLOT(showTime()));
    qtimer1->start(1000);

    parseTimer1 = new QTimer;
    connect(parseTimer1,SIGNAL(timeout()),this,SLOT(startToParseBLE1()));
    parseTimer2 = new QTimer;
    connect(parseTimer2,SIGNAL(timeout()),this,SLOT(startToParseBLE2()));

    //QTableWidget的表头UI效果(单独设定)
    ui->tableWidget_BLE1->horizontalHeader()->setStyleSheet("QHeaderView::section{border-image: url(:/images/back/back10.jpg);}");
    ui->tableWidget_BLE1->verticalHeader()->setStyleSheet("QHeaderView::section{border-image: url(:/images/back/back10.jpg);}");

    ui->tableWidget_BLE2->horizontalHeader()->setStyleSheet("QHeaderView::section{border-image: url(:/images/back/back10.jpg);}");
    ui->tableWidget_BLE2->verticalHeader()->setStyleSheet("QHeaderView::section{border-image: url(:/images/back/back10.jpg);}");

    //串口
    ui->textEdit_recvSerial->append(QString("检测到端口列表:"));
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox_serialport->addItem(info.portName());
            ui->textEdit_recvSerial->append(info.portName());
            ui->textEdit_recvSerial->append(info.description());
            ui->textEdit_recvSerial->append(info.manufacturer());
            serial.close();
        }
    }
    if(ui->comboBox_serialport->count()==0)ui->textEdit_recvSerial->append(QString("未检测到串口设备！"));
    ui->pushButton_openserial->setText(QString("打开"));
    ui->pushButton_serialSend->setEnabled(false);
    mSerialport= new QSerialPort();
    //接收串口数据并显示
    connect(mSerialport,SIGNAL(readyRead()),this,SLOT(readUart()));
    //处理串口错误(中途断开连接等错误)
    connect(mSerialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &BeaconControlCenter::handleSerialError);
    //串口超时处理
    serialTimer = new QTimer(this); //建立串口读写超时定时器
    connect(serialTimer,SIGNAL(timeout()),this,SLOT(serialTimerUpdate()));

    //TCP/IP Socket
    mSocket = new QTcpSocket(this);
    connect(ui->pushButton_connect,SIGNAL(clicked(bool)),this,SLOT(connectToServer()));
    connect(ui->pushButton_disconnect,SIGNAL(clicked(bool)),this,SLOT(disconnectToServer()));
    connect(ui->pushButton_networkSend,SIGNAL(clicked(bool)),this,SLOT(sendRequest()));
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(mSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(handleSocketError(QAbstractSocket::SocketError)));
    ui->pushButton_networkSend->setEnabled(false);

    //BLE
    mSerialBLEpackageQueue = new QQueue<QString>;
    mSocketBLEpackageQueue = new QQueue<QString>;
    mSerialParsedQueue = new QQueue<BLEPackage>;
    mSocketParsedQueue = new QQueue<BLEPackage>;
}

BeaconControlCenter::~BeaconControlCenter()
{
    delete ui;
}


//解析BLE广播包(iBeacon)
/*
 网关组织后的数据包格式为{
                        引导码：3
                        AD1：6(包括：length(2),type(2),flags(2)),
                        AD2：54(包括：length(2),type(2),MIDDLE_CODE(8),UUID(32),
                                 MAJOR(4),MINOR(4),RSSI(2)),
                        传感器数据：8 (包括：temperature(4),humidity(4))
                        结束码：1
                      }

*/

void BeaconControlCenter::parseBLEpackage(QQueue<QString> *buffQueue,
        QQueue<BLEPackage> *parsedList)
{
    int position=0;
    while(!buffQueue->isEmpty())
    {
        //curPackage示例：
        //"ble 02011a 1aff4c000215 e2c56db5dffb48d2b060d0f5a71096e0 0000 0000 c5 1122 3344 #"(无空格)

        QString curPackage=buffQueue->dequeue();
        BLEPackage package;
        if(curPackage.mid(position,GUIDE_Length)!=QString("ble"))
        {
            //qDebug()<<"not a ble package";
            continue;
        }
        position+=GUIDE_Length;//移动到AD1首字节
        package.flags = curPackage.mid(position+4,FLAGS_Length);
            //跳过AD1的length和type，读取flags
        position+=AD1_Length;//移动到AD2首字节
        package.uuid = curPackage.mid(position+4+MIDDLE_CODE_Length,UUID_Length);
            //跳过AD2的length和type以及中间信息，读取UUID
        position+=4+MIDDLE_CODE_Length+UUID_Length;//移动到MAJOR首字节
        package.major=curPackage.mid(position,MAJOR_Length);
            //读取major
        position+=MAJOR_Length;//移动到MINOR首字节
        package.minor=curPackage.mid(position,MINOR_Length);
            //读取major
        position+=MINOR_Length;//移动到RSSI字节
        package.rssi = curPackage.mid(position,RSSI_Length);
            //读取RSSI
        position+=RSSI_Length;//移动到传感器数据首字节
        package.sensorData = curPackage.mid(position,TEMPERATURE_Length+HUMIDITY_Length);
            //读取传感器数据
        position=0;//一个包解析完毕
        parsedList->enqueue(package);//加入到解析后的队列
    }
}

void BeaconControlCenter::on_menuButton_serial_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->stackedWidget->setCurrentIndex(0);
}

void BeaconControlCenter::on_menuButton_socket_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->stackedWidget->setCurrentIndex(1);
}

void BeaconControlCenter::on_menuButton_tools_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->stackedWidget->setCurrentIndex(2);
}

void BeaconControlCenter::on_menuButton_help_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->stackedWidget->setCurrentIndex(3);
}

void BeaconControlCenter::showTime()
{
    QDateTime time=QDateTime::currentDateTime();
    QString textTime=time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_time->setText(textTime);
}



//手动刷新
void BeaconControlCenter::on_pushButton_refresh_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->comboBox_serialport->clear();//清空初始检测结果，重新检测
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox_serialport->addItem(info.portName());
            ui->textEdit_recvSerial->append(info.portName());
            ui->textEdit_recvSerial->append(info.description());
            ui->textEdit_recvSerial->append(info.manufacturer());
            serial.close();
        }
    }
    if(ui->comboBox_serialport->count()==0)ui->textEdit_recvSerial->append(QString("未检测到串口设备！"));
}

//打开/关闭串口通信
void BeaconControlCenter::on_pushButton_openserial_clicked()
{
    if(ui->pushButton_openserial->text()==QString("打开"))
    {

        //检测该设备是否仍处于连接（检测优化，避免打开串口前设备失去连接）
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            if(info.portName()==ui->comboBox_serialport->currentText())goto OPEN;//若设备确实还处于连接，则开始打开该串口
        }
        //否则提示
        if(!soundFlag)QSound::play(":/sounds/sound/wrong.wav");
        QMessageBox::StandardButton reply;
        reply= QMessageBox::information(this,"提示","未检测到串口设备，请检查连接后重试！",QMessageBox::Cancel);
        if(reply==QMessageBox::Cancel)
             goto CLOSE;


OPEN:
        mSerialport->setPortName(ui->comboBox_serialport->currentText());
        mSerialport->open(QIODevice::ReadWrite);
        mSerialport->setBaudRate(ui->comboBox_baund->currentText().toInt());
        switch(ui->comboBox_checkbit->currentIndex()){
        case 0: mSerialport->setParity(QSerialPort::NoParity);break;
        case 1: mSerialport->setParity(QSerialPort::OddParity);break;
        case 2: mSerialport->setParity(QSerialPort::EvenParity);break;
        default: break;
        }
        switch(ui->comboBox_databit->currentIndex()){
        case 0: mSerialport->setDataBits(QSerialPort::Data8);break;
        case 1: mSerialport->setDataBits(QSerialPort::Data7);break;
        case 2: mSerialport->setDataBits(QSerialPort::Data6);break;
        default: break;
        }
        switch(ui->comboBox_stopbit->currentIndex()){
        case 0: mSerialport->setStopBits(QSerialPort::OneStop);break;
        case 1: mSerialport->setStopBits(QSerialPort::TwoStop);break;
        default: break;
        }
        mSerialport->setFlowControl(QSerialPort::NoFlowControl);


        ui->comboBox_serialport->setEnabled(false);
        ui->comboBox_baund->setEnabled(false);
        ui->comboBox_checkbit->setEnabled(false);
        ui->comboBox_databit->setEnabled(false);
        ui->comboBox_stopbit->setEnabled(false);
        ui->pushButton_refresh->setEnabled(false);
        ui->label_serialStatus->setStyleSheet("QLabel{background-color: rgb(255, 0, 0);}");
        ui->pushButton_openserial->setText(QString("关闭"));
        ui->pushButton_serialSend->setEnabled(true);
        if(!soundFlag)QSound::play(":/sounds/sound/success.wav");
        ui->textEdit_recvSerial->append(QString("当前连接上：")+mSerialport->portName());

    }
    else
    {
        mSerialport->clear();
        if (mSerialport->isOpen())
            mSerialport->close();
        ui->comboBox_serialport->setEnabled(true);
        ui->comboBox_baund->setEnabled(true);
        ui->comboBox_checkbit->setEnabled(true);
        ui->comboBox_databit->setEnabled(true);
        ui->comboBox_stopbit->setEnabled(true);
        ui->pushButton_refresh->setEnabled(true);
        ui->label_serialStatus->setStyleSheet("QLabel{background-color: rgb(0, 255, 255);}");
        ui->textEdit_recvSerial->append(QString("连接已断开"));
        ui->pushButton_openserial->setText(QString("打开"));
        ui->pushButton_serialSend->setEnabled(false);

    }


CLOSE:  ;
}


void BeaconControlCenter::serialTimerUpdate()
{
    serialTimer->stop();

    mSerialRecvNum += mSerialRecvData.count();

    if(ui->radioButton_recvHex->isChecked())
    {
        ui->textEdit_recvSerial->append(QString(mSerialRecvData.toHex()));//十六进制显示
    }
    else
    {
        ui->textEdit_recvSerial->append(QString(mSerialRecvData.data()));//字符模式显示
    }

    ui->label_serialRecvNum->setText(QString::number(mSerialRecvNum));

    //存储到BLE数据包缓存队列,每个BLE package为一个QString
    qDebug()<<mSerialRecvData;
    for(int i=0;i<mSerialRecvData.count();i+=PACK_Length)
    {
        QString tempStr=mSerialRecvData.mid(i,i+PACK_Length-1);
        mSerialBLEpackageQueue->enqueue(tempStr);
        qDebug()<<mSerialBLEpackageQueue-> back();
    }

    mSerialRecvData.clear();

}

//串口接收
void BeaconControlCenter::readUart()
{
    serialTimer->start(10);
    mSerialRecvData.append(mSerialport->readAll());

}

//串口接收数据清空
void BeaconControlCenter::on_pushButton_serialClear_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->textEdit_recvSerial->clear();
}

//串口发送
void BeaconControlCenter::on_pushButton_serialSend_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    mSerialSendData = ui->lineEdit_sendSerial->text().toLatin1();
    mSerialSendNum += mSerialSendData.count();
    if(ui->radioButton_sendHex->isChecked())
    {
        mSerialport->write(mSerialSendData.toHex());//十六进制发送
    }
    else
    {
        mSerialport->write(mSerialSendData.data());//字符模式发送
    }
    ui->label_serialSendNum->setText(QString::number(mSerialSendNum));
}

void BeaconControlCenter::handleSerialError(QSerialPort::SerialPortError error)
{
    if(!soundFlag)QSound::play(":/sounds/sound/wrong.wav");
    switch(error)
    {
    case QSerialPort::NoError:
        QMessageBox::information(this,"串口助手","返回码："+QString::number(error)
                                 +"\n分析中...\n串口连接成功",
                                 QMessageBox::Cancel);
        break;
    case QSerialPort::DeviceNotFoundError:
        QMessageBox::information(this,"串口助手","返回码："+QString::number(error)
                                 +"\n分析中...\n未找到串口设备",
                                 QMessageBox::Cancel);
        break;
    case QSerialPort::PermissionError:
        QMessageBox::information(this,"串口助手","返回码："+QString::number(error)
                                 +"\n分析中...\n权限获取错误",
                                 QMessageBox::Cancel);
        break;
    case QSerialPort::WriteError:
        QMessageBox::information(this,"串口助手","返回码："+QString::number(error)
                                 +"\n分析中...\nIO错误：写串口数据失败",
                                 QMessageBox::Cancel);
        break;
    case QSerialPort::ReadError:
        QMessageBox::information(this,"串口助手","返回码："+QString::number(error)
                                 +"\n分析中...\nIO错误：读串口数据失败",
                                 QMessageBox::Cancel);
        break;
    case QSerialPort::ResourceError:
        QMessageBox::information(this,"串口助手","返回码："+QString::number(error)
                                 +"\n分析中...\n当前设备已被移除，请检查连接",
                                 QMessageBox::Cancel);
        break;
     default:
        break;
    }

}

//TCP连接
void BeaconControlCenter::connectToServer()
{
    mServerIPAdress = QHostAddress(ui->lineEdit_ip->text());
    mServerPort = ui->lineEdit_port->text().toInt();
    mSocket->connectToHost(mServerIPAdress,mServerPort);
    if(mSocket->waitForConnected(30000))
    {
        if(!soundFlag)QSound::play(":/sounds/sound/success.wav");
        ui->textEdit_recvNetwork->append(QString("当前连接上：")
                                                           +mServerIPAdress.toString()
                                                           +QString(":")+QString::number(mServerPort));
    }
    ui->pushButton_networkSend->setEnabled(true);
}

//TCP断开连接
void BeaconControlCenter::disconnectToServer()
{
    mSocket->disconnectFromHost();
    mSocket->close();
    ui->textEdit_recvNetwork->append(QString("已从")+mServerIPAdress.toString()
                                     +QString(":")+QString::number(mServerPort)
                                     +QString("断开连接！"));
    ui->pushButton_networkSend->setEnabled(false);
}

//socket发送数据
void BeaconControlCenter::sendRequest()
{
    mSocketSendData = ui->lineEdit_sendNetwork->text().toLatin1();
    mSocket->write(mSocketSendData);//实际以const char*格式发送
    mSocketSendNum += mSocketSendData.count();
    ui->label_networkSendNum->setText(QString::number(mSocketSendNum));
}

//socket接收数据
void BeaconControlCenter::readData()
{
    mSocketRecvData = mSocket->readAll();
    ui->textEdit_recvNetwork->append(QString(mSocketRecvData));
    mSocketRecvNum += mSocketRecvData.count();
    ui->label_networkRecvNum->setText(QString::number(mSocketRecvNum));

    //存储到BLE数据包缓存队列,每个BLE package为一个QString
    mSocketBLEpackageQueue->enqueue(QString(mSocketRecvData.data()));
    //qDebug()<<mSocketBLEpackageQueue->back();
}

void BeaconControlCenter::handleSocketError(QAbstractSocket::SocketError)
{
    if(!soundFlag)QSound::play(":/sounds/sound/wrong.wav");
    QMessageBox::information(this,"检测到Socket错误",mSocket->errorString(),
                             QMessageBox::Cancel);
}

//socket接收数据清空
void BeaconControlCenter::on_pushButton_networkClear_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    ui->textEdit_recvNetwork->clear();
}

//帮助
void BeaconControlCenter::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn3.wav");
    ui->label_help->setText(current->text(0));
    if(current->text(0)==QString("串口配置"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于通信前对串口相关参数的配置\n\n")
                               +QString( "串口推荐配置如下：\n"
                                         "1.串口号：默认串口号\n（软件能自动识别活动的串口设备，请选择可连接的串口）\n")
                               +QString("2.波特率：9600\n（根据通信速率要求选择，可根据实际需求选择）\n")
                               +QString("3.校验位：NONE\n（奇校验或偶校验，一般不用）\n")
                               +QString("4.数据位：8\n")
                               +QString("5.停止位：1\n\n")
                               +QString("打开/关闭：打开或关闭串口设备，成功操作会在串口助手中打印信息\n")
                               +QString("刷新：用于连接发生变化时重新检测串口设备")
                               );
 
    }
    else if(current->text(0)==QString("串口助手"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("1.串口助手包括接收区和发送区：\n")
                               +QString("接收区：\n显示接收到的数据，可选择接收和发送格式：字符或十六进制。\n")
                               +QString("发送区：\n发送数据，可选择接收和发送格式：字符或十六进制。\n\n")
                               +QString("2.清空操作：点击清空显示图标可清空当前显示\n\n")
                               +QString("3.状态监测：串口配置好后，点击打开即可开始通信。串口支持状态监测，自动反馈通信中出现的错误。")
                               +QString("反馈以对话框的形式给出错误代码和分析结果，错误代码对应结果如下：\n")
                               +QString("   0 --- NoError,\n"
                                        "   1 --- DeviceNotFoundError,\n"
                                        "   2 --- PermissionError,\n"
                                        "   3 --- OpenError,\n"
                                        "   4 --- ParityError,\n"
                                        "   5 --- FramingError,\n"
                                        "   6 --- BreakConditionError,\n"
                                        "   7 --- WriteError,\n"
                                        "   8 --- ReadError,\n"
                                        "   9 --- ResourceError,\n"
                                        "   10 --- UnsupportedOperationError,\n"
                                        "   11 --- UnknownError,\n"
                                        "   12 --- TimeoutError,\n"
                                        "   13 --- NotOpenError.\n\n")
                               +QString("4.串口统计:串口助手会实时统计接收和发送的字节数，显示累计结果，该结果会在保存时写入报告。\n")
                               );
    }
    else if(current->text(0)==QString("网络配置"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于通信前对TCP连接的配置\n\n")
                               +QString("1.配置\n"
                                        "集总器IP：Beacon集总器的IP地址，该版采用IPv4地址\n"
                                        "集总器Port：Beacon集总器wifi应用的端口号\n")
                               +QString("2.连接：基于TCP/IP协议，连接成功会在网络助手中打印信息。\n")
                               +QString("3.断开连接：向服务端发送断开连接请求，操作成功会在网络助手中打印信息。\n\n")
                               +QString("本地测试方法：\n1.启动软件配套的TcpServer测试程序，可在[工具]中打开。\n"
                                        "2.集总器IP输入本机回路地址：127.0.0.1，集总器port输入TcpServer测试软件的端口号：8888。\n"
                                        "3.点击连接，若连接成功会显示：当前连接上：127.0.0.1:8888，"
                                        "并收到TcpServer发来的“10000”数据表示连接成功。\n"
                                        "4.两边发送一些数据能成功显示，则说明通信成功。\n")
                               );

    }
    else if(current->text(0)==QString("网络助手"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("1.网络助手包括接收区和发送区：\n")
                               +QString("接收区：\n显示接收到的数据。\n")
                               +QString("发送区：\n发送数据。\n\n")
                               +QString("2.清空操作：点击清空显示图标可清空当前显示。\n\n")
                               +QString("3.状态监测：网络配置好后，点击连接即可开始通信。支持状态监测，自动反馈通信中出现的错误。")
                               +QString("反馈以对话框的形式给出错误信息，可能出现的错误信息如下：\n")
                               +QString("   -1 --- UnknownSocketError,\n"
                                        "   0 --- ConnectionRefusedError,\n"
                                        "   1 --- RemoteHostClosedError,\n"
                                        "   2 --- HostNotFoundError,\n"
                                        "   3 --- SocketAccessError,\n"
                                        "   4 --- SocketResourceError,\n"
                                        "   5 --- SocketTimeoutError,\n"                     /* 5 */
                                        "   6 --- DatagramTooLargeError,\n"
                                        "   7 --- NetworkError,\n"
                                        "   8 --- AddressInUseError,\n"
                                        "   9 --- SocketAddressNotAvailableError,\n"
                                        "   10 --- UnsupportedSocketOperationError,\n"       /* 10 */
                                        "   11 --- UnfinishedSocketOperationError,\n"
                                        "   12 --- ProxyAuthenticationRequiredError,\n"
                                        "   13 --- SslHandshakeFailedError,\n"
                                        "   14 --- ProxyConnectionRefusedError,\n"
                                        "   15 --- ProxyConnectionClosedError,\n"             /* 15 */
                                        "   16 --- ProxyConnectionTimeoutError,\n"
                                        "   17 --- ProxyNotFoundError,\n"
                                        "   18 --- ProxyProtocolError,\n"
                                        "   19 --- OperationError,\n"
                                        "   20 --- SslInternalError,\n"                       /* 20 */
                                        "   21 --- SslInvalidUserDataError,\n"
                                        "   22 --- TemporaryError,\n"
                                        "注：该版本未使用SSL加密连接和网络代理，故12-21的错误不可能出现。\n\n"
                                        )
                               +QString("4.网络统计:网络助手会实时统计接收和发送的字节数，显示累计结果，该结果会在保存时写入报告。\n")
                               );
    }
    else if(current->text(0)==QString("Beacon集总器配置"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于对当前连接的Beacon集总器硬件配置\n\n")
                               +QString("1.发射功率\n")
                               +QString("2.广播间隔\n")
                               +QString("3.扫描间隔\n")
                               +QString("4.扫描窗口\n")
                               +QString("5.配置集总器：点击该按钮开始更新配置到硬件")
                               );

    }
    else if(current->text(0)==QString("BLE数据中心"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("对从串口或网络接收的数据进行解析\n按蓝牙4.0广播包的格式解析并列表显示。\n\n")
                               +QString("串口和网络接收的数据包相互独立，两个页面的BLE数据表也互不影响。\n")
                               +QString("1.开始解析：若串口或网络接收到数据，则数据包写入缓冲队列，点击BLE数据中心的[开始/暂停]按钮后，开始解析\n")
                               +QString("2.解析间隔：开始解析后，软件开始从缓冲队列中提取数据包解析出Beacon的相应字段，并在列表中更新显示。"
                                        "从缓冲区中提取数据包的时间间隔为1s,即每隔1s提取出收到的所有数据包并完成解析显示\n")
                               +QString("3.暂停解析：解析过程中，用户可以通过点击[开始/暂停]按钮随时暂停解析，此时定时器停止工作，"
                                        "数据包只是通过串口或网络写入到缓冲数据区而不会解析显示。"
                                        "为保证缓冲队列的数据不因串口或网络的接收数据写满溢出，"
                                        "请在串口或网络开始接收的时候尽快开始解析，并及时生成报告。\n")
                               +QString("4.生成报告：解析任务完成后（请在完成时点击暂停按钮，表示该阶段解析任务完毕），"
                                        "请通过点击[保存]按钮，选择保存报告文件及时生成报告，"
                                        "报告请保存在当前路径下，以免[工具]中的[查看报告]功能无法获取到报告路径。\n")
                               +QString("5.写入到数据库表：解析任务完成后（请在完成时点击暂停按钮，表示该阶段解析任务完毕），"
                                        "请通过点击[保存]按钮，选择保存数据库文件及时写入到数据库，"
                                        "数据库文件BeaconDB.db在当前路径下，已默认创建iBeaconFromSerial和iBeaconFromSocket两个数据库表，"
                                        "分别存储来自串口和网络的数据包，可以通过[工具]中的[数据库编辑工具]查看和编辑数据库表文件。\n")
                                );

    }
    else if(current->text(0)==QString("SQLite简介"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("软件集成的轻量级数据库系统\n用于存储串口和网络接收的BLE数据包\n\n")
                                +QString("SQLite是一款轻型数据库，是遵守ACID的关系型数据库管理系统，它包含在一个相对小的C库中，"
                                         "体积小巧且功能强大，广泛应用于嵌入式系统。本软件有嵌入式终端设备的移植版本，故集成本数据库以便数据存储。\n\n"
                                         "SQLiteStudio是一款SQLite数据库的可视化管理工具，本软件已集成进[工具]系统。\n\n"
                                         "软件从V1.1开始全面支持SQLite3的数据存储操作，请在[帮助]-[关于]中查看您使用的软件版本。\n")

                                );

    }
    else if(current->text(0)==QString("数据库操作"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                    QString("数据库文件名：BeaconDB.db\n"
                             "请勿擅自变更数据库名，以免软件连接数据库失败。\n")
                    +QString("数据库表文件名：iBeaconFromSerial   iBeaconFromSocket\n"
                             "串口和网络接收的数据包默认分别存入到两个库表中，相互独立。"
                             "请勿擅自变更数据库表名，以免读写数据失败。\n\n")

                    +QString("保存BLE数据包到数据库：\n"
                             "若BLE数据中心已开始解析，并且表格中有数据展示时，当点击[保存]按钮时，会提示是否保存到据库数据库，"
                             "该选项可以让表格中的实时数据自动写入到对应的数据库表文件。\n")
                    +QString("查看和编辑数据库表：\n"
                             "可以通过[工具]中的[数据库编辑工具]打开SQLiteStudio可视化工具，该工具可以方便地查看和编辑数据库表文件。\n")
                                );

    }
    else if(current->text(0)==QString("查看报告"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于查看、编辑生成的报告\n\n")
                               +QString("报告在[串口]和[TCP/IP]栏目下的BLE数据中心中生成，点击保存生成报告文件，"
                                        "报告默认路径在该软件exe相同路径下，文件格式为txt文本文件。\n")
                               +QString("查看报告会定位到报告保存的路径，打开指定文件会调用系统默认的文本查看软件（win下为记事本）。\n")
                               );

    }
    else if(current->text(0)==QString("音效开关"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于打开/关闭软件音效\n\n")
                               +QString("该软件在按钮点击和打开文件的时候加入了提示音效，用户可选择打开或关闭，默认打开。\n")

                               );

    }
    else if(current->text(0)==QString("TcpServer测试程序"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于打开软件附带的TCP测试工具\n\n")
                               +QString("该工具基于Qt5.6.0编写，作为TCP服务端，本软件作为TCP客户端，可以方便地测试本软件的TCP功能。\n")
                               +QString("该工具无任何病毒，某些杀毒软件可能会误报！该工具在tools目录下。\n")
                               );

    }
    else if(current->text(0)==QString("icSearcher工具"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于打开软件附带的芯片查询工具\n\n")
                               +QString("该工具可以方便地查询芯片手册及相关资料，使用前请联网。第三方工具，不保证有效性。\n")
                               +QString("该工具无任何病毒，某些杀毒软件可能会误报！该工具在tools目录下。\n")
                               );

    }
    else if(current->text(0)==QString("串口监控精灵"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于打开软件附带的串口监控工具\n\n")
                               +QString("该工具便于用户实时监控串口通讯中的数据，比本软件的串口助手功能更加全面。第三方工具，不保证有效性。\n")
                               +QString("该工具无任何病毒，某些杀毒软件可能会误报！该工具在tools目录下。\n")
                               );

    }
    else if(current->text(0)==QString("SQLite可视化工具"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("用于打开软件内嵌的SQLite可视化编辑工具\n\n")
                               +QString("该工具便于用户查看和编辑数据库表文件，以监视数据是否已正确存入数据库。第三方工具，不保证有效性。\n")
                               +QString("该工具无任何病毒，某些杀毒软件可能会误报！该工具在tools目录下。\n")
                               );

    }
    else if(current->text(0)==QString("联系我们"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("更新说明以及四川红宇信息科技公司服务信息\n")
                               +QString("您在使用过程中遇到的任何问题请及时反馈给我们。\n")
                               );

    }
    else if(current->text(0)==QString("安全退出"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("关闭程序所有线程，退出应用程序。\n")

                               );

    }
    else if(current->text(0)==QString("关于"))
    {
        ui->textBrowser_help->clear();
        ui->textBrowser_help->append(
                                QString("本软件基于Qt5.6.0开发，您在使用过程中遇到的任何Bug请反馈给作者：QQ328237809\n\n"
                                        "版本号：v1.0\n")
                                +QString("版权声明：版权归四川红宇创智信息科技公司所有\n")
                                +QString("http://www.scishine.net/")
                               );

    }
}

bool BeaconControlCenter::connectSQLite(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Database Error!";
        return false;
    }
    return true;
}

//1.生成报告文件
//2.写入到数据库表（SQLite3）
void BeaconControlCenter::on_pushButton_saveBLE1_clicked()
{
    int buttonNum=2;

    buttonNum=QMessageBox::information(this,tr("选择"),tr("请选择您要保存的类型？"),
                                       tr("报告文件"),tr("数据库表文件"),tr("取消"),2);

    if(buttonNum==0)
    {
    qDebug()<<"生成报告文件";
    QString fileName=QFileDialog::getSaveFileName(this,tr("保存"),
                                  QCoreApplication::applicationDirPath()+"/serialReport",
                                  "Text files(*.txt)");
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite))
        {
            if(!soundFlag)QSound::play(":/sounds/sound/wrong.wav");
            //qDebug()<<"cannot open the file for writting..";
        }
        QTextStream out(&file);
        QDateTime time=QDateTime::currentDateTime();
        QString textTime=time.toString("yyyy-MM-dd hh:mm:ss dddd");

       out<<QStringLiteral("报告编号")<<QString::number(mReportNo)<<"\r\n"
          <<"-----------------------------------------\r\n";
        if(mSerialport==NULL)
            goto NONE;
        out<<QStringLiteral("本次串口通信：") <<"\r\n"
           <<QStringLiteral("串口号：")<<mSerialport->portName() <<"\r\n"
           <<QStringLiteral("波特率：")<<QString::number(mSerialport->baudRate())<<"\r\n"
           <<QStringLiteral("校验位：")<<QString::number(mSerialport->parity()) <<"\r\n"
           <<QStringLiteral("数据位：")<<QString::number(mSerialport->dataBits()) <<"\r\n"
           <<QStringLiteral("停止位：")<<QString::number(mSerialport->stopBits()) <<"\r\n"
           <<QStringLiteral("累计接收：")<<QString::number(mSerialRecvNum) <<"\r\n"
           <<QStringLiteral("累计发送：")<<QString::number(mSerialSendNum) <<"\r\n"
           <<QStringLiteral("共解析BLE数据包：")<<QString::number(mSerialBLEpackageNum) <<"\r\n"
           <<QStringLiteral("数据包如下：")<<"\r\n";
        for(int i=0;i<ui->tableWidget_BLE1->rowCount();++i)
        {
            out<<QStringLiteral("BLE包编号：")<<i<<"\r\n"
               <<QStringLiteral("Flags：")<<ui->tableWidget_BLE1->item(i,0)->text()<<"\r\n"
               <<QStringLiteral("major")<<ui->tableWidget_BLE1->item(i,1)->text()<<"\r\n"
               <<QStringLiteral("minor")<<ui->tableWidget_BLE1->item(i,2)->text()<<"\r\n"
               <<QStringLiteral("RSSI：")<<ui->tableWidget_BLE1->item(i,3)->text()<<"\r\n"
               <<QStringLiteral("Sensor Data：")<<ui->tableWidget_BLE1->item(i,4)->text()<<"\r\n"
               <<QStringLiteral("UUID：")<<ui->tableWidget_BLE1->item(i,5)->text()<<"\r\n";
        }
        goto END;
NONE:
        out<<QStringLiteral("串口通信未进行")<<"\r\n";
END:
        out<<QStringLiteral("----------------------------------------")<<"\r\n"
           <<QStringLiteral("四川红宇科技公司研发部     报告日期：")<<textTime<<"\r\n";

        //qDebug()<<"write the file succeed";

    }
    QDesktopServices::openUrl(QUrl(fileName));
    if(!soundFlag)QSound::play(":/sounds/sound/success.wav");
    mReportNo++;
    }

    if(buttonNum==1)
    {
        qDebug()<<"生成数据库表文件";
        if(connectSQLite("BeaconDB.db"))
        {
            qDebug()<<"connect SQL successfully";
            for(int i=0;i<ui->tableWidget_BLE1->rowCount();++i)
            {
                QSqlQuery query;
                qDebug()<<ui->tableWidget_BLE1->rowCount();
                query.prepare("INSERT INTO iBeaconFromSerial(Flags,major,minor,RSSI,SensorData,UUID)"
                           "VALUES(?,?,?,?,?,?)");
                query.addBindValue(ui->tableWidget_BLE1->item(i,0)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE1->item(i,1)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE1->item(i,2)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE1->item(i,3)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE1->item(i,4)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE1->item(i,5)->text().toLatin1().data());
                query.exec();
                if(query.lastError().isValid())
                   QMessageBox::information(this,"数据库错误",query.lastError().text(),QMessageBox::Cancel);
            }
        }
    }

}

//1.生成报告文件
//2.写入到数据库表（SQLite3）
void BeaconControlCenter::on_pushButton_saveBLE2_clicked()
{
    int buttonNum=2;

    buttonNum=QMessageBox::information(this,tr("选择"),tr("请选择您要保存的类型？"),
                                       tr("报告文件"),tr("数据库表文件"),tr("取消"),2);

    if(buttonNum==0)
    {
    qDebug()<<"生成报告文件";
    QString fileName=QFileDialog::getSaveFileName(this,tr("保存"),
                                  QCoreApplication::applicationDirPath()+"/socketReport",
                                  "Text files(*.txt)");

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadWrite))
        {
            if(!soundFlag)QSound::play(":/sounds/sound/wrong.wav");
            //qDebug()<<"cannot open the file for writting..";
        }
        QTextStream out(&file);
        QDateTime time=QDateTime::currentDateTime();
        QString textTime=time.toString("yyyy-MM-dd hh:mm:ss dddd");

        out<<QStringLiteral("报告编号")<<QString::number(mReportNo)<<"\r\n"
           <<"-----------------------------------------\r\n"
           <<QStringLiteral("本次socket通信：") <<"\r\n"
           <<QStringLiteral("集总器IP地址：")<<mServerIPAdress.toString() <<"\r\n"
           <<QStringLiteral("集总器Port:");
           if(mServerPort!=0)out<<QString::number(mServerPort)<<"\r\n";
           else out<<"\r\n";//socket未通信
        out<<QStringLiteral("累计接收：")<<QString::number(mSocketRecvNum) <<"\r\n"
           <<QStringLiteral("累计发送：")<<QString::number(mSocketSendNum) <<"\r\n"
           <<QStringLiteral("共解析BLE数据包：")<<QString::number(mSocketBLEpackageNum) <<"\r\n"
           <<QStringLiteral("数据包如下：\r\n");
        for(int i=0;i<ui->tableWidget_BLE2->rowCount();++i)
        {
            out<<QStringLiteral("BLE包编号：")<<i<<"\r\n"
              <<QStringLiteral("Flags：")<<ui->tableWidget_BLE2->item(i,0)->text()<<"\r\n"
              <<QStringLiteral("major")<<ui->tableWidget_BLE2->item(i,1)->text()<<"\r\n"
              <<QStringLiteral("minor")<<ui->tableWidget_BLE2->item(i,2)->text()<<"\r\n"
              <<QStringLiteral("RSSI：")<<ui->tableWidget_BLE2->item(i,3)->text()<<"\r\n"
              <<QStringLiteral("Sensor Data：")<<ui->tableWidget_BLE2->item(i,4)->text()<<"\r\n"
              <<QStringLiteral("UUID：")<<ui->tableWidget_BLE2->item(i,5)->text()<<"\r\n";
        }
        out<<QStringLiteral("----------------------------------------\r\n")
           <<QStringLiteral("四川红宇创智信息科技公司研发部\r\n")
           <<QStringLiteral("报告生成日期：")<<textTime<<endl;

        //qDebug()<<"write the file succeed";

    }
    QDesktopServices::openUrl(QUrl(fileName));
    if(!soundFlag)QSound::play(":/sounds/sound/success.wav");
    mReportNo++;
    }

    if(buttonNum==1)
    {
        qDebug()<<"生成数据库表文件";
        if(connectSQLite("BeaconDB.db"))
        {
            qDebug()<<"connect SQL successfully";
            for(int i=0;i<ui->tableWidget_BLE2->rowCount();++i)
            {
                QSqlQuery query;
                qDebug()<<ui->tableWidget_BLE2->rowCount();
                query.prepare("INSERT INTO iBeaconFromSocket(Flags,major,minor,RSSI,SensorData,UUID)"
                           "VALUES(?,?,?,?,?,?)");
                query.addBindValue(ui->tableWidget_BLE2->item(i,0)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE2->item(i,1)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE2->item(i,2)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE2->item(i,3)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE2->item(i,4)->text().toLatin1().data());
                query.addBindValue(ui->tableWidget_BLE2->item(i,5)->text().toLatin1().data());
                query.exec();
                if(query.lastError().isValid())
                   QMessageBox::information(this,"数据库错误",query.lastError().text(),QMessageBox::Cancel);
            }
        }
    }
}

void BeaconControlCenter::on_pushButton_report_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("打开"),QCoreApplication::applicationDirPath(),
                                 "Text files(*.txt)");
    if(!fileName.isEmpty())
    {
        if(!soundFlag)QSound::play(":/sounds/sound/success.wav");
        QDesktopServices::openUrl(QUrl(fileName));
    }
    else
        if(!soundFlag)QSound::play(":/sounds/sound/wrong.wav");
}

void BeaconControlCenter::on_pushButton_tcpServer_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    QString appName=QCoreApplication::applicationDirPath()+"/tools/tcpServer/TcpServer_Test.exe";
    QProcess *toolProcess = new QProcess;
    toolProcess->start(appName);
}

void BeaconControlCenter::on_pushButton_ic_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    QString appName=QCoreApplication::applicationDirPath()+"/tools/icSearcher/icSearcher.exe";
    QProcess *toolProcess = new QProcess;
    toolProcess->start(appName);
}

void BeaconControlCenter::on_pushButton_com_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    QString appName=QCoreApplication::applicationDirPath()+"/tools/commMonitor6.1/CommMonitor.exe";
    QProcess *toolProcess = new QProcess;
    toolProcess->start(appName);
}

void BeaconControlCenter::on_pushButton_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    QString appName=QCoreApplication::applicationDirPath()+"/tools/SQLiteStudio/sqlitestudio-2.1.5.exe";
    QProcess *toolProcess = new QProcess;
    toolProcess->start(appName);
}

void BeaconControlCenter::on_pushButton_contact_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    QDesktopServices::openUrl(QUrl(QString("http://www.scishine.net/")));
    QDesktopServices::openUrl(QUrl(QString(QCoreApplication::applicationDirPath()+"/readme.txt")));
}

void BeaconControlCenter::on_pushButton_quit_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    int reply=QMessageBox::information(this,QString("温馨提示"),QString("您确定要退出吗?"),
                                   tr("确定"),tr("取消"));

    if(reply==tr("确定").toInt())emit closeTitle();
}

void BeaconControlCenter::on_pushButton_sound_clicked()
{
    if(!soundFlag)QSound::play(":/sounds/sound/btn1.wav");
    soundFlag=~soundFlag;
    if(soundFlag)ui->pushButton_sound->setStyleSheet("QPushButton{border-image: url(:/images/btn/no_sound.jpg);}");
    else ui->pushButton_sound->setStyleSheet("QPushButton{border-image: url(:/images/btn/sound.jpg);}");
}


void BeaconControlCenter::on_pushButton_startBLE1_clicked()
{


    //定时调用BLE解析函数

     if(ui->pushButton_startBLE1->text()==QString("开始"))
     {
         /*
         //test
         //集总器实际发送的数据包已转换为字符串，两个字符表示一个十六进制，如“05”表示0x05
          char* sendData="ble02011a1aff4c000215e2c56db5dffb48d2b060d0f5a71096e000000000c511223344#";
          //上位机将串口接收到的数据包转换成QString
          QByteArray recvData(sendData);
          QString readyToParseData(recvData.data());
          qDebug()<<readyToParseData;
          //模拟串口接收到数据包进队
          mSerialBLEpackageQueue->enqueue(readyToParseData);
           */

          parseTimer1->start(1000);//每隔一秒，取出缓存队列进行解析
          ui->pushButton_startBLE1->setText(QString("暂停"));
     }
     else
     {
         parseTimer1->stop();
         ui->pushButton_startBLE1->setText(QString("开始"));
     }


}

void BeaconControlCenter::startToParseBLE1()
{
    parseBLEpackage(mSerialBLEpackageQueue,mSerialParsedQueue);
    /*test
    qDebug()<<mSerialBLEpackageQueue->isEmpty();
    if(!mSerialParsedQueue->isEmpty())
    {
         foreach(BLEPackage e,*mSerialParsedQueue)
         {
             qDebug()<<"FLAGS:"<<e.flags
                     <<"UUID:"<<e.uuid
                     <<"MAJOR:"<<e.major
                     <<"MINOR:"<<e.minor
                     <<"RSSI:"<<e.rssi
                     <<"DATA:"<<e.sensorData;
         }
    }
    */
    //更新到BLE1表格显示
    while(!mSerialParsedQueue->isEmpty())
    {
        BLEPackage packageToShow=mSerialParsedQueue->dequeue();
        mSerialBLEpackageNum++;
        ui->tableWidget_BLE1->setRowCount(ui->tableWidget_BLE1->rowCount()+1);//增加一行
        QTableWidgetItem *flagsItem = new QTableWidgetItem(packageToShow.flags);
        QTableWidgetItem *majorItem = new QTableWidgetItem(packageToShow.major);
        QTableWidgetItem *minorItem = new QTableWidgetItem(packageToShow.minor);
        QTableWidgetItem *rssiItem = new QTableWidgetItem(packageToShow.rssi);
        QTableWidgetItem *sensorDataItem = new QTableWidgetItem(packageToShow.sensorData);
        QTableWidgetItem *uuidItem = new QTableWidgetItem(packageToShow.uuid);

        ui->tableWidget_BLE1->setItem(ui->tableWidget_BLE1->rowCount()-1,0,flagsItem);
        ui->tableWidget_BLE1->setItem(ui->tableWidget_BLE1->rowCount()-1,1,majorItem);
        ui->tableWidget_BLE1->setItem(ui->tableWidget_BLE1->rowCount()-1,2,minorItem);
        ui->tableWidget_BLE1->setItem(ui->tableWidget_BLE1->rowCount()-1,3,rssiItem);
        ui->tableWidget_BLE1->setItem(ui->tableWidget_BLE1->rowCount()-1,4,sensorDataItem);
        ui->tableWidget_BLE1->setItem(ui->tableWidget_BLE1->rowCount()-1,5,uuidItem);
    }

}

void BeaconControlCenter::on_pushButton_startBLE2_clicked()
{
    if(ui->pushButton_startBLE2->text()==QString("开始"))
    {
        /*
        //test
        //集总器实际发送的数据包已转换为字符串，两个字符表示一个十六进制，如“05”表示0x05
         char* sendData="ble02011a1aff4c000215e2c56db5dffb48d2b060d0f5a71096e000000000c511223344#";
         //上位机将网络接收到的数据包转换成QString
         QByteArray recvData(sendData);
         QString readyToParseData(recvData.data());
         qDebug()<<readyToParseData;
         //模拟网口接收到数据包进队
         mSocketBLEpackageQueue->enqueue(readyToParseData);
         */

         parseTimer2->start(1000);//每隔一秒，取出缓存队列进行解析
         ui->pushButton_startBLE2->setText(QString("暂停"));
    }
    else
    {
        parseTimer2->stop();
        ui->pushButton_startBLE2->setText(QString("开始"));
    }
}

void BeaconControlCenter::startToParseBLE2()
{
    parseBLEpackage(mSocketBLEpackageQueue,mSocketParsedQueue);
    /*test
    qDebug()<<mSocketBLEpackageQueue->isEmpty();
    if(!mSocketParsedQueue->isEmpty())
    {
         foreach(BLEPackage e,*mSocketParsedQueue)
         {
             qDebug()<<"FLAGS:"<<e.flags
                     <<"UUID:"<<e.uuid
                     <<"MAJOR:"<<e.major
                     <<"MINOR:"<<e.minor
                     <<"RSSI:"<<e.rssi
                     <<"DATA:"<<e.sensorData;
         }
    }
    */
    //更新到BLE2表格显示
    while(!mSocketParsedQueue->isEmpty())
    {
        BLEPackage packageToShow=mSocketParsedQueue->dequeue();
        mSocketBLEpackageNum++;
        ui->tableWidget_BLE2->setRowCount(ui->tableWidget_BLE2->rowCount()+1);//增加一行
        QTableWidgetItem *flagsItem = new QTableWidgetItem(packageToShow.flags);
        QTableWidgetItem *majorItem = new QTableWidgetItem(packageToShow.major);
        QTableWidgetItem *minorItem = new QTableWidgetItem(packageToShow.minor);
        QTableWidgetItem *rssiItem = new QTableWidgetItem(packageToShow.rssi);
        QTableWidgetItem *sensorDataItem = new QTableWidgetItem(packageToShow.sensorData);
        QTableWidgetItem *uuidItem = new QTableWidgetItem(packageToShow.uuid);

        ui->tableWidget_BLE2->setItem(ui->tableWidget_BLE2->rowCount()-1,0,flagsItem);
        ui->tableWidget_BLE2->setItem(ui->tableWidget_BLE2->rowCount()-1,1,majorItem);
        ui->tableWidget_BLE2->setItem(ui->tableWidget_BLE2->rowCount()-1,2,minorItem);
        ui->tableWidget_BLE2->setItem(ui->tableWidget_BLE2->rowCount()-1,3,rssiItem);
        ui->tableWidget_BLE2->setItem(ui->tableWidget_BLE2->rowCount()-1,4,sensorDataItem);
        ui->tableWidget_BLE2->setItem(ui->tableWidget_BLE2->rowCount()-1,5,uuidItem);
    }
}


void BeaconControlCenter::on_pushButton_serialClear2_clicked()
{
    QList<QTableWidgetSelectionRange>ranges=ui->tableWidget_BLE1->selectedRanges();
    int count=ranges.count();
    for(int i=0;i<count;i++)
    {
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++)
        {
  //          qDebug()<<"selectRow"<<j;
            ui->tableWidget_BLE1->removeRow(j);
        }
    }
    if(count==0)
    {
        QMessageBox::information(this,"提示","当前未选中任何记录",QMessageBox::Cancel);
    }

}

void BeaconControlCenter::on_pushButton_networkClear2_clicked()
{
    QList<QTableWidgetSelectionRange>ranges=ui->tableWidget_BLE2->selectedRanges();
    int count=ranges.count();
    for(int i=0;i<count;i++)
    {
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++)
        {
  //          qDebug()<<"selectRow"<<j;
            ui->tableWidget_BLE2->removeRow(j);
        }
    }
    if(count==0)
    {
        QMessageBox::information(this,"提示","当前未选中任何记录",QMessageBox::Cancel);
    }
}


