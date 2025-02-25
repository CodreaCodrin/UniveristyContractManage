#include "gui.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include <qtimer.h>
#include<qdebug.h>
#include <string>
#include <algorithm>

void Gui::initGUICmps()
{
	setLayout(lyMain);

	//adaug lista si sub doua butoane de sort
	QWidget* widStanga = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widStanga->setLayout(vl);

	model = new MyModel{ _controller.GetAll(), true };
	lst->setModel(model);
	vl->addWidget(lst);

	QWidget* widBtnStanga = new QWidget;
	QHBoxLayout* lyBtnsSt = new QHBoxLayout;
	widBtnStanga->setLayout(lyBtnsSt);
	btnSortByDenumire = new QPushButton("Sort by Denumire");
	lyBtnsSt->addWidget(btnSortByDenumire);

	btnAddToContract = new QPushButton("Adauga in contract");
	lyBtnsSt->addWidget(btnAddToContract);
	btnAddToContract->setDisabled(true);

	btnSortByOre = new QPushButton("Sort by Ore");
	lyBtnsSt->addWidget(btnSortByOre);
	vl->addWidget(widBtnStanga);

	btnSortByDenumireOre = new QPushButton("Sort by Tip && Prof");
	vl->addWidget(btnSortByDenumireOre);
	lyMain->addWidget(widStanga);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtDenumire = new QLineEdit;
	formLDetalii->addRow(new QLabel("Denumire:"), txtDenumire);
	txtNrOre = new QLineEdit;
	formLDetalii->addRow(new QLabel("NrOre:"), txtNrOre);
	txtTip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), txtTip);
	txtProfesor = new QLineEdit;
	formLDetalii->addRow(new QLabel("Profesor:"), txtProfesor);

	btnAdd = new QPushButton("Add disciplina");
	btnDelete = new QPushButton("Delete disciplina");
	btnModify = new QPushButton("Modify disciplina");
	btnModify->setDisabled(true);
	btnCountType = new QPushButton("CountType");
	auto widAddDelMod = new QWidget;
	auto lyBasicFunct = new QHBoxLayout;
	widAddDelMod->setLayout(lyBasicFunct);
	lyBasicFunct->addWidget(btnAdd);
	lyBasicFunct->addWidget(btnDelete);
	lyBasicFunct->addWidget(btnModify);

	btnFiltrareNrOre = new QPushButton("Filtrare NrOre");
	btnFiltrareProfesor = new QPushButton("Filtrare Profesor");
	auto widFiltre = new QWidget;
	auto lyFiltre = new QHBoxLayout;
	widFiltre->setLayout(lyFiltre);
	lyFiltre->addWidget(btnFiltrareNrOre);
	lyFiltre->addWidget(btnFiltrareProfesor);

	btnShowList = new QPushButton("Show List");
	btnOpenContract = new QPushButton("Show contract");
	btnOpenContractRead = new QPushButton("Show contractRead");
	auto widShow_and_contract = new QWidget;
	auto lyShow_and_contract = new QHBoxLayout;
	widShow_and_contract->setLayout(lyShow_and_contract);
	lyShow_and_contract->addWidget(btnShowList);
	lyShow_and_contract->addWidget(btnOpenContract);
	lyShow_and_contract->addWidget(btnOpenContractRead);

	btnUndo = new QPushButton("Undo");
	auto widCountUndo = new QWidget;
	auto lyCountUndo = new QHBoxLayout;
	widCountUndo->setLayout(lyCountUndo);
	lyCountUndo->addWidget(btnCountType);
	lyCountUndo->addWidget(btnUndo);

	formLDetalii->addWidget(widAddDelMod);
	formLDetalii->addWidget(widShow_and_contract);
	formLDetalii->addWidget(widFiltre);
	formLDetalii->addWidget(widCountUndo);

	lyMain->addWidget(widDetalii);

	btnDyn->setLayout(lyBtnDy);
	lyMain->addWidget(btnDyn);
}

void Gui::connectSignalsSlots()
{
	QObject::connect(btnShowList, &QPushButton::clicked, [&]() {
		reloadList(_controller.GetAll());
		});
	QObject::connect(btnSortByDenumire, &QPushButton::clicked, [&]() {
		reloadList(_controller.Sortare(Service::ComparareDupaDenumire));
		});
	QObject::connect(btnSortByOre, &QPushButton::clicked, [&]() {
		reloadList(_controller.Sortare(Service::ComparareDupaOre));
		});
	QObject::connect(btnSortByDenumireOre, &QPushButton::clicked, [&]() {
		reloadList(_controller.Sortare(Service::ComparareDupaTipProf));
		});
	QObject::connect(btnFiltrareNrOre, &QPushButton::clicked, [&]() {
		reloadList(_controller.filtrare_dupa_ore(txtNrOre->text().toInt()));
		});
	QObject::connect(btnFiltrareProfesor, &QPushButton::clicked, [&]() {
		reloadList(_controller.filtrare_dupa_prof(txtProfesor->text().toStdString()));
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &Gui::addNewDisciplina);
	QObject::connect(btnDelete, &QPushButton::clicked, this, &Gui::deleteExistingDisciplina);
	QObject::connect(btnModify, &QPushButton::clicked, this, &Gui::modifyADisciplina);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &Gui::undoAction);
	QObject::connect(btnCountType, &QPushButton::clicked, this, &Gui::make_type_buttons);
	QObject::connect(btnAddToContract, &QPushButton::clicked, this, &Gui::addincontractDiscipina);


	/*QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtDenumire->setText("");
			txtNrOre->setText("");
			txtTip->setText("");
			txtProfesor->setText("");
			btnAddToContract->setDisabled(true);
			btnModify->setDisabled(true);
		}
		else {
			auto selItem = sel.at(0);
			auto denumire = selItem->data(Qt::UserRole).toString();
			txtDenumire->setText(denumire);
			auto p = _controller.cauta_dupa_nume(denumire.toStdString());
			txtNrOre->setText(QString::number(p.get_ore()));
			txtTip->setText(QString::fromStdString(p.get_tip()));
			txtProfesor->setText(QString::fromStdString(p.get_profesor()));
			btnAddToContract->setEnabled(true);
			btnModify->setEnabled(true);	
		}
		});*/

	QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lst->selectionModel()->selectedIndexes().isEmpty()) {
			txtDenumire->setText("");
			txtNrOre->setText("");
			txtTip->setText("");
			txtProfesor->setText("");
			btnAddToContract->setDisabled(true);
			btnModify->setDisabled(true);
			return;
		}
		QModelIndex selIndex = lst->selectionModel()->selectedIndexes().at(0);
		auto denumire = selIndex.data(Qt::UserRole).toString();

		txtDenumire->setText(denumire);
		auto p = _controller.cauta_dupa_nume(denumire.toStdString());
		txtNrOre->setText(QString::number(p.get_ore()));
		txtTip->setText(QString::fromStdString(p.get_tip()));
		txtProfesor->setText(QString::fromStdString(p.get_profesor()));
		btnAddToContract->setEnabled(true);
		btnModify->setEnabled(true);
		});

	QObject::connect(btnOpenContract, &QPushButton::clicked, [&]() {
		ContractGui* interface_contract = new ContractGui{ _controller , *this};
		ferestreCRUDGUI.push_back(interface_contract);
		interface_contract->setFixedWidth(450);
		interface_contract->show();
		});

	QObject::connect(btnOpenContractRead, &QPushButton::clicked, [&]() {
		ContractGuiReadOnly* interface_contract = new ContractGuiReadOnly{_controller};
		ferestreREAD.push_back(interface_contract);
		interface_contract->setFixedWidth(450);
		interface_contract->show();
		});
}

void Gui::reloadList(const std::vector<Disciplina>& discs)
{
	/*lst->clear();
	for (const auto& p : discs) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.to_string()));
		item->setData(Qt::UserRole, QString::fromStdString(p.get_denumire()));
		lst->addItem(item);
	}*/
	model->setDisc(discs);
}

void Gui::make_type_buttons()
{
	QWidget* dictionary_buttons = new QWidget;
	QVBoxLayout* lyDictBtn = new QVBoxLayout;
	dictionary_buttons->setLayout(lyDictBtn);

	auto m = _controller.Creeaza_dictionar();
	for (auto it = m.begin(); it != m.end(); it++)
	{
		auto type_button = new QPushButton(QString::fromStdString((*it).first));
		lyDictBtn->addWidget(type_button);
	}

	QList<QPushButton*> l = dictionary_buttons->findChildren<QPushButton*>();
	for (auto it = l.begin(); it != l.end(); it++)
	{
		QPushButton* pushbtn = (*it);
		QObject::connect(pushbtn, &QPushButton::clicked, [=]() {
			auto key = pushbtn->text();
			//QMessageBox::warning(this, "Warning", key);
			countTheType(key.toStdString());
			});
	}
	
	dictionary_buttons->show();
}

void Gui::notify_contracts()
{
	for (auto obj : ferestreCRUDGUI) obj->reloadList(_controller.GetAllContract());
	for (auto obj : ferestreREAD) obj->repaint();
}

void Gui::addNewDisciplina()
{
	try {
		_controller.Adauga(txtDenumire->text().toStdString(),
			txtNrOre->text().toInt(), txtTip->text().toStdString(),
			txtProfesor->text().toStdString());
		reloadList(_controller.GetAll());
	}
	catch (MyException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_type() + ex.what()));
	}
}

void Gui::deleteExistingDisciplina()
{
	try {
		_controller.Sterge(txtDenumire->text().toStdString(),
			txtNrOre->text().toInt(), txtTip->text().toStdString(),
			txtProfesor->text().toStdString());
		reloadList(_controller.GetAll());
	}
	catch (MyException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_type() + ex.what()));
	}
}

void Gui::modifyADisciplina()
{
	QModelIndex selItem = lst->selectionModel()->selectedIndexes().at(0);
	auto denumire = selItem.data(Qt::UserRole).toString();
	auto p = _controller.cauta_dupa_nume(denumire.toStdString());

	try {
		_controller.Modifica(p.get_denumire(), p.get_ore(), p.get_tip(), p.get_profesor(), 
			txtDenumire->text().toStdString(),
			txtNrOre->text().toInt(), txtTip->text().toStdString(),
			txtProfesor->text().toStdString());
		reloadList(_controller.GetAll());
	}
	catch (MyException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_type() + ex.what()));
	}
}

void Gui::undoAction()
{
	bool status = _controller.Undo();
	if(!status)
		QMessageBox::warning(this, "Warning", QString::fromStdString("Undo no longer possible"));
	reloadList(_controller.GetAll());
}

void Gui::countTheType(const string& type)
{
	auto m = _controller.Creeaza_dictionar();
	auto it = m.find(type);
	QMessageBox::information(nullptr, "Numarul disciplinelor", QString::number((*it).second));
}

void Gui::addincontractDiscipina()
{
	QModelIndex selItem = lst->selectionModel()->selectedIndexes().at(0);
	auto denumire = selItem.data(Qt::UserRole).toString().toStdString();
	
	try {
		_controller.Adauga_disc_in_contract(denumire);
		notify_contracts();
	}
	catch (MyException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_type() + ex.what()));
	}
}

Gui::Gui(Service& controller) : _controller{ controller }
{
	initGUICmps();
	connectSignalsSlots();
	reloadList(_controller.GetAll());
}

void ContractGui::initGUICmps()
{
	setLayout(mainLayout);

	QStringList m_tableheader;
	m_tableheader << "Denumire" << "NrOre" << "Tip" << "Profesor";
	int nrlinii = 0;
	int nrcoloane = 4;
	discWidget = new QTableWidget{ nrlinii, nrcoloane };
	discWidget->setHorizontalHeaderLabels(m_tableheader);
	mainLayout->addWidget(discWidget);

	btnClearContract = new QPushButton("Clear");
	btnGenerateContract = new QPushButton("Generate");
	btnExportContract = new QPushButton("Export");

	QWidget* widClearGenerate = new QWidget;
	QHBoxLayout* lyClearGenerate = new QHBoxLayout;
	widClearGenerate->setLayout(lyClearGenerate);
	lyClearGenerate->addWidget(btnClearContract);
	lyClearGenerate->addWidget(btnGenerateContract);

	QWidget* widExport = new QWidget;
	QFormLayout* lyFilename = new QFormLayout;
	widExport->setLayout(lyFilename);
	lyFilename->addRow(new QLabel("Number to generate:"), txtnrtogenerate);
	lyFilename->addRow(new QLabel("FileName to export:"), txtfilename);

	mainLayout->addWidget(widClearGenerate);
	mainLayout->addWidget(widExport);
	mainLayout->addWidget(btnExportContract);
}

void ContractGui::connectSignalsSlots()
{
	/*QTimer* refreshTimer = new QTimer;
	QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
		reloadList(_controller.GetAllContract());
		});
	refreshTimer->start(1000);*/

	QObject::connect(btnClearContract, &QPushButton::clicked, [&]() {
		_controller.Curata_contract();
		reloadList(_controller.GetAllContract());
		_mainwindow.notify_contracts();
		});

	QObject::connect(btnGenerateContract, &QPushButton::clicked, [&]() {
		int status = _controller.Genereaza_contract(txtnrtogenerate->text().toInt());
		QMessageBox::information(nullptr, "Nr of disc generated", QString::number(status));
		reloadList(_controller.GetAllContract());
		_mainwindow.notify_contracts();
		});

	QObject::connect(btnExportContract, &QPushButton::clicked, [&]() {
		try {
			_controller.Exporta_contract(txtfilename->text().toStdString());
		}
		catch (MyException& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_type() + ex.what()));
		}
		});
}

void ContractGui::reloadList(const std::vector<Disciplina>& discs)
{
	discWidget->clear();
	QStringList m_tableheader;
	m_tableheader << "Denumire" << "NrOre" << "Tip" << "Profesor";
	discWidget->setHorizontalHeaderLabels(m_tableheader);
	discWidget->setRowCount(int(discs.size()));

	int index = 0;
	for (const auto& p : discs) {
		discWidget->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(p.get_denumire())));
		discWidget->setItem(index, 1, new QTableWidgetItem(QString::number(p.get_ore())));
		discWidget->setItem(index, 2, new QTableWidgetItem(QString::fromStdString(p.get_tip())));
		discWidget->setItem(index, 3, new QTableWidgetItem(QString::fromStdString(p.get_profesor())));
		index++;
	}
}

ContractGui::ContractGui(Service& controller, Gui& mainwindow) : _controller{ controller }, _mainwindow{ mainwindow }
{
	initGUICmps();
	connectSignalsSlots();
	reloadList(_controller.GetAllContract());
}

ContractGuiReadOnly::ContractGuiReadOnly(Service& controller) : _controller{ controller }
{
}

void ContractGuiReadOnly::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };
	srand(time(NULL));
	int marime = int(_controller.GetAllContract().size());
	for (int i = 0; i < marime; i++)
	{
		int x = abs(rand() % width() - 32);
		int y = abs(rand() % height() - 32);
		p.drawImage(x, y, QImage("C:\\Users\\Codrin\\Downloads\\mugshot.jpg").scaled(32, 32));
	}
	//QPainter myellip(this);
	//QPen epen;
	//epen.setWidth(3);
	//epen.setColor(Qt::yellow);
	//epen.setBrush(Qt::SolidPattern);
	//// myellip.setBrush(Qt::SolidPattern);
	//myellip.setPen(epen);
	//int marime = int(_controller.GetAllContract().size());
	//for (int i = 0; i < marime; i++)
	//	myellip.drawEllipse(QRect(150, 300, 100, 100));
}
