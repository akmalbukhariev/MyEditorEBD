#pragma once

#include <QDebug>
#include <QWidget>

#include "ReadFile.h"
#include "ReadDstFile.h"
#include "ReadEbdFile.h"
#include "ReadSstFile.h"
#include "ReadTbfFile.h"
#include "ui_WidgetWokrDesign.h"

class WidgetWokrDesign : public QWidget
{
	Q_OBJECT

public:
	WidgetWokrDesign(const QString& fileName, QWidget *parent = Q_NULLPTR);
	~WidgetWokrDesign();

	const QPixmap& getDesignMap() const
	{
		return ui.grViewSewing->getDesignMap();
	}

	//Set design icon.
	void setDesignIcon(const QIcon& icon)
	{
		_designIcon = icon;
	}

	//Draw and show the design.
	bool drawDesign(int id);

	//Set stitch color.
	void setStitchColor(const QList<QColor>& cList);

	//*Get a Header info.
	EbdFileInfo& getFileInfo();
  
	//Set transform.
	void setReArrangeObjects(bool clicked);

	//Set edit stitches.
	void setEditStitches(bool clicked);

	//Set grid visible.
	void setGridVisible(bool clicked);

	//Set axis visible.
	void setAxisVisible(bool clicked);

	//Set pointing when user click on pointInfo table.
	void setPointingPoint(bool click);

	//Make a visible axis.
	bool getVisibleAxis() const;

	//Make a visible grid.
	bool getVisibleGrid() const;

	//Click design part.
	bool getReArrangeObjects() const;

	//Click Edit stitches.
	bool getEditStitches() const;

	//Click set pointing.
	bool getVisiblePointingPoint() const;

	//Get a line point.
	LinePoint getLinePoint(int row);

	//Set click point info.
	void setClickPointInfo(const LinePoint& point);

	//Get a row of moving part in the design.
	int getRowOfMovingPart();

	//Update design.
	void replot()
	{
		ui.grViewSewing->replot();
	}

	const QString& getFileName() const
	{
		return _fileName;
	}

signals:
	void sigDesignDataChanged();
	void sigClickDesign(const LinePoint& point);
	void sigFileHasDropped(const QString& strFile);
	void sigWorkDesignClosing(WidgetWokrDesign* wDesign);

private:

	//Initialize the chart. 
	void initializeDrawing();

	//Initialize connection;
	void initConnection();

protected:

	void closeEvent(QCloseEvent *event);

private slots:
	void slotClickDesign2(const LinePoint& point);

private:
	Ui::WidgetWokrDesign ui;
	QIcon _designIcon;
	QString _fileName;

	ReadFile* _readFile;
	EbdFileInfo _ebdFileInfo;
	QList<QColor> _stitchColor;
};
