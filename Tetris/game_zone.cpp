#include "game_zone.h"

static const qreal SCENE_OFFSET = 2;
static const qreal XNUM = 18;
static const qreal YNUM = 30;

GameZone::GameZone(QWidget * parent)
	: m_fSceneWidth(XNUM * BLOCK_SIZE), 
	  m_fSceneHeight(YNUM * BLOCK_SIZE),
	  m_fZoneWidth(m_fSceneWidth + 2 * SCENE_OFFSET),
	  m_fZoneHeight(m_fSceneHeight + SCENE_OFFSET),
	  m_qBackgroundColor(Qt::lightGray)
{
	this->setParent(parent);
	// Indicates that the engine should antialias edges of primitives if possible.
	this->setRenderHint(QPainter::Antialiasing);
	// Cache background. Can accelerate rendering.
	this->setCacheMode(CacheBackground);
	// Fix the size of game zone.
	this->setMinimumSize(m_fZoneWidth, m_fZoneHeight);
	this->setMaximumSize(m_fZoneWidth, m_fZoneHeight);

	m_pScene = new QGraphicsScene(this);
	// Set rect of GraphicsScene.
	m_pScene->setSceneRect(0, 0, m_fSceneWidth, m_fSceneHeight);
	// Set background of GraphicsScene.
	m_pScene->setBackgroundBrush(m_qBackgroundColor);
	this->setScene(m_pScene);

	m_pBottomLine = m_pScene->addLine(0, m_fZoneHeight, m_fZoneWidth, m_fZoneHeight, m_qBackgroundColor);
	m_pLeftLine = m_pScene->addLine(-SCENE_OFFSET, 0, -SCENE_OFFSET, m_fZoneHeight, m_qBackgroundColor);
	m_pRightLine = m_pScene->addLine(m_fZoneWidth, 0, m_fZoneWidth, m_fZoneHeight, m_qBackgroundColor);
}

GameZone::~GameZone()
{
	delete m_pScene;
	m_pScene = NULL;
}

void GameZone::initView()
{	
	// For test.
	m_pShape = new IShape();
	//m_pShape->setRotation(90);
	m_pScene->addItem(m_pShape);
	this->setShapeInitPos();
	// Test end.
}

void GameZone::keyPressEvent(QKeyEvent *event)
{
	if ( m_pShape->isFixed() )
	{
		return ;
	}
	switch (event->key())
	{
	case Qt::Key_Down:
		m_pShape->moveBy(0, BLOCK_SIZE);
		if ( m_pShape->isColliding() )
		{
			m_pShape->setFixed();
			m_pShape->moveBy(0, -BLOCK_SIZE);
		}
		break;
	case Qt::Key_Up:
		m_fOldRotation = m_pShape->rotation();
		m_pShape->changeRotation();
		if ( m_pShape->isColliding() )
		{
			m_pShape->setRotation(m_fOldRotation);
		}
		break;
	case Qt::Key_Left:
		m_pShape->moveBy(-BLOCK_SIZE, 0);
		if ( m_pShape->isColliding() )
		{
			m_pShape->moveBy(BLOCK_SIZE, 0);
		}
		break;
	case Qt::Key_Right:
		m_pShape->moveBy(BLOCK_SIZE, 0);
		if ( m_pShape->isColliding() )
		{
			m_pShape->moveBy(-BLOCK_SIZE, 0);
		}
		break;
	default:
		break;
	}
}

const qreal GameZone::getWidth() const
{
	return m_fZoneWidth;
}

const qreal GameZone::getHeight() const
{
	return m_fZoneHeight;
}

void GameZone::setShapeInitPos()
{
	int width;
	QRectF tmp = m_pShape->childrenBoundingRect();
	if ( 0 == (m_pShape->rotation() / 180) )
	{
		width = m_pShape->childrenBoundingRect().width();
	}
	else
	{
		width = m_pShape->childrenBoundingRect().height();
	}

	int x;
	x = m_fSceneWidth / 2 - (BLOCK_SIZE * (int)((width / BLOCK_SIZE) / 2));
	m_pShape->setPos(x, 0);
}
