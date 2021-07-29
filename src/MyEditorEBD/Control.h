#pragma once

#include <QMap>
#include <QObject>

#include "CommonDef.h"
#include "ThreadLoading.h"
#include "WidgetLoading.h"

using namespace CommonDef;

struct NavigationMap
{
	int _id;
	QPixmap _pixmap;

	NavigationMap(int id) :_id(id) {}

	NavigationMap(int id, const QPixmap& pixmap)
		:_id(id), _pixmap(pixmap) {}

	bool operator == (const NavigationMap& other)
	{
		return this->_id == other._id;
	}
};

class Control : public QObject
{
	Q_OBJECT

public:
	static Control* instance();
	Control(QObject* parent = Q_NULLPTR);
	~Control();

	enum MsgOption
	{
		Info,
		Warring,
		Critical
	};

	//Add a pixmap to the navigation list.
	void addPixmapToNavigationList(int id, const QPixmap& pixmap = QPixmap());

	//Update the navigation list.
	void updatePixmapInNavigationList(int id, const QPixmap& pixmap);

	//Get a pixmap based on the file name.
	QPixmap getPixmapFromNavigationList(int id);

	//Remove a map from navigation list.
	void removePixmapFromNavigationList(int id);

	//Show loading process.
	void showLoading(QWidget* parent = Q_NULLPTR);

	//Cloae loading process.
	void closeLoading();

	//Show a message box.
	void showMessageBox(QWidget* parent, const QString& title, const QString& text, MsgOption option = Info);

	//Set needle color.
	void setNeedleColor(const QList<QColor>& lColor)
	{
		_lColor = lColor;
	}

	//Get a Needle color.
	const QList<QColor>& getNeedleColor() const
	{
		return _lColor;
	}

	//Set click point info signal when user click the table.
	void setClickPointInfoTable(const LinePoint& point);

	//Set click point info signal when user click the design
	void setClickDesign(const LinePoint& point);

	void setSelectedDesign(const QString& strFile);

	//File has dropped.
	void setFileHasDropped(const QString& strFile);
	 
	void designDataChanged();

	void cleanAllModels(const QString& strFile = QString());

	FileSuffix fileSuffix(const QString& strFile);

	template<typename T>
	char* structToByte(T t)
	{
		//return reinterpret_cast<char*>(&t);
		return static_cast<char*>(static_cast<void*>(&t));
	}

	template<typename T>
	T byteToStruct(char* data, T t)
	{
		return *(T*)((void*)data);
	}

signals:
	void sigUpdateNavigate(const QPixmap& pixmap);
	void sigDesignDataChanged();

	void sigFileHasDropped(const QString& strFile);
	 
	void sigSelectedDesign(const QString& strFile);

	void sigClickPointInfoTable(const LinePoint& point);
	void sigClickDesign(const LinePoint& point);
	void sigCleanAllModels(const QString& strFile = QString());

private:
	static Control* _self;

	QList<QColor> _lColor;

	QList<NavigationMap> _navigationMapList;

	WidgetLoading* _wLoading;
	ThreadLoading* _thLoading;
};
