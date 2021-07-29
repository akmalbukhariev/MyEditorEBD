#include "WriteFile.h"

WriteFile::WriteFile(const QString& fileName, QObject* parent)
	: _fileName(fileName), QObject(parent)
{
}

WriteFile::~WriteFile()
{
}

bool WriteFile::write(EbdFileInfo& ebdFile)
{
	return true;
}

QList<LinePoint> WriteFile::getList(const EbdFileInfo& ebdInfo)
{
	QList<LinePoint> list;

	for (int i = 0; i < ebdInfo.dParts->count(); i++)
	{
		DesignPart& dPart = (*ebdInfo.dParts)[i];

		for (int j = 0; j < dPart.points.count(); j++)
		{
			const LinePoint& lPoint = dPart.points[j];
			list.append(lPoint);
		}
	}

	return list;
}

uchar* WriteFile::encodeDst(char sx, char sy, uchar fn)
{
	uchar b[3] = { 0, 0, 3 };
	/*uchar* b = new uchar[3];
	memset(b, 0, 3);*/

	for (int i = 0; i <= 4; i++)
	{
		int kx = ConvertData[qAbs(sx)][i];
		int ky = ConvertData[qAbs(sy)][i];
		if (sx < 0)
			kx = -kx;
		if (sy < 0)
			ky = -ky;

		switch (qAbs(kx))
		{
			case 0: break;
			case 1:
				b[0] |= (uchar)(kx == 1 ? 0x01 : 0x02);
				break;
			case 3:
				b[1] |= (uchar)(kx == 3 ? 0x01 : 0x02);
				break;
			case 9:
				b[0] |= (uchar)(kx == 9 ? 0x04 : 0x08);
				break;
			case 27:
				b[1] |= (uchar)(kx == 27 ? 0x04 : 0x08);
				break;
			case 81:
				b[2] |= (uchar)(kx == 81 ? 0x04 : 0x08);
				break;
		}

		switch (qAbs(ky))
		{
			case 0: break;
			case 1:
				b[0] |= (uchar)(ky == 1 ? 0x80 : 0x40);
				break;
			case 3:
				b[1] |= (uchar)(ky == 3 ? 0x80 : 0x40);
				break;
			case 9:
				b[0] |= (uchar)(ky == 9 ? 0x20 : 0x10);
				break;
			case 27:
				b[1] |= (uchar)(ky == 27 ? 0x20 : 0x10);
				break;
			case 81:
				b[2] |= (uchar)(ky == 81 ? 0x20 : 0x10);
				break;
		}

		switch (fn & STITCH::FUNCTION_FILTER)
		{
			case STITCH::STOP_CODE:
			case STITCH::TRIM_STOP_CODE:
			case STITCH::CC_CODE:
				b[2] |= 0xc0;
				break;
			case STITCH::FRONTSQ_CODE:
			case STITCH::REARSQ_CODE:
			case STITCH::ALLSQ_CODE:
			case STITCH::SEQUIN_CODE:
			case STITCH::JUMP_CODE:
				b[2] |= 0x80;
				break;
			case STITCH::SQSTART_CODE:
			case STITCH::SQEND_CODE:
				b[2] |= 0x40;
				break;
			case STITCH::END_CODE:
				b[2] |= 0xf0;
				break;
			case STITCH::NORMAL_CODE_SLOW:
			case STITCH::NORMAL_CODE:
			default:
				break;
		}
	}

	return b;
}