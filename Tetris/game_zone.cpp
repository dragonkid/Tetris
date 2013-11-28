#include "game_zone.h"
#include <cstdlib>
#include <ctime>
#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QMessageBox>

static const qreal SCENE_OFFSET = 2;
static const qreal XNUM = 16;
static const qreal YNUM = 26;

GameZone::GameZone(ZoneMode mode, QWidget * parent)
	: m_fSceneWidth(XNUM * BLOCK_SIZE), 
	  m_fSceneHeight(YNUM * BLOCK_SIZE),
	  m_fZoneWidth(m_fSceneWidth + 2 * SCENE_OFFSET),
	  m_fZoneHeight(m_fSceneHeight + SCENE_OFFSET),
	  m_qBackgroundColor(Qt::lightGray),
	  m_iSeed(time(NULL)),
	  m_eZoneMode(mode)
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
	m_pScene->setSceneRect(0, 0, m_fSceneWidth, m_fSceneHeight);
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
	srand(m_iSeed);
	this->createNewShape();
}

void GameZone::keyPressEvent(QKeyEvent *event)
{
	this->gameControl(event->key());
	emit keyPressed(event->key());
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
	int width = m_pShape->getShapeWidth();
	int x = m_fSceneWidth / 2 - (BLOCK_SIZE * (int)((width / BLOCK_SIZE) / 2));
	m_pShape->moveBy(x, 0);
}

void GameZone::createNewShape()
{
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
	//m_pShape->randomRotation();	
	m_pScene->addItem(m_pShape);
	this->setShapeInitPos();
	if ( m_pShape->isColliding() )
	{
		emit gameFinished();
		return ;
	}
	connect(m_pShape, SIGNAL(clearFullRows(const qreal, const qreal)), 
		this, SLOT(clearFullRows(const qreal, const qreal)));
}

void GameZone::clearFullRows(const qreal in_fStart, const qreal in_fEnd)
{
	FullRow_Vec tmp_vecFullRow;
	tmp_vecFullRow.clear();
	// ItemSelectionMode is ContainsItemShape. So offset of 0.5 is needed.
	QRectF tmp_qScanRect(-0.5, 0, m_fSceneWidth + 1, BLOCK_SIZE + 1);
	for (qreal y = in_fStart; y < in_fEnd; y += BLOCK_SIZE)
	{
		tmp_qScanRect.setY(y - 0.5);
		// Function setY may change the height. So reset it.
		tmp_qScanRect.setHeight(BLOCK_SIZE + 1);	
		ItemList tmp_lstItems = m_pScene->items(tmp_qScanRect, Qt::ContainsItemShape);
		if ( XNUM == tmp_lstItems.count() )	// Full row.
		{
			foreach(QGraphicsItem *item, tmp_lstItems) 
			{
				// Todo: Animation effects for clear full rows.
				//QGraphicsBlurEffect *blur_effect = new QGraphicsBlurEffect;
				//item->setGraphicsEffect(blur_effect);
				delete item;
			}
			tmp_vecFullRow.push_back(y);
		}
	}
	if ( 0 != tmp_vecFullRow.size() )
	{
		this->moveClearedRowsDown(tmp_vecFullRow);
	}

	this->createNewShape();
}

void GameZone::moveClearedRowsDown( const FullRow_Vec & in_vecFulls )
{
	// ItemSelectionMode is ContainsItemShape. So offset of 0.5 is needed.
	QRectF tmp_qMoveRect(-0.5, 0, m_fSceneWidth + 1, 0);
	for ( FullRow_Vec::size_type i = 0; i < in_vecFulls.size(); ++i )
	{
		tmp_qMoveRect.setHeight(in_vecFulls[i] + 0.5);
		ItemList tmp_lstItems = m_pScene->items(tmp_qMoveRect, Qt::ContainsItemShape);
		foreach(QGraphicsItem * item, tmp_lstItems)
		{
			item->moveBy(0, BLOCK_SIZE);
		}
	}
}

void GameZone::stopGame()
{
	// debug
	g_pLogfile->close();
	m_pShape->setMoveable(false);
}

void GameZone::continueGame()
{
	// debug
	g_pLogfile->open(QIODevice::Append | QIODevice::Text);
	m_pShape->setMoveable(true);
}

void GameZone::shapeDown()
{
	if ( m_pShape->isFixed() )
	{
		return ;
	}
	m_pShape->moveBy(0, BLOCK_SIZE);
	m_pShape->resetTimer();	// For better user experience.
	if ( m_pShape->isColliding() )
	{
		m_pShape->moveBy(0, -BLOCK_SIZE);
		m_pShape->setFixed();
	}
}

void GameZone::shapeLeft()
{
	if ( m_pShape->isFixed() )
	{
		return ;
	}
	m_pShape->moveBy(-BLOCK_SIZE, 0);
	if ( m_pShape->isColliding() )
	{
		m_pShape->moveBy(BLOCK_SIZE, 0);
	}
}

void GameZone::shapeRight()
{
	if ( m_pShape->isFixed() )
	{
		return ;
	}
	m_pShape->moveBy(BLOCK_SIZE, 0);
	if ( m_pShape->isColliding() )
	{
		m_pShape->moveBy(-BLOCK_SIZE, 0);
	}
}

void GameZone::shapeRotate()
{
	if ( m_pShape->isFixed() )
	{
		return ;
	}
	m_fOldRotation = m_pShape->rotation();
	m_pShape->changeRotation();
	if ( m_pShape->isColliding() )
	{
		m_pShape->setRotation(m_fOldRotation);
	}
}

const int GameZone::getRandomSeed() const
{
	return m_iSeed;
}

void GameZone::setRandomSeed( int seed )
{
	m_iSeed = seed;
}

void GameZone::gameControl( int in_iKey )
{
	switch (in_iKey)
	{
	case Qt::Key_Down:
		this->shapeDown();
		break;
	case Qt::Key_Left:
		this->shapeLeft();
		break;
	case Qt::Key_Right:
		this->shapeRight();
		break;
	case Qt::Key_Up:
		this->shapeRotate();
		break;
	case Qt::Key_S:
		this->stopGame();
		break;
	case Qt::Key_C:
		this->continueGame();
		break;
	default:
		break;
	}
}
