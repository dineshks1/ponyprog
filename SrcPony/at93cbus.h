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

#ifndef _AT93CBUS_H
#define _AT93CBUS_H

#include "microbus.h"

class At93cBus : public MicroWireBus
{
  public:
	At93cBus(BusInterface *ptr = 0);
	//virtual ~At93cBus();

	long Read(int addr, quint8 *data, long length, int page_size = 0);
	long Write(int addr, quint8 const *data, long length, int page_size = 0);

	void SetOrganization(int org)
	{
		if (org == ORG8 || org == ORG16)
		{
			organization = org;
		}
	}
	int GetOrganization() const
	{
		return organization;
	}

	int Erase(int type = 0);

	//int CalcAddressSize(int mem_size) const override
	//{
	//	return MicroWireBus::CalcAddressSize(mem_size);
	//}

  protected:

	int SendCmdOpcode(int opcode)
	{
		return SendDataWord(opcode, 3);
	}

  private:

	//Command Opcode
	const quint8 ReadCode;
	const quint8 WriteCode;
	const quint8 WriteEnableCode;
	const quint8 EraseAllCode;
	const quint8 PrClearCode;

	const long loop_timeout;

	void setCS()
	{
		SetReset();			//27/05/98
	}

	void clearCS()
	{
		ClearReset();		//27/05/98
	}

	int address_len;
	int organization;
};

#endif
