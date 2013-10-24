#include "tetris.h"

Tetris::Tetris(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pGameZone = new GameZone(this);
	m_pGameZone->initView();
	m_pGameZone->setGeometry(20, 20, m_pGameZone->getWidth(), m_pGameZone->getHeight());
	m_pGameZone->show();
}

Tetris::~Tetris()
{
	delete m_pGameZone;
	m_pGameZone = NULL;
}
