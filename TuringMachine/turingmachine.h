#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QDataStream>
#include <tuple>
#include "ui_turingmachine.h"
#include "machine.h"

#define DEFAULT_CONTROLLER_FILE "./controller.json"
#define DEFAULT_TAPE_FILE		"./tape.json"

// #TODO: Вынести функции парсинга файлов json в отдельный класс.

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
	void machineErrorReceived(QString &errorString);

private:
	void setConnections() const;
	void parseControllerFile(const QString& data) throw(QString&);
	void parseCommands(const QJsonObject commands) throw(QString&);
	std::tuple<QStringList, unsigned int> parseTapeFile(const QString& data) const throw(QString&);


	Ui::TuringMachineClass ui;
	Machine* machine;
};

#endif // TURINGMACHINE_H
