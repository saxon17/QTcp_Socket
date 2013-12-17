#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ip = ui->lineEdit;
    port = ui->lineEdit_2;
    messageBrowser = ui->textBrowser;
    tcpSocket = new QTcpSocket(this);

    //commit

    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(showError(QAbstractSocket::SocketError)));

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));


}

void MainWindow::newConnect()
{
    messageBrowser->append(QString("开始连接到%1使用端口：%2...\n").arg(ip->text()).arg(port->text()));
    blockSize = 0;//初始大小为零
    tcpSocket->abort();//清除已有连接
    tcpSocket->connectToHost(ui->lineEdit->text(),ui->lineEdit_2->text().toInt());
    if(tcpSocket->waitForConnected(3000))
    {
        messageBrowser->append("连接成功！\n");
    }
    else
    {
        messageBrowser->append("连接失败！\n");
    }

}

void MainWindow::readMessage()
{
    messageBrowser->append("开始读取数据...");
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);
    if(0==blockSize)//如果是开始接收数据
    {
        if(tcpSocket->bytesAvailable()<(int)sizeof(quint16))  return;//判断是否有表示数据大小的两个字节的数据，没有就返回

        in>>blockSize;//有则输出到表示数据大小的变量中
    }
    if(tcpSocket->bytesAvailable()<blockSize)
        return;//如果未收到全部信息就返回

//    QTextCodec *code = QTextCodec::codeForName("utf8");

    in>>message;  //否则表示接收完毕把数据放到message中；

    messageBrowser->append(QString("接收完毕\n接收到的数据为：%1\n").arg(message));
    blockSize=0;
    message.clear();

}

void MainWindow::showError(QAbstractSocket::SocketError)
{
    messageBrowser->append(QString("接收数据错误...\n错误信息：%1\n").arg(tcpSocket->errorString()));

}


MainWindow::~MainWindow()
{
    delete ui;
    delete ip;
    delete port;
    delete tcpSocket;
}

void MainWindow::on_pushButton_clicked()
{
    newConnect();
}
