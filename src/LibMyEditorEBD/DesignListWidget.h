#pragma once

#include <QMenu>
#include <QListWidget>

#include "CommonDef.h"

using namespace CommonDef;

class LIBMYEDITOREBD_EXPORT DesignListWidget : public QListWidget
{
	Q_OBJECT

public:
	DesignListWidget(QWidget *parent);
	~DesignListWidget();

	void showDialogs(bool show);

signals:
	void sigSelectedRepeat(const EbdFileInfo& ebdInfo);
	void sigSelectedFiltering(const EbdFileInfo& ebdInfo);
	void sigSelectedStitEdit(const EbdFileInfo& ebdInfo);
	void sigSelectedStitchDivide(const EbdFileInfo& ebdInfo);
	void sigClickedFile(const EbdFileInfo& ebdInfo);
	void sigDoubleClickedFile(const QString& strFile, const QIcon& icon);

public slots:
	void slotSetEbdiInfo(const EbdFileInfo& endInfo);
	void slotCurrentIndexChanged(int index);

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void initView();
	void initMenu();
	void initConnection();
	QString makeText(const EbdFileInfo& ebdInfo);

private slots:
	void slotSelectAction();
	void slotClickMenuAction();
	void slotClickItem(QListWidgetItem* item);
	void slotDoubleClickItem(QListWidgetItem* item);

private:
	QMenu _menu;
	QMenu _menuMode;
	QAction* _actionIconMode;
	QAction* _actionListMode;
	QAction* _actionViewMode;
	QAction* _actionRepeatDialog;
	QAction* _actionFilteringDialog;
	QAction* _actionStitchEditDialog;
	QAction* _actionStitchDivideDialog;
	QAction* _actionProperties;

	EbdFileInfo _ebdInfo;
};

Q_DECLARE_METATYPE(EbdFileInfo);