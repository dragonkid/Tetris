#include "common.h"
#include <QMessageBox>

void Common::showWarnInfo(const QString warnInfo)
{
	QMessageBox msgBox;
	msgBox.setText(warnInfo);
	msgBox.exec();
}