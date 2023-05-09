#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ui_settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class settingsDialog; }
QT_END_NAMESPACE

class settingsDialog : public QDialog
{
    Q_OBJECT
public:
    settingsDialog(QWidget * parent) : QDialog(parent), ui(new Ui::settingsDialog) { ui->setupUi(this); };
public slots:
    void selectPicture();
    void disableEnable();
    void setData(QMap<QString, alValueList> data );
    QMap<QString, alValueList> getData();
    void init( alEngine * engine );
    void selectImpExpDir();
    void selectBill();
    void selectOrder();
private:
    Ui::settingsDialog * ui;
    QPixmap pix;
    alEngine * fEngine;
};

#endif // SETTINGSDIALOG_H
