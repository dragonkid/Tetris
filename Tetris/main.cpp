#include "tetris.h"
#include <QtWidgets/QApplication>

QFile * g_pLogfile = new QFile("D://debug.log");
QDebug g_Debug(g_pLogfile);

int main(int argc, char *argv[])
{
	g_pLogfile->open(QIODevice::Append | QIODevice::Text);

	QApplication a(argc, argv);
	Tetris w;
	w.show();
	return a.exec();
}
