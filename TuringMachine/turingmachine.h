#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QtWidgets/QMainWindow>
#include "ui_turingmachine.h"

class TuringMachine : public QMainWindow
{
	Q_OBJECT

public:
	TuringMachine(QWidget *parent = 0);
	~TuringMachine();

private:
	Ui::TuringMachineClass ui;
};

#endif // TURINGMACHINE_H
