#ifndef _GAME_ZONE_
#define _GAME_ZONE_

#include "base_shapes.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class GameZone : public QGraphicsView
{
	Q_OBJECT
public:
	GameZone(QWidget * parent = 0);
	~GameZone();
	void initView();
protected:
private:
	const int			m_iZoneWidth;
	const int			m_iZoneHeight; 
	BaseShape *			m_pShape;
	QGraphicsScene *	m_pQGraphicsScene;
};

#endif