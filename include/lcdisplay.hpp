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

class BaseLCDisplay
{
	class OperatorCol
	{
		class OperatorColBrac
		{
			BaseLCDisplay *lcd;
			unsigned row;
			unsigned col;

		public:
			OperatorColBrac(BaseLCDisplay *lcd, unsigned row, unsigned col);
			void operator=(char chr);
			void operator=(const char *str);
		};

		friend OperatorColBrac;
		friend BaseLCDisplay;
		BaseLCDisplay *lcd;
		unsigned row;
	public:
		OperatorCol(BaseLCDisplay *lcd, unsigned row);

		OperatorColBrac operator[](unsigned col);

		void operator=(const char *str);

	};
	friend OperatorCol;

protected:
	unsigned rows;
	unsigned cols;
	char *contentArray;
	char *writtenContent;
	char space_chr;

public:
	BaseLCDisplay(unsigned rows,unsigned cols, char *contentArray, char *writtenContent, char space_chr=' ');
	virtual ~BaseLCDisplay(){};

	OperatorCol operator[](unsigned row);

	virtual void writeCharToLCD(unsigned row, unsigned col, char chr)=0;

	virtual void update();

	void clearDisp();


};

template <unsigned ROWS, unsigned COLS>
class LCDisplay : public BaseLCDisplay
{
private:
	char content[ROWS*COLS];
	char written_content[ROWS*COLS];

public:
	LCDisplay(char space_chr=' ')
	:BaseLCDisplay(ROWS,COLS, content, written_content, space_chr)
	{
		this->clearDisp();
	}

	virtual void writeCharToLCD(unsigned row, unsigned col, char chr)=0;
};



}/*NAMESPACE VERTIGUSELECTIO*/
#endif /* LCDISPLAY_HPP_ */
