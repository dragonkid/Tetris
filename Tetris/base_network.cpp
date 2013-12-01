#include "base_network.h"
#include "common.h"
#include <QMessageBox>
#include <QByteArray>

void BaseNetwork::initNetwork()
{
	m_pTcpServer = new QTcpServer(this);
	m_pTcpSocket = new QTcpSocket(this);
	// Signal and slots.
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), 
		this, SLOT(showWarnInfo(QAbstractSocket::SocketError)));
	connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
//	connect(m_pSelfGameZone, SIGNAL(keyPressed(int)), this, SLOT(sendData(int)));
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
		Common::showWarnInfo(m_pTcpServer->errorString());
		m_pTcpSocket->close();
		return ;
	}
}


void BaseNetwork::newConnection( const QString ipAddr )
{
	m_pTcpSocket->connectToHost(ipAddr, PORT);
	connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recvData()));
	// Exchange seed.
//	m_pTcpSocket->write(QByteArray::number(m_pSelfGameZone->getRandomSeed()));
}

void BaseNetwork::acceptConnection()
{
	m_pTcpSocket = m_pTcpServer->nextPendingConnection();
	if ( NULL != m_pTcpServer )
	{
		connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
		if ( m_pTcpSocket->waitForReadyRead() )
		{
//			m_pOppsiteGameZone->setRandomSeed(QString(m_pTcpSocket->readAll()).toInt());
//			m_pOppsiteGameZone->gameStart();
		}
		connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recvData()));
	}
}

void BaseNetwork::sendData( int data )
{
	m_pTcpSocket->write(QByteArray::number(data));
}

void BaseNetwork::recvData()
{
	int tmp_iKeyPressed = QString(m_pTcpSocket->readAll()).toInt();
//	m_pOppsiteGameZone->gameControl(tmp_iKeyPressed);
}

void BaseNetwork::showWarnInfo( QAbstractSocket::SocketError )
{
	QMessageBox msgBox;
	msgBox.setText(m_pTcpSocket->errorString());
	msgBox.exec();
}