#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
//#include <QString>
class QLineEdit;
class QTextBrowser;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newConnect();
    void readMessage();
    void showError(QAbstractSocket::SocketError);

    void on_pushButton_clicked();

private:
    QLineEdit *ip,*port;
    QTextBrowser *messageBrowser;
    QTcpSocket *tcpSocket;
    QString message;
    quint16 blockSize;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
