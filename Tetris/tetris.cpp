#include "tetris.h"

Tetris::Tetris(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_pGameZone = new GameZone(this);
	m_pGameZone->show();
	m_pGameZone->gameStart();

	this->setMinimumWidth(m_pGameZone->width());
	this->setMinimumHeight(m_pGameZone->height());
}

Tetris::~Tetris()
{
	delete m_pGameZone;
	m_pGameZone = NULL;
}
