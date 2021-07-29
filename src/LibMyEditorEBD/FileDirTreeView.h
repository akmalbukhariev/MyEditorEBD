#pragma once

#include <QTreeView>
#include <QDirModel>

#include "libmyeditorebd_global.h"

class LIBMYEDITOREBD_EXPORT FileDirTreeView : public QTreeView
{
	Q_OBJECT

public:
	FileDirTreeView(QWidget* parent);
	~FileDirTreeView();

	void initView();
	void setPath(const QString& path);

private:
	void initConnection();

	//Save the last path of selected folder.
	void saveLastFolder(const QString& path);

	void openDir(const QString& path);

signals:
	void sigFiles(const QString& path, const QStringList& files);

private slots:
	void slotClickTreeView(const QModelIndex& index);

private:

	QDirModel* _dirModel;
};
