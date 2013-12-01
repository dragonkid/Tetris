#ifndef TETRIS_H
#define TETRIS_H

#include "game_zone.h"
#include "base_network.h"
#include <QtWidgets/QMainWindow>
#include "ui_tetris.h"

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

private:
	Ui::TetrisClass ui;
	GameZone *		m_pSelfGameZone;
	GameZone *		m_pOppsiteGameZone;
	BaseNetwork *	m_pBaseNetwork;

	Tetris( const Tetris & );
	Tetris & operator=( const Tetris & );

	void initTetris( PlayMode mode );
};

#endif // TETRIS_H
