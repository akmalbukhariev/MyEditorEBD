#include "ColorFilmModel.h"

ColorFilmModel::ColorFilmModel(int nCol, QObject* parent)
	: QAbstractItemModel(parent)
{
	_nCol = nCol;
}

ColorFilmModel::~ColorFilmModel()
{

}

QVariant ColorFilmModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();

	if (role == Qt::DisplayRole)
	{
		if (_obj.isNull()) return QVariant();

		if (_wDesign->getFileInfo().colorFilmTable.count() == 0) return QVariant();

		if (index.row() >= _wDesign->getFileInfo().colorFilmTable.count()) return QVariant();

		quint32 colorIndex = _wDesign->getFileInfo().colorFilmTable[index.row()].colorIndex;
		quint32 stitches = _wDesign->getFileInfo().colorFilmTable[index.row()].stitches;

		switch (index.column())
		{
			case 0: return index.row() + 1;
			case 1: return colorIndex;
			case 2: return stitches;
			default: break;
		}
	}

	if (role == Qt::BackgroundColorRole)
	{ 
		if (index.column() == 1)
		{
			return extractColor(index.row());
		}
	}

	if (role == Qt::TextAlignmentRole)
	{
		return Qt::AlignCenter;
	}

	if (role == Qt::TextColorRole)
	{
		switch (index.column())
		{
			case 0: 
			case 2: return QColor(Qt::black);
			default: return QColor(Qt::white);
		}
	}

	return QVariant();
}

QVariant ColorFilmModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
				case 0:	return QObject::tr("Stop #");
				case 1:	return QObject::tr("Color");
				case 2:	return QObject::tr("Stitches");
				default: return QAbstractItemModel::headerData(section, orientation, role);
			}
		}
	}

	return QAbstractItemModel::headerData(section, orientation, role);
}

QVariant ColorFilmModel::data(int row, int col, int role) const
{
	QModelIndex idx = index(row, col);
	return data(idx, role);
}

QModelIndex ColorFilmModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);

	int maxRow = 0;
	if (_obj.isNull() == false)
		maxRow = _wDesign->getFileInfo().colorFilmTable.count();
	 
	if (row < maxRow && row >= 0 && column < _nCol && column >= 0)
	{
		return createIndex(row, column);
	}

	return QModelIndex();
}

QModelIndex ColorFilmModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	return QModelIndex();
}

int ColorFilmModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);

	int rowCount = 0;
	if (_obj.isNull() == false)
		rowCount = _wDesign->getFileInfo().colorFilmTable.count();
	 
	return rowCount;
}

int ColorFilmModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return _nCol;
}

void ColorFilmModel::reset()
{
	QAbstractItemModel::beginResetModel();
	QAbstractItemModel::endResetModel();
}

QColor ColorFilmModel::extractColor(int RowNum) const
{
	QColor sColor = Qt::white;

	if (_wDesign->getFileInfo().ebdHeader.ColorFilmDataSize == 0) return sColor;

	EbdHeader& header = _wDesign->getFileInfo().ebdHeader;

	if (header.ColorFilmDataSize > 0 && header.ColorPaletteSize > 0)
	{
		if ((RowNum + 1) < header.ColorFilmDataSize / 3)
		{
			ColorFilmStruct colorFilm = header.ColorFilmData[RowNum + 1];

			for (int i = 0; i < header.ColorPaletteSize / 4; i++)
			{
				quint32 colorIndex = header.ColorPaletteData[i] >> 24;

				if (colorIndex == colorFilm.PalletIndex)
				{
					int color = header.ColorPaletteData[i] & 0x00FFFFFF;

					return QColor::fromRgb(color);
				}
			}
		}
	}

	return sColor;
}

void ColorFilmModel::setWorkDesign(WidgetWokrDesign* wDesign)
{
	_obj = QPointer<WidgetWokrDesign>(wDesign);

	_wDesign = wDesign;
}