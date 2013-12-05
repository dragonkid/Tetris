#include "base_network.h"
#include "common.h"
#include <QMessageBox>
#include <QByteArray>

void BaseNetwork::initNetwork()
{
	m_pTcpServer = new QTcpServer(this);
	m_pTcpSocket = new QTcpSocket(this);
	// Signal and slots.
	bool tmp_bTest;
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), 
		this, SLOT(emitSocketError(QAbstractSocket::SocketError)));
	connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
	connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void BaseNetwork::uninitNetwork()
{
	if ( NULL == m_pTcpServer )
	{
		delete m_pTcpServer;
		m_pTcpServer = NULL;
	}
	if ( NULL == m_pTcpSocket )
	{
		delete m_pTcpSocket;
		m_pTcpSocket = NULL;
	}
}

void BaseNetwork::newListen()
{
	if ( false == m_pTcpServer->listen(QHostAddress::Any, PORT) )
	{
		// When debug, both run in one machine. So this line need to be annotated.
		//m_pTcpSocket->close();
		emit errorOccur(m_pTcpServer->errorString());
		return ;
	}
}


void BaseNetwork::createConnection( const QString ipAddr )
{
	m_pTcpSocket->connectToHost(ipAddr, PORT);
	connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recvData()));
	// Exchange seed.
//	m_pTcpSocket->write(QByteArray::number(m_pSelfGameZone->getRandomSeed()));
}

void BaseNetwork::acceptConnection()
{
	m_pTcpSocket = m_pTcpServer->nextPendingConnection();
	if ( NULL != m_pTcpSocket )
	{
		connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
		//if ( m_pTcpSocket->waitForReadyRead() )
		//{
		//	m_pOppsiteGameZone->setRandomSeed(QString(m_pTcpSocket->readAll()).toInt());
		//	m_pOppsiteGameZone->gameStart();
		//}
		connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recvData()));
		emit connEstablished();
	}
}

//void basenetwork::senddata( int data )
//{
//	m_ptcpsocket->write(qbytearray::number(data));
//}

//void BaseNetwork::recvData()
//{
//	int tmp_iKeyPressed = QString(m_pTcpSocket->readAll()).toInt();
////	m_pOppsiteGameZone->gameControl(tmp_iKeyPressed);
//}

void BaseNetwork::emitSocketError( QAbstractSocket::SocketError )
{
	emit errorOccur(m_pTcpSocket->errorString());
}

void BaseNetwork::sendData( const QByteArray & data )
{
	m_pTcpSocket->write(data);
}

void BaseNetwork::recvData()
{
	QByteArray tmp_qData = m_pTcpSocket->readAll();
	emit dataReceived(tmp_qData);
}

BaseNetwork::BaseNetwork()
{
	this->initNetwork();
}

BaseNetwork::~BaseNetwork()
{
	this->uninitNetwork();
}
