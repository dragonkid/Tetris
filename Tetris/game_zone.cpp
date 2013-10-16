#include "game_zone.h"

GameZone::GameZone(QWidget * parent)
	: m_iZoneWidth(14 * BLOCK_SIZE), m_iZoneHeight(500)
{
	this->setParent(parent);
	m_pQGraphicsScene = new QGraphicsScene(this);
}

GameZone::~GameZone()
{
	delete m_pQGraphicsScene;
	m_pQGraphicsScene = NULL;
}

void GameZone::initView()
{
	// Indicates that the engine should antialias edges of primitives if possible.
	this->setRenderHint(QPainter::Antialiasing);
	// Cache background. Can accelerate rendering.
	this->setCacheMode(CacheBackground);
	// Fix the size of game zone.
	this->setMinimumSize(m_iZoneWidth, m_iZoneHeight);
	this->setMaximumSize(m_iZoneWidth, m_iZoneHeight);
	// Set rect of GraphicsScene.
	m_pQGraphicsScene->setSceneRect(0, 0, m_iZoneWidth - 5, m_iZoneHeight - 5);
	this->setScene(m_pQGraphicsScene);
	// For test.
	m_pShape = new ZShape();
	m_pQGraphicsScene->addItem(m_pShape);
	m_pShape->setPos(0, 0);
}
