#include "tetris.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QMessageBox tmp_qModeChoose;
	tmp_qModeChoose.setText("Please choose the mode.");
	QPushButton * tmp_pSingle = tmp_qModeChoose.addButton("Single", QMessageBox::ActionRole);
	QPushButton * tmp_pNetwork = tmp_qModeChoose.addButton("Network", QMessageBox::ActionRole);
	QPushButton * tmp_pExit = tmp_qModeChoose.addButton("Exit", QMessageBox::ActionRole);
	tmp_qModeChoose.exec();

	Tetris * tmp_pTetris = NULL;
	if ( tmp_qModeChoose.clickedButton() == tmp_pSingle )
	{
		tmp_pTetris = new Tetris(SINGLE);
	} 
	else if ( tmp_qModeChoose.clickedButton() == tmp_pNetwork )
	{
		tmp_pTetris = new Tetris(NETWORK);
	}
	else
	{
		return a.quit();
	}
	tmp_pTetris->show();

	return a.exec();
}
