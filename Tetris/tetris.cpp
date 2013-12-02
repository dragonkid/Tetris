#include "tetris.h"

Tetris::Tetris(PlayMode mode, QWidget *parent)
	: QMainWindow(parent),
	  PREVIEW_ZONE_WIDTH(4 * BLOCK_SIZE + 2),
	  PREVIEW_ZONE_HEIGHT(3 * BLOCK_SIZE + 2),
	  m_pCentralWidget(new QWidget(this)),
	  m_pSelfGameZone(NULL),
	  m_pOppsiteGameZone(NULL),
	  m_pBaseNetwork(NULL),
	  m_pNextShape(NULL),
	  m_pPreviewZone(new QGraphicsView(m_pCentralWidget)),
	  m_pPreviewScene(new QGraphicsScene(m_pPreviewZone)),
	  m_pHLayout(new QHBoxLayout(m_pCentralWidget)),
	  m_pVLayout(new QVBoxLayout(m_pCentralWidget)),
	  m_pLabel(new QLabel(this))
{
	ui.setupUi(this);

	this->initTetris(mode);
}

Tetris::~Tetris()
{
	if ( NULL == m_pSelfGameZone )
	{
		delete m_pSelfGameZone;
		m_pSelfGameZone = NULL;
	}
	if ( NULL == m_pOppsiteGameZone )
	{
		delete m_pOppsiteGameZone;
		m_pOppsiteGameZone = NULL;
	}
}

void Tetris::initTetris( PlayMode mode )
{
	switch (mode)
	{
	case NETWORK:	
		{
			// Initiate status bar.
			this->statusBar()->showMessage("Network mode.");
		}
		break;
	case SINGLE:
		{
			// Initiate status bar.
			this->statusBar()->showMessage("Single mode.");
			// Initiate self game zone.
			m_pSelfGameZone = new GameZone(m_pCentralWidget);
			connect(m_pSelfGameZone, SIGNAL(nextShapeIs(int)), this, SLOT(previewNextShape(int)));
			// Initiate and layout middle zone.
			this->initMiddleZone();
			// Layout.
			m_pHLayout->addWidget(m_pSelfGameZone);
			m_pHLayout->addStretch();
			m_pHLayout->addLayout(m_pVLayout);
			m_pHLayout->addStretch();
			m_pCentralWidget->setLayout(m_pHLayout);
			this->setCentralWidget(m_pCentralWidget);
			// Set key press focus.
			m_pSelfGameZone->setFocus();
			// Game start.
			m_pSelfGameZone->gameStart();
		}
		break;
	default:
		break;
	}
}

void Tetris::previewNextShape( int nextShape )
{
	if ( NULL != m_pNextShape )
	{
		delete m_pNextShape;
		m_pNextShape = NULL;
	}
	m_pNextShape = ShapeFactory::createShape(nextShape);
	if ( NULL == m_pNextShape )
	{
		return ;
	}
	m_pPreviewScene->addItem(m_pNextShape);
	m_pNextShape->setMoveable(false);
}

void Tetris::initMiddleZone(/*PlayMode mode*/)
{
	m_pLabel->setText("Next Shape:");
	m_pLabel->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

	m_pPreviewZone->setMinimumSize(PREVIEW_ZONE_WIDTH, PREVIEW_ZONE_HEIGHT);
	m_pPreviewZone->setMaximumSize(PREVIEW_ZONE_WIDTH, PREVIEW_ZONE_HEIGHT);
	m_pPreviewZone->setScene(m_pPreviewScene);
	m_pPreviewZone->setBackgroundBrush(QColor(236, 233, 216));
	m_pPreviewZone->setStyleSheet("border:0px");

	m_pVLayout->addWidget(m_pLabel);
	m_pVLayout->addWidget(m_pPreviewZone);
	m_pVLayout->addStretch();
}
