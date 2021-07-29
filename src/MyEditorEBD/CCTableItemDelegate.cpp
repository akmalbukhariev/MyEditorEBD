#include "CCTableItemDelegate.h"

#include <QSpinBox>
#include <QTextEdit>
#include <QTableWidgetItem>

CCTableItemDelegate::CCTableItemDelegate(QObject *parent)
	: QItemDelegate(parent)
{
	_use = true;
}

CCTableItemDelegate::~CCTableItemDelegate()
{

}

QWidget* CCTableItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 3 && _use)
	{
		QSpinBox* hSpinBox = new QSpinBox(parent);
		hSpinBox->setMaximum(7);
		hSpinBox->setMinimum(0);
		return hSpinBox;
	}
	else return Q_NULLPTR;
	
	return QItemDelegate::createEditor(parent, option, index);
}

void CCTableItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	QSpinBox* sp = dynamic_cast<QSpinBox*>(editor);
	if (index.isValid() && index.column() == 3 && _use)
	{
		int val = index.model()->data(index).toInt();
		sp->setValue(val);
	}
}

void CCTableItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QSpinBox* sp = dynamic_cast<QSpinBox*>(editor);

	CCTableModel* ccModel = qobject_cast<CCTableModel*>(model);
	if (ccModel != Q_NULLPTR && index.isValid() && _use)
	{
		ccModel->getData()[index.row()].Height = sp->value();
	}
}

void CCTableItemDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);
}