#ifndef _BASE_SHAPES_
#define _BASE_SHAPES_

#include "one_block.h"
#include <QGraphicsItemGroup>
#include <QList>
#include <QTimer>

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

class BaseShape : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
public:
	BaseShape();
	virtual ~BaseShape() = 0;

	const ShapeType getShapeType() const;
	virtual void changeRotation() = 0;
	bool isColliding() const;
	bool isFixed() const;
	void setFixed();
protected:
	ShapeType			m_eShapeType;
	QList<OneBlock *>	m_qBaseShape;
	QTransform			m_qOldTransform;

	void initShapeBlock(unsigned int num, ShapeType shapeType);
	void destroyShapeBlock();
private:
	QTimer *			m_pQTimer;
	int					m_iDownSpeed;
	bool				m_bIsFixed;
public slots:
	void slotsMoveDown();
};

class IShape : public BaseShape
{
public:
	IShape();
	~IShape();

	virtual void changeRotation();
protected:
private:
};

class JShape : public BaseShape
{
public:
	JShape();
	~JShape();

	virtual void changeRotation();
protected:
private:
};

class LShape : public BaseShape
{
public:
	LShape();
	~LShape();

	virtual void changeRotation();
protected:
private:
};

class TShape : public BaseShape
{
public:
	TShape();
	~TShape();

	virtual void changeRotation();
protected:
private:
};

class OShape : public BaseShape
{
public:
	OShape();
	~OShape();

	virtual void changeRotation();
protected:
private:
};

class SShape : public BaseShape
{
public:
	SShape();
	~SShape();

	virtual void changeRotation();
protected:
private:
};

class ZShape : public BaseShape
{
public:
	ZShape();
	~ZShape();

	virtual void changeRotation();
protected:
private:
};

#endif