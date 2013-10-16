#include "one_block.h"

OneBlock::OneBlock(const QColor & in_qColor, QGraphicsItem * parent)
	: m_qRectF(0, 0, BLOCK_SIZE, BLOCK_SIZE), m_qBrush(in_qColor), m_qPen(BLOCK_PEN)
{
	this->setParentItem(parent);
	this->setRect(m_qRectF);
	this->setPen(m_qPen);
	this->setBrush(m_qBrush);
}

OneBlock::~OneBlock()
{

}
