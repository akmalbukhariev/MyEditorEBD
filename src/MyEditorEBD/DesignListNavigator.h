#pragma once

#include <QMenu>
#include <QListWidget>

#include <WidgetWokrDesign.h>

class DesignListNavigator : public QListWidget
{
	Q_OBJECT

public:
	DesignListNavigator(QWidget* parent);
	~DesignListNavigator();

	void addDesign(const QIcon& icon, const QString& iconFileName);
	void removeDesign(const QString& iconFileName = QString());

	void addDesign(WidgetWokrDesign* design);

	void selectItemFile(const QString& iconFileName);

private:
	void initView();

	//Initialize menu.
	void initMenu();

	void initConnection();

	bool exist(WidgetWokrDesign* design);
	bool exist(const QString& iconFileName);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void slotClickMenuAction();
	void slotDoubleClickItem(QListWidgetItem* item);
	void slotOnListMailItemClicked(QListWidgetItem* item);

private:
	bool _click;

	QMenu _menu;
	QAction* _actionCCTable;
};
