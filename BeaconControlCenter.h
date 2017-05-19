#ifndef BEACONCONTROLCENTER_H
#define BEACONCONTROLCENTER_H


namespace Ui {
class BeaconControlCenter;
}

typedef struct{
    QString flags;
    QString uuid;
    QString major;
    QString minor;
    QString rssi;
    QString sensorData;

}BLEPackage;



class BeaconControlCenter : public QWidget
{
    Q_OBJECT

public:
    explicit BeaconControlCenter(QWidget *parent = 0);
    ~BeaconControlCenter();
    //解析BLE广播包，传入BLE缓存队列，返回解析好的队表
    void parseBLEpackage(QQueue<QString> *buffQueue,
                                              QQueue<BLEPackage> *parsedList);
    bool connectSQLite(const QString &dbName);

signals:
    void closeTitle();

private slots:
    void on_menuButton_help_clicked();

    void on_menuButton_serial_clicked();

    void on_menuButton_socket_clicked();

    void on_menuButton_tools_clicked();

    void showTime();

    void on_pushButton_refresh_clicked();

    void on_pushButton_openserial_clicked();

    void readUart();

    void handleSerialError(QSerialPort::SerialPortError error);

    void serialTimerUpdate();

    void on_pushButton_serialClear_clicked();

    void on_pushButton_serialSend_clicked();

    void connectToServer();

    void disconnectToServer();

    void sendRequest();

    void readData();

    void handleSocketError(QAbstractSocket::SocketError);

    void on_pushButton_networkClear_clicked();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    
    void on_pushButton_saveBLE1_clicked();

    void on_pushButton_saveBLE2_clicked();

    void on_pushButton_report_clicked();

    void on_pushButton_tcpServer_clicked();

    void on_pushButton_ic_clicked();

    void on_pushButton_com_clicked();

    void on_pushButton_contact_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_sound_clicked();

    void on_pushButton_startBLE1_clicked();

    void startToParseBLE1();
    void startToParseBLE2();

    void on_pushButton_startBLE2_clicked();

    void on_pushButton_serialClear2_clicked();

    void on_pushButton_networkClear2_clicked();


    void on_pushButton_clicked();

private:
    Ui::BeaconControlCenter *ui;

    int soundFlag=0;//音效开关：默认打开
    QTimer *parseTimer1;//BLE1
    QTimer *parseTimer2;//BLE2

    QSerialPort *mSerialport=NULL;
    QByteArray mSerialRecvData=0;
    QByteArray mSerialSendData=0;
    int mSerialRecvNum=0;
    int mSerialSendNum=0;
    QTimer *serialTimer;//串口超时处理定时器

    QTcpSocket *mSocket=NULL;
    QHostAddress mServerIPAdress;
    int mServerPort=0;
    QByteArray mSocketRecvData=0;
    QByteArray mSocketSendData=0;
    int mSocketRecvNum=0;
    int mSocketSendNum=0;

    int mReportNo=0;
    int mSerialBLEpackageNum=0;//串口收到的BLE数据包个数
    int mSocketBLEpackageNum=0;//TCP收到的BLE数据包个数

    QQueue<QString> *mSerialBLEpackageQueue;//串口接收的BLE数据包缓存队列
    QQueue<QString> *mSocketBLEpackageQueue;//串口接收的BLE数据包缓存队列
    QQueue<BLEPackage> *mSerialParsedQueue;//解析后的BLE数据包队列(串口)
    QQueue<BLEPackage> *mSocketParsedQueue;//解析后的BLE数据包队列(Socket)

};

#endif // BEACONCONTROLCENTER_H
