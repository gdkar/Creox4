/***************************************************************************
					crsplashscreen.cpp  -  description
							 -------------------
		begin                : Sat Dec 29 2001
		copyright            : (C) 2001 by Jozef Kosoru
                                     : (C) 2011 by Kasper Laudrup
		email                : jozef.kosoru@pobox.sk
                                     : laudrup@stacktrace.dk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2        *
 *   as published by the Free Software Foundation                          *
 *                                                                         *
 ***************************************************************************/

#include <QApplication>
#include <QPixmap>
#include <QDesktopWidget>
#include <QLabel>

#include <KGlobal>
#include <KStandardDirs>

#include "settings.h"
#include "crsplashscreen.h"

CrSplashScreen* CrSplashScreen::s_this = 0;

CrSplashScreen::CrSplashScreen(const QString& strPixmapName, const char *name )
  : QLabel(0, name, Qt::WStyle_Customize | Qt::WStyle_NoBorder | Qt::WStyle_Tool
           | Qt::WStyle_StaysOnTop | Qt::WX11BypassWM | Qt::WNoAutoErase | Qt::WResizeNoErase)
{
  setBackgroundMode(Qt::NoBackground);

  if(Settings::showSplashScreen()){
    const KStandardDirs* const stdDirs = KGlobal::dirs();
    const QString strFileName(stdDirs->findResource("appdata", QString::fromLatin1("pics/") + strPixmapName));

    QPixmap pixmap(strFileName, "PNG");
    setPixmap(pixmap);
    adjustSize();

    const QDesktopWidget* const desktop = QApplication::desktop();
    move((desktop->width() - width())/2, (desktop->height() - height())/2);
  }

  if(!s_this){
    s_this = this;
  }
}

CrSplashScreen::~CrSplashScreen()
{
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
