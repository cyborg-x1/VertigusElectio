/*
 * vertiguselectio.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: cyborg-x1
 */

#include "lcdisplay.hpp"

namespace VertigusElectio
{


	/*
	 * BaseLCDisplay
	 */

	BaseLCDisplay::BaseLCDisplay(unsigned rows,unsigned cols, char *contentArray, char *writtenContent, char space_chr)
	:	rows(rows),
		cols(cols),
		contentArray(contentArray),
		writtenContent(writtenContent),
		space_chr(space_chr)
	{}

	void BaseLCDisplay::clearDisp()
	{
		for (unsigned row = 0; row < this->rows; ++row) {
			for (unsigned col = 0; col < this->cols; ++col) {
				*(this->contentArray+(row * this->cols)+col)=this->space_chr;
			}
		}
	}

    void BaseLCDisplay::updateLCDContent()
	{
		for (unsigned row = 0; row < this->rows; ++row)
		{
			for (unsigned col = 0; col < this->cols; ++col)
			{
				if(*(this->contentArray+(row * this->cols)+col) !=
				   *(this->writtenContent+(row * this->cols)+col))
				{
					writeCharToLCD(row,col, *(this->contentArray+(row * this->cols)+col) );
					*(this->writtenContent+(row * this->cols)+col)=*(this->contentArray+(row * this->cols)+col);
				}
			}
		}
	}


	BaseLCDisplay::OperatorCol BaseLCDisplay::operator[](unsigned row)
	{
		return OperatorCol(this, row);
	}


	/*
	 * BaseLCDisplay::OperatorCol
	 */
	BaseLCDisplay::OperatorCol::OperatorCol(BaseLCDisplay *lcd, unsigned row)
	:lcd(lcd),
	 row(row)
	{}

	BaseLCDisplay::OperatorCol::OperatorColBrac BaseLCDisplay::OperatorCol::operator[](unsigned col)
	{
		return BaseLCDisplay::OperatorCol::OperatorColBrac(this->lcd, this->row, col);
	}

	void BaseLCDisplay::OperatorCol::operator=(const char *str)
	{
		bool str_end=false;
		if(this->row < this->lcd->rows)
		for (unsigned c = 0; c < lcd->cols; ++c)
		{
			if(str[c]==0)
			{
				str_end=true;
			}
			if(str_end)
			{
				*(lcd->contentArray+(this->row * lcd->cols)+c)=this->lcd->space_chr;
			}
			else
			{
				*(lcd->contentArray+(this->row * lcd->cols)+c)=str[c];
			}
		}
	}

	void BaseLCDisplay::OperatorCol::insertString(const char *str, int len)
	{
		if(this->row<this->lcd->rows)
		{
			if(len<0)
			{
				this->operator =(str);
			}
			else
			{
				for (unsigned c = 0; c < (unsigned)len  && c < this->lcd->cols; ++c)
				{
					*(lcd->contentArray+(this->row * lcd->cols)+c)=str[c];
				}
			}
		}
	}

	/*
	 * BaseLCDisplay::OperatorCol::OperatorColBrac
	 */
	BaseLCDisplay::OperatorCol::OperatorColBrac::OperatorColBrac(BaseLCDisplay *lcd, unsigned row, unsigned col)
	:lcd(lcd),
	 row(row),
	 col(col)
	{}

	void BaseLCDisplay::OperatorCol::OperatorColBrac::operator=(char chr)
	{
		if(this->row < this->lcd->rows && this->col < this->lcd->cols)
			*(lcd->contentArray+(this->row * lcd->cols)+this->col)=chr;
	}

	void BaseLCDisplay::OperatorCol::OperatorColBrac::operator=(const char *str)
	{
		if(this->row < this->lcd->rows)
		for (unsigned c = this->col; c < lcd->cols; ++c)
		{
			if(str[c-this->col]==0)
			{
				break;
			}
			else
			{
				*(lcd->contentArray+(row * lcd->cols)+c)=str[c-this->col];
			}
		}
	}

	void BaseLCDisplay::OperatorCol::centered(const char *str, int len, int rowSize, int left)
	{
		//Get stringsize if len given (>0)
		if(len<0)
			for (len = 0; str[len]!=0; ++len);

		//If no rowsize is given get it
		if(rowSize<0)
			rowSize=this->lcd->cols;

		//Calculate left shift
		int leftpos=((rowSize-len)/2)+left;


		(*this->lcd)[this->row][leftpos].insertString(str, len);

	}
	void BaseLCDisplay::OperatorCol::centered(const char chr, int rowSize, int left)
	{

	}


	void BaseLCDisplay::OperatorCol::OperatorColBrac::insertString(const char *str, int len)
	{
		if(( this->row<this->lcd->rows ) && ( this->col < this->lcd->cols ))
		{
			if(len<0)
			{
				this->operator =(str);
			}
			else
			{
				for (unsigned c = 0; c < (unsigned)len  && (c+this->col) < this->lcd->cols; ++c)
				{
					*(lcd->contentArray+(this->row * lcd->cols)+ (c+this->col))=str[c];
				}
			}
		}
	}




}
