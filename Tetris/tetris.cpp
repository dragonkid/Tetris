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
	  m_pLabelPreview(new QLabel(this)),
	  m_pLabelIP(NULL),
	  m_pEditIP(NULL),
	  m_pConnectButton(NULL)
{
	ui.setupUi(this);

	this->initTetris(mode);
}

Tetris::~Tetris()
{
	if ( NULL != m_pSelfGameZone )
	{
		delete m_pSelfGameZone;
		m_pSelfGameZone = NULL;
	}
	if ( NULL != m_pOppsiteGameZone )
	{
		delete m_pOppsiteGameZone;
		m_pOppsiteGameZone = NULL;
	}
	if ( NULL != m_pBaseNetwork )
	{
		delete m_pBaseNetwork;
		m_pBaseNetwork = NULL;
	}
}

void Tetris::initTetris( PlayMode mode )
{
	switch (mode)
	{
	case NETWORK:	
		{
			// Initiate status bar.
			this->showStatusMsg("Network mode.");
			// Initiate self game zone.
			m_pSelfGameZone = new GameZone(m_pCentralWidget, SELF);
			connect(m_pSelfGameZone, SIGNAL(nextShapeIs(int)), this, SLOT(previewNextShape(int)));
			// Initiate opposite game zone.
			m_pOppsiteGameZone = new GameZone(m_pCentralWidget, OPPOSITE);
			// Initiate and layout middle zone.
			this->initMiddleZone(mode);
			// Layout.
			m_pHLayout->addWidget(m_pSelfGameZone);
			m_pHLayout->addStretch();
			m_pHLayout->addLayout(m_pVLayout);
			m_pHLayout->addStretch();
			m_pHLayout->addWidget(m_pOppsiteGameZone);
			m_pCentralWidget->setLayout(m_pHLayout);
			this->setCentralWidget(m_pCentralWidget);
			// Set key press focus.
			m_pSelfGameZone->setFocus();
			m_pOppsiteGameZone->setFocusPolicy(Qt::NoFocus);
			// Initiate network and signals.
			m_pBaseNetwork = new BaseNetwork();
			connect(m_pBaseNetwork, SIGNAL(errorOccur(QString)), this, SLOT(showStatusMsg(QString)));
			connect(m_pBaseNetwork, SIGNAL(connReqAccepted()), this, SLOT(connEstablished()));
			connect(m_pSelfGameZone, SIGNAL(keyPressed(QByteArray)), m_pBaseNetwork, SLOT(sendData(QByteArray)));
			bool tmp = connect(m_pBaseNetwork, SIGNAL(dataReceived(QByteArray)), this, SLOT(recvData(QByteArray)));
			m_pBaseNetwork->newListen();
		}
		break;
	case SINGLE:
		{
			// Initiate status bar.
			this->showStatusMsg("Single mode.");
			// Initiate self game zone.
			m_pSelfGameZone = new GameZone(m_pCentralWidget);
			connect(m_pSelfGameZone, SIGNAL(nextShapeIs(int)), this, SLOT(previewNextShape(int)));
			// Initiate and layout middle zone.
			this->initMiddleZone(mode);
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

void Tetris::initMiddleZone(PlayMode mode)
{
	m_pLabelPreview->setText("Next Shape:");
	m_pLabelPreview->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

	m_pPreviewZone->setMinimumSize(PREVIEW_ZONE_WIDTH, PREVIEW_ZONE_HEIGHT);
	m_pPreviewZone->setMaximumSize(PREVIEW_ZONE_WIDTH, PREVIEW_ZONE_HEIGHT);
	m_pPreviewZone->setScene(m_pPreviewScene);
	m_pPreviewZone->setBackgroundBrush(QColor(236, 233, 216));
	m_pPreviewZone->setStyleSheet("border:0px");

	m_pVLayout->addWidget(m_pLabelPreview);
	m_pVLayout->addWidget(m_pPreviewZone);
	m_pVLayout->addStretch();
	if ( NETWORK == mode )
	{
		m_pConnectButton = new QPushButton("Connect", m_pCentralWidget);
		connect(m_pConnectButton, SIGNAL(clicked()), this, SLOT(connRequest()));
		m_pLabelIP = new QLabel("Opposite IP:", m_pCentralWidget);
		m_pEditIP = new QLineEdit(m_pCentralWidget);
		m_pEditIP->setInputMask("000.000.000.000");
		m_pVLayout->addStretch();
		m_pVLayout->addWidget(m_pLabelIP);
		m_pVLayout->addWidget(m_pEditIP);
		m_pVLayout->addWidget(m_pConnectButton);
		m_pVLayout->addStretch();
	}
}

void Tetris::showStatusMsg( QString msg )
{
	this->statusBar()->showMessage(msg);
}

void Tetris::connRequest()
{
	QString tmp_strOppositeIP = m_pEditIP->text();
	m_pBaseNetwork->createConnection(tmp_strOppositeIP);
	this->exchangeRandomSeed();
	this->startGame();
}

void Tetris::connEstablished()
{
	this->showStatusMsg("Connection established.");
	this->exchangeRandomSeed();
	m_pConnectButton->setDisabled(true);
	this->startGame();
}

void Tetris::exchangeRandomSeed()
{
	// Exchange random seed when connection established.
	// Send self random seed.
	m_pBaseNetwork->sendData(QByteArray::number(m_pSelfGameZone->getRandomSeed()));
	// Get opposite random seed.
	QByteArray tmp_qData = m_pBaseNetwork->waitForGetData();
	if ( tmp_qData.isEmpty() )
	{
		this->showStatusMsg("Connection error occure.");
		return ;
	}
	m_pOppsiteGameZone->setRandomSeed(QString(tmp_qData).toInt());
	// debug
	this->showStatusMsg("Self: " + QString::number(m_pSelfGameZone->getRandomSeed()) + "\tOpposite: " + QString::number(m_pOppsiteGameZone->getRandomSeed()));
}

void Tetris::recvData( QByteArray data )
{
	int tmp_iKey= QString(data).toInt();
	m_pOppsiteGameZone->gameControl(tmp_iKey);
}

void Tetris::startGame()
{
	m_pSelfGameZone->gameStart();
	m_pOppsiteGameZone->gameStart();
}
