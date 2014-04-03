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

class LCDMenu {
	BaseLCDisplay *lcd;
public:
	LCDMenu(BaseLCDisplay *lcd);
	virtual ~LCDMenu();
};

} /* namespace VertigusElectio */

#endif /* LCDMENU_H_ */
