#include "MyDesignEditorEBD.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyDesignEditorEBD w;
	w.show();
	return a.exec();
}
