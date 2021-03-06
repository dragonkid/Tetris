#ifndef _ONE_BLOCK_
#define _ONE_BLOCK_

#include <QGraphicsRectItem>
#include <QRectF>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QFile>

const int BLOCK_ALPHA = 255;
const int BLOCK_SIZE = 20;
const QColor BLOCK_PEN(255, 255, 255, 255);

class OneBlock : public QGraphicsRectItem, public QObject
{
public:
	OneBlock(const QColor & in_qColor, QGraphicsItem * parent = 0);
	~OneBlock();

	virtual QRectF boundingRect() const;
protected:
private:
	const QRectF	m_qRectF;
	const QPen		m_qPen;
	QBrush			m_qBrush;

	OneBlock();
};

#endif