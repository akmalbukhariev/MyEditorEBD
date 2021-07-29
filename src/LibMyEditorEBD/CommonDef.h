#pragma once

#include <QVariant>
#include <QPainter>

#include "libmyeditorebd_global.h"

namespace CommonDef
{
	enum { Margin = 50 };

	enum FileSuffix
	{
		NoneFile,
		Sst,
		Ebd,
		Dst,
		Tbf
	};

	enum SAxis
	{
		sXAxis,
		sYAxis
	};

	enum MenuButton
	{
		BTN_NONE,
		BTN_CLEAR,
		BTN_BACK,
		BTN_START,
		BTN_NEXT,
	};

	enum ToolBarButton
	{
		Transform,
		EditStitches,
		RotateDesign,
		ScaleDesign
	};

	struct STITCH
	{
		 static const ushort SEQUIN_FILTER = 0xE000;
		 static const ushort FRONT_SEQUIN = 0x8000;
		 static const ushort REAR_SEQUIN = 0x4000;
		 static const ushort ALL_SEQUIN = 0xC000;
		 static const ushort REPEAT_SEQUIN = 0x2000;

		 static const ushort OFFSET_NEEDLE_FILTER = 0x1000;

		 static const char FUNCTION_FILTER = 0x0F;
		 static const char NORMAL_CODE = 0x00;
		 static const char CC_CODE = 0x01;
		 static const char JUMP_CODE = 0x02;
		 static const char SEQUIN_CODE = 0x03;
		 static const char END_CODE = 0x04;
		 static const char SQSTART_CODE = 0x05;
		 static const char SQEND_CODE = 0x06;
		 static const char FRONTSQ_CODE = 0x07;
		 static const char REARSQ_CODE = 0x08;
		 static const char ALLSQ_CODE = 0x09;
		 static const char STOP_CODE = 0x0A;
		 static const char TRIM_STOP_CODE = 0x0B;
		 static const char TRIM_CODE = 0x0C;
		 static const char ERROR_CODE = 0xFF;

		 static const char T_SEQUIN_STEND_CODE = 0x03;
		 
		 static const int FRAME_MARGIN = 5;
		 static const int DRAWING_MARGIN = 15;
		 
		 static const char DRAW_GRAYBG = 0x00;
		 static const char DRAW_JOB = 0x01;
	};

	enum TypeOfFunction
	{
		//NONE, //Unknown code
		NORMAL_CODE = 0x00, //Normal stitch
		NORMAL_CODE_Slow = 0x80, //Slow stitch
		CC_CODE = 0x01, //Color change
		JUMP_CODE = 0x02, //Jump stitch
		SEQUIN_CODE = 0x03, //Manufactory only
		END_CODE = 0x04, //End of design
		SQSTART_CODE = 0x05, //Start of sequin
		SQEND_CODE = 0x06, //End of sequin
		FRONTSQ_CODE = 0x07, //Front sequin
		REARSQ_CODE = 0x08, //Rear sequin
		ALLSQ_CODE = 0x09, //All sequin
		STOP_CODE = 0x0A, //Stop only
		TRIM_STOP_CODE = 0x0B, //Trim and stop
		TRIM_CODE = 0x0C  //Trim only
	};
	 
	struct SAxisRange
	{
		double lower;
		double upper;

		SAxisRange() : lower(0), upper(5) {}

		double size()
		{
			return upper - lower;
		}
	};

	struct SAxisText
	{
		QString label;
		double position;

	private :
		SAxisText()
		{
			label = QString::null;
			position = 0.0;
		}
	};

	struct ChartInfo
	{
		QColor background;
		QColor axisColor;
		QColor axisLabelColor;
	};

	struct CCTableItem 
	{
		bool setColor;
		quint16 Needle;
		QPixmap Type;
		quint16 Height;
		QString Group;

		CCTableItem()
		{
			setColor = true;
		}

		CCTableItem(quint16 needle)
		{
			setColor = false;
			Needle = needle;
			Group = "AL";
		}

		CCTableItem(quint16 needle, QPixmap type)
		{
			setColor = false;
			Needle = needle;
			Type = type;
			Group = "AL";
		}

		CCTableItem(quint16 needle, QPixmap type, QString group)
		{
			setColor = false;
			Needle = needle;
			Type = type;
			Group = group;
		}
	};

	struct NeedleSet
	{
		bool useColor;
		quint16 Needle;
		quint16 Group;
		quint16 Height;
		quint16 Option;

		NeedleSet(quint16 needle, quint16 type, quint16 height, quint16 group)
		{
			useColor = false;
			Needle = needle;
			Group = group;
			Height = height;
			Option = type;
		}

		NeedleSet()
		{
			useColor = true;
			Needle = 0;
			Group = 0;
			Height = 0;
			Option = 0;
		}

		void Copy(NeedleSet other)
		{
			Needle = other.Needle;
			Group = other.Group;
			Height = other.Height;
			Option = other.Option;
		}
	};

	struct HeaderDataInfo
	{
		QString name;
		QString value;

		HeaderDataInfo()
		{
			name = "";
			value = "";
		}

		HeaderDataInfo(const QString& strName, const QString& strValue)
			: name(strName), value(strValue)
		{}

		bool isEmpty() const
		{
			return (name.trimmed() == "" && value.trimmed() == "");
		}
	};

	struct NeedleColor
	{
		qint32* Color;

		NeedleColor()
		{
			Color = new qint32[46];
			Color[0] = 0x00ffffff;  // 썸네일 배경 흰색
									// normal               // X2(BX)               // X3
			Color[1] = 0xffe60612; Color[16] = 0xff7fbe25; Color[31] = 0xffaa00aa;
			Color[2] = 0xffe5065f; Color[17] = 0xfff6ec05; Color[32] = 0xff00aaaa;
			Color[3] = 0xff016666; Color[18] = 0xff4a1d85; Color[33] = 0xff660000;
			Color[4] = 0xff078080; Color[19] = 0xff162171; Color[34] = 0xff006600;
			Color[5] = 0xffe8440b; Color[20] = 0xffd2df50; Color[35] = 0xff000066;
			Color[6] = 0xffe2006c; Color[21] = 0xffff0000; Color[36] = 0xff666600;
			Color[7] = 0xff179097; Color[22] = 0xff00ff00; Color[37] = 0xff660066;
			Color[8] = 0xff0f953c; Color[23] = 0xff0000ff; Color[38] = 0xff006666;
			Color[9] = 0xffeb6301; Color[24] = 0xffffff00; Color[39] = 0xff202020;
			Color[10] = 0xff7b0f53; Color[25] = 0xffff00ff; Color[40] = 0xff404040;
			Color[11] = 0xff2d449a; Color[26] = 0xff00ffff; Color[41] = 0xff606060;
			Color[12] = 0xff23ac39; Color[27] = 0xffaa0000; Color[42] = 0xff808080;
			Color[13] = 0xfffdd200; Color[28] = 0xff00aa00; Color[43] = 0xffa0a0a0;
			Color[14] = 0xff7b1877; Color[29] = 0xff0000aa; Color[44] = 0xffc0c0c0;
			Color[15] = 0xff07338c; Color[30] = 0xffaaaa00; Color[45] = 0xffe0e0e0;
		}
	};

	struct EBD_ID
	{
		static const quint16 START = 0x0EBD;
		static const quint16 HEADER = 0xA001;

		static const quint16 COLOR = 0xB001;
		static const quint16 CCTABLE = 0xB002;
		static const quint16 THUMBNAIL = 0xB003;
		static const quint16 STITCHDATA = 0xB004;
		static const quint16 WORKINFO = 0xB005; 
		static const quint16 DESIGN_PARA = 0xB006;
	};

	struct CONSTANT
	{
		static const quint16 DesignFileVer = 2;  // 디자인 파일 버전, '1'부터 시작
	};

	struct SstHeader
	{
		qint32 Stitch;
		qint16 Plus_x;
		qint16 Plus_y;
		quint16 Color;
		quint16 Jumper;
		char Name[9];
		qint32 Read_file;  //25 //old format = 0 (sst,dst,SWFxp..) 가져온 파일 포멧 종류
		char Option;       //1->sequin//26
		char Dummy[134];

		SstHeader()
		{
			Stitch = 0;
			Plus_x = 0;
			Plus_y = 0;
			Color = 0;
			Jumper = 0;
			Read_file = 0;
			Option = 0;
		}
	};

	struct ColorFilmStruct
	{
		char Sequin;
		char WorkType;
		char PalletIndex;

		ColorFilmStruct(char sequin, char workType, char palletIndex)
		{
			Sequin = sequin;
			WorkType = workType;
			PalletIndex = palletIndex;
		}

		ColorFilmStruct()
		{
			init();
		}

		void init()
		{
			Sequin = 0;//No sequin 
			WorkType = 0;//Normal work 
			PalletIndex = 0;
		}
	};

	struct ColorFilmTable
	{
		int colorIndex;
		int stitches;

		ColorFilmTable(int index, int stitchCount)
		{
			colorIndex = index;
			stitches = stitchCount;
		}

		void init()
		{
			colorIndex = 0;
			stitches = 0;
		}
	};

	struct EbdHeader
	{
		#pragma region Properties
		quint16 DesignStartID;		//0x0EBD
		quint16 Version;			//0x0100 ~ 

		quint16 HeaderID;			//0xA001
		quint32 TotalHeaderSize;	// HeaderSize; ~ ThumbNailData[];
		quint32 HeaderSize;			// StitchCount; ~ FileName[];
		quint32 StitchCount;		// 디자인 침수
		qint16 Plus_x;				//	자수 시작점부터 +X
		qint16 Plus_y;				//	자수 시작점부터 +Y
		qint16 Minus_x;				//	자수 시작점부터 -X
		qint16 Minus_y;				//	자수 시작점부터 -Y
		qint16 Gap_x;				//	
		qint16 Gap_y;				//	
		quint16 DesignLock;			//	Export 제한
		quint16 ColorChangeNum;		//	C/C Function 개수, 1 ~ 4000
		quint16 JumpNum;			//	Jump Function 개수
		quint16 DesignNameLength;	//	디자인 이름 길이

		QString DesignName;			//	디자인 이름
		quint16 FileNameLength;		//	원본 파일 이름 길이

		QString FileName;			//	원본 파일 이름

		quint32 ColorPaletteSize;	//	ColorPalleteData 길이
		quint32* ColorPaletteData;	//	4byte * 사용 칼라 개수

		quint32 ColorFilmDataSize;
		QList<ColorFilmStruct> ColorFilmData;

		quint16 CCTableID;			//	0xB002
		quint32 CCTableSize;		//	CCTableData 길이

		QList<NeedleSet> CCTableData;	// 8byte * ColorChangeNum

		quint16 ThumbNailID;			//	0xB003
		quint32 ThumbNailSize;			//	ThumbNailData 길이

		QByteArray ThumbNailData;		//	bitmap

		quint16 WorkInfoID;				//0xB005
		quint32 WorkInfoSize;			//WorkInfoDataSize
		quint16 StartPointUse;			//Design Start point use(1) or not(0) 
		qint32 XStartGap;				//Design start point distance to frame center point X  
		qint32 YStartGap;				//Design start point distance to frame center point Y
		quint16 FrameHoopUse;			//Frame & hoop setting use(1) or not(0)
		quint16 FrameType;				//Square, round, CAP.....
		quint16 HoopType;				//Hoop type(TRF12, SEMI CAP, WIDE CAP, 15X15, 30X30.....)
		quint16 WorkAreaWidth;			//Hoop width(1unit mm)
		quint16 WorkAreaHeight;			//Hoop height(1unit mm)
		quint16 PhysicalXSpace;			//MC max X space(1unit mm)
		quint16 PhysicalYSpace;			//MC MAx y space(1unit mm)
		quint16 Dummy16_1;				//2byte Reserved
		quint16 Dummy16_2;				//2byte Reserved
		quint16 Dummy16_3;				//2byte Reserved
		quint16 Dummy16_4;				//2byte Reserved
		quint32 Dummy32_1;				//4byte Reserved
		quint32 Dummy32_2;				//4byte Reserved
		quint32 Dummy32_3;				//4byte Reserved
		quint32 Dummy32_4;				//4byte Reserved

		quint16 DesignParaID;
		quint32 DesignParaSize;
		quint16 DesignModifyUse;
		quint16 Mirror;
		quint16 XScale;
		quint16 YScale;
		quint16 Angle;
		qint16 XSatin;
		qint16 YSatin;
		quint32 StartStitch;
		quint16 StartEndFiltering;
		quint16 Dummy_16_5;
		quint16 Dummy_16_6;
		quint16 Dummy_16_7;
		quint16 Dummy_16_8;
		quint32 Dummy_32_5;
		quint32 Dummy_32_6;
		quint32 Dummy_32_7;
		quint32 Dummy_32_8;

		quint32 MCColorPaletteID;   //0xB008 (Machine needle color pallete store filed)
		quint32 MCColorPaletteDataSize; //Fixed value 244 bytes(index 0~60, 1 item size 4bytes)
		quint32* MCColorPaletteData;

		quint16 DesignDataID;	//0xB004
		quint32 DesignDataSize;	//3byte * StitchCount;
		#pragma endregion

		EbdHeader()
		{
			#pragma region MyRegion
			DesignStartID = EBD_ID::START;
			Version = CONSTANT::DesignFileVer;

			HeaderID = EBD_ID::HEADER;
			TotalHeaderSize = 50;
			HeaderSize = 28;

			ColorPaletteData = Q_NULLPTR;

			StitchCount = 0;
			Plus_x = 0;
			Plus_y = 0;
			Minus_x = 0;
			Minus_y = 0;
			Gap_x = 0;
			Gap_y = 0;
			DesignLock = 0;
			ColorChangeNum = 1;
			JumpNum = 0;

			DesignNameLength = 0;
			DesignName = "";
			FileNameLength = 0;
			FileName = "";

			ColorPaletteSize = 0;
			ColorFilmDataSize = 0;

			CCTableID = EBD_ID::CCTABLE;

			ThumbNailID = EBD_ID::THUMBNAIL;

			WorkInfoID = EBD_ID::WORKINFO;	//0xB005
			WorkInfoSize = 48;				//WorkInfoDataSize
			StartPointUse = 0;				//Design Start point use(1) or not(0) 
			XStartGap = 0;					//Design start point distance to frame center point X  
			YStartGap = 0;					//Design start point distance to frame center point Y
			FrameHoopUse = 0;				//Frame & hoop setting use(1) or not(0)
			FrameType = 0;					//Square, round, CAP.....
			HoopType = 0;					//Hoop type(TRF12, SEMI CAP, WIDE CAP, 15X15, 30X30.....)
			WorkAreaWidth = 0;				//Hoop width(1unit mm)
			WorkAreaHeight = 0;				//Hoop height(1unit mm)
			PhysicalXSpace = 0;				//MC max X space(1unit mm)
			PhysicalYSpace = 0;				//MC MAx y space(1unit mm)
			Dummy16_1 = 0;					//2byte Reserved
			Dummy16_2 = 0;					//2byte Reserved
			Dummy16_3 = 0;					//2byte Reserved
			Dummy16_4 = 0;					//2byte Reserved
			Dummy32_1 = 0;					//4byte Reserved
			Dummy32_2 = 0;					//4byte Reserved
			Dummy32_3 = 0;					//4byte Reserved
			Dummy32_4 = 0;					//4byte Reserved

			DesignParaID = EBD_ID::DESIGN_PARA;
			DesignParaSize = 44;
			DesignModifyUse = 0;
			Mirror = 0;
			XScale = 100;
			YScale = 100;
			Angle = 0;
			XSatin = 0;
			YSatin = 0;
			StartStitch = 0;
			StartEndFiltering = 0;
			Dummy_16_5 = 0;
			Dummy_16_6 = 0;
			Dummy_16_7 = 0;
			Dummy_16_8 = 0;
			Dummy_32_5 = 0;
			Dummy_32_6 = 0;
			Dummy_32_7 = 0;
			Dummy_32_8 = 0;

			MCColorPaletteDataSize = 0;
			MCColorPaletteData = Q_NULLPTR;

			DesignDataID = EBD_ID::STITCHDATA;
			DesignDataSize = 0;
			#pragma endregion
		}
	};

	struct PointData
	{
		QPointF point;
		unsigned char func;

		PointData(const QPointF& p, unsigned char f)
		{
			point = p;
			func = f;
		}

		PointData()
		{

		}
	};

	struct LinePoint
	{
		QPointF startP;
		QPointF endP;
		QPointF rPoint;

		QPointF realPoint;
		
		TypeOfFunction type;

		LinePoint()
		{
			startP = QPoint(-1, -1);
			endP = QPoint(-1, -1);
			realPoint = QPoint(-1, -1);
			//type = TypeOfFunction::NORMAL_CODE;
		}

		LinePoint(QPointF sPoint, QPointF ePoint)
			:startP(sPoint), endP(ePoint) { }

		QPointF calcDiffXY() const
		{
			return QPointF(endP.x() - startP.x(), endP.y() - startP.y());
		}

		bool isValid()
		{
			if (startP.x() == -1 && startP.y() == -1 &&
				endP.x() == -1 && endP.y() == -1)
				return false;
			
			return true;
		}

		double minX() const
		{
			return qMin(startP.x(), endP.x());
		}

		double maxX() const
		{
			return qMax(startP.x(), endP.x());
		}

		double minY() const
		{
			return qMin(startP.y(), endP.y());
		}

		double maxY() const
		{
			return qMax(startP.y(), endP.y());
		}
	};

	struct DesignPart
	{
		int id;
		int colorIndex;
		bool removed;
		bool isActive;
		QPen lineColor;
		QRectF border;
		QPointF center;
		QPointF startPoint;
		QColor borderColor;
		QColor designColor;

		QList<LinePoint> points;

		DesignPart()
		{
			id = -1;
			colorIndex = 0;
			removed = false;
			isActive = false;
		}

		DesignPart(int listId, const QList<LinePoint>& pList)
			:id(listId), points(pList)
		{
			colorIndex = 0;
			removed = false;
			isActive = false;
		}

		/*void operator = (DesignPart other)
		{
			this->id = other.id;
			this->removed = removed;
			this->lineColor = other.lineColor;
			this->border = other.border;
			this->center = other.center;
			this->startPoint = other.startPoint;
			this->borderColor = other.borderColor;
			this->designColor = other.designColor;
			this->points = other.points;
		}*/

		int width() const
		{
			return border.width();
		}

		int height() const
		{
			return border.height();
		}

		void setColor(const QPen& pen)
		{
			lineColor = pen;
		}

		void calcBorder()
		{
			double startX = 0.0;
			double startY = 0.0;
			double endX = 0.0;
			double endY = 0.0;

			if (points.count() > 0)
			{
				startX = points[0].minX();
				startY = points[0].minY();
			}

			for each(LinePoint p in points)
			{
				startX = qMin(p.minX(), startX);
				endX = qMax(p.maxX(), endX);

				startY = qMin(p.minY(), startY);
				endY = qMax(p.maxY(), endY);
			}

			startPoint = QPointF(startX, startY);

			double bWidth = endX - startX;
			double bHeight = endY - startY;

			/*double bWidth = 0.0;
			double bHeight = 0.0;
			
			double _startX = 0.0;
			double _startY = 0.0;

			double _endX = 0.0;
			double _endY = 0.0;

			if (startX < 0) _startX = qAbs(startX);
			if (startY < 0) _startY = qAbs(startY);
			
			if (endX < 0) _endX = qAbs(endX);
			if (endY < 0) _endY = qAbs(endY);

			bWidth = (_endX >= _startX) ? _endX - _startX : _startX - _endX;
			bHeight = (_endY >= _startY) ? _endY - _startY : _startY - _endY;*/

			border = QRectF(startX, startY, bWidth, bHeight);

			double cX = qAbs(startX) + bWidth / 2;
			double cY = qAbs(startY) + bHeight / 2;

			cX = startX < 0 ? cX * -1 : cX;
			cY = startY < 0 ? cY * -1 : cY;

			center = QPointF(cX, cY);
		}

		/*void calcBorder()
		{
			double startX = 0.0;
			double startY = 0.0;
			double endX = 0.0;
			double endY = 0.0;

			if (points.count() > 0)
			{
				startX = points[0].x();
				startY = points[0].y();
			}

			for each(QPointF p in points)
			{
				startX = qMin(p.x(), startX);
				endX = qMax(p.x(), endX);

				startY = qMin(p.y(), startY);
				endY = qMax(p.y(), endY);
			}

			startPoint = QPointF(startX, startY);

			double bWidth = endX - startX;
			double bHeight = endY - startY;

			border = QRectF(startX, startY, bWidth, bHeight);

			double cX = qAbs(startX) + bWidth / 2;
			double cY = qAbs(startY) + bHeight / 2;

			cX = startX < 0 ? cX * -1 : cX;
			cY = startY < 0 ? cY * -1 : cY;

			center = QPointF(cX, cY);
		}*/
	};

	typedef QList<DesignPart> DataDesign;

	struct EbdFileInfo
	{
		int navigateId;
		QString strFile;
		QPixmap thumbNail;
		DataDesign* dParts;
		EbdHeader ebdHeader;
		QList<PointData> points;
		QList<QColor> defaultPalettes;
		QList<HeaderDataInfo> headers;
		QList<ColorFilmTable> colorFilmTable;

		int getCountOfData() const
		{
			int nCount = 0;
			
			if (dParts == Q_NULLPTR) return nCount;

			for (int i = 0; i < dParts->count(); i++)
			{
				nCount += dParts->at(i).points.count();
			}

			return nCount;
		}
	}; 
}

