//=========================================================================//
//                                                                         //
//  PonyProg - Serial Device Programmer                                    //
//                                                                         //
//  Copyright (C) 1997-2020   Claudio Lanconelli                           //
//                                                                         //
//  http://ponyprog.sourceforge.net                                        //
//                                                                         //
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
// along with this program (see LICENSE);     if not, write to the         //
// Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. //
//                                                                         //
//=========================================================================//


#include <QDebug>
#include <QCheckBox>
#include <QLabel>
#include <QPixmap>

#include "version.h"
#include "aboutmdlg.h"
#include "e2profil.h"


AboutModalDialog::AboutModalDialog(QWidget *bw, const QString title)
	: QDialog(bw)
{
	qDebug() << Q_FUNC_INFO;

	setupUi(this);

	setWindowTitle(title);

	cmdw = static_cast<e2CmdWindow *>(bw);

	if (cmdw->getStyleSheet().length() > 0)
	{
		setStyleSheet(cmdw->getStyleSheet());
	}

	lblAbout0->setText(APP_NAME " - " + translate(STR_APPNAME_EXT)  + "<br>" + translate(STR_MSGVERSION) + "  " APP_VERSION ", " __DATE__);
	QString t = "Copyright (C) " + QString(COPYRIGHTYEAR) + "  by  <a href=\"" + QString(APP_EMAIL) + "\">" + QString(APP_AUTHOR) + "</a><br><br>" +
				"Porting to Qt4/Qt5 by <a href=\"" + QString(PORTERMAIL) + "\">" + QString(PORTERGQT) + "</a><br><br>" +
				translate(STR_APPDOWNLOAD1) + " " + QString(APP_NAME) + " " + translate(STR_APPDOWNLOAD2) + "<br>" +
				"<a href=\"" + QString(AUTHORWEB) + "\">" + QString(AUTHORWEB) + "</a>";

	if (translate(MSG_TRANSLATORNAME).length() > 0)
	{
		t += "<br><br>" + translate(MSG_TRANSLATORCREDITS) +  "<br>" +
			 translate(MSG_TRANSLATORNAME).replace("\n", "<br>");
	}
	lblAbout1->setText(t);

	chkSound->setChecked(E2Profile::GetSkipStartupDialog());
	chkSound->setText(translate(STR_LBLSKIPMSG));

	pushOk->setText(translate(STR_BTNOK));
	pushHelp->setText(translate(STR_BTNHELP));

	icoPonyProg->setPixmap(QPixmap(":/icons/ponyprog.png"));

	connect(pushOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(pushHelp, SIGNAL(clicked()), this, SLOT(onHelp()));

	connect(chkSound, SIGNAL(clicked(bool)), this, SLOT(onChkStart(bool)));

	adjustSize();
}


AboutModalDialog::~AboutModalDialog()
{
	qDebug() << Q_FUNC_INFO;
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

