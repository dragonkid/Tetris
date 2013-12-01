#ifndef _BASE_NETWORK_
#define _BASE_NETWORK_

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

const quint16 PORT = 6666;

class BaseNetwork : public QObject
{
public:
	BaseNetwork();
	~BaseNetwork();

	void initNetwork();
	void uninitNetwork();
	void newListen();
	void newConnection(const QString ipAddr);
public slots:
	void showWarnInfo(QAbstractSocket::SocketError);
	void sendData(int);
	void recvData();
	void acceptConnection();
protected:
private:
	QTcpServer *	m_pTcpServer;
	QTcpSocket *	m_pTcpSocket;

	BaseNetwork( const BaseNetwork & );
	BaseNetwork & operator=(const BaseNetwork &);
};

#endif	// _BASE_NETWORK_