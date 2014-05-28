/*
 * lcdmenu.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: cyborg-x1
 */

#include <lcdmenu.hpp>

namespace VertigusElectio
{

LCDMenu::LCDMenu(BaseLCDisplay *lcd, SortRule sortrule, DisableRule disablerule, char disabledChar)
:lcd(lcd),
 current(0),
 sortRule(sortrule),
 disableRule(disablerule),
 disableChar(disabledChar)
{
	// TODO Auto-generated constructor stub

}

LCDMenu::~LCDMenu() {
	// TODO Auto-generated destructor stub
}


void LCDMenu::addEntry(LCDBaseMenuEntry* entry)
{
	if(current==0)
	{
		current=entry;
	}
	else
	{
		switch(this->sortRule)
		{
		case ALPHABETIC_UP:


			break;
		case ALPHABETIC_DOWN:

			break;
		default:
		case INSERTION:

			break;
		}
	}
}

void LCDMenu::up()
{

}

void LCDMenu::down()
{

}

void LCDMenu::button()
{

}

} /* namespace VertigusElectio */
