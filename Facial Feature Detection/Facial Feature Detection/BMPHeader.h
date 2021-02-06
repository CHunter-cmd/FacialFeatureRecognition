// BMPHeader.h handles the methods for bitmap images
// Author Unknown
//---------------------------------------------------------------------------
#ifndef BMPH
#define BMPH
//---------------------------------------------------------------------------
// colormap entry structure
typedef struct
{
	//declares blue entry
	unsigned char  blue;
	//declares green entry
	unsigned char  green;
	//declares red entry
	unsigned char  red;
	//declares reserved entry
	unsigned char  reserved;
} RgbQuad;
//---------------------------------------------------------------------------
// BMP header structure
typedef struct
{
	//declares the type of the image
	char		type[2];
	//declares the size of the image
	int       file_size;
	//declares reserved area
	int       reserved;
	//declares the offset from the beginning of file to image
	int       offset;
	//declares the size of the information header
	int       info_header_size;
	//declares the width of the image
	int       width;
	//declares the height of the image
	int       height;
	//declares the number of planes
	short int planes;
	//declares the number of bits per pixel
	short int bits_per_pixel;
	//declares the compression applied to the image
	int       compression;
	//declares the size of the image
	int       data_size;
	//declares the resolution of the x-axis
	int       h_resolution;
	//declares the resolution of the y-axis
	int       v_resolution;
	//declares the number of colours used in the image
	int       colors;
	//declares the number of important colours used in the image
	int	      important_colors;
	//declares the colour table as having 256bits
	RgbQuad   color_table[256];
} TBMPHeader;
//---------------------------------------------------------------------------
#endif
