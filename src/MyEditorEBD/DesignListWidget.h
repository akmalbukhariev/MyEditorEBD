#pragma once

#include <QMenu>
#include <QListWidget>

#include "CommonDef.h"

using namespace CommonDef;

class DesignListWidget : public QListWidget
{
	Q_OBJECT

public:
	DesignListWidget(QWidget *parent);
	~DesignListWidget();

signals:
	void sigSelectedFile(const QString& strFile, const QIcon& icon);

public slots:
	void slotSetEbdiInfo(const EbdFileInfo& endInfo);
	void slotCurrentIndexChanged(int index);

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void initView();
	void initConnection();
	QString makeText(EbdFileInfo& ebdInfo);

private slots:
	void slotDoubleClickItem(QListWidgetItem* item);
	void slotClickMenuAction();

private:
	QMenu _menu;
	QMenu _menuMode;
	QAction* _actionIconMode;
	QAction* _actionListMode;
	QAction* _actionViewMode;
	QAction* _actionProperties;
};

Q_DECLARE_METATYPE(EbdFileInfo);