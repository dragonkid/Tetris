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
	// Random seed.
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
			m_qBaseShape.append(tmp_pOneBlock);
		}
	}
}

void BaseShape::destroyShapeBlock()
{
	for (QList<OneBlock *>::size_type i = 0; i < m_qBaseShape.size(); ++i)
	{
		delete m_qBaseShape[i];
		m_qBaseShape[i] = NULL;
	}
	m_qBaseShape.erase(m_qBaseShape.begin(), m_qBaseShape.end());
}

void BaseShape::moveDown()
{
	this->moveBy(0, BLOCK_SIZE);
	if ( this->isColliding() )
	{
		this->moveBy(0, -BLOCK_SIZE);
		m_pQTimer->stop();
		this->setFixed();
	}
}

bool BaseShape::isColliding() const
{
	QList<QGraphicsItem *> tmp_lstItems = this->childItems();	
	QGraphicsItem * tmp_pItem = NULL;
	foreach(tmp_pItem, tmp_lstItems)
	{
		if ( tmp_pItem->collidingItems().count() != 0 )
		{
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
	emit shapeFixed();
}

void BaseShape::restartTimer()
{
	m_pQTimer->start(m_iDownSpeed);
}

void BaseShape::stopTimer()
{
	m_pQTimer->stop();
}

// IShape
IShape::IShape()
{
	m_eShapeType = ISHAPE;
	this->initShapeBlock(4, ISHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(3 * BLOCK_SIZE, 0 * BLOCK_SIZE);
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
	qreal tmp_randRotation = 0;
	tmp_randRotation = 90 * (rand() % 2);
	this->setRotation(tmp_randRotation);
}

// JShape
JShape::JShape()
{
	m_eShapeType = JSHAPE;
	this->initShapeBlock(4, JSHAPE);
	m_qBaseShape.at(0)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

JShape::~JShape()
{

}

void JShape::changeRotation()
{
	this->setRotation(this->rotation() + 90);
}

void JShape::randomRotation()
{
	qreal tmp_randRotation = 0;
	tmp_randRotation = 90 * (rand() % 4);
	this->setRotation(tmp_randRotation);
	if ( 270 == (int)tmp_randRotation )
	{
		this->setY(-BLOCK_SIZE);
	}
}

// LShape
LShape::LShape()
{
	m_eShapeType = LSHAPE;
	this->initShapeBlock(4, LSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(1 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

LShape::~LShape()
{

}

void LShape::changeRotation()
{
	this->setRotation(this->rotation() + 90);
}

void LShape::randomRotation()
{
	qreal tmp_randRotation = 0;
	tmp_randRotation = 90 * (rand() % 4);
	this->setRotation(tmp_randRotation);
	if ( 270 == (int)tmp_randRotation )
	{
		this->setY(-BLOCK_SIZE);
	}
}

// TShape
TShape::TShape()
{
	m_eShapeType = TSHAPE;
	this->initShapeBlock(4, TSHAPE);
	m_qBaseShape.at(0)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

TShape::~TShape()
{

}

void TShape::changeRotation()
{
	this->setRotation(this->rotation() + 90);
}

void TShape::randomRotation()
{
	qreal tmp_randRotation = 0;
	tmp_randRotation = 90 * (rand() % 4);
	this->setRotation(tmp_randRotation);
	if ( 180 == (int)tmp_randRotation )
	{
		this->setY(-BLOCK_SIZE);
	}
}

// OShape
OShape::OShape()
{
	m_eShapeType = OSHAPE;
	this->initShapeBlock(4, OSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
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
	this->initShapeBlock(4, SSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

SShape::~SShape()
{

}

void SShape::changeRotation()
{
	this->setRotation(this->rotation() + 90);
}

void SShape::randomRotation()
{
	qreal tmp_randRotation = 0;
	tmp_randRotation = 90 * (rand() % 2);
	this->setRotation(tmp_randRotation);
}

// ZShape
ZShape::ZShape()
{
	m_eShapeType = ZSHAPE;
	this->initShapeBlock(4, ZSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	this->setTransformOriginPoint(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5);
}

ZShape::~ZShape()
{

}

void ZShape::changeRotation()
{
	this->setRotation(this->rotation() + 90);
}

void ZShape::randomRotation()
{
	qreal tmp_randRotation = 0;
	tmp_randRotation = 90 * (rand() % 2);
	this->setRotation(tmp_randRotation);
}
