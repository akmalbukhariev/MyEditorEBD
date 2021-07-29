#include "CCTableModel.h"

#include <QIcon>
#include <QDebug>

CCTableModel::CCTableModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	_colCount = 5;
	_optionRow = 0;
	MaxNeedleNum = 15;

	DesignColor = Q_NULLPTR;
	DesignColor = new QColor[MaxNeedleNum + 1];
}

CCTableModel::~CCTableModel()
{
	if (DesignColor != Q_NULLPTR)
	{
		delete[] DesignColor;
		DesignColor = Q_NULLPTR;
	}
}

QVariant CCTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();

	const NeedleSet& needle = _items[index.row()];

	if( role ==  Qt::DisplayRole)
	{
		switch (index.column())
		{
			case 0: return index.row() + 1;
			case 1: return convertToNeedle(needle);
			case 3: return needle.Height;
			case 4: return converToGroup(needle);
			default: return QVariant();
		}
	}
	
	if( role == Qt::DecorationRole)
	{
		if(index.column() == 2)
		{
			return convertToType(needle);
		}
	}
	
	if (role == Qt::BackgroundColorRole)
	{
		if(index.column() == 0)
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
			case 0:  return (extractColor(index.row()) == Qt::white) ?  QColor(Qt::black) : QColor(Qt::white);
			default: return QColor(Qt::black);
		}
	}

	return QVariant();
}

QVariant CCTableModel::data(int row, int col, int role) const
{
	QModelIndex idx = index(row, col);
	return data(idx, role);
}

QModelIndex CCTableModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	int maxRow = _items.count();

	if (row < maxRow && row >= 0 && column < _colCount && column >= 0)
	{
		return createIndex(row, column);
	}

	return QModelIndex();
}

QVariant CCTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch (role)
	{
		case Qt::DisplayRole:
		{
			if (orientation == Qt::Horizontal)
			{
				switch (section)
				{
					case 0: return "No";
					case 1: return "N";
					case 2: return "T";
					case 3: return "H";
					case 4: return "G";
					default: return QVariant();
				}
			}
			else if (orientation == Qt::Vertical)
			{
				return "";
			}
		}
		break;
		case Qt::DecorationRole:
		{
			if(orientation == Qt::Vertical )
				return converToOption(_items[section]);

			return QVariant();
		}
		case Qt::SizeHintRole:
		{
			if (orientation == Qt::Vertical)
				return QSize(30, 10);
		}
		break;
	}

	return QAbstractItemModel::headerData(section, orientation, role);
}

QModelIndex CCTableModel::parent(const QModelIndex &child) const
{
	Q_UNUSED(child);
	return QModelIndex();
}

Qt::ItemFlags CCTableModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	if (!index.isValid()) return flags;

	/*if (index.column() == 0)
		return Qt::ItemIsDragEnabled
	else*/
		if (index.column() == 3)
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	return flags;
}

int CCTableModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return _items.count();
}

int CCTableModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return _colCount;
}

int CCTableModel::convertToNeedle(const NeedleSet& needle) const
{
	int temp = needle.Needle & 0x7f;//0x3f
	return (char)temp;
}

QPixmap CCTableModel::convertToType(const NeedleSet& needle) const
{
	QPixmap pixmap;

	quint16 value = needle.Needle;

	int temp = value & 0x3000; //0x6000;
	int TValue = (char)(temp >> 11);

	int mtemp = value & 0x780; //0xf00;
	int Mode = (char)(mtemp >> 7);

	int ttemp = value & 0x800; //0x1000;
	int bobbin = (char)(ttemp >> 11);

	if (Mode == 0)
	{
		switch (TValue)
		{
			case 2: pixmap = QPixmap("Resources/icon_center_r.png"); break; //Rear
			case 4: pixmap = QPixmap("Resources/icon_center_f.png"); break; //Front
			case 6: pixmap = QPixmap("Resources/icon_center_a.png"); break; //All
		}
	}
	else
	{
		switch (Mode)
		{
			//Chenille
			case 1: pixmap = QPixmap("Resources/L.png"); break;
			case 2: pixmap = QPixmap("Resources/C.png"); break;

			//Taping
			case 4: pixmap = QPixmap("Resources/icon_list_tn.png");														    break; //Normal
			case 5: pixmap = (bobbin == 0) ? QPixmap("Resources/icon_list_tf.png") : QPixmap("Resources/icon_list_tr.png"); break; //Tape
			case 6: pixmap = (bobbin == 0) ? QPixmap("Resources/icon_list_cf.png") : QPixmap("Resources/icon_list_cr.png"); break; //Coil
			case 7: pixmap = (bobbin == 0) ? QPixmap("Resources/icon_list_ff.png") : QPixmap("Resources/icon_list_fr.png"); break; //Frill 

			//Zigzag
			case 8:  pixmap = QPixmap("Resources/icon_z1.png"); break;
			case 9:  pixmap = QPixmap("Resources/icon_z2.png"); break;
			case 10: pixmap = QPixmap("Resources/icon_z3.png"); break;
			case 11: pixmap = QPixmap("Resources/icon_z4.png"); break;
			case 12: pixmap = QPixmap("Resources/icon_z5.png"); break;
			case 13: pixmap = QPixmap("Resources/icon_z6.png"); break;
			default: break;
		}
	}

	if(!pixmap.isNull())
		pixmap = pixmap.scaled(QSize(35, 35));

	return pixmap;
}

QString CCTableModel::converToGroup(const NeedleSet& needle) const
{
	QString strGroup = "";
	switch(needle.Group)
	{
		case 0: strGroup = "AL"; break;
		case 1: strGroup = "OD"; break;
		case 2: strGroup = "EV"; break;
		default: break;
	}

	return strGroup;
}

QPixmap CCTableModel::converToOption(const NeedleSet& needle) const
{
	int temp = needle.Needle & 0xc000; //0xC0
	int TValue = (char)(temp >> 14);   //6

	QPixmap pixmap;
	switch (TValue)
	{
		case 1: pixmap = QPixmap("Resources/point_s_left.png"); break;
		case 2: pixmap = QPixmap("Resources/point_o_left.png"); break;
	}

	return pixmap;
}

QColor CCTableModel::extractColor(int RowNum) const
{
	QColor sColor = Qt::white;

	if(_ebdInfo->ebdHeader.ColorFilmDataSize == 0) return sColor;

	EbdHeader& header = _ebdInfo->ebdHeader;

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

void CCTableModel::setData(const NeedleSet& needls)
{
	_items.append(needls);
}

void CCTableModel::reset()
{
	QAbstractItemModel::beginResetModel();
	QAbstractItemModel::endResetModel();
}