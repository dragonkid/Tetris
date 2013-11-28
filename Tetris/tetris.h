#ifndef TETRIS_H
#define TETRIS_H

#include "game_zone.h"
#include <QtWidgets/QMainWindow>
#include "ui_tetris.h"
#include <QTcpServer>
#include <QTcpSocket>

class Tetris : public QMainWindow
{
	Q_OBJECT

public:
	Tetris(QWidget *parent = 0);
	~Tetris();

private:
	Ui::TetrisClass ui;
	GameZone *		m_pSelfGameZone;
	GameZone *		m_pOppsiteGameZone;

	void showErrorInfo(const QString errorInfo);
	// Network
	QTcpServer *	m_pTcpServer;
	QTcpSocket *	m_pTcpSocket;
	//bool			m_bSeedExchanged;

	void initNetwork();
	void uninitNetwork();
	void newListen();
	void newConnection(const QString ipAddr);
private slots:
	void showErrorInfo(QAbstractSocket::SocketError);	void sendData(int);
	void recvData();
	void acceptConnection();
};

#endif // TETRIS_H
