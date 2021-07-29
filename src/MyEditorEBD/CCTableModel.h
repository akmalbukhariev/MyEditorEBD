#pragma once

#include <QAbstractItemModel>

#include "CommonDef.h"

using namespace CommonDef;

class CCTableModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	CCTableModel(QObject* parent = Q_NULLPTR);
	~CCTableModel();

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant data(int row, int col, int role = Qt::DisplayRole) const;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;

	Qt::ItemFlags flags(const QModelIndex &index) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	void setData(const NeedleSet& needls);

	void setEbdFileInfo(EbdFileInfo* ebdInfo)
	{
		_ebdInfo = ebdInfo;
	}

	QVector<NeedleSet>& getData()
	{
		return _items;
	}

	int MaxNeedleNum;
	QColor* DesignColor;

	void setOptionRow(int row)
	{
		_optionRow = row;
	}

	void reset();

protected:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	int convertToNeedle(const NeedleSet& needle) const;
	QPixmap convertToType(const NeedleSet& needle) const;
	QString converToGroup(const NeedleSet& needle) const;
	QPixmap converToOption(const NeedleSet& needle) const;

	QColor extractColor(int RowNum) const;

private:
	int _colCount;
	int _optionRow;

	//QBrush* _brush;

	EbdFileInfo* _ebdInfo;
	QVector<NeedleSet> _items;
};