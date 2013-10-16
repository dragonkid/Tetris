#include "tetris.h"

Tetris::Tetris(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pGameZone = new GameZone(this);
	m_pGameZone->initView();
	m_pGameZone->show();
}

Tetris::~Tetris()
{
	delete m_pGameZone;
	m_pGameZone = NULL;
}
