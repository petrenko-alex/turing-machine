#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QList>
#include <QDebug>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QDataStream>
#include <QtConcurrent/QtConcurrentRun>
#include <tuple>
#include "ui_turingmachine.h"
#include "machine.h"

#define DEFAULT_CONTROLLER_FILE "./controller.json"
#define DEFAULT_TAPE_FILE		"./tape.json"
#define DEFAULT_TAPE_COLUMNS	50
#define TAPE_OFFSET				10
#define TAPE_BLANK				"-"

class TuringMachine : public QMainWindow
{
	Q_OBJECT

public:
	TuringMachine(QWidget *parent = 0);
	~TuringMachine();

private slots:
	void resetMachine();
	void addState();
	void addSymbol();
	void importTape();
	void exportTape();
	void importController();
	void exportController();
	void machineStep();
	void machineBeginWork();
	void machineStopWork();
	void machineErrorReceived(QString &errorString);
	void machineFinished();
	void machineStopped();
	void machineTapeSymbolChanged(unsigned int index, QString newSymbol);
	void machineTapePointerChanged(unsigned int oldTapePointer, unsigned int newTapePointer);

	void expandTape(int currentRow, 
					int currentColumn, 
					int previousRow, 
					int previousColumn);
	void showLoadedTape();
	void showLoadedController();
	void showCurrentState();
	void showNextCommand();
	void repaintTape();
	void setControlButtonsEnabled(bool isEnabled);
	void rememberCurrentTapeSymbol(QTableWidgetItem* item);
	void rememberCurrentCommand(QTableWidgetItem* item);
	void modifyCurrentTapeSymbol(QTableWidgetItem* item);
	void modifyCurrentCommand(QTableWidgetItem* item);

private:
	QByteArray prepareDataToExportTape() const;
	QByteArray prepareDataToExportController() const;
	void addRow(QTableWidget* table, const QString& row);
	void addColumn(QTableWidget* table, const QString& column);
	void initializeTape();
	void paintRow(int rowNumber, const QColor& color);
	void setConnections() const;
	void parseControllerFile(const QString& data) throw(QString&);
	void parseCommands(const QJsonObject commands) throw(QString&);
	std::tuple<QStringList, unsigned int, QString> parseTapeFile(const QString& data) const throw(QString&);


	Ui::TuringMachineClass ui;
	Machine* machine;
	int tapeOffet;

	QString currentTapeSymbol;
	QString currentCommand;
};

#endif // TURINGMACHINE_H
