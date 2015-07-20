#include "TcpServer.h"
#include "NLTcpSocket.h"
#include <QProcess>
#include <QString>
#include <QtGui>

#define PORT 7474

TcpServer::TcpServer(QObject *parent)
                           : QObject(parent)
{
    server = new QTcpServer();
    connect(server, SIGNAL(newConnection()),
                    this, SLOT(slotNewConnection()));

    if(!server->listen(QHostAddress::Any, PORT))
    {
        qDebug()<< "Server Could Not be Started";
        return;
    }
    else
    {
        qDebug()<< "Server Started";
    }
}

TcpServer::~TcpServer()
{
}

void TcpServer::slotNewConnection()
{
    qDebug()<<"Connected";
    QTcpSocket* socket = server->nextPendingConnection();
    NLTcpSocket* customSocket = new NLTcpSocket(socket);
    socket->write("Hello Client");
    connect(customSocket, SIGNAL(dataReady(NLTcpSocket*)),this, SLOT(slotReceive(NLTcpSocket*)));
    connect(customSocket, SIGNAL(socketDisconnected(NLTcpSocket*)),this, SLOT(slotDisconnectSocket(NLTcpSocket*)));
}

void TcpServer::slotReceive(NLTcpSocket* socket)
{
    QString dataReceived = socket->getData();
    //socket->write(response); One can use NLTcpSocket write function to send data
}

void TcpServer::slotDisconnectSocket(NLTcpSocket* socket)
{
    delete socket;
    qDebug()<< "Disconnected";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString executablePath = QCoreApplication::applicationDirPath();
    QDir::setCurrent(executablePath);
    TcpServer tcpServer;
    return app.exec();
}
