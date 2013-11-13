#ifndef _GAME_ZONE_
#define _GAME_ZONE_

#include "base_shapes.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsLineItem>
#include <QTransform>
#include <vector>

typedef std::vector<qreal> FullRow_Vec;

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
	void moveClearedRowsDown(const FullRow_Vec &);
	// Game control.
	void shapeDown();
	void shapeLeft();
	void shapeRight();
	void shapeRotation();
	void stopGame();
	void continueGame();
private slots:
	void createNewShape();
	void clearFullRows(const qreal, const qreal);
signals:
	void gameFinished();
};

#endif