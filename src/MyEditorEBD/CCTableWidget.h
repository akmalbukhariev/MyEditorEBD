#pragma once

#include <QMenu>
#include <QTableWidget>

#include "CommonDef.h"
#include "CCTableItemDelegate.h"

using namespace CommonDef;

class CCTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	 
	CCTableWidget(QWidget* parent);
	~CCTableWidget();

	void setEbdInfo(EbdFileInfo* ebdInfo);

	void saveEbdFile();

	void removeRow();
	void clean();

public slots:
	void slotInsertRow(const CCTableItem& ccItem);

private:
	void initUI();
	void initMenu();
	void initConnection();

	QTableWidgetItem* getSelectedItem(int col);

	CCTableItem convertToCCItem(EbdFileInfo* ebdInfo, int i);

	CCTableItem getCCItem(int row);

	int convertToNeedle(EbdFileInfo* ebdInfo, int i);
	/*Option convertToType(EbdFileInfo* ebdInfo, int i);*/
	QString convertToGroup(EbdFileInfo* ebdInfo, int i);

protected:
	void paintEvent(QPaintEvent* event);
	void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void slotClickMenu();

private:

	int _row;

	QMenu _menu;
	QAction* _actionOffset;

	EbdFileInfo* _ebdFileInfo;
	CCTableItemDelegate* _ccDelegate; 
};
