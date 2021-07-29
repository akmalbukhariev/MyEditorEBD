#include "Control.h"
#include "ColorMenu.h"

#include <QColorDialog>

ColorMenu::ColorMenu(QWidget* source, QObject *parent)
	:QObject(parent)
{
	_sourceWidget = (QToolBar*)source;

	connect(Control::instance(), &Control::sigCleanAllModels, this, &ColorMenu::slotCleanMenu);
}

ColorMenu::~ColorMenu()
{
}
 
void ColorMenu::setWorkDesign(WidgetWokrDesign* workDesign)
{
	cleanMenuBar();
	_workDesign = workDesign;

	EbdHeader& header = workDesign->getFileInfo().ebdHeader;

	if (header.ColorPaletteSize == 0)
	{
		for (int i = 0; i < _workDesign->getFileInfo().defaultPalettes.count(); i++)
		{
			QPushButton* cBtn = new QPushButton();
			QColor color = _workDesign->getFileInfo().defaultPalettes[i];

			cBtn->setText(QString::number(i + 1));
			cBtn->setStyleSheet(QString("background-color: %1; color: white").arg(color.name(QColor::HexArgb)));
			connect(cBtn, SIGNAL(clicked()), this, SLOT(slotColorButton()));

			_btnList.append(cBtn);
			_sourceWidget->addWidget(cBtn);
		}
	}
	else
	{
		QList<QList<int>> indexList;
		quint32 maxNo = 0;
		for (int i = 1; i < header.ColorPaletteSize / 4; i++)
		{
			quint32 maxNoTemp = (header.ColorPaletteData[i] >> 24) & 0x000000FF;

			if (maxNoTemp >= maxNo)
				maxNo = maxNoTemp;

			qint32 cc = (qint32)(header.ColorPaletteData[i] & 0x00FFFFFF);

			QList<int> data;
			data.append(maxNoTemp);
			data.append(cc);

			indexList.append(data);
		}

		if (maxNo == 0)
			maxNo = 15;

		_btnList.append(new QPushButton());

		for (int i = 1; i <= maxNo; i++)
		{
			bool found = false;

			QPushButton* cBtn = new QPushButton();

			for each (QList<int> var in indexList)
			{
				if (i == var[0])
				{
					found = true;
					cBtn->setProperty("SetColor", true);
					cBtn->setStyleSheet(QString("background-color: %1; color: white").arg(QColor(var[1]).name(QColor::HexArgb)));
					break;
				}
			}

			if (!found)
				cBtn->setVisible(false);

			cBtn->setText(QString::number(i));
			cBtn->setProperty("SetColor", false);
			connect(cBtn, SIGNAL(clicked()), this, SLOT(slotColorButton()));

			_sourceWidget->addWidget(cBtn);
			_btnList.append(cBtn);
		}

		//setRandomColor2Buttons();
	}
}

void ColorMenu::slotColorButton()
{
	for each (QPushButton* btn in _btnList)
	{
		if (sender() == btn)
		{
			QColorDialog colorDialog;
			if (!colorDialog.exec()) return;

			QRgb rgbColor = colorDialog.selectedColor().rgb();
			int btnIndex = btn->text().toInt();

			modifyPaletteColor(btnIndex, rgbColor);

			btn->setStyleSheet(QString("background-color: %1").arg(QColor(rgbColor).name(QColor::HexArgb)));
			
			for (int i = 0; i < _workDesign->getFileInfo().dParts->count(); i++)
			{
				DesignPart& dd = (*_workDesign->getFileInfo().dParts)[i];

				int colorIndex = 0;
				if (_workDesign->getFileInfo().ebdHeader.ColorFilmDataSize == 0)
					colorIndex = dd.colorIndex + 1;
				else
					colorIndex = dd.colorIndex;

				if (btnIndex == colorIndex)
				{
					dd.lineColor = QPen(rgbColor);
					_workDesign->replot();
				}
			}

			emit sigClickButton();
			break;
		}
	}
}

void ColorMenu::modifyPaletteColor(int index, const QColor& rgbColor)
{
	EbdHeader& header = _workDesign->getFileInfo().ebdHeader;

	for (int i = 0; i < header.ColorPaletteSize / 4; i++)
	{
		quint32 colorIndex = header.ColorPaletteData[i] >> 24;

		if (colorIndex == index)
		{
			header.ColorPaletteData[i] &= 0xFF000000;
			header.ColorPaletteData[i] |= (rgbColor.red() << 16) & 0x00FF0000;
			header.ColorPaletteData[i] |= (rgbColor.green() << 8) & 0x0000FF00;
			header.ColorPaletteData[i] |= rgbColor.blue() & 0x000000FF;
		}
	}
}

const QList<QPushButton*>& ColorMenu::GetColorButtonList() const
{
	return _btnList;
}

void ColorMenu::setRandomColor2Buttons()
{
	short cMax = 255;
	short cMin = 0;
	for (int i = 0; i < _btnList.count(); i++)
	{
		bool use = _btnList[i]->property("SetColor").toBool();
		if (!use)
		{
			int R = qrand() % (cMax - cMin + 1) + cMin;
			int G = qrand() % (cMax - cMin + 1) + cMin;
			int B = qrand() % (cMax - cMin + 1) + cMin;
			QString btnColor = QString("background-color: %1").arg(QColor(R, G, B).name(QColor::HexArgb));
			_btnList[i]->setStyleSheet(btnColor);

			//_stitchColor.append(QColor(R, G, B));
		}
	}

	//Control::instance()->setNeedleColor(_stitchColor);
}

void ColorMenu::cleanMenuBar()
{
	try
	{
		for each (QPushButton* var in _btnList)
		{
			if (var != Q_NULLPTR)
			{
				delete var;
				var = Q_NULLPTR;
			}
		}

		_btnList.clear();
	}
	catch (const std::exception& ex)
	{
		qDebug() << ex.what();
	}
}

void ColorMenu::slotCleanMenu()
{
	for (int i = 0; i < _btnList.count(); i++)
	{
		QPushButton* btn = _btnList[i];

		if (btn != Q_NULLPTR)
		{
			delete btn;
			btn = Q_NULLPTR;
		}
	}

	_btnList.clear();
}