#pragma once

#include <QWidget>
#include <QPushButton>

#include "CCTableView.h"
#include "CCTableModel.h"

class CCAbstractWidget : public QWidget
{
	Q_OBJECT

public:
	CCAbstractWidget(QWidget* parent);
	~CCAbstractWidget();

	void setEbdInfo(EbdFileInfo* ebdInfo);

	void setTableView(CCTableView* view)
	{
		_tableView = view;
	}

	void updateColorButtons();

	virtual void fillButtonList() = 0;

	//QString _className;

signals:
	void sigSendClickButton(QPushButton* btn);
	void sigSendClickColorButton(bool isChenile = false);

protected:

	//Initialize connection.
	void initConnection();

	//Set color button.
	void setColorButton(QPushButton* btn, const QColor& color);

	//Set a Needle info to the model.
	void setNeedleSetToModel(const NeedleSet& nInfo);

	//Modify a needleSet based on Offset and Stop.
	void modifyNeedleSetWithOffsetAndStop(NeedleSet& nInfo);
	 
	template< typename T >
	inline QVariant convert(const T &item)
	{
		QVariant var;
		var.setValue(item);

		return var;
	}

private:
	int getButtonIndex(QPushButton* btn);

protected slots:
	void slotClickButton();

protected:
	
	bool _isChenile;

	EbdFileInfo* _ebdInfo;
	CCTableView* _tableView;
	QList<QPushButton*> _btnList;
};

Q_DECLARE_METATYPE(CCTableItem);