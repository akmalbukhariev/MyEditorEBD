#pragma once

#include <QBrush> 
#include <QPointer>
#include <QAbstractItemModel>

#include "WidgetWokrDesign.h"

class ColorFilmModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	ColorFilmModel(int nCol, QObject* parent = Q_NULLPTR);
	~ColorFilmModel();

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant data(int row, int col, int role = Qt::DisplayRole) const;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	void reset();

	//Set work design.
	void setWorkDesign(WidgetWokrDesign* wDesign);

	//Get a Work design.
	WidgetWokrDesign* getWorkDesign() const
	{
		return _wDesign;
	}

protected:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	QColor extractColor(int RowNum) const;

private:
	int _nCol;

	QBrush* _brush;
	WidgetWokrDesign* _wDesign;

	QPointer<WidgetWokrDesign> _obj;
};
