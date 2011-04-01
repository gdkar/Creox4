/***************************************************************************
					crsplashscreen.cpp  -  description
							 -------------------
		begin                : Sat Dec 29 2001
		copyright            : (C) 2001 by Jozef Kosoru
		email                : jozef.kosoru@pobox.sk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2        *
 *   as published by the Free Software Foundation                          *
 *                                                                         *
 ***************************************************************************/

#include "control.h"
#include <iostream>
#include <QApplication>
#include <QString>
#include <QPixmap>
//Added by qt3to4:
#include <QLabel>
#include <kconfig.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include "crsplashscreen.h"

#include <KConfig>
#include <KConfigGroup>

CrSplashScreen* CrSplashScreen::s_this = 0;

CrSplashScreen::CrSplashScreen(const QString& strPixmapName, const char *name )
		: QLabel(0, name, Qt::WStyle_Customize | Qt::WStyle_NoBorder | Qt::WStyle_Tool
							| Qt::WStyle_StaysOnTop | Qt::WX11BypassWM | Qt::WNoAutoErase | Qt::WResizeNoErase)
{
	setBackgroundMode(Qt::NoBackground);

	KConfigGroup conf = KGlobal::config()->group(QString::fromLatin1("Splash_Screen"));
	m_bLoadOnStartup = conf.readEntry("loadOnStartup", true);

	if(m_bLoadOnStartup){
		const KStandardDirs* const stdDirs = KGlobal::dirs();
		const QString strFileName(stdDirs->findResource("appdata", QString::fromLatin1("pics/") + strPixmapName));

		QPixmap pixmap(strFileName, "PNG");
                // XXX!
		//pixmap.setOptimization(QPixmap::NoOptim);

		setPixmap(pixmap);
		adjustSize();

                // XXX!
		//const QWidget* const desktop = QApplication::desktop();
		//move((desktop->width() - width())/2, (desktop->height() - height())/2);
	}

	if(!s_this){
		s_this = this;
	}
}

CrSplashScreen::~CrSplashScreen()
{
#ifdef _DEBUG
	std::cerr << "CrSplashScreen deleted...\n";
#endif
}

void CrSplashScreen::show()
{
	if(m_bLoadOnStartup){
		QLabel::show();
		repaint(false);
		QApplication::flush();
	}
}

void CrSplashScreen::setLoadOnStartup(const bool bLoad)
{
	KConfigGroup conf = KGlobal::config()->group(QString::fromLatin1("Splash_Screen"));
	conf.writeEntry("loadOnStartup", bLoad);
}
