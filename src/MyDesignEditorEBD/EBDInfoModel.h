#pragma once

#include <QBrush> 
#include <QPointer>
#include <QAbstractItemModel>

#include "CommonDef.h"

using namespace CommonDef;

class EBDInfoModel : public QAbstractItemModel
{
	Q_OBJECT

public:

	enum TableOption
	{
		None,
		PointTable,
		ColorTable,
		HeaderTable,
	};

	EBDInfoModel(int nCol, QObject *parent = 0);
	~EBDInfoModel();

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant data(int row, int col, int role = Qt::DisplayRole) const;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	void cleanModel();
	void reset();

	void setTableOption(TableOption tOption)
	{
		_tableOption = tOption;
	}

	void setEbdInfo(const EbdFileInfo& ebdInfo)
	{
		_ebdInfo = ebdInfo;
	}

protected:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:

	QString getFuncString(TypeOfFunction func) const;

private:

	int _nCol;

	QBrush* _brush;
	
	TableOption _tableOption;
	EbdFileInfo _ebdInfo;
};