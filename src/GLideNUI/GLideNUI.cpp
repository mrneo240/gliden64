#include <thread>
#include <QApplication>
#include <QTranslator>

#include "GLideNUI.h"
#include "AboutDialog.h"
#include "ConfigDialog.h"
#include "Settings.h"
#include "../Config.h"

#ifdef QT_STATICPLUGIN
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QICOPlugin)
Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin)
#endif

//#define RUN_DIALOG_IN_THREAD

inline void initMyResource() { Q_INIT_RESOURCE(icon); }
inline void cleanMyResource() { Q_CLEANUP_RESOURCE(icon); }

static std::unique_ptr<QApplication> s_pQApp;
static QCoreApplication* s_pAppInstance;

static
int openConfigDialog(const wchar_t * _strFileName, const char * _romName, unsigned int _maxMSAALevel, float _maxAnisotropy, bool & _accepted)
{
	QString strIniFileName = QString::fromWCharArray(_strFileName);
	loadSettings(strIniFileName);
	if (config.generalEmulation.enableCustomSettings != 0 && _romName != nullptr && strlen(_romName) != 0)
		loadCustomRomSettings(strIniFileName, _romName);

	QTranslator translator;
	if (translator.load(getTranslationFile(), strIniFileName)) {
		s_pAppInstance->installTranslator(&translator);
	}

	ConfigDialog w(Q_NULLPTR, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint, _maxMSAALevel, _maxAnisotropy);

	w.setIniPath(strIniFileName);
	w.setRomName(_romName);
	w.setTitle();
	w.show();

	int res = s_pQApp ? s_pQApp->exec() : w.exec();
	_accepted = w.isAccepted();
	return res;
}

static
int openAboutDialog(const wchar_t * _strFileName)
{
	QTranslator translator;
	if (translator.load(getTranslationFile(), QString::fromWCharArray(_strFileName)))
		s_pAppInstance->installTranslator(&translator);

	AboutDialog w(Q_NULLPTR, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
	w.show();
	return s_pQApp ? s_pQApp->exec() : w.exec();
}

bool runConfigThread(const wchar_t * _strFileName, const char * _romName, unsigned int _maxMSAALevel, unsigned int _maxAnisotropy) {
	bool accepted = false;
#ifdef RUN_DIALOG_IN_THREAD
	std::thread configThread(openConfigDialog, _strFileName, _maxMSAALevel, std::ref(accepted));
	configThread.join();
#else
	openConfigDialog(_strFileName, _romName, _maxMSAALevel, _maxAnisotropy, accepted);
#endif
	return accepted;

}

int runAboutThread(const wchar_t * _strFileName) {
#ifdef RUN_DIALOG_IN_THREAD
	std::thread aboutThread(openAboutDialog, _strFileName);
	aboutThread.join();
#else
	openAboutDialog(_strFileName);
#endif
	return 0;
}

EXPORT void CALL ConfigInit(void * hinst)
{
	initMyResource();

	s_pAppInstance = QCoreApplication::instance();

	if (s_pAppInstance == nullptr) {
		int argc = 0;
		char * argv = 0;
		s_pQApp.reset(new QApplication(argc, &argv));
		s_pAppInstance = s_pQApp.get();
	}
}

EXPORT void CALL ConfigCleanup(void)
{
	cleanMyResource();
	s_pQApp.release();
}

EXPORT bool CALL RunConfig(const wchar_t * _strFileName, const char * _romName, unsigned int _maxMSAALevel, unsigned int _maxAnisotropy)
{
	return runConfigThread(_strFileName, _romName, _maxMSAALevel, _maxAnisotropy);
}

EXPORT int CALL RunAbout(const wchar_t * _strFileName)
{
	return runAboutThread(_strFileName);
}

EXPORT void CALL LoadConfig(const wchar_t * _strFileName)
{
	loadSettings(QString::fromWCharArray(_strFileName));
}

EXPORT void CALL LoadCustomRomSettings(const wchar_t * _strFileName, const char * _romName)
{
	loadCustomRomSettings(QString::fromWCharArray(_strFileName), _romName);
}
