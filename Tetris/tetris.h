#ifndef TETRIS_H
#define TETRIS_H

#include "game_zone.h"
#include "base_network.h"
#include "ui_tetris.h"
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

typedef enum
{
	SINGLE,
	NETWORK
} PlayMode;

class Tetris : public QMainWindow
{
	Q_OBJECT

public:
	Tetris(PlayMode mode = SINGLE, QWidget *parent = 0);
	~Tetris();
private:	// const values.
	const int PREVIEW_ZONE_WIDTH;
	const int PREVIEW_ZONE_HEIGHT;
private:
	Ui::TetrisClass ui;
	QWidget *		m_pCentralWidget;
	GameZone *		m_pSelfGameZone;
	GameZone *		m_pOppsiteGameZone;
	BaseNetwork *	m_pBaseNetwork;
	BaseShape *		m_pNextShape;
	QGraphicsView * m_pPreviewZone;
	QGraphicsScene* m_pPreviewScene;
	QHBoxLayout *	m_pHLayout;
	QVBoxLayout *	m_pVLayout;
	QLabel *		m_pLabelPreview;
	QLabel *		m_pLabelIP;
	QLineEdit *		m_pEditIP;
	QPushButton *	m_pConnectButton;

	Tetris( const Tetris & );
	Tetris & operator=( const Tetris & );

	void initTetris( PlayMode mode );
	void initMiddleZone( PlayMode mode );
	void exchangeRandomSeed();
private slots:
	void previewNextShape(int);
	void connRequest();
	void connEstablished();
	void showStatusMsg(QString);
};

#endif // TETRIS_H
