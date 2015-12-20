#include "turingmachine.h"

TuringMachine::TuringMachine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	machine = new Machine;
	ui.tape->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.controller->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	initializeTape();
	setConnections();
}

TuringMachine::~TuringMachine()
{
	delete machine;
}

void TuringMachine::importTape()
{
	/*QString fileName = QFileDialog::getOpenFileName( this, 
													 "Выберите файл ленты", 
													 "./", 
													 "JSON файлы(*.json)");*/
	QString fileName = DEFAULT_TAPE_FILE;

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QDataStream stream(&file);
			QString data = file.readAll();

			try
			{
				auto tuple = parseTapeFile(data);

				machine->setTape(	std::get<0>(tuple),
									std::get<1>(tuple));
			}
			catch (QString& errorString)
			{
				QMessageBox::critical(this, "Ошибка разбора файла \"" + fileName + "\"", errorString);
				return;
			}
			file.close();
			machine->setTapeLoaded();
			showLoadedTape();
		}
	}
}

void TuringMachine::exportTape()
{
	// #TODO: Сохранение ленты в json файл.
}

void TuringMachine::importController()
{
	/*QString fileName = QFileDialog::getOpenFileName(	this,
														"Выберите файл ленты",
														"./",
														"JSON файлы(*.json)");*/
	QString fileName = DEFAULT_CONTROLLER_FILE;

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QDataStream stream(&file);
			QString data = file.readAll();
			try
			{
				parseControllerFile(data);
			}
			catch (QString& errorString)
			{
				QMessageBox::critical(this, "Ошибка разбора файла \"" + fileName + "\"", errorString);
				return;
			}
			file.close();
			machine->setControllerLoaded();
			showLoadedController();
		}
	}
}

void TuringMachine::exportController()
{
	// #TODO: Сохранение УУ в json файл.
}

void TuringMachine::machineStep()
{
	// #TODO: Один шаг машины.
}

void TuringMachine::machineBeginWork()
{
	// #TODO: Начать работу машины.
}

void TuringMachine::machineStopWork()
{
	// #TODO: Остановать работу машины.
}

void TuringMachine::machineErrorReceived(QString &errorString)
{
	QMessageBox::critical(this, "Ошибка машины", errorString);
}

void TuringMachine::expandTape(int currentRow,int currentColumn,int previousRow,int previousColumn)
{
	int columns = ui.tape->columnCount();

	if (currentColumn == (columns - 1))
	{
		QTableWidgetItem* item = new QTableWidgetItem("-");
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->setColumnCount(columns + 1);
		ui.tape->setItem(0, columns, item);
	}
	else if (currentColumn == 0)
	{
		QTableWidgetItem* item = new QTableWidgetItem("-");
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->insertColumn(0);
		ui.tape->setColumnCount(columns + 1);
		ui.tape->setItem(0, 0, item);
	}
}

void TuringMachine::showLoadedTape()
{
	QStringList tape = machine->getTape ();
	int size = tape.size();

	if (machine->isTapeLoaded() && size != 0)
	{
		for (int i = 0; i < size; ++i)
		{
			ui.tape->item(0, (TAPE_OFFSET + i))->setText(tape[i]);
		}
		ui.tape->item(0, (TAPE_OFFSET + machine->getTapePointer()))->setBackgroundColor(Qt::green);

		if (machine->isControllerLoaded())
		{
			showNextCommand();
		}
	}
}

void TuringMachine::showLoadedController()
{
	QStringList alphabet = machine->getAlphabet();
	QStringList states = machine->getStates(false);
	int columns = alphabet.size();
	int rows = states.size();

	if (machine->isControllerLoaded() && columns != 0 && rows != 0)
	{
		ui.controller->setColumnCount(columns);
		ui.controller->setRowCount(rows);

		ui.controller->setHorizontalHeaderLabels(alphabet);
		ui.controller->setVerticalHeaderLabels(states);	

		for (int i = 0; i < rows; ++i)
		{
			QString currentState = ui.controller->verticalHeaderItem(i)->text();

			for (int j = 0; j < columns; ++j)
			{
				QString currentLetter = ui.controller->horizontalHeaderItem(j)->text();
				QString key = currentLetter + currentState;
				QString command = machine->getCommand(key);

				if (!command.isEmpty())
				{
 					QTableWidgetItem* item = new QTableWidgetItem(command);
 					ui.controller->setItem(i, j,item);
				}
			}

			showCurrentState();

			if (machine->isTapeLoaded())
			{
				showNextCommand();
			}
		}
	}
}

void TuringMachine::showCurrentState()
{
	int rows = ui.controller->rowCount();
	QString currentState = machine->getCurrentState();

	for (int i = 0; i < rows; ++i)
	{
		QString state = ui.controller->verticalHeaderItem(i)->text ();

		if (state == currentState)
		{
			ui.controller->verticalHeaderItem(i)->setForeground(QColor("green"));
			int columns = ui.controller->columnCount();
			for (int j = 0; j < columns; ++j)
			{
				ui.controller->item(i, j)->setBackgroundColor(Qt::green);
			}
		}
	}
	ui.currentState->setText(currentState);
}

void TuringMachine::showNextCommand()
{
	QString currentState = machine->getCurrentState();
	QString currentSymbol = machine->getCurrentTapeSymbol();
	QString key = currentSymbol + currentState;
	QString cmd = machine->getCommand(key);
	QString text = currentSymbol + "-" + currentState + "->" + cmd;

	ui.nextCommand->setText(text);
}

void TuringMachine::initializeTape()
{
	ui.tape->setRowCount(1);
	ui.tape->setColumnCount(DEFAULT_TAPE_COLUMNS);

	for (int i = 0; i < DEFAULT_TAPE_COLUMNS; ++i)
	{
		QTableWidgetItem* item = new QTableWidgetItem("-");
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->setItem(0, i, item);
	}
}

void TuringMachine::setConnections() const
{
	connect(ui.step, SIGNAL(clicked(bool)), SLOT(machineStep ()));
	connect(ui.stop, SIGNAL(clicked(bool)), SLOT(machineStopWork()));
	connect(ui.exportTape, SIGNAL(clicked(bool)), SLOT(exportTape()));
	connect(ui.importTape, SIGNAL(clicked(bool)), SLOT(importTape()));
	connect(ui.begin, SIGNAL(clicked(bool)), SLOT(machineBeginWork()));
	connect(ui.exportController, SIGNAL(clicked(bool)), SLOT(exportController()));
	connect(ui.importController, SIGNAL(clicked(bool)), SLOT(importController()));
	connect(ui.tape, SIGNAL(currentCellChanged(int, int,int,int)), this, SLOT(expandTape(int, int,int,int)));
	connect(machine, SIGNAL(machineError(QString&)), this, SLOT(machineErrorReceived(QString&)));
}

void TuringMachine::parseControllerFile(const QString& data) throw(QString&)
{
	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonObject obj = doc.object();

	/* Считываем и устанавливаем алфавит */
	if (obj.contains("alphabet"))
	{
		QJsonArray arr = obj["alphabet"].toArray();
		QStringList alphabet;

		for (auto i : arr)
		{
			QString tmp = i.toString();
			alphabet << tmp;
		}
		machine->setAlphabet(alphabet);
	}
	else
	{
		QString errorString = "Не найден алфавит по тегу \"alphabet\".";
		throw errorString;
	}

	/* Считываем и устанавливаем состояния */
	if (obj.contains("states"))
	{
		QJsonArray arr = obj["states"].toArray();
		QStringList states;

		for (auto i : arr)
		{
			QString tmp = i.toString();
			states << tmp;
		}
		machine->setStates(states);
	}
	else
	{
		QString errorString = "Не найдены состояния по тегу \"states\".";
		throw errorString;
	}

	/* Считываем и устанавливаем начальные и конечные состояния */
	QString beginState;
	QString endState;

	if (obj.contains("begin-state"))
	{
		beginState = obj["begin-state"].toString();
	}
	else
	{
		QString errorString = "Не найдено начальное состояние по тегу \"begin-state\".";
		throw errorString;
	}

	if (obj.contains("end-state"))
	{
		endState = obj["end-state"].toString();
	}
	else
	{
		QString errorString = "Не найдено конечное состояние по тегу \"end-state\".";
		throw errorString;
	}
	machine->setBeginEndStates(beginState, endState);

	/* Считываем команды */
	if (obj.contains("commands"))
	{
		QJsonObject commands = obj["commands"].toObject();
		parseCommands(commands);
	}
	else
	{
		QString errorString = "Не найдены команды по тегу \"commands\".";
		throw errorString;
	}
}

void TuringMachine::parseCommands(const QJsonObject commands) throw(QString&)
{
	QStringList states = machine->getStates(false);
	QStringList alphabet = machine->getAlphabet();
	QStringList commandsList;

	/* Формируем список команд по алфавиту и множеству состояний */
	for (int i = 0; i < states.size(); ++i)
	{
		for (int j = 0; j < alphabet.size(); ++j)
		{
			QString command = states[i];
			command.prepend(alphabet[j]);
			commandsList << command;
		}
	}

	/* Считываем и запоминаем команды */
	for (auto i : commandsList)
	{
		if (commands.contains(i))
		{
			QJsonObject tmp = commands[i].toObject();

			Command cmd(tmp["new-symbol"].toString(),
					    tmp["new-state"].toString(),
					    tmp["action"].toString());

			try
			{
				machine->addComand(i, cmd);
			}
			catch (QString& errorString)
			{
				errorString.prepend("Команда \"" + i + "\":\n");
				throw errorString;
			}
		}
		else
		{
			QString errorString = "Недостаточно команд. Не найдена команда \"" + i + "\"";
			throw errorString;
		}
	}
}

std::tuple<QStringList, unsigned int> TuringMachine::parseTapeFile(const QString& data) const throw(QString&)
{
	QStringList list;
	unsigned int number;

	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonObject obj = doc.object();

	if (obj.contains("tape-view"))
	{
		QJsonArray arr = obj["tape-view"].toArray();

		for (auto i : arr)
		{
			QString tmp = i.toString();
			list << tmp;
		}
	}
	else
	{
		QString errorString = "Не найдены данные о состоянии ленты по тегу \"tape-view\".";
		throw errorString;
	}

	if (obj.contains("pointer-index"))
	{
		number = obj["pointer-index"].toInt();
	}
	else
	{
		QString errorString = "Не найдены данные об указателе ленты по тегу \"pointer-index\".";
		throw errorString;
	}

	return std::make_tuple(list, number);
}
