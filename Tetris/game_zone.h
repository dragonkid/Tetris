#ifndef _GAME_ZONE_
#define _GAME_ZONE_

#include "base_shapes.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsLineItem>
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
	const int getRandomSeed() const;
	void setRandomSeed(int);
protected:
	virtual void keyPressEvent(QKeyEvent *event);
private:	// const values.
	const qreal			SCENE_WIDTH;
	const qreal			SCENE_HEIGHT;
	const qreal			ZONE_WIDTH;
	const qreal			ZONE_HEIGHT; 
	const QColor		BACKGROUND_COLOE;
private:
	BaseShape *			m_pShape;
	QGraphicsScene *	m_pScene;
	QGraphicsLineItem * m_pBottomLine;
	QGraphicsLineItem * m_pLeftLine;
	QGraphicsLineItem * m_pRightLine;
	qreal				m_fOldRotation;
	int					m_iSeed;
	int					m_iNextShape;

	void setShapeInitPos();
	void moveClearedRowsDown(const FullRow_Vec &);
	// Game control.
	void shapeDown();
	void shapeLeft();
	void shapeRight();
	void shapeRotate();
	void stopGame();
	void continueGame();
public slots:
	void gameControl(int);
signals:
	void gameFinished();
	void keyPressed(int);
	void nextShapeIs(int);
private slots:
	void createNewShape();
	void clearFullRows(const qreal, const qreal);
};

#endif