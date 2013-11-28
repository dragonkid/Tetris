#include "tetris.h"
#include <QMessageBox>
#include <QByteArray>

const quint16 PORT = 6666;

#define _SELF_

Tetris::Tetris(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

#ifdef _SELF_
	m_pSelfGameZone = new GameZone(SELF, this);
	this->initNetwork();
	m_pSelfGameZone->gameStart();
	this->setMinimumWidth(m_pSelfGameZone->width());
	this->setMinimumHeight(m_pSelfGameZone->height());

	this->newConnection("127.0.0.1");
#else
	m_pOppsiteGameZone = new GameZone(OPPOSITE, this);
	this->initNetwork();
	this->setMinimumWidth(m_pOppsiteGameZone->width());
	this->setMinimumHeight(m_pOppsiteGameZone->height());

	this->newListen();
#endif
}

Tetris::~Tetris()
{
	this->uninitNetwork();

	if ( NULL == m_pSelfGameZone )
	{
		delete m_pSelfGameZone;
		m_pSelfGameZone = NULL;
	}
	if ( NULL == m_pOppsiteGameZone )
	{
		delete m_pOppsiteGameZone;
		m_pOppsiteGameZone = NULL;
	}
}

void Tetris::showErrorInfo( const QString errorInfo )
{
	QMessageBox msgBox;
	msgBox.setText(errorInfo);
	msgBox.exec();
}

void Tetris::showErrorInfo( QAbstractSocket::SocketError )
{
	QMessageBox msgBox;
	msgBox.setText(m_pTcpSocket->errorString());
	msgBox.exec();
}

void Tetris::newListen()
{
	if ( false == m_pTcpServer->listen(QHostAddress::Any, PORT) )
	{
		this->showErrorInfo(m_pTcpServer->errorString());
		m_pTcpSocket->close();
		return ;
	}
}

void Tetris::newConnection( const QString ipAddr )
{
	m_pTcpSocket->connectToHost(ipAddr, PORT);
	connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recvData()));
	// Exchange seed.
	m_pTcpSocket->write(QByteArray::number(m_pSelfGameZone->getRandomSeed()));
}

void Tetris::acceptConnection()
{
	m_pTcpSocket = m_pTcpServer->nextPendingConnection();
	if ( NULL != m_pTcpServer )
	{
		connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
		if ( m_pTcpSocket->waitForReadyRead() )
		{
			m_pOppsiteGameZone->setRandomSeed(QString(m_pTcpSocket->readAll()).toInt());
			m_pOppsiteGameZone->gameStart();
		}
		connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recvData()));
	}
}

void Tetris::sendData( int data )
{
	m_pTcpSocket->write(QByteArray::number(data));
}

void Tetris::recvData()
{
	int tmp_iKeyPressed = QString(m_pTcpSocket->readAll()).toInt();
	m_pOppsiteGameZone->gameControl(tmp_iKeyPressed);
}

void Tetris::initNetwork()
{
	m_pTcpServer = new QTcpServer(this);
	m_pTcpSocket = new QTcpSocket(this);
	// Signal and slots.
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), 
		    this, SLOT(showErrorInfo(QAbstractSocket::SocketError)));
	connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));
	connect(m_pSelfGameZone, SIGNAL(keyPressed(int)), this, SLOT(sendData(int)));
	connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void Tetris::uninitNetwork()
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
