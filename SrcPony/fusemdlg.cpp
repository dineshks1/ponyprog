//=========================================================================//
//                                                                         //
//  PonyProg - Serial Device Programmer                                    //
//                                                                         //
//  Copyright (C) 1997-2017   Claudio Lanconelli                           //
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
// along with this program (see COPYING);     if not, write to the         //
// Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. //
//                                                                         //
//-------------------------------------------------------------------------//
//=========================================================================//


#include "fusemdlg.h"

#include <QDebug>
#include <QTreeWidget>
#include <QRadioButton>



//======================>>> fuseModalDialog::fuseModalDialog <<<==================
fuseModalDialog::fuseModalDialog(e2CmdWindow *bw, e2AppWinInfo *p, bool readonly, const QString &msg) :
	QDialog(bw)
{
	setupUi(this);

	setWindowTitle(translate(STR_MSGFUSEDLG));

	awip = p;

	lock = awip->GetLockBits();
	fuse = awip->GetFuseBits();

	e2CmdWindow *cmdw = static_cast<e2CmdWindow *>(bw);

	if (cmdw->getStyleSheet().length() > 0)
	{
		setStyleSheet(cmdw->getStyleSheet());
	}

	long type = bw->GetCurrentChipType();

	qDebug() << "fuseModalDialog::fuseModalDialog()";

// 	chkFuse = (QVector<QCheckBox *>() << chk0_F0 << chk1_F0 << chk2_F0 << chk3_F0 << chk4_F0 << chk5_F0 << chk6_F0 << chk7_F0
// 			   << chk0_F1 << chk1_F1 << chk2_F1 << chk3_F1 << chk4_F1 << chk5_F1 << chk6_F1 << chk7_F1
// 			   << chk0_F2 << chk1_F2 << chk2_F2 << chk3_F2 << chk4_F2 << chk5_F2 << chk6_F2 << chk7_F2
// 			   << chk0_F3 << chk1_F3 << chk2_F3 << chk3_F3 << chk4_F3 << chk5_F3 << chk6_F3 << chk7_F3
// 			  );
//
// 	chkLock = (QVector<QCheckBox *>() << chk0_L0 << chk1_L0 << chk2_L0 << chk3_L0 << chk4_L0 << chk5_L0 << chk6_L0 << chk7_L0
// 			   << chk0_L1 << chk1_L1 << chk2_L1 << chk3_L1 << chk4_L1 << chk5_L1 << chk6_L1 << chk7_L1
// 			   << chk0_L2 << chk1_L2 << chk2_L2 << chk3_L2 << chk4_L2 << chk5_L2 << chk6_L2 << chk7_L2
// 			   << chk0_L3 << chk1_L3 << chk2_L3 << chk3_L3 << chk4_L3 << chk5_L3 << chk6_L3 << chk7_L3
// 			  );

	read = write = false;

// 	frmLock->setTitle("Lock");

	setTextWidgets();

// 	frmFuses->setTitle("Fuse");

	initWidgets(msg, type, readonly);

	connect(pushRead, SIGNAL(clicked()), this, SLOT(onRead()));
	connect(pushWrite, SIGNAL(clicked()), this, SLOT(onProg()));
	connect(pushOk, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(pushCancel, SIGNAL(clicked()), this, SLOT(reject()));
}


//===================>>> fuseModalDialog::~fuseModalDialog <<<====================
fuseModalDialog::~fuseModalDialog()
{
	qDebug() << "fuseModalDialog::~fuseModalDialog()";
}

void fuseModalDialog::setTextWidgets()
{
// 	int i = 0;
//
// 	foreach (QCheckBox *c, chkFuse)
// 	{
// 		c->setText(QString().sprintf(" %d", i));
// 		i++;
//
// 		if (i == 8)
// 		{
// 			i = 0;
// 		}
// 	}
//
// 	i = 0;
//
// 	foreach (QCheckBox *c, chkLock)
// 	{
// 		c->setText(QString().sprintf(" %d", i));
// 		i++;
//
// 		if (i == 8)
// 		{
// 			i = 0;
// 		}
// 	}

	pushRead->setText(translate(STR_BTNREAD));
	pushWrite->setText(translate(STR_BTNWRITE));
	pushOk->setText(translate(STR_BTNOK));
	pushCancel->setText(translate(STR_BTNCANC));
}


void fuseModalDialog::onOk()
{
	unsigned int l = 0;
	unsigned int f = 0;

#if 0
	for (int k = 0; k < LOCKPACKSIZE; k++)
	{
		lock |= (chkLock.at(0 * 8 + k)->isChecked()) ? (0x80000000 >> k) : 0;
		lock |= (chkLock.at(1 * 8 + k)->isChecked()) ? (0x800000 >> k) : 0;
		lock |= (chkLock.at(2 * 8 + k)->isChecked()) ? (0x8000 >> k) : 0;
		lock |= (chkLock.at(3 * 8 + k)->isChecked()) ? (0x80 >> k) : 0;

		fuse |= (chkFuse.at(0 * 8 + k)->isChecked()) ? (0x80000000 >> k) : 0;
		fuse |= (chkFuse.at(1 * 8 + k)->isChecked()) ? (0x800000 >> k) : 0;
		fuse |= (chkFuse.at(2 * 8 + k)->isChecked()) ? (0x8000 >> k) : 0;
		fuse |= (chkFuse.at(3 * 8 + k)->isChecked()) ? (0x80 >> k) : 0;
	}
#endif
	//      lock = lock;
	//      fuse = fuse;

	if (read == true)
	{
		emit done(2);
	}
	else
	{
		awip->SetLockBits(l);
		awip->SetFuseBits(f);

		if (write == true)
		{
			emit done(3);
		}
		else
		{
			accept();
		}
	}
}


void fuseModalDialog::onProg()
{
	write = true;

	emit onOk();
}


void fuseModalDialog::onRead()
{
	read = true;

	emit onOk();
}


int fuseModalDialog::eep_FindFuses(long type)
{
	for (int k = 0; eep_bits.count(); k++)
	{
		if (eep_bits.at(k).type == type)
		{
			return k;
		}
	}

	return -1;
}


void fuseModalDialog::initWidgets(const QString &msg, long int type, bool readonly)
{
	int j = eep_FindFuses(type);

	if (j >= 0)
	{
		ChipBits fBit = eep_bits.at(j);
		if (fBit.lock.count() > 0)
		{
			QTreeWidgetItem *lckItem = new QTreeWidgetItem();
			lckItem->setText(0, "Lock");
			treeWidget->insertTopLevelItem(0, lckItem);

			for (int i = 0; i < fBit.lock.count(); i++)
			{
				QTreeWidgetItem *itm = new QTreeWidgetItem();
				itm->setText(0, QString().sprintf("Bit %d ", i) + fBit.lock.at(i).ShortDescr);
				if (fBit.lock.at(i).LongDescr.length() > 0)
				{
					itm->setText(1, fBit.lock.at(i).LongDescr);
				}
				itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
				itm->setCheckState(0, Qt::Checked);
				lckItem->addChild(itm);
			}
		}

		if (fBit.fuse.count() > 0)
		{
			QTreeWidgetItem *lckItem = new QTreeWidgetItem();
			lckItem->setText(0, "Fuse");
			treeWidget->insertTopLevelItem(0, lckItem);

			for (int i = 0; i < fBit.fuse.count(); i++)
			{
				QTreeWidgetItem *itm = new QTreeWidgetItem();
				itm->setText(0, QString().sprintf("Bit %d ", i) + fBit.fuse.at(i).ShortDescr);
				if (fBit.fuse.at(i).LongDescr.length() > 0)
				{
					itm->setText(1, fBit.fuse.at(i).LongDescr);
				}
				itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
				itm->setCheckState(0, Qt::Checked);
				lckItem->addChild(itm);
			}
		}
#if 0
		frmLock0->setHidden(fBit.lockenable3 == 0);
		frmLock1->setHidden(fBit.lockenable2 == 0);
		frmLock2->setHidden(fBit.lockenable1 == 0);
		frmLock3->setHidden(fBit.lockenable0 == 0);

		frmFuses0->setHidden(fBit.fuseenable3 == 0);
		frmFuses1->setHidden(fBit.fuseenable2 == 0);
		frmFuses2->setHidden(fBit.fuseenable1 == 0);
		frmFuses3->setHidden(fBit.fuseenable0 == 0);

		if (fBit.lockenable3 == 0 &&
				fBit.lockenable2 == 0 &&
				fBit.lockenable1 == 0 &&
				fBit.lockenable0 == 0)
		{
			frmLock->setHidden(true);
		}
		else
		{
			frmLock->setHidden(false);
		}

		if (fBit.fuseenable3 == 0 &&
				fBit.fuseenable2 == 0 &&
				fBit.fuseenable1 == 0 &&
				fBit.fuseenable0 == 0)
		{
			frmFuses->setHidden(true);
		}
		else
		{
			frmFuses->setHidden(false);
		}


		//Label
		for (int k = 0; k < LOCKPACKSIZE; k++)
		{
			QString sp;
			int pos = LOCKPACKSIZE - k - 1;
			QString def = QString().sprintf(" %d", k);

			sp = fBit.locklabel3[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkLock.at(0 * 8 + k)->setText(sp);

			sp = fBit.locklabel2[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkLock.at(1 * 8 + k)->setText(sp);

			sp = fBit.locklabel1[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkLock.at(2 * 8 + k)->setText(sp);

			sp = fBit.locklabel0[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkLock.at(3 * 8 + k)->setText(sp);


			sp = fBit.fuselabel3[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkFuse.at(0 * 8 + k)->setText(sp);

			sp = fBit.fuselabel2[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkFuse.at(1 * 8 + k)->setText(sp);

			sp = fBit.fuselabel1[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkFuse.at(2 * 8 + k)->setText(sp);

			sp = fBit.fuselabel0[pos];

			if (!sp.length())
			{
				sp = def;
			}

			chkFuse.at(3 * 8 + k)->setText(sp);
		}

		//Sensitive
		for (int k = 0; k < LOCKPACKSIZE; k++)
		{
			int pos = LOCKPACKSIZE - k - 1;
			chkLock.at(0 * 8 + pos)->setEnabled((fBit.lockenable3 & (0x80 >> k)) ? true : false);
			chkLock.at(1 * 8 + pos)->setEnabled((fBit.lockenable2 & (0x80 >> k)) ? true : false);
			chkLock.at(2 * 8 + pos)->setEnabled((fBit.lockenable1 & (0x80 >> k)) ? true : false);
			chkLock.at(3 * 8 + pos)->setEnabled((fBit.lockenable0 & (0x80 >> k)) ? true : false);

			chkFuse.at(0 * 8 + pos)->setEnabled((fBit.fuseenable3 & (0x80 >> k)) ? true : false);
			chkFuse.at(1 * 8 + pos)->setEnabled((fBit.fuseenable2 & (0x80 >> k)) ? true : false);
			chkFuse.at(2 * 8 + pos)->setEnabled((fBit.fuseenable1 & (0x80 >> k)) ? true : false);
			chkFuse.at(3 * 8 + pos)->setEnabled((fBit.fuseenable0 & (0x80 >> k)) ? true : false);
		}
#endif
	}
	else
	{
#if 0
		//Default (disable all)
		for (int k = 0; k < LOCKPACKSIZE; k++)
		{
			QString def = QString().sprintf(" %d", k);
			//Label
			chkLock.at(0 * 8 + k)->setText(def);
			chkLock.at(1 * 8 + k)->setText(def);
			chkLock.at(2 * 8 + k)->setText(def);
			chkLock.at(3 * 8 + k)->setText(def);

			chkFuse.at(0 * 8 + k)->setText(def);
			chkFuse.at(1 * 8 + k)->setText(def);
			chkFuse.at(2 * 8 + k)->setText(def);
			chkFuse.at(3 * 8 + k)->setText(def);

			//Sensitive
			chkLock.at(0 * 8 + k)->setEnabled(false);
			chkLock.at(1 * 8 + k)->setEnabled(false);
			chkLock.at(2 * 8 + k)->setEnabled(false);
			chkLock.at(3 * 8 + k)->setEnabled(false);

			chkFuse.at(0 * 8 + k)->setEnabled(false);
			chkFuse.at(1 * 8 + k)->setEnabled(false);
			chkFuse.at(2 * 8 + k)->setEnabled(false);
			chkFuse.at(3 * 8 + k)->setEnabled(false);
		}
#endif
	}

#if 0
	//Checked
	for (int k = 0; k < LOCKPACKSIZE; k++)
	{
		chkLock.at(0 * 8 + k)->setChecked(((lock >> 24) & (0x80 >> k)) ? true : false); // L0
		chkLock.at(1 * 8 + k)->setChecked(((lock >> 16) & (0x80 >> k)) ? true : false); // L1
		chkLock.at(2 * 8 + k)->setChecked(((lock >>  8) & (0x80 >> k)) ? true : false); // L2
		chkLock.at(3 * 8 + k)->setChecked(((lock) & (0x80 >> k)) ? true : false);     // L3

		chkFuse.at(0 * 8 + k)->setChecked(((fuse >> 24) & (0x80 >> k)) ? true : false); // F0
		chkFuse.at(1 * 8 + k)->setChecked(((fuse >> 16) & (0x80 >> k)) ? true : false); // F1
		chkFuse.at(2 * 8 + k)->setChecked(((fuse >>  8) & (0x80 >> k)) ? true : false); // F2
		chkFuse.at(3 * 8 + k)->setChecked(((fuse) & (0x80 >> k)) ? true : false);     // F3
	}
#endif
	chkHlp1->setText(translate(STR_FUSEDLGNOTESET) + " (bit = 0)");
	chkHlp1->setEnabled(false);
	chkHlp0->setText(translate(STR_FUSEDLGNOTECLR) + " (bit = 1)");
	chkHlp0->setEnabled(false);

	if (readonly)
	{
		pushOk->setEnabled(false);
		pushWrite->setEnabled(false);
	}
	else
	{
		pushOk->setEnabled(true);
		pushWrite->setEnabled(true);
	}
}



QVector<ChipBits> fuseModalDialog::eep_bits =
{
	{
		AT90S1200,
		{
			// fuse
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		},
	},
	{
		AT90S2313,
		{
			// fuse
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		AT90S4414,
		{
			// fuse
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		AT90S8515,
		{
			// fuse
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		AT90S4434,
		{
			// fuse
			{ 0, "FSTRT", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		AT90S8535,
		{
			// fuse
			{ 0, "FSTRT", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		AT90S2333,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "BODEN", },
			{ 4, "BODLEVEL", },
			{ 5, "SPIEN", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		AT90S4433,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "BODEN", },
			{ 4, "BODLEVEL", },
			{ 5, "SPIEN", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		AT90S2323,
		{
			// fuse
			{ 0, "FSTRT", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		AT90S2343,
		{
			// fuse
			{0, "RCEN", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		AT90S8534,
		{
			// fuse
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		ATtiny12,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "RSTDISBL", },
			{ 5, "SPIEN", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		ATtiny13,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "SUT0", },
			{ 3, "SUT1", },
			{ 4, "CKDIV8", },
			{ 5, "WDTON", },
			{ 6, "EESAVE", },
			{ 7, "SPIEN", },
			{ 8, "RSTDISBL", },
			{ 9, "BODLEVEL0", },
			{ 10, "BODLEVEL1", },
			{ 11, "DWEN", },
			{ 12, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},
	{
		ATtiny15,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 4, "RSTDISBL", },
			{ 5, "SPIEN", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		ATtiny22,
		{
			// fuse
			{ 0, "RCEN", },
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},
	{
		ATtiny26,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOPT", },
			{ 7, "PLLCK", },
			{ 8, "BODEN", },
			{ 9, "BODLEVEL", },
			{ 10, "EESAVE", },
			{ 11, "SPIEN", },
			{ 12, "RSTDISBL", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},

	{
		ATtiny2313,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "RSTDISBL", },
			{ 9, "BODLEVEL0", },
			{ 10, "BODLEVEL1", },
			{ 11, "BODLEVEL2", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "EESAVE", },
			{ 15, "DWEN", },
			{ 16, "SPMEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},
	{
		ATtiny25,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},

	{
		ATtiny45,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},
	{
		ATtiny85,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},

	{
		ATtiny261,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},

	{
		ATtiny461,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},

	{
		ATtiny861,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", }
		}
	},

	{
		ATmega48,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "SELFPRGEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega88,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "BOOTRST", },
			{ 17, "BOOTSZ0", },
			{ 18, "BOOTSZ1", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega168,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "BOOTRST", },
			{ 17, "BOOTSZ0", },
			{ 18, "BOOTSZ1", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega328,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BODLEVEL0", },
			{ 9, "BODLEVEL1", },
			{ 10, "BODLEVEL2", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "DWEN", },
			{ 15, "RSTDISBL", },
			{ 16, "BOOTRST", },
			{ 17, "BOOTSZ0", },
			{ 18, "BOOTSZ1", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega164,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega324,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega644,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega640,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega1280,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega1281,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega2560,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega2561,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "BODLEVEL0", },
			{ 17, "BODLEVEL1", },
			{ 18, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		AT90CAN32,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "TA0SEL", },
			{ 17, "BODLEVEL0", },
			{ 18, "BODLEVEL1", },
			{ 19, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		AT90CAN64,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "TA0SEL", },
			{ 17, "BODLEVEL0", },
			{ 18, "BODLEVEL1", },
			{ 19, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		AT90CAN128,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "TA0SEL", },
			{ 17, "BODLEVEL0", },
			{ 18, "BODLEVEL1", },
			{ 19, "BODLEVEL2", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega603,
		{
			// fuse
			{ 0, "SUT0", },
			{ 1, "SUT1", },
			{ 3, "EESAVE", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		ATmega103,
		{
			// fuse
			{ 0, "SUT0", },
			{ 1, "SUT1", },
			{ 3, "EESAVE", }
		},
		{
			// lock
			{ 1, "Lock1", },
			{ 2, "Lock2", }
		}
	},

	{
		ATmega8,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "WDTON", },
			{ 15, "RSTDISBL", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega8515,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "WDTON", },
			{ 15, "S8515C", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega8535,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "WDTON", },
			{ 15, "S8535C", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega64,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "WDTON", },
			{ 17, "M103C", }

		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega128,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "WDTON", },
			{ 17, "M103C", }

		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega16,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega161,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "BODEN", },
			{ 4, "BODLEVEL", },
			{ 5, "SPIEN", },
			{ 6, "BOOTRST", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega163,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega162,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 17, "BOD0LEVEL", },
			{ 18, "BOD1LEVEL", },
			{ 19, "BOD2LEVEL", },
			{ 20, "M161C", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega169,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "CKOUT", },
			{ 7, "CKDIV8", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "WDTON", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", },
			{ 16, "RSTDISBL", },
			{ 17, "BOD0LEVEL", },
			{ 18, "BOD1LEVEL", },
			{ 19, "BOD2LEVEL", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega323,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		ATmega32,
		{
			// fuse
			{ 0, "CKSEL0", },
			{ 1, "CKSEL1", },
			{ 2, "CKSEL2", },
			{ 3, "CKSEL3", },
			{ 4, "SUT0", },
			{ 5, "SUT1", },
			{ 6, "BODEN", },
			{ 7, "BODLEVEL", },
			{ 8, "BOOTRST", },
			{ 9, "BOOTSZ0", },
			{ 10, "BOOTSZ1", },
			{ 11, "EESAVE", },
			{ 12, "CKOPT", },
			{ 13, "SPIEN", },
			{ 14, "JTAGEN", },
			{ 15, "OCDEN", }
		},
		{
			// lock
			{ 0, "Lock1", },
			{ 1, "Lock2", },
			{ 2, "BootLock01", },
			{ 3, "BootLock02", },
			{ 4, "BootLock11", },
			{ 5, "BootLock12", }
		}
	},

	{
		AT89S8252,
		{
			// fuse
		},
		{
			// lock
			{ 5, "LB3", },
			{ 6, "LB2", },
			{ 7, "LB1", }
		}
	},

	{
		AT89S8253,
		{
			// fuse
		},
		{
			// lock
			{ 0, "LB3", },
			{ 1, "LB2", },
			{ 2, "LB1", }
		}
	},

	{
		AT89S51,
		{
			// fuse
		},
		{
			// lock
			{ 2, "LB3", },
			{ 3, "LB2", },
			{ 4, "LB1", }
		}
	},

	{
		AT89S52,
		{
			// fuse
		},
		{
			// lock
			{ 2, "LB3", },
			{ 3, "LB2", },
			{ 4, "LB1", }
		}
	},

	{
		AT89S53,
		{
			// fuse
		},
		{
			// lock
			{ 5, "LB3", },
			{ 6, "LB2", },
			{ 7, "LB1", }
		}
	},

	{
		PIC12508,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "CP", },
			{ 4, "MCLRE", }
		}
	},

	{
		PIC12509,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "CP", },
			{ 4, "MCLRE", }
		}
	},

	{
		PIC12508A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "CP", },
			{ 4, "MCLRE", }
		}
	},

	{
		PIC12509A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "CP", },
			{ 4, "MCLRE", }
		}
	},

	{
		PIC12E518,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "CP", },
			{ 4, "MCLRE", }
		}
	},

	{
		PIC12E519,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "CP", },
			{ 4, "MCLRE", }
		}
	},

	{
		PIC12671,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "FOSC2", },
			{ 3, "WDTE", },
			{ 4, "PWRTE", },
			{ 5, "CP0", },
			{ 6, "CP1", },
			{ 7, "MCLRE", },
			{ 8, "CP0", },
			{ 9, "CP1", },
			{ 10, "CP0", },
			{ 11, "CP1", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC12672,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "FOSC2", },
			{ 3, "WDTE", },
			{ 4, "PWRTE", },
			{ 5, "CP0", },
			{ 6, "CP1", },
			{ 7, "MCLRE", },
			{ 8, "CP0", },
			{ 9, "CP1", },
			{ 10, "CP0", },
			{ 11, "CP1", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC12673,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "FOSC2", },
			{ 3, "WDTE", },
			{ 4, "PWRTE", },
			{ 5, "CP0", },
			{ 6, "CP1", },
			{ 7, "MCLRE", },
			{ 8, "CP0", },
			{ 9, "CP1", },
			{ 10, "CP0", },
			{ 11, "CP1", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC12674,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "FOSC2", },
			{ 3, "WDTE", },
			{ 4, "PWRTE", },
			{ 5, "CP0", },
			{ 6, "CP1", },
			{ 7, "MCLRE", },
			{ 8, "CP0", },
			{ 9, "CP1", },
			{ 10, "CP0", },
			{ 11, "CP1", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC1683,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP", }
		}
	},

	{
		PIC1684,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP", }
		}
	},

	{
		PIC1684A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP", }
		}
	},

	{
		PIC16870,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16871,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16872,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16873,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16874,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16876,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16877,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTE", },
			{ 3, "PWRTE", },
			{ 4, "CP0", },
			{ 5, "CP1", },
			{ 6, "BODEN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT", },
			{ 11, "RESV", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16873A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTEN", },
			{ 3, "/PWRTEN", },
			{ 6, "BOREN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT0", },
			{ 11, "WRT1", },
			{ 12, "DEBUG", },
			{ 14, "CP", }
		}
	},

	{
		PIC16874A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTEN", },
			{ 3, "/PWRTEN", },
			{ 6, "BOREN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT0", },
			{ 11, "WRT1", },
			{ 12, "DEBUG", },
			{ 14, "CP", }
		}
	},

	{
		PIC16876A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTEN", },
			{ 3, "/PWRTEN", },
			{ 6, "BOREN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT0", },
			{ 11, "WRT1", },
			{ 12, "DEBUG", },
			{ 14, "CP", }
		}
	},

	{
		PIC16877A,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTEN", },
			{ 3, "/PWRTEN", },
			{ 6, "BOREN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 9, "WRT0", },
			{ 11, "WRT1", },
			{ 12, "DEBUG", },
			{ 14, "CP", }
		}
	},

	{
		PIC16627,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTEN", },
			{ 3, "/PWRTEN", },
			{ 4, "FOSC2", },
			{ 5, "MCLRE", },
			{ 6, "BOREN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 10, "CP0", },
			{ 11, "CP1", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	},

	{
		PIC16628,
		{
			// fuse
		},
		{
			// lock
			{ 0, "FOSC0", },
			{ 1, "FOSC1", },
			{ 2, "WDTEN", },
			{ 3, "/PWRTEN", },
			{ 4, "FOSC2", },
			{ 5, "MCLRE", },
			{ 6, "BOREN", },
			{ 7, "LVP", },
			{ 8, "CPD", },
			{ 10, "CP0", },
			{ 11, "CP1", },
			{ 12, "CP0", },
			{ 13, "CP1", }
		}
	}
};

