#include "turingmachine.h"

TuringMachine::TuringMachine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setControlButtonsEnabled(false);
	ui.stop->setEnabled(false);
	tapeOffet = TAPE_OFFSET;
	currentTapeSymbol = "";
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

void TuringMachine::addState()
{
	ui.controller->blockSignals(true);
	QString newState = ui.newState->text();

	if (!newState.isEmpty())
	{
		bool isBeginState = ui.beginState->isChecked();
		bool isEndState = ui.endState->isChecked();
		bool isCurrState = ui.currState->isChecked();

		if (machine->isStateUnique(newState))
		{
			machine->addState(newState);

			if (isBeginState || machine->getBeginState().isEmpty())
			{
				machine->setBeginState(newState);
			}

			if (isEndState || machine->getEndState().isEmpty())
			{
				machine->setEndState(newState);
			}

			if (isCurrState || machine->getCurrentState().isEmpty())
			{
				machine->setCurrentState(newState);
			}

			addRow(ui.controller, newState);
		}
		else
		{
			QMessageBox::warning(this, "Ошибка", "Такое состояние уже существует в машине.");
			ui.controller->blockSignals(false);
			return;
		}
	}
	else
	{
		QMessageBox::warning(this, "Ошибка", "Название нового состояния не введено.");
		ui.controller->blockSignals(false);
		return;
	}
	ui.controller->blockSignals(false);
}

void TuringMachine::addSymbol()
{
	ui.controller->blockSignals(true);
	QString newSymbol = ui.newSymbol->text();

	if (!newSymbol.isEmpty())
	{
		bool isEmptySymbol = ui.emptySymbol->isChecked();

		if (machine->isSymbolUnique(newSymbol))
		{
			machine->addSymbol(newSymbol);

			if (isEmptySymbol || machine->getEmptySymbol().isEmpty())
			{
				machine->setEmptySymbol(newSymbol);
			}
			
			addColumn(ui.controller, newSymbol);
			showCurrentState();
		}
		else
		{
			QMessageBox::warning(this, "Ошибка", "Такой символ уже существует в алфавите машины.");
			ui.controller->blockSignals(false);
			return;
		}
	}
	else
	{
		QMessageBox::warning(this, "Ошибка", "Символ не введен.");
		ui.controller->blockSignals(false);
		return;
	}
	ui.controller->blockSignals(false);
}

void TuringMachine::importTape()
{
	ui.tape->blockSignals(true);
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
									std::get<1>(tuple),
									std::get<2>(tuple));
			}
			catch (QString& errorString)
			{
				QMessageBox::critical(this, "Ошибка разбора файла \"" + fileName + "\"", errorString);
				file.close();
				ui.tape->blockSignals(false);
				return;
			}
			file.close();
			machine->setTapeLoaded();
			showLoadedTape();
		}
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::exportTape()
{
	// #TODO: Сохранение ленты в json файл.
}

void TuringMachine::importController()
{
	ui.controller->blockSignals(true);
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
				file.close();
				ui.controller->blockSignals(false);
				return;
			}
			file.close();
			machine->setControllerLoaded();
			showLoadedController();
		}
	}
	ui.controller->blockSignals(false);
}

void TuringMachine::exportController()
{
	// #TODO: Сохранение УУ в json файл.
}

void TuringMachine::machineStep()
{
	ui.tape->blockSignals(true);
	if (machine->isReady())
	{
		machine->oneStep(true);
		showCurrentState();
		showNextCommand();
	}
	else
	{
		QMessageBox::warning(this, "Машина", "Машина еще не готова к работе.\nПожалуйста, убедитесь, что лента и управляющее устройство заданы.");
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::machineBeginWork()
{
	ui.tape->blockSignals(true);
	if (machine->isReady())
	{
		ui.stop->setEnabled(true);
		QtConcurrent::run(this->machine,&Machine::startWork);
	}
	else
	{
		QMessageBox::warning(this, "Машина", "Машина еще не готова к работе.\nПожалуйста, убедитесь, что лента и управляющее устройство заданы.");
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::machineStopWork()
{
	ui.tape->blockSignals(true);
	machine->stopWork();
	ui.tape->blockSignals(false);
}

void TuringMachine::machineErrorReceived(QString &errorString)
{
	QMessageBox::critical(this, "Ошибка машины", errorString);
}

void TuringMachine::machineFinished()
{
	// #TODO: Что сделать еще?
	ui.nextCommand->setText("Машина завершила работу");
	showCurrentState();
	QMessageBox::information(this, "Состояние машины", "Машина достигла конечного состояния");
	ui.tape->blockSignals(false);
}

void TuringMachine::machineStopped()
{
	ui.stop->setEnabled(false);
	showCurrentState();
	showNextCommand();
	ui.tape->blockSignals(false);
}

void TuringMachine::machineTapeSymbolChanged(unsigned int index, QString newSymbol)
{
	ui.tape->blockSignals(true);
	QTableWidgetItem* item = ui.tape->item(0, index);

	if (item != nullptr)
	{
		ui.tape->item(0, index)->setText(newSymbol);
	}
	else
	{
		qDebug() << "Метод:machineTapeSymbolChanged()\nНе удалось перезаписать текущий символ ленты.";
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::machineTapePointerChanged(unsigned int oldTapePointer, unsigned int newTapePointer)
{
	ui.tape->blockSignals(true);
	QTableWidgetItem* item = nullptr;
	int tapeSize = ui.tape->columnCount();
	
	/* Удаляем старый указатель */
	ui.tape->item(0, oldTapePointer)->setBackgroundColor(Qt::white);

	if ((oldTapePointer == 0 && newTapePointer == 0) ||
		(newTapePointer == tapeSize))
	/* В ленту добавился крайнией символ слева или справа */
	{
		ui.tape->insertColumn(newTapePointer);
		item = new QTableWidgetItem(machine->getEmptySymbol());
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->setItem(0, newTapePointer, item);
		item->setBackgroundColor(Qt::green);
	}
	else
	{
		item = ui.tape->item(0, newTapePointer);
		item->setBackgroundColor(Qt::green);
		item->setTextAlignment(Qt::AlignCenter);
	}

	/* Ставим пустой символ машины, если в текущей ячейке ленты пусто */
	if (item->text() == TAPE_BLANK)
	{
		item->setText(machine->getEmptySymbol());
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::expandTape(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	ui.tape->blockSignals(true);
	int columns = ui.tape->columnCount();

	if (currentColumn == (columns - 1))
	/* Добавляем ячейку справа */
	{
		QTableWidgetItem* item = new QTableWidgetItem(TAPE_BLANK);
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->setColumnCount(columns + 1);
		ui.tape->setItem(0, columns, item);

		if (machine->isTapeLoaded())
		{
			machine->appendToTape(TAPE_BLANK);
		}
	}
	else if (currentColumn == 0)
	/* Добавляем ячейку слева */
	{
		QTableWidgetItem* item = new QTableWidgetItem(TAPE_BLANK);
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->insertColumn(0);
		ui.tape->setColumnCount(columns + 1);
		ui.tape->setItem(0, 0, item);
		++tapeOffet;

		if (machine->isTapeLoaded())
		{
			machine->prependToTape(TAPE_BLANK);
			if (machine->getTapePointer() == 0)
			{
				machine->incrementTapePointer();
			}
		}
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::showLoadedTape()
{
	ui.tape->blockSignals(true);
	QStringList tape = machine->getTape ();
	int size = tape.size();
	ui.tape->setColumnCount(size);

	if (machine->isTapeLoaded() && size != 0)
	{
		for (int i = 0; i < size; ++i)
		{
			QTableWidgetItem* item = ui.tape->item(0, i);
			if (item != nullptr)
			{
				item->setText(tape[i]);
			}
			else
			{
				item = new QTableWidgetItem(tape[i]);
				ui.tape->setItem(0, i, item);
			}
		}
		ui.tape->item(0, machine->getTapePointer())->setBackgroundColor(Qt::green);

		if (machine->isControllerLoaded())
		{
			showNextCommand();
			setControlButtonsEnabled(true);
		}
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::showLoadedController()
{
	ui.controller->blockSignals(true);
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
			ui.controller->blockSignals(true);

			if (machine->isTapeLoaded())
			{
				showNextCommand();
				setControlButtonsEnabled(true);
			}
		}
	}
	ui.controller->blockSignals(false);
}

void TuringMachine::showCurrentState()
{
	ui.controller->blockSignals(true);
	int rows = ui.controller->rowCount();
	QString currentState = machine->getCurrentState();

	for (int i = 0; i < rows; ++i)
	{
		paintRow(i, Qt::white);
		QString state = ui.controller->verticalHeaderItem(i)->text ();

		if (state == currentState)
		{
			paintRow(i, Qt::green);
		}
	}
	ui.currentState->setText(currentState);
	ui.controller->blockSignals(false);
}

void TuringMachine::showNextCommand()
{
	if (!machine->isFinished ())
	{
		QString currentState = machine->getCurrentState();
		QString currentSymbol = machine->getCurrentTapeSymbol();
		QString key = currentSymbol + currentState;
		QString cmd = machine->getCommand(key);
		QString text;

		if (cmd.isEmpty())
		{
			text = "Команда не задана";
		}
		else
		{
			text = currentSymbol + "-" + currentState + "->" + cmd;
		}

		ui.nextCommand->setText(text);
	}
}

void TuringMachine::repaintTape()
{
	ui.tape->blockSignals(true);
	ui.tape->clear();
	QStringList tapeView = machine->getTape();
	int tapeSize = tapeView.size();

	/* Перерисовываем ленту */
	ui.tape->setColumnCount(tapeSize);
	for (int i = 0; i < tapeSize; ++i)
	{
		QTableWidgetItem* item = new QTableWidgetItem(tapeView[i]);
		item->setTextAlignment(Qt::AlignCenter);		
		ui.tape->setItem(0, i, item);
	}
	/* Устанавливаем указатель */
	unsigned int tapePointer = machine->getTapePointer();
	ui.tape->item(0,tapePointer)->setBackgroundColor(Qt::green);
	ui.tape->blockSignals(false);
}

void TuringMachine::setControlButtonsEnabled(bool isEnabled)
{
	ui.step->setEnabled(isEnabled);
	ui.begin->setEnabled(isEnabled);
}

void TuringMachine::rememberCurrentTapeSymbol(QTableWidgetItem* item)
{
	currentTapeSymbol = item->text();
	qDebug() << "Cell symbol - " + currentTapeSymbol;
}

void TuringMachine::rememberCurrentCommand(QTableWidgetItem* item)
{
	currentCommand = item->text();
	qDebug() << "Command - " + currentCommand;
}

void TuringMachine::modifyCurrentTapeSymbol(QTableWidgetItem* item)
{
	ui.tape->blockSignals(true);
	int itemIndex = item->column();
	QString itemText = item->text();

	if (!machine->isTapeLoaded())
	/* Если ленты еще нет */
	{
		if (machine->isTapeSymbolValid(itemText))
		{
			/* Создаем ленту */
			QVector<QString> tmp;
			tmp.fill(TAPE_BLANK, ui.tape->columnCount());
			QStringList list(QList<QString>::fromVector(tmp));
			list[itemIndex] = itemText;
			machine->setTape(list, itemIndex);
			ui.tape->item(0, machine->getTapePointer())->setBackgroundColor(Qt::green);
			machine->setTapeLoaded();
		}
	}
	else
	/* Лента загружена */
	{
		if (machine->isTapeSymbolValid(itemText))
		{
			machine->setTapeSymbol(itemText, itemIndex);
		}
		else
		{
			item->setText(currentTapeSymbol);
			QMessageBox::warning(this,
								 "Ошибка ввода",
								 "Невозможно установить \"" +
								 itemText +
								 "\" в ленту, так как этот символ не найден в алфавите машины.");
		}
	}
	ui.tape->blockSignals(false);
}

void TuringMachine::modifyCurrentCommand(QTableWidgetItem* item)
{
	ui.controller->blockSignals(true);
	QString newCommand = item->text();
	QString state = ui.controller->verticalHeaderItem(item->row())->text ();
	QString symbol = ui.controller->horizontalHeaderItem(item->column())->text();

	if (newCommand.count('-') != 2)
	{
		QMessageBox::warning(this, "Ошибка", "Неверный синтаксис команды.\nКоманда должна задаваться:\n<символ алфавита>-<состояния>-<действие>");
		item->setText(currentCommand);
		ui.controller->blockSignals(false);
		return;
	}
	else
	{
		QStringList list = newCommand.split('-');

		if (!machine->isTapeSymbolValid(list[0]))
		{
			QMessageBox::warning(this, "Ошибка", "Символ \"" + list[0] + "\" отсутствует в алфавите.");
			item->setText(currentCommand);
			ui.controller->blockSignals(false);
			return;
		}

		if (!machine->isStateValid(list[1]))
		{
			QMessageBox::warning(this, "Ошибка", "Состояние \"" + list[1] + "\" отсутствует в множестве состояний.");
			item->setText(currentCommand);
			ui.controller->blockSignals(false);
			return;
		}

		if (list[2] != "R" && list[2] != "L" && list[2] != "N")
		{
			QMessageBox::warning(this, "Ошибка", "Неизвестное действие \"" + list[2] + "\".\nВозможные действия:\"R\",\"L\",\"N\".");
			item->setText(currentCommand);
			ui.controller->blockSignals(false);
			return;
		}

		/* Создаем команду */
		Command cmd(list[0], list[1], list[2]);
		QString key = symbol + state;
		machine->addComand(key, cmd);	
	}
	ui.controller->blockSignals(false);
}

void TuringMachine::addRow(QTableWidget* table, const QString& row)
{
	int rows = table->rowCount();
	table->insertRow(rows);
	QTableWidgetItem* header = new QTableWidgetItem(row);
	table->setVerticalHeaderItem(rows, header);
	table->setRowCount(rows + 1);

	int columns = table->columnCount();
	for (int i = 0; i < columns; ++i)
	{
		QTableWidgetItem* item = table->item(rows, i);
		if (item == nullptr)
		{
			item = new QTableWidgetItem();
			table->setItem(rows, i, item);
		}
	}
}

void TuringMachine::addColumn(QTableWidget* table, const QString& column)
{
	int columns = table->columnCount();
	table->insertColumn(columns);
	QTableWidgetItem* header = new QTableWidgetItem(column);
	table->setHorizontalHeaderItem(columns, header);
	table->setColumnCount(columns + 1);

	int rows = table->rowCount();
	for (int i = 0; i < rows; ++i)
	{
		QTableWidgetItem* item = table->item(i, columns);
		if (item == nullptr)
		{
			item = new QTableWidgetItem();
			table->setItem(i, columns, item);
		}
	}
}

void TuringMachine::initializeTape()
{
	ui.tape->setRowCount(1);
	ui.tape->setColumnCount(DEFAULT_TAPE_COLUMNS);

	for (int i = 0; i < DEFAULT_TAPE_COLUMNS; ++i)
	{
		QTableWidgetItem* item = new QTableWidgetItem(TAPE_BLANK);
		item->setTextAlignment(Qt::AlignCenter);
		ui.tape->setItem(0, i, item);
	}
}

void TuringMachine::paintRow(int rowNumber, const QColor& color)
{
	int columns = ui.controller->columnCount();
	for (int j = 0; j < columns; ++j)
	{
		QTableWidgetItem* tmp = ui.controller->item(rowNumber, j);
		if (tmp != nullptr)
		{
			tmp->setBackgroundColor(color);
		}
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
	connect(ui.tape, SIGNAL(itemPressed(QTableWidgetItem*)), this, SLOT(rememberCurrentTapeSymbol(QTableWidgetItem*)));
	connect(ui.tape, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(modifyCurrentTapeSymbol(QTableWidgetItem*)));
	connect(machine, SIGNAL(machineError(QString&)), this, SLOT(machineErrorReceived(QString&)));
	connect(machine, SIGNAL(machineFinished()), this, SLOT(machineFinished()));
	connect(machine, SIGNAL(tapeSymbolChanged(unsigned int, QString)), this, SLOT(machineTapeSymbolChanged(unsigned int,QString)));
	connect(machine, SIGNAL(tapePointerChanged(unsigned int, unsigned int)), this, SLOT(machineTapePointerChanged(unsigned int, unsigned int)));
	connect(machine, SIGNAL(tapeChanged()), this, SLOT(repaintTape()));
	connect(machine, SIGNAL(machineStopped()), this, SLOT(machineStopped()));
	connect(ui.addNewState, SIGNAL(clicked(bool)), SLOT(addState()));
	connect(ui.addNewSymbol, SIGNAL(clicked(bool)), SLOT(addSymbol()));
	connect(ui.controller, SIGNAL(itemPressed(QTableWidgetItem*)), this, SLOT(rememberCurrentCommand(QTableWidgetItem*)));
	connect(ui.controller, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(modifyCurrentCommand(QTableWidgetItem*)));
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

std::tuple<QStringList, unsigned int,QString> TuringMachine::parseTapeFile(const QString& data) const throw(QString&)
{
	QString string;
	unsigned int number;
	QVector<QString> tmp;
	
	tmp.fill(TAPE_BLANK, ui.tape->columnCount());
	QStringList list(QList<QString>::fromVector (tmp));

	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonObject obj = doc.object();

	if (obj.contains("tape-view"))
	{
		QJsonArray arr = obj["tape-view"].toArray();
		int size = arr.size();

		for (int i = 0; i < size;++i)
		{
			QString tmp = arr[i].toString();
			int insertIndex = TAPE_OFFSET + i;

			if (list.size() < insertIndex)
			{
				list.insert((TAPE_OFFSET + i),tmp);
			}
			else
			{
				list[insertIndex] = tmp;
			}
		}
	}
	else
	{
		QString errorString = "Не найдены данные о состоянии ленты по тегу \"tape-view\".";
		throw errorString;
	}

	if (obj.contains("pointer-index"))
	{
		number = obj["pointer-index"].toInt() + TAPE_OFFSET;

		if (number < 0 || number >= list.size())
		{
			QString errorString = "Указатель ленты по тегу \"pointer-index\" задан не верно.";
			throw errorString;
		}
	}
	else
	{
		QString errorString = "Не найдены данные об указателе ленты по тегу \"pointer-index\".";
		throw errorString;
	}

	if (obj.contains("empty-symbol"))
	{
		string = obj["empty-symbol"].toString();
	}
	else
	{
		QString errorString = "Не найдены данные о пустом символе ленты по тегу \"empty-symbol\".";
		throw errorString;
	}

	return std::make_tuple(list, number,string);
}
