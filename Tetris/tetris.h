#ifndef TETRIS_H
#define TETRIS_H

#include "game_zone.h"
#include "base_network.h"
#include "ui_tetris.h"
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

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
	QLabel *		m_pLabel;

	Tetris( const Tetris & );
	Tetris & operator=( const Tetris & );

	void initTetris( PlayMode mode );
	void initMiddleZone( /*PlayMode mode*/ );
private slots:
	void previewNextShape(int);
};

#endif // TETRIS_H
