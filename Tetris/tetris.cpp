#include "tetris.h"

Tetris::Tetris(PlayMode mode, QWidget *parent)
	: QMainWindow(parent),
	  m_pSelfGameZone(NULL),
	  m_pOppsiteGameZone(NULL),
	  m_pBaseNetwork(NULL)
{
	ui.setupUi(this);

	this->initTetris(mode);
}

Tetris::~Tetris()
{
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

void Tetris::initTetris( PlayMode mode )
{
	switch (mode)
	{
	case NETWORK:	
		{
			this->statusBar()->showMessage("Network mode.");
		}
		break;
	case SINGLE:
		{
			m_pSelfGameZone = new GameZone(this);
			m_pSelfGameZone->gameStart();
			this->setCentralWidget(m_pSelfGameZone);
			this->statusBar()->showMessage("Single mode.");
		}
		break;
	default:
		break;
	}
}
