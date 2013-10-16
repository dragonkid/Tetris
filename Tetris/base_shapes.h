#ifndef _BASE_SHAPES_
#define _BASE_SHAPES_

#include "one_block.h"
#include <QGraphicsItemGroup>
#include <QList>
#include <QTransform>

enum ShapeType
{
	ISHAPE	= 0,
	JSHAPE	= 1, 
	LSHAPE	= 2,
	TSHAPE	= 3,
	OSHAPE	= 4,
	SSHAPE	= 5, 
	ZSHAPE	= 6,
	END
};

const QColor SHAPE_COLORS[7] = {
	QColor(210, 63, 45, BLOCK_ALPHA),		// ISHAPE
	QColor(112, 73, 137, BLOCK_ALPHA),		// JSHAPE
	QColor(153, 165, 177, BLOCK_ALPHA),		// LSHAPE
	QColor(247, 195, 52, BLOCK_ALPHA),		// TSHAPE
	QColor(0, 93, 135, BLOCK_ALPHA),		// OSHAPE
	QColor(105, 197, 88, BLOCK_ALPHA),		// SSHAPE
	QColor(83, 153, 177, BLOCK_ALPHA)		// ZSHAPE
};

class BaseShape : public QGraphicsItemGroup
{
public:
	BaseShape();
	virtual ~BaseShape() = 0;
	const ShapeType getShapeType() const;
protected:
	ShapeType			m_eShapeType;
	QList<OneBlock *>	m_qBaseShape;
	QTransform			m_qOldTransform;

	void initShapeBlock(unsigned int num, ShapeType shapeType);
	void destroyShapeBlock();
private:
};

class IShape : public BaseShape
{
public:
	IShape();
	~IShape();
protected:
private:
};

class JShape : public BaseShape
{
public:
	JShape();
	~JShape();
protected:
private:
};

class LShape : public BaseShape
{
public:
	LShape();
	~LShape();
protected:
private:
};

class TShape : public BaseShape
{
public:
	TShape();
	~TShape();
protected:
private:
};

class OShape : public BaseShape
{
public:
	OShape();
	~OShape();
protected:
private:
};

class SShape : public BaseShape
{
public:
	SShape();
	~SShape();
protected:
private:
};

class ZShape : public BaseShape
{
public:
	ZShape();
	~ZShape();
protected:
private:
};

#endif