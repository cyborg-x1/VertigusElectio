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

	BaseLCDisplay::BaseLCDisplay(unsigned rows,unsigned cols, char *contentArray, char *writtenContent, bool cursor_support, bool blink_support, char space_chr, char overflow_chr)
	:	rows(rows),
		cols(cols),
		cursor_pos_row(0),
		cursor_pos_col(0),
		cursor_blink_supported(blink_support),
		cursor_display_supported(cursor_support),
		cursor_blink(false),
		cursor_display(false),
		contentArray(contentArray),
		writtenContent(writtenContent),
		space_chr(space_chr),
		overflow_chr(overflow_chr)
	{}

	void BaseLCDisplay::clearDisp()
	{
		clearArrays();
	}


	void BaseLCDisplay::clearArrays()
	{
		for (unsigned row = 0; row < this->rows; ++row) {
			for (unsigned col = 0; col < this->cols; ++col) {
				*(this->contentArray+(row * this->cols)+col)=this->space_chr;
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

	void BaseLCDisplay::put(char chr, unsigned row, unsigned col)
	{
		if(col<this->cols && row<this->cols)
		{
			*(this->contentArray+(row * this->cols)+col)=chr;
		}
	}

	void BaseLCDisplay::put(const char *str, unsigned row, unsigned col, unsigned fieldSize, TextAlignment align,  int len)
	{
		bool oversize=false;


		if(len<0)
			for(len=0;str[len]!='\0';++len);

		if(len>(int)fieldSize && fieldSize != 0)
		{
			len=fieldSize;
			oversize=true;
		}


		if(row<this->rows&&col<this->cols)
		{
			switch(align)
			{
			case LEFT:
			{		unsigned c=0;

					for(; c < (unsigned)len  && (col+c) < this->cols; ++c)
					{
						*(this->contentArray+(row * this->cols)+col+c)=str[c];
					}

					if(fieldSize>0)
					{
						for(;c<fieldSize && (col+c) < this->cols;++c)
						{
							*(this->contentArray+(row * this->cols)+col+c)=this->space_chr;
						}
					}

					if(oversize && this->overflow_chr != '\0')
					{
						*(this->contentArray+(row * this->cols)+col+len-1)=this->overflow_chr;
					}
			}
				break;
			case RIGHT:
			{
				int posright=(this->cols-1-col);
				int posleft=(fieldSize!=0)?posright-fieldSize:posright-len;
				if(posleft<0) posleft=0;
				int c=len-1;
				int p=posright;
				for(; p>=0 && p>posleft && c>=0 ; --c, --p)
				{
					if(p<(int)this->cols)
						*(this->contentArray+(row * this->cols)+p)=str[c];
				}

				for(;p>=0 && p>posleft ;--p)
					*(this->contentArray+(row * this->cols)+p)=this->space_chr;

				if(oversize && this->overflow_chr != '\0')
				{
					*(this->contentArray+(row * this->cols)+posright)=this->overflow_chr;
				}

			}
				break;
			case CENTER:
				unsigned posright=(fieldSize!=0)?col+fieldSize:this->cols-1;

				unsigned c=col;
				//Clear the whole thing ...
				for (; c < posright; ++c) {
					*(this->contentArray+(row * this->cols)+c)=this->space_chr;
				}

				if(len<(int)fieldSize)
				{
					c=col+((fieldSize-len)/2);
				}
				else
				{
					c=col;
				}

				for (int chr=0; c < this->cols && chr<len; ++c, ++chr)
				{
					*(this->contentArray+(row * this->cols)+c)=str[chr];
				}

				if(oversize)
				{
					unsigned end=col+fieldSize-1;

					if(end>this->cols-1)
						end=this->cols-1;

					*(this->contentArray+(row * this->cols)+end)=this->overflow_chr;
				}

				break;
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

	void BaseLCDisplay::OperatorCol::centered(const char *str, int len, int rowSize, unsigned left)
	{
		//fill left digits with spaces
		for (unsigned l = 0;  l < left && l <this->lcd->cols; ++ l)
		{
			(*this->lcd)[this->row][l]=this->lcd->space_chr;
		}

		//Get stringsize if len given (>0)
		if(len<0)
			for (len = 0; str[len]!=0; ++len);

		//If no rowsize is given get it
		if(rowSize<=0)
			rowSize=this->lcd->cols;

		//Calculate left shift
		int leftpos=((rowSize-len)/2)+left;


		(*this->lcd)[this->row][leftpos].insertString(str, len);

		//fill remaining spaces right with spaces
		for (unsigned r = len+left; r < this->lcd->cols; ++r) {
			(*this->lcd)[this->row][r]=this->lcd->space_chr;
		}

	}
	void BaseLCDisplay::OperatorCol::centered(const char chr, int rowSize, unsigned left)
	{
		centered(&chr,1,rowSize,left);
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
