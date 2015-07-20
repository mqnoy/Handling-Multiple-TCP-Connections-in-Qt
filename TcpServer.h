#ifndef NATIVE_LAUNCHER_H
#define NATIVE_LAUNCHER_H

#include <QTcpSocket>
#include <QTcpServer>

class NLTcpSocket;

class TcpServer : public QObject
{
    Q_OBJECT
private:
	QTcpServer *server;
public:
		TcpServer(QObject *parent=0);
		~TcpServer();
    public slots:
        void slotNewConnection();
        void slotReceive(NLTcpSocket* socket);
        void slotDisconnectSocket(NLTcpSocket* socket);
};

#endif