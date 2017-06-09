/*****************************************************************************
 *
 *  XVID MPEG-4 VIDEO CODEC
 *  - Font rendering to frame buffer functions -
 *
 *  Copyright(C) 2002-2003 Peter Ross <pross@xvid.org>
 *
 *  This program is free software ; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation ; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY ; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program ; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * $Id: font.c,v 1.7 2005/11/22 10:23:01 suxen_drol Exp $
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdarg.h>

#include "image.h"
#include "font.h"

#define FONT_WIDTH	4
#define FONT_HEIGHT	6


static const char ascii33[33][FONT_WIDTH*FONT_HEIGHT] = {

	/* ! */
	{0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,1,0},

	/* " */
	{0,1,0,1,
	 0,1,0,1,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0},

	/* # */
	{0,1,1,0,
	 1,1,1,1,
	 0,1,1,0,
	 0,1,1,0,
	 1,1,1,1,
	 0,1,1,0},

	/* $ */
	{0,1,1,0,
	 1,0,1,1,
	 1,1,1,0,
	 0,1,1,1,
	 1,1,0,1,
	 0,1,1,0},

	/* % */
	{1,1,0,1,
	 1,0,0,1,
	 0,0,1,0,
	 0,1,0,0,
	 1,0,0,1,
	 1,0,1,1},

	/* & */
	{0,1,1,0,
	 1,0,0,0,
	 0,1,0,1,
	 1,0,1,0,
	 1,0,1,0,
	 0,1,0,1},

	/* ' */
	{0,0,1,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0},

	/* ( */
	{0,0,1,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,0,1,0},

	/* ) */
	{0,1,0,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,1,0,0},

	/* * */
	{0,0,0,0,
	 1,0,0,1,
	 0,1,1,0,
	 1,1,1,1,
	 0,1,1,0,
	 1,0,0,1},

	/* + */
	{0,0,0,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,1,1,1,
	 0,0,1,0,
	 0,0,1,0},

	/* , */
	{0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,1,1,0,
	 0,0,1,0},

	/* - */
	{0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 1,1,1,1,
	 0,0,0,0,
	 0,0,0,0},

	/* . */
	{0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,1,1,0,
	 0,1,1,0},

	/* / */
	{0,0,0,1,
	 0,0,0,1,
	 0,0,1,0,
	 0,1,0,0,
	 1,0,0,0,
	 1,0,0,0},

	/* 0 */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,1,1,
	 1,1,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* 1 */
	{0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0},

	/* 2 */
	{0,1,1,0,
	 1,0,0,1,
	 0,0,1,0,
	 0,1,0,0,
	 1,0,0,0,
	 1,1,1,1},

	/* 3 */
	{0,1,1,0,
	 1,0,0,1,
	 0,0,1,0,
	 0,0,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* 4 */
	{0,0,1,0,
	 0,1,1,0,
	 1,0,1,0,
	 1,1,1,1,
	 0,0,1,0,
	 0,0,1,0},

	/* 5 */
	{1,1,1,1,
	 1,0,0,0,
	 1,1,1,0,
	 0,0,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* 6 */
	{0,1,1,1,
	 1,0,0,0,
	 1,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* 7 */
	{1,1,1,0,
	 0,0,0,1,
	 0,0,0,1,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0},

	/* 8 */
	{0,1,1,0,
	 1,0,0,1,
	 0,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* 9 */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 0,1,1,1,
	 0,0,0,1,
	 1,1,1,0},

	/* : */
	{0,0,0,0,
	 0,0,0,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,1,0,
	 0,0,0,0},

	/* ; */
	{0,0,0,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,1,1,0,
	 0,0,1,0},

	/* < */
	{0,0,0,1,
	 0,0,1,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,0,1,0,
	 0,0,0,1},

	/* = */
	{0,0,0,0,
	 1,1,1,1,
	 0,0,0,0,
	 0,0,0,0,
	 1,1,1,1,
	 0,0,0,0},

	/* > */
	{0,1,0,0,
	 0,0,1,0,
	 0,0,0,1,
	 0,0,0,1,
	 0,0,1,0,
	 0,1,0,0},

	/* ? */
	{0,1,1,0,
	 1,0,0,1,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,1,0},

	/* @ */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,1,1,
	 1,0,1,1,
	 1,0,0,0,
	 0,1,1,0},

};


static const char ascii65[26][FONT_WIDTH*FONT_HEIGHT] = {
	/* A */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,1,1,1,
	 1,0,0,1,
	 1,0,0,1},

	/* B */
	{1,1,1,0,
	 1,0,0,1,
	 1,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,1,1,0},

	/* C */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,1,
	 0,1,1,0},

	/* D */
	{1,1,0,0,
	 1,0,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,1,0,
	 1,1,0,0},

	/* E */
	{1,1,1,1,
	 1,0,0,0,
	 1,1,1,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,1,1,1},

	/* F */
	{1,1,1,1,
	 1,0,0,0,
	 1,1,1,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0},

	/* G */
	{0,1,1,1,
	 1,0,0,0,
	 1,0,1,1,
	 1,0,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* H */
	{1,0,0,1,
	 1,0,0,1,
	 1,1,1,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1},

	/* I */
	{0,1,1,1,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,1,1,1},

	/* J */
	{0,1,1,1,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 1,0,1,0,
	 0,1,0,0},

	/* K */
	{1,0,0,1,
	 1,0,0,1,
	 1,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1},

	/* L */
	{1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,1,1,1},

	/* M */
	{1,0,0,1,
	 1,1,1,1,
	 1,1,1,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1},

	/* N */
	{1,0,0,1,
	 1,1,0,1,
	 1,1,0,1,
	 1,0,1,1,
	 1,0,1,1,
	 1,0,0,1},

	/* 0 */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 0,1,1,0},

	/* P */
	{1,1,1,0,
	 1,0,0,1,
	 1,1,1,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0},

	/* Q */
	{0,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,1,0,
	 0,1,0,1},


	/* R */
	{1,1,1,0,
	 1,0,0,1,
	 1,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1},

	/* S */
	{0,1,1,0,
	 1,0,0,1,
	 0,1,0,0,
	 0,0,1,0,
	 1,0,0,1,
	 0,1,1,0},

	/* T */
	{0,1,1,1,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0},

	/* U */
	{1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,1,1,1},

	/* V */
	{1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 0,1,1,0,
	 0,1,1,0,
	 0,1,1,0},

	/* W */
	{1,0,0,1,
	 1,0,0,1,
	 1,0,0,1,
	 1,1,1,1,
	 1,1,1,1,
	 1,0,0,1},

	/* X */
	{1,0,0,1,
	 1,0,0,1,
	 0,1,1,0,
	 1,0,0,1,
	 1,0,0,1,
	 1,0,0,1},

	/* Y */
	{1,0,0,1,
	 1,0,0,1,
	 0,1,0,0,
	 0,0,1,0,
	 0,1,0,0,
	 1,0,0,0},

	/* Z */
	{1,1,1,1,
	 0,0,0,1,
	 0,0,1,0,
	 0,1,0,0,
	 1,0,0,0,
	 1,1,1,1},

};



static const char ascii91[6][FONT_WIDTH*FONT_HEIGHT] = {
	/* [ */
	{0,1,1,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,1,0,0,
	 0,1,1,0},

	/* '\' */
	{1,0,0,0,
	 1,0,0,0,
	 0,1,0,0,
	 0,0,1,0,
	 0,0,0,1,
	 0,0,0,1},

	/* ] */
	{0,1,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,0,1,0,
	 0,1,1,0},

	/* ^ */
	{0,1,0,1,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0},

	/* _ */
	{0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 1,1,1,1},

	/* ` */
	{0,1,0,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0}
};


#define FONT_ZOOM	4

static void
draw_num(IMAGE * img, const int stride, const int height,
			  const char * font, const int x, const int y)
{
	int i, j;

	for (j = 0; j < FONT_ZOOM * FONT_HEIGHT && y+j < height; j++)
		for (i = 0; i < FONT_ZOOM * FONT_WIDTH && x+i < stride; i++)
			if (font[(j/FONT_ZOOM)*FONT_WIDTH + (i/FONT_ZOOM)])
			{
				int offset = (y+j)*stride + (x+i);
				int offset2 =((y+j)/2)*(stride/2) + ((x+i)/2);
				img->y[offset] = 255;
				img->u[offset2] = 127;
				img->v[offset2] = 127;
			}
}


#define FONT_BUF_SZ  1024

void image_printf(IMAGE * img, int edged_width, int height,
				  int x, int y, char *fmt, ...)
{
	va_list args;
	char buf[FONT_BUF_SZ];
	int i;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	for (i = 0; i < buf[i]; i++) {
		const char * font;

		if (buf[i] >= '!' && buf[i] <= '@')
			font = ascii33[buf[i]-'!'];
		else if (buf[i] >= 'A' && buf[i] <= 'Z')
			font = ascii65[buf[i]-'A'];
		else if (buf[i] >= '[' && buf[i] <= '`')
			font = ascii91[buf[i]-'['];
		else if (buf[i] >= 'a' && buf[i] <= 'z')
			font = ascii65[buf[i]-'a'];
		else
			continue;

		draw_num(img, edged_width, height, font, x + i*FONT_ZOOM*(FONT_WIDTH+1), y);
	}
}
