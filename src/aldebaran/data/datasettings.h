#ifndef DATASETTINGS_H
#define DATASETTINGS_H

#include "data.h"

class alDataSettings : public alData
{
    public:
	alDataSettings(alEngine * e);
	void save(QString subsystem, QString key, QVariant val);
    protected slots:
	virtual void checkTable();
};

#endif
