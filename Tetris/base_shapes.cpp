#include "base_shapes.h"
#include <QGraphicsWidget>
#include <QMessageBox>
#include <QString>
#include <cstdlib>
#include <ctime>

// BaseShape
BaseShape::BaseShape() 
	: m_eShapeType(END), m_iDownSpeed(500), m_bIsFixed(false)
{
	// Set and initialize timer.
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

void BaseShape::initShapeBlock( unsigned int num, ShapeType shapeType )
{
	for (unsigned int i = 0; i < num; ++i)
	{
		OneBlock * tmp_pOneBlock = new OneBlock(SHAPE_COLORS[shapeType], this);
		if ( NULL != tmp_pOneBlock )
		{
			this->addToGroup(tmp_pOneBlock);
		}
	}
	ItemList tmp_lstItems = this->childItems();
	switch (this->getShapeType())
	{
	case ISHAPE:
		tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(3 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		this->setTransformOriginPoint(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
		break;
	case JSHAPE:
		tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		this->setTransformOriginPoint(BLOCK_SIZE * 0.5, BLOCK_SIZE * 1.5);
		break;
	case LSHAPE:
		tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(1 * BLOCK_SIZE, 2 * BLOCK_SIZE);
		this->setTransformOriginPoint(BLOCK_SIZE * 0.5, BLOCK_SIZE * 1.5);
		break;
	case TSHAPE:
		tmp_lstItems.at(0)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
		break;
	case OSHAPE:
		tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		break;
	case SSHAPE:
		tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
		break;
	case ZSHAPE:
		tmp_lstItems.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
		tmp_lstItems.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		tmp_lstItems.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
		this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
		break;
	default:
		break;
	}
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
		this->moveBy(0, -BLOCK_SIZE);
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
	m_pQTimer->stop();
	m_bIsFixed = true;
	// The base pos(0, 0) will changed when shape rotates.
	qreal tmp_fScanStart = this->sceneBoundingRect().y();
	// Plus 1 for correction of penWidth.
	qreal tmp_fScanEnd = this->sceneBoundingRect().y() + (this->getShapeHeight() + 1);
	if ( (180 == this->rotation()) || (270 == this->rotation()) )
	{
		tmp_fScanStart -= (this->getShapeHeight() + 1);
		tmp_fScanEnd = this->sceneBoundingRect().y();
	}
	this->clearBoxGroup();
	emit clearFullRows(tmp_fScanStart, tmp_fScanEnd);
}

void BaseShape::resetTimer()
{
	m_pQTimer->start(m_iDownSpeed);
}

const qreal BaseShape::getShapeWidth() const
{
	qreal width = 0;
	// The real height and width will change when it rotates.
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
	// The real height and width will change when it rotates.
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
	this->initShapeBlock(4, ISHAPE);
}

IShape::~IShape()
{
	
}
// Rotation angle: 0, 90
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
	this->initShapeBlock(4, JSHAPE);
}

JShape::~JShape()
{

}
// Rotation angle: 0, 90, 180, 270
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
	this->initShapeBlock(4, LSHAPE);
}

LShape::~LShape()
{

}
// Rotation angle: 0, 90, 180, 270
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
	this->initShapeBlock(4, TSHAPE);
}

TShape::~TShape()
{

}
// Rotation angle: 0, 90, 180, 270
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
	this->initShapeBlock(4, OSHAPE);
}

OShape::~OShape()
{

}
// Rotation angle: needn't to rotate.
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
	this->initShapeBlock(4, SSHAPE);
}

SShape::~SShape()
{

}
// Rotation angle: 0, 90
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
	this->initShapeBlock(4, ZSHAPE);
}

ZShape::~ZShape()
{

}
// Rotation angle: 0, 90
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
