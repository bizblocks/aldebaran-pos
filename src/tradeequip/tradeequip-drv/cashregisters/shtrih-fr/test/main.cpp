#include <shtrih-fr.h>
#include "ui_mainform.h"
#include <qapplication.h>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
#ifdef Q_OS_WIN32
  QString appPath=app.applicationDirPath();
  app.addLibraryPath(app.applicationDirPath());
#endif
//TODO implement
  //	MainForm *mainForm;
//	app.setMainWidget(mainForm=new MainForm());
//  if (mainForm->success())
//  {
//	  mainForm->show();
//	  return app.exec();
//  }
  return 100;
}
