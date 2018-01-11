#ifndef ALSQLTABLEMODEL_H
#define ALSQLTABLEMODEL_H

#include <QSqlTableModel>
#include <QPixmap>

class alEngine;

class alSqlTableModel : public QSqlTableModel
{
Q_OBJECT
public:
    alSqlTableModel(alEngine * parent, QSqlDatabase db=QSqlDatabase(), const QString& table="");

    virtual QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    virtual QPixmap pixmap(int) const;
    QSqlRecord record(int row);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);
    virtual bool setHeaderData(int section, const QVariant & value);

    virtual bool insertColumn(int column, const QModelIndex & parent = QModelIndex());
    virtual bool removeColumns(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual int	columnCount(const QModelIndex & index = QModelIndex()) const;
public slots:
    int columnNum(QString attr);
protected:
    friend class alDataTable;
    void addHeaders(QStringList headers);
private:
    QVariantList fHeaders;
};

#endif // ALSQLTABLEMODEL_H
