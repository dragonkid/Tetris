#include "game_zone.h"
#include <cstdlib>
#include <ctime>

static const qreal SCENE_OFFSET = 2;
static const qreal XNUM = 16;
static const qreal YNUM = 26;

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

void GameZone::gameStart()
{	
	this->createNewShape();
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
		m_pShape->restartTimer();
		if ( m_pShape->isColliding() )
		{
			m_pShape->moveBy(0, -BLOCK_SIZE);
			m_pShape->stopTimer();
			m_pShape->setFixed();
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
	int width = 0;
	QRectF tmp = m_pShape->childrenBoundingRect();
	if ( 0 == (m_pShape->rotation() / 180) )
	{
		width = m_pShape->childrenBoundingRect().width();
	}
	else
	{
		width = m_pShape->childrenBoundingRect().height();
	}

	int x = 0;
	x = m_fSceneWidth / 2 - (BLOCK_SIZE * (int)((width / BLOCK_SIZE) / 2));
	m_pShape->setX(x);
}

void GameZone::createNewShape()
{
	srand(time(NULL));
	int tmp_iRandShapeType = rand() % END;
	switch (tmp_iRandShapeType)
	{
	case ISHAPE:
		m_pShape = new IShape();
		break;
	case JSHAPE:
		m_pShape = new JShape();
		break;
	case LSHAPE:
		m_pShape = new LShape();
		break;
	case TSHAPE:
		m_pShape = new TShape();
		break;
	case OSHAPE:
		m_pShape = new OShape();
		break;
	case SSHAPE:
		m_pShape = new SShape();
		break;
	case ZSHAPE:
		m_pShape = new ZShape();
		break;
	default:
		break;
	}
	m_pShape->randomRotation();	
	m_pScene->addItem(m_pShape);
	this->setShapeInitPos();
	if ( m_pShape->isColliding() )
	{
		emit gameFinished();
		return ;
	}
	connect(m_pShape, SIGNAL(shapeFixed()), this, SLOT(createNewShape()));
}
