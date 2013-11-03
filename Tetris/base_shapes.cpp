#include "base_shapes.h"
#include <QGraphicsWidget>
#include <QMessageBox>
#include <QString>
#include <cstdlib>
#include <ctime>

// BaseShape
BaseShape::BaseShape()
{
	m_bIsFixed = false;
	// Set and initialize timer.
	m_iDownSpeed = 500;
	m_pQTimer = new QTimer(this);
	connect(m_pQTimer, SIGNAL(timeout()), this, SLOT(moveDown()));
	m_pQTimer->start(m_iDownSpeed);
	// Set random seed.
	srand(time(NULL));
}

BaseShape::~BaseShape()
{
	this->destroyShapeBlock();
}

const ShapeType BaseShape::getShapeType() const
{
	return m_eShapeType;
}

ItemList BaseShape::initShapeBlock( unsigned int num, ShapeType shapeType )
{
	for (unsigned int i = 0; i < num; ++i)
	{
		OneBlock * tmp_pOneBlock = new OneBlock(SHAPE_COLORS[shapeType], this);
		if ( NULL != tmp_pOneBlock )
		{
			this->addToGroup(tmp_pOneBlock);
		}
	}
	return this->childItems();
}

void BaseShape::destroyShapeBlock()
{
	// Memory of OneBlocks in ShapeBlock managed by QGraphicsScene.
	ItemList tmp_lstItems = this->childItems();
 	for (ItemList::size_type i = 0; i < tmp_lstItems.count(); ++i)
 	{
 		if ( NULL != tmp_lstItems[i] )
 		{
			this->removeFromGroup(tmp_lstItems[i]);
 			delete tmp_lstItems[i];
 			tmp_lstItems[i] = NULL;
 		}
 	}
}

void BaseShape::moveDown()
{
	this->moveBy(0, BLOCK_SIZE);
	if ( this->isColliding() )
	{
		m_pQTimer->stop();
		this->setFixed();
	}
}

bool BaseShape::isColliding() const
{	
	ItemList tmp_lstItems = this->childItems();	
	foreach(QGraphicsItem * tmp_pItem, tmp_lstItems)
	{
		if ( tmp_pItem->collidingItems().count() != 0 )
		{
			ItemList tmp = tmp_pItem->collidingItems();
			return true;
		}
	}
	return false;
}

bool BaseShape::isFixed() const
{
	return m_bIsFixed;
}

void BaseShape::setFixed()
{
	m_bIsFixed = true;
	this->moveBy(0, -BLOCK_SIZE);
	qreal tmp_fScanStart = this->sceneBoundingRect().y();
	qreal tmp_fScanEnd = this->sceneBoundingRect().y() + this->getShapeHeight();
	if ( (180 == this->rotation()) || (270 == this->rotation()) )
	{
		tmp_fScanStart -= (this->getShapeHeight() + 1);
		tmp_fScanEnd = this->sceneBoundingRect().y() - 1;
	}
	this->clearBoxGroup();
	emit clearFullRows(tmp_fScanStart, tmp_fScanEnd);
}

void BaseShape::restartTimer()
{
	m_pQTimer->start(m_iDownSpeed);
}

void BaseShape::stopTimer()
{
	m_pQTimer->stop();
}

const qreal BaseShape::getShapeWidth() const
{
	qreal width = 0;
	if ( 0 == (static_cast<int>(this->rotation()) % 180) )
	{
		width = this->childrenBoundingRect().width();
	}
	else
	{
		width = this->childrenBoundingRect().height();
	}
	return width;
}

const qreal BaseShape::getShapeHeight() const
{
	qreal height = 0;
	if ( 0 == (static_cast<int>(this->rotation()) % 180) )
	{
		height = this->childrenBoundingRect().height();
	}
	else
	{
		height = this->childrenBoundingRect().width();
	}
	return height;
}

void BaseShape::clearBoxGroup()
{
	foreach(QGraphicsItem * item, this->childItems())
	{
		this->removeFromGroup(item);
	}
}

QRectF BaseShape::boundingRect() const
{
	return QRectF(0, 0, 0, 0);
}

// IShape
IShape::IShape()
{
	m_eShapeType = ISHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, ISHAPE);
	tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(3 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
}

IShape::~IShape()
{
	
}

void IShape::changeRotation()
{
	if ( 0 == (static_cast<int>(this->rotation()) % 180) )
	{
		this->setRotation(this->rotation() + 90);
	}
	else
	{
		this->setRotation(0);
	}
}

void IShape::randomRotation()
{
	qreal tmp_randRotation = 90 * (rand() % 2);
	this->setRotation(tmp_randRotation);
}

// JShape
JShape::JShape()
{
	m_eShapeType = JSHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, JSHAPE);
	tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 0.5, BLOCK_SIZE * 1.5);
}

JShape::~JShape()
{

}

void JShape::changeRotation()
{
	if ( 360 == static_cast<int>(this->rotation()) )
	{
		this->setRotation(90);
	}
	else
	{
		this->setRotation(this->rotation() + 90);
	}
}

void JShape::randomRotation()
{
	qreal tmp_randRotation = 90 * (rand() % 4);
	this->setRotation(tmp_randRotation);
	if ( 270 == (int)tmp_randRotation )
	{
		this->moveBy(0, -BLOCK_SIZE);
	}
}

// LShape
LShape::LShape()
{
	m_eShapeType = LSHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, LSHAPE);
	tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(1 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 0.5, BLOCK_SIZE * 1.5);
}

LShape::~LShape()
{

}

void LShape::changeRotation()
{
	if ( 360 == static_cast<int>(this->rotation()) )
	{
		this->setRotation(90);
	}
	else
	{
		this->setRotation(this->rotation() + 90);
	}
}

void LShape::randomRotation()
{
	qreal tmp_randRotation = 90 * (rand() % 4);
	this->setRotation(tmp_randRotation);
	if ( 270 == (int)tmp_randRotation )
	{
		this->moveBy(0, -BLOCK_SIZE);
	}
}

// TShape
TShape::TShape()
{
	m_eShapeType = TSHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, TSHAPE);
	tmp_lstItems.at(0)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

TShape::~TShape()
{

}

void TShape::changeRotation()
{
	if ( 360 == static_cast<int>(this->rotation()) )
	{
		this->setRotation(90);
	}
	else
	{
		this->setRotation(this->rotation() + 90);
	}
}

void TShape::randomRotation()
{
	qreal tmp_randRotation = 90 * (rand() % 4);
	this->setRotation(tmp_randRotation);
	if ( 180 == (int)tmp_randRotation )
	{
		this->moveBy(0, -BLOCK_SIZE);
	}
}

// OShape
OShape::OShape()
{
	m_eShapeType = OSHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, OSHAPE);
	tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
}

OShape::~OShape()
{

}

void OShape::changeRotation()
{

}

void OShape::randomRotation()
{

}

// SShape
SShape::SShape()
{
	m_eShapeType = SSHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, SSHAPE);
	tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

SShape::~SShape()
{

}

void SShape::changeRotation()
{
	if ( 0 == (static_cast<int>(this->rotation()) % 180) )
	{
		this->setRotation(this->rotation() + 90);
	}
	else
	{
		this->setRotation(0);
	}
}

void SShape::randomRotation()
{
	qreal tmp_randRotation = 90 * (rand() % 2);
	this->setRotation(tmp_randRotation);
}

// ZShape
ZShape::ZShape()
{
	m_eShapeType = ZSHAPE;
	ItemList tmp_lstItems = this->initShapeBlock(4, ZSHAPE);
	tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	tmp_lstItems.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

ZShape::~ZShape()
{

}

void ZShape::changeRotation()
{
	if ( 0 == (static_cast<int>(this->rotation()) % 180) )
	{
		this->setRotation(this->rotation() + 90);
	}
	else
	{
		this->setRotation(0);
	}
}

void ZShape::randomRotation()
{
	qreal tmp_randRotation = 90 * (rand() % 2);
	this->setRotation(tmp_randRotation);
}
