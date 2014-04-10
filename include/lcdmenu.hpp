/*
 * lcdmenu.h
 *
 *  Created on: Apr 4, 2014
 *      Author: cyborg-x1
 */

#ifndef LCDMENU_HPP_
#define LCDMENU_HPP_

#include <lcdisplay.hpp>

namespace VertigusElectio {

class LCDBaseMenuEntry
{

	const char *entryname;
	bool isDisabled;
	LCDBaseMenuEntry *next;
	LCDBaseMenuEntry *prev;

public:
	LCDBaseMenuEntry(const char * entryname)
	:entryname(entryname)
	{
		this->next=0;
		this->prev=0;
		this->isDisabled=false;
	}
	virtual ~LCDBaseMenuEntry(){};


	void setDisabled(bool disabled);

	virtual void on_up()=0;
	virtual void on_down()=0;
	virtual void on_button()=0;
};


class LCDMenu {

public:

	typedef enum
	{
		ALPHABETIC_UP,
		ALPHABETIC_DOWN,
		INSERTION,
	}SortRule;

	typedef enum
	{
		HIDE,
		DISABLE_CHAR,
		DISPLAY_ALT,
	}DisableRule;


private:
	BaseLCDisplay *lcd;
	LCDBaseMenuEntry *current;
	SortRule sortRule;
	DisableRule disableRule;
	char disableChar;


public:

	LCDMenu(BaseLCDisplay *lcd, SortRule sortrule, DisableRule disablerule, char disabledChar='#');
	virtual ~LCDMenu();

	void addEntry(LCDBaseMenuEntry* entry);

	void up();
	void down();
	void button();
};

} /* namespace VertigusElectio */

#endif /* LCDMENU_H_ */
