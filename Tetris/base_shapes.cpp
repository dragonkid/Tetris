#include "base_shapes.h"

// BaseShape
BaseShape::BaseShape()
{

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

// IShape
IShape::IShape()
{
	this->initShapeBlock(4, ISHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(3 * BLOCK_SIZE, 0 * BLOCK_SIZE);
}

IShape::~IShape()
{

}

// JShape
JShape::JShape()
{
	this->initShapeBlock(4, JSHAPE);
	m_qBaseShape.at(0)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
}

JShape::~JShape()
{

}

// LShape
LShape::LShape()
{
	this->initShapeBlock(4, LSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(0 * BLOCK_SIZE, 2 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(1 * BLOCK_SIZE, 2 * BLOCK_SIZE);
}

LShape::~LShape()
{

}

// TShape
TShape::TShape()
{
	this->initShapeBlock(4, TSHAPE);
	m_qBaseShape.at(0)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
}

TShape::~TShape()
{

}

// OShape
OShape::OShape()
{
	this->initShapeBlock(4, OSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
}

OShape::~OShape()
{

}

// SShape
SShape::SShape()
{
	this->initShapeBlock(4, SSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(2 * BLOCK_SIZE, 0 * BLOCK_SIZE);
}

SShape::~SShape()
{

}

// ZShape
ZShape::ZShape()
{
	this->initShapeBlock(4, ZSHAPE);
	m_qBaseShape.at(0)->setPos(0 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(1)->setPos(1 * BLOCK_SIZE, 0 * BLOCK_SIZE);
	m_qBaseShape.at(2)->setPos(1 * BLOCK_SIZE, 1 * BLOCK_SIZE);
	m_qBaseShape.at(3)->setPos(2 * BLOCK_SIZE, 1 * BLOCK_SIZE);
}

ZShape::~ZShape()
{

}
