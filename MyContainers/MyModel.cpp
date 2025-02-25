#include "MyModel.h"

MyModel::MyModel(const vector<Disciplina>& vect, bool isList) : _v{ vect }, status{ isList } {
}

int MyModel::rowCount(const QModelIndex& parent) const
{
	return int(_v.size());
}

int MyModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::UserRole)
		return QString::fromStdString(_v.at(index.row()).get_denumire());
	if (status)
	{
		if (role == Qt::DisplayRole) {
			return QString::fromStdString(_v.at(index.row()).to_string());
		}
		return QVariant();
	}
	if (role == Qt::DisplayRole) {
		//incomplete table model
		return QString("Row%1, Column%2").arg(index.row() + 1).arg(
			index.column() + 1);
	}
	return QVariant();
}

void MyModel::setDisc(const vector<Disciplina>& vect)
{
	emit layoutAboutToBeChanged();
	_v = vect;
	emit layoutChanged();
}
