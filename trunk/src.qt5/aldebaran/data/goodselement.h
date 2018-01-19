#ifndef GOODSELEMENT_H
#define GOODSELEMENT_H

#include "ui_goodselement.h"

class GoodsElement : public Ui::GoodsElement, QObject
{
public:
    GoodsElement(QDialog * parent);
public slots:
    void selectPicture();
    void clearPicture();
    void setData(alGoodsRecord * data);
    void refresh();
    void init();
    void update();
    void ok();
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void fileOpen();
    void fileSave();
    void textStyle( int i );
    void textSize( const QString &p );
    void textAlign( QAction *a );
    void textColor();
    void doConnections();
    void fontChanged( const QFont &f );
    void colorChanged( const QColor &c );
    void alignmentChanged( int a );
private:
    QDialog * fParent;
    alGoodsRecord * fData, * fParentGroup;
};

#endif // GOODSELEMENT_H
