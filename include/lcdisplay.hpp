/*
 * lcdisplay.hpp
 *
 *  Created on: Apr 3, 2014
 *      Author: cyborg-x1
 */

#ifndef LCDISPLAY_HPP_
#define LCDISPLAY_HPP_

namespace VertigusElectio
{

/**
 * The base display class for every display, to provide a common interface for multiple different character displays
 */
class BaseLCDisplay
{

public:
	class OperatorCol
	{
		class OperatorColBrac
		{
			BaseLCDisplay *lcd;
			const unsigned row;
			const unsigned col;

		public:
			OperatorColBrac(BaseLCDisplay *lcd, unsigned row, unsigned col);
			void operator=(char chr);
			void operator=(const char *str);
			void insertString(const char *str, int len);
		};

		friend OperatorColBrac;
		friend BaseLCDisplay;
		BaseLCDisplay *lcd;
		unsigned row;
	public:
		OperatorCol(BaseLCDisplay *lcd, unsigned row);

		OperatorColBrac operator[](unsigned col);

		void operator=(const char *str);
		void insertString(const char *str, int len=-1);
		void centered(const char *str, int len=-1, int rowSize=-1, unsigned left=0);
		void centered(const char chr, int rowSize=-1, unsigned left=0);

	};
	friend OperatorCol;

protected:

	/**
	 * These variables contain the amount of columns and rows of the display
	 * @{
	 */
	unsigned rows;
	unsigned cols;
	/**
	 * @}
	 */


	/**
	 * These variables contain the current cursor position, when a cursor is supported and active.
	 * This position will be restored after each full display update.
	 * @{
	 */
	unsigned cursor_pos_row;
	unsigned cursor_pos_col;
	/**
	 * @}
	 */


	/**
	 *
	 * These variables tell if the display supports cursors and blinking mode or not.
	 * @{
	 */
	const bool cursor_blink_supported;
	const bool cursor_display_supported;
	/**
	 * @}
	 */

	/**
	 * These variables contain the state of the cursor and blink setting
	 * @{
	 */
	bool cursor_blink;
	bool cursor_display;
	/**
	 * @}
	 */

	/**
	 * This array contains the content on about how the display should look like at the moment
	 */
	char *contentArray;

	/**
	 * This array contains the current state of the display (written bytes)
	 */
	char *writtenContent;

	/**
	 * This variable specifies the standard hex value of the space character
	 */
	char space_chr;

	void clearArrays();

protected:


public:
	BaseLCDisplay(unsigned rows,unsigned cols, char *contentArray, char *writtenContent, bool cursor_support=false, bool blink_support=false, char space_chr=' ');
	virtual ~BaseLCDisplay();

	OperatorCol operator[](unsigned row);


	/**
	 * This function is a virtual dummy, if the display supports the cursor display it must be implemented in the derived class.
	 * It should set the cursors current position
	 * @param row The row where the cursor should be located
	 * @param col The column where the cursor should be located
	 */
	virtual void setCursorPosition(unsigned row, unsigned col){};

	/**
	 * This function is a virtual dummy, if the display supports the cursor display it must be implemented in the derived class .
	 * It should set the display of the cursor on or off
	 */
	virtual void setCursorDisplay(bool display){};

	/**
	 * This function is a virtual dummy, if the display supports the blinking mode it must be implemented in the derived class .
	 */
	virtual void setCursorBlink(bool blink){};

	/**
	 * If the display features a busy feature, this must be implemented in a derived class
	 * @return Should return 0 if the display is able to receive commands
	 */
	virtual bool busy(){return 0;};

	/**
	 * This virtual function should write the current state to the LCD, it must be coded by the implementation of the real display class
	 */
	virtual void updateLCDContent()=0;

	/**
	 * This function can be reimplemented to save time, for example by waiting for busy flags,
	 * if the display supports a single clear command.
	 * A reimplemented function <b>MUST</b> call clearArrays()
	 */
	virtual void clearDisp();
};


/**
 * Template class for implementing a derived clase to BaseLCDisplay
 */
template <unsigned ROWS, unsigned COLS>
class LCDisplay : public BaseLCDisplay
{
protected:
	char content[ROWS*COLS];
	char written_content[ROWS*COLS];

public:
	LCDisplay(char space_chr=' ')
	:BaseLCDisplay(ROWS,COLS, content, written_content, space_chr)
	{
		this->clearDisp();
	}
};



}/*NAMESPACE VERTIGUSELECTIO*/
#endif /* LCDISPLAY_HPP_ */
