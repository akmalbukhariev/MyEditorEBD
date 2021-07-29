#pragma once
#include <qmdiarea.h>

#include "WidgetWokrDesign.h"

class DesignContainer : public QMdiArea
{
	Q_OBJECT

public:
	DesignContainer(QWidget* parent = nullptr);
	virtual ~DesignContainer();

	//Add a new design window.
	void addWindow(const QString& fileName);

	//Set stitch color.
	void setStitchColor(const QList<QColor>& cList);

	//Get an active sub window.
	WidgetWokrDesign* getActiveDesignWindow();

	//Get a pixmap.
	const QPixmap& getDesignMap();

	bool hasError()
	{
		return _hasError;
	}

	void setActiveWindow(const QString& strFile);

signals:
	void sigDesignDataChanged(WidgetWokrDesign* wDesign);

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);

private:

	void initConnections();

	//Check a file if is opened.
	bool checkFile(const QString& strFile);

private slots:
	void slotDesignDataChanged();
	void slotClickPointInfoTable(const LinePoint& point);
	
	void slotWorkDesignClosing(WidgetWokrDesign* wDesign);
private:
	bool _hasError;
	int _navigateId;
	QString _fileName;

	QList<QColor> _stitchColor;
};

