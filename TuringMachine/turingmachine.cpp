#include "turingmachine.h"

TuringMachine::TuringMachine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setConnections();
}

TuringMachine::~TuringMachine()
{

}

void TuringMachine::importTape()
{

}

void TuringMachine::exportTape()
{

}

void TuringMachine::importController()
{

}

void TuringMachine::exportController()
{

}

void TuringMachine::machineStep()
{

}

void TuringMachine::machineBeginWork()
{

}

void TuringMachine::machineStopWork()
{

}

void TuringMachine::setConnections()
{
	connect(ui.step, SIGNAL(clicked(bool)), SLOT(machineStep ()));
	connect(ui.stop, SIGNAL(clicked(bool)), SLOT(machineStopWork()));
	connect(ui.exportTape, SIGNAL(clicked(bool)), SLOT(exportTape()));
	connect(ui.importTape, SIGNAL(clicked(bool)), SLOT(importTape()));
	connect(ui.begin, SIGNAL(clicked(bool)), SLOT(machineBeginWork()));
	connect(ui.exportController, SIGNAL(clicked(bool)), SLOT(exportController()));
	connect(ui.importController, SIGNAL(clicked(bool)), SLOT(importController()));
}
