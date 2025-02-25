#pragma once

#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <qpainter.h>
#include <qimage.h>
#include <qlistview.h>
#include <qtableview.h>

#include "../Service/service.h"
#include "../MyContainers/MyModel.h"

class ContractGui;
class ContractGuiReadOnly;

class Gui : public QWidget {
private:
	Service& _controller;
	vector<ContractGui*> ferestreCRUDGUI;
	vector<ContractGuiReadOnly*> ferestreREAD;
private:
	QHBoxLayout* lyMain = new QHBoxLayout;

	MyModel* model;
	QListView* lst = new QListView;

	QPushButton* btnSortByDenumire;
	QPushButton* btnAddToContract;
	QPushButton* btnSortByOre;
	QPushButton* btnSortByDenumireOre;
	QLineEdit* txtDenumire;
	QLineEdit* txtNrOre;
	QLineEdit* txtTip;
	QLineEdit* txtProfesor;
	QPushButton* btnShowList;
	QPushButton* btnAdd;
	QPushButton* btnDelete;
	QPushButton* btnModify;
	QPushButton* btnCountType;
	QPushButton* btnUndo;
	QPushButton* btnFiltrareNrOre;
	QPushButton* btnFiltrareProfesor;
	QPushButton* btnOpenContract;
	QPushButton* btnOpenContractRead;
	QVBoxLayout* lyBtnDy = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;
private:
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Disciplina>& discs);
	void make_type_buttons();
private:
	void addNewDisciplina();
	void deleteExistingDisciplina();
	void modifyADisciplina();
	void undoAction();
	void countTheType(const string& type);
	void addincontractDiscipina();
public:
	Gui(Service& controller);
	void notify_contracts();
};

class ContractGui : public QWidget
{
	friend class Gui;
private:
	Service& _controller;
	Gui& _mainwindow;
private:
	QVBoxLayout* mainLayout = new QVBoxLayout;

	//QListWidget* discWidget = new QListWidget;
	QTableWidget* discWidget;

	QLineEdit* txtfilename = new QLineEdit;
	QLineEdit* txtnrtogenerate = new QLineEdit;
	QPushButton* btnClearContract;
	QPushButton* btnGenerateContract;
	QPushButton* btnExportContract;
private:
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Disciplina>& discs);
public:
	ContractGui(Service& controller, Gui& mainwindow);
};

class ContractGuiReadOnly : public QWidget
{
	friend class Gui;
private:
	Service& _controller;
public:
	ContractGuiReadOnly(Service& controller);
	void paintEvent(QPaintEvent* ev) override;
};