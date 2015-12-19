#include "turingmachine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TuringMachine w;
	w.show();
	return a.exec();
}
