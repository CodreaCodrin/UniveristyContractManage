#pragma once
#include <qabstractitemmodel.h>
#include <vector>
#include <Domain/entity.h>

using std::vector;

class MyModel : public QAbstractListModel {
private:
	vector<Disciplina> _v;
	bool status;
public:
	MyModel(const vector<Disciplina>& vect, bool isList);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setDisc(const vector<Disciplina>& vect);
};