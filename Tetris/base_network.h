#ifndef _BASE_NETWORK_
#define _BASE_NETWORK_

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>

const quint16 PORT = 6666;

class BaseNetwork : public QObject
{
	Q_OBJECT
public:
	BaseNetwork();
	~BaseNetwork();

	void initNetwork();
	void uninitNetwork();
	void newListen();
	void createConnection(const QString ipAddr);
public slots:
	void sendData(const QByteArray & data);
	void recvData();
	void acceptConnection();
	// For get data proactively.
	// Description:	This method will disconnect readyRead signal and recvData, 
	//				and connect them after waitForReadyRead.
	// In general, this method is used for exchange something at first.
	QByteArray waitForGetData(int timeout = 30);
signals:
	void errorOccur(QString);
	void dataReceived(QByteArray);
	void connReqAccepted();
protected:
private:
	QTcpServer *	m_pTcpServer;
	QTcpSocket *	m_pTcpSocket;

	BaseNetwork( const BaseNetwork & );
	BaseNetwork & operator=(const BaseNetwork &);
private slots:
	void emitSocketError(QAbstractSocket::SocketError);
};

#endif	// _BASE_NETWORK_