#ifndef _GAME_ZONE_
#define _GAME_ZONE_

#include "base_shapes.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsLineItem>
#include <QTransform>

class GameZone : public QGraphicsView
{
	Q_OBJECT
public:
	GameZone(QWidget * parent = 0);
	~GameZone();

	void gameStart();
	const qreal getWidth() const;
	const qreal getHeight() const;
protected:
	virtual void keyPressEvent(QKeyEvent *event);
private:
	const qreal			m_fSceneWidth;
	const qreal			m_fSceneHeight;
	const qreal			m_fZoneWidth;
	const qreal			m_fZoneHeight; 
	const QColor		m_qBackgroundColor;
	BaseShape *			m_pShape;
	QGraphicsScene *	m_pScene;
	QGraphicsLineItem * m_pBottomLine;
	QGraphicsLineItem * m_pLeftLine;
	QGraphicsLineItem * m_pRightLine;
	qreal				m_fOldRotation;

	void setShapeInitPos();
public slots:
	void createNewShape();
signals:
	void gameFinished();
};

#endif