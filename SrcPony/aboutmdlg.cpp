//=========================================================================//
//                                                                         //
//  PonyProg - Serial Device Programmer                                    //
//                                                                         //
//  Copyright (C) 1997-2017   Claudio Lanconelli                           //
//                                                                         //
//  http://ponyprog.sourceforge.net                                        //
//                                                                         //
//-------------------------------------------------------------------------//
// $Id: aboutmdlg.cpp,v 1.9 2013/11/05 13:23:01 lancos Exp $
//-------------------------------------------------------------------------//
//                                                                         //
// This program is free software; you can redistribute it and/or           //
// modify it under the terms of the GNU  General Public License            //
// as published by the Free Software Foundation; either version2 of        //
// the License, or (at your option) any later version.                     //
//                                                                         //
// This program is distributed in the hope that it will be useful,         //
// but WITHOUT ANY WARRANTY; without even the implied warranty of          //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       //
// General Public License for more details.                                //
//                                                                         //
// You should have received a copy of the GNU  General Public License      //
// along with this program (see COPYING);     if not, write to the         //
// Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. //
//                                                                         //
//-------------------------------------------------------------------------//
//=========================================================================//


#include <QDebug>
#include <QCheckBox>
#include <QLabel>
#include <QPixmap>


#include "aboutmdlg.h"
#include "e2profil.h"


using namespace Translator;


AboutModalDialog::AboutModalDialog(QWidget* bw, const QString title)
	: QDialog(bw)
{
	qDebug() << "AboutModalDialog::AboutModalDialog()";

	setupUi(this);

	setWindowTitle(title);

	cmdw = static_cast<e2CmdWindow *>(bw);

	if (cmdw->getStyleSheet().length() > 0)
	{
		setStyleSheet(cmdw->getStyleSheet());
	}

	lblAbout0->setText(APPNAME + " - " + APPNAME_EXT  + "<br>" + STR_MSGVERSION + "  " + APPVERSION + "  " __DATE__);
	lblAbout1->setText("Copyright (C) " + COPYRIGHTYEAR + "  by  <a href=\"" + AUTHORMAIL + "\">" + AUTHORNAME + "</a><br><br>" +
	                   "Porting to Qt4/Qt5 by <a href=\"" + PORTERMAIL + "\">" + PORTERGQT + "</a><br><br>" +
	                   STR_APPDOWNLOAD1 + " " + APPNAME + " " + STR_APPDOWNLOAD2 + "<br>" +
	                   "<a href=\"" + AUTHORWEB + "\">" + AUTHORWEB + "</a>" );

	chkSound->setChecked( E2Profile::GetSkipStartupDialog());
	chkSound->setText(STR_LBLSKIPMSG);

	pushOk->setText(STR_BTNOK);
	pushHelp->setText(STR_BTNHELP);

	icoPonyProg->setPixmap(QPixmap(":/icons/ponyprog.png"));

	connect(pushOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(pushHelp, SIGNAL(clicked()), this, SLOT(onHelp()));

	connect(chkSound, SIGNAL(clicked(bool)), this, SLOT(onChkStart(bool)));

	adjustSize();
}


AboutModalDialog::~AboutModalDialog()
{
	qDebug() << "AboutModalDialog::~AboutModalDialog()";
}


void AboutModalDialog::onHelp()
{
	cmdw->CmdHelp();

	accept();
}


void AboutModalDialog::onChkStart(bool c)
{
	E2Profile::SetSkipStartupDialog(c);
}

