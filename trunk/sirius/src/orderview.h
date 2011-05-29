#ifndef ORDERTABLE_H
#define ORDERTABLE_H

#include <qwidget.h>

class QListView;
class QListViewItem;
class QLabel;
class sirius;
class sDataOrder;
class sHeaderItem;
class sOrderItem;

class sOrderView : public QWidget
{
	Q_OBJECT
public:
	sOrderView(sirius * s, QWidget * parent);
	~sOrderView();
	void setOrder(sDataOrder * order);
	QListView * orderView() { return view; };
public slots:
	void updateRow(int row);
	virtual void clear();
signals:
	void plusClicked(int row);
	void minusClicked(int row);	
protected:
	virtual void resizeEvent(QResizeEvent *);
	void enumerate();
	void showTotals();
protected slots:
	void onItem(QListViewItem*, const QPoint&, int c);
	void onUp();
	void onDown();
private:	
	sirius * fSirius;
	sDataOrder * fOrder;
	QValueList<sOrderItem*> fItems;
	sHeaderItem * fHeader;
	QListView * headerView, * view;
	QLabel * totalView;
};

#endif

