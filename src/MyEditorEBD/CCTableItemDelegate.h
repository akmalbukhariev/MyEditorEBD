#pragma once

#include <QItemDelegate>

#include "CCTableModel.h"

class CCTableItemDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	CCTableItemDelegate(QObject* parent = Q_NULLPTR);
	~CCTableItemDelegate();

	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;

	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;

	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex & index) const;

	virtual void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;

	void useThis(bool use)
	{
		_use = use;
	}

protected:
	/*bool editorEvent(QEvent *event, QAbstractItemModel *model,
		const QStyleOptionViewItem &option, const QModelIndex &index) override;*/

private:
	bool _use;
};
