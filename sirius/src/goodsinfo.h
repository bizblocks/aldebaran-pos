#ifndef GOODSINFO_H
#define GOODSINFO_H

#include <qdialog.h>
#include <qpixmap.h>

class sirius;
class sDataCursor;
class QTextView;

class sGoodsInfo : public QDialog
{
	Q_OBJECT
public:
	sGoodsInfo(sirius * s, sDataCursor * goods);
	~sGoodsInfo();
	void init();
public slots:
	void scrollUp();
	void scrollDown();
private:
	sirius * fSirius;
	QString name;
	double price;
	QString description;
	QPixmap picture;
	QTextView * tv;
	double hc, fat, protein, calories;
};

#endif
