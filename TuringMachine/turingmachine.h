#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "ui_turingmachine.h"

#define DEFAULT_CONTROLLER_FILE "./controller.json"
#define DEFAULT_TAPE_FILE		"./tape.json"

class TuringMachine : public QMainWindow
{
	Q_OBJECT

public:
	TuringMachine(QWidget *parent = 0);
	~TuringMachine();

private slots:
	void importTape();
	void exportTape();
	void importController();
	void exportController();
	void machineStep();
	void machineBeginWork();
	void machineStopWork();

private:
	void setConnections();


	Ui::TuringMachineClass ui;
};

#endif // TURINGMACHINE_H
