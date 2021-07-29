#include "EBDInfoModel.h"

#include <qmath.h>

EBDInfoModel::EBDInfoModel(int nCol, QObject* parent)
	:_nCol(nCol), QAbstractItemModel(parent)
{
	QLinearGradient none(100, 30, 100, 0);
	none.setColorAt(0, QColor(228, 228, 247, 255));
	none.setColorAt(1, QColor(247, 247, 247, 255));
	none.setSpread(QGradient::PadSpread);

	_brush = NULL;
	_brush = new QBrush(none);

	_wDesign = Q_NULLPTR;
}

EBDInfoModel::~EBDInfoModel()
{
	if (_brush != NULL)
	{
		delete _brush;
		_brush = NULL;
	}
}

QVariant EBDInfoModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	
	if (role == Qt::DisplayRole)
	{
		if (_obj.isNull()) return QVariant();

		if (_tableOption == TableOption::PointTable)
		{
			if (_wDesign->getFileInfo().getCountOfData() == 0 || index.row() >= _wDesign->getFileInfo().getCountOfData()) return QVariant();

			const LinePoint& item = _wDesign->getLinePoint(index.row());//_dataPoint[index.row()];

			switch (index.column())
			{
				case 0:	 return round(item.realPoint.x());
				case 1:	 return round(item.realPoint.y());
				case 2:	 return getFuncString(item.type);
				default: return QVariant();
			}
		}
		else if (_tableOption == TableOption::HeaderTable)
		{
			if (_wDesign->getFileInfo().headers.count() == 0 || index.row() >= _wDesign->getFileInfo().headers.count())	return QVariant();

			const HeaderDataInfo& items = _wDesign->getFileInfo().headers[index.row()];

			switch (index.column())
			{
				case 0:	  return items.name;
				case 1:	  return items.value;
				default:  return QVariant();
			}
		}
		else if (_tableOption == TableOption::ColorTable)
		{
			if (_wDesign->getFileInfo().ebdHeader.CCTableData.count() == 0 || 
				index.row() >= _wDesign->getFileInfo().ebdHeader.CCTableData.count())	
				return QVariant();

			const NeedleSet& items = _wDesign->getFileInfo().ebdHeader.CCTableData[index.row()];

			switch (index.column())
			{
				case 0:	  return items.Needle;
				case 1:	  return items.Option;
				case 2:	  return items.Height;
				case 3:	  return items.Group;
				default:  return QVariant();
			}
		}
	}

	if (role == Qt::BackgroundColorRole)
	{
		if (_tableOption == TableOption::HeaderTable)
		{
			if (index.row() >= 0 && index.row() <= 1)
			{
				return QBrush(QColor::fromRgb(221, 235, 247)); //Signature filed ID
			}
			else if (index.row() >= 2 && index.row() <= 18)
			{
				return QBrush(QColor::fromRgb(172, 185, 202)); //Design information header filed ID
			}
			else if (index.row() >= 19 && index.row() <= 20)
			{
				return QBrush(QColor::fromRgb(252, 228, 214)); //Color palette table ID
			}
			else if (index.row() >= 21 && index.row() <= 22)
			{
				return QBrush(QColor::fromRgb(247, 202, 172)); //Used sequence of color palette ID
			}
			else if (index.row() >= 23 && index.row() <= 24)
			{
				return QBrush(QColor::fromRgb(156, 194, 229)); //Thumbnail ID
			}
			else if (index.row() >= 25 && index.row() <= 44)
			{
				return QBrush(QColor::fromRgb(142, 170, 219)); //Work info ID
			}
			else if (index.row() >= 45 && index.row() <= 63)
			{
				return QBrush(QColor::fromRgb(255, 217, 102)); //Design modify parameter ID
			}
			else if (index.row() >= 64 && index.row() <= 66)
			{
				return QBrush(QColor::fromRgb(198, 224, 180)); //Design ID
			}
			else if (index.row() >= 67 && index.row() <= 69)
			{
				return QBrush(QColor::fromRgb(217, 217, 217)); //Reserved ID
			}
			else
				return *_brush;
		}
		else
			return *_brush;
	}

	if (role == Qt::TextAlignmentRole)
	{
		return Qt::AlignCenter;
	}

	if (role == Qt::TextColorRole) return QColor(Qt::black);

	return QVariant();
}

QVariant EBDInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			if (_tableOption == TableOption::PointTable)
			{
				switch (section)
				{
					case 0:	return QObject::tr("X");
					case 1:	return QObject::tr("Y");
					case 2:	return QObject::tr("Func");
					default: return QAbstractItemModel::headerData(section, orientation, role);
				}
			}
			else if (_tableOption == TableOption::HeaderTable)
			{
				switch (section)
				{
					case 0:	return QObject::tr("Name");
					case 1:	return QObject::tr("Value");
					default: return QAbstractItemModel::headerData(section, orientation, role);
				}
			}
			else if (_tableOption == TableOption::ColorTable)
			{
				switch (section)
				{
					case 0:	return QObject::tr("Needle");
					case 1:	return QObject::tr("Type");
					case 2:	return QObject::tr("Height");
					case 3:	return QObject::tr("Group");
					default: return QAbstractItemModel::headerData(section, orientation, role);
				}
			}
		}
	}

	return QAbstractItemModel::headerData(section, orientation, role);
}

QVariant EBDInfoModel::data(int row, int col, int role) const
{
	QModelIndex idx = index(row, col);
	return data(idx, role);
}

QModelIndex EBDInfoModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	
	int maxRow = 0;

	//QPointer< WidgetWokrDesign> obj(_wDesign);

	if(_obj.isNull() == false) 
	//if (_wDesign != Q_NULLPTR)
	{
		switch (_tableOption)
		{
			case TableOption::PointTable: maxRow = _wDesign->getFileInfo().getCountOfData(); break;
			case TableOption::HeaderTable: maxRow = _wDesign->getFileInfo().headers.count(); break;
			case TableOption::ColorTable: maxRow = _wDesign->getFileInfo().ebdHeader.CCTableData.count(); break;
		}
	}

	if (row < maxRow && row >= 0 && column < _nCol && column >= 0)
	{
		return createIndex(row, column);
	}

	return QModelIndex();
}

QModelIndex EBDInfoModel::parent(const QModelIndex& child) const
{
	Q_UNUSED(child);
	return QModelIndex();
}

int EBDInfoModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	
	int rowCount = 0;

	if (_obj.isNull() == false)
	//if (_wDesign != Q_NULLPTR)
	{
		switch (_tableOption)
		{
			case TableOption::PointTable: rowCount = _wDesign->getFileInfo().getCountOfData();  break;
			case TableOption::HeaderTable: rowCount = _wDesign->getFileInfo().headers.count(); break;
			case TableOption::ColorTable: rowCount = _wDesign->getFileInfo().ebdHeader.CCTableData.count(); break;
		}
	}

	return rowCount;
}

int EBDInfoModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return _nCol;
}

LinePoint EBDInfoModel::getData(int row)
{
	return (_obj.isNull() == false) ? _wDesign->getLinePoint(row) : LinePoint();
}

void EBDInfoModel::reset()
{
	QAbstractItemModel::beginResetModel();
	QAbstractItemModel::endResetModel();
}

void EBDInfoModel::setWorkDesign(WidgetWokrDesign* wDesign)
{
	_obj = QPointer<WidgetWokrDesign>(wDesign);

	_wDesign = wDesign;
}

QString EBDInfoModel::getFuncString(TypeOfFunction func) const
{
	QString strFunc = "";
	switch (func)
	{
		case TypeOfFunction::NORMAL_CODE:		strFunc = "Normal";		break;
		case TypeOfFunction::NORMAL_CODE_Slow:	strFunc = "Normal Slow"; break;
		case TypeOfFunction::CC_CODE:			strFunc = "CC";			break;
		case TypeOfFunction::JUMP_CODE:			strFunc = "Jump";		break;
		case TypeOfFunction::SEQUIN_CODE:		strFunc = "Sequin";		break;
		case TypeOfFunction::END_CODE:			strFunc = "End";		break;
		case TypeOfFunction::SQSTART_CODE:		strFunc = "Sqstart";	break;
		case TypeOfFunction::SQEND_CODE:		strFunc = "Sqend";		break;
		case TypeOfFunction::FRONTSQ_CODE:		strFunc = "Frontsq";	break;
		case TypeOfFunction::REARSQ_CODE:		strFunc = "Rearsq";		break;
		case TypeOfFunction::ALLSQ_CODE:		strFunc = "Allsq";		break;
		case TypeOfFunction::STOP_CODE:			strFunc = "Stop";		break;
		case TypeOfFunction::TRIM_STOP_CODE:	strFunc = "Trim stop";	break;
		case TypeOfFunction::TRIM_CODE:			strFunc = "Trim";		break;
		default:
		break;
	}

	return QString::number(func) + " [" + strFunc + "]";
}