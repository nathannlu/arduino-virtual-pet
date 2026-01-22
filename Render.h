// 'apple', 5x6px
const unsigned char epd_bitmap_apple [] PROGMEM = {
	0x10, 0x20, 0xf8, 0xf8, 0xf8, 0x70
};

// 'heart', 5x4px
const unsigned char epd_bitmap_heart [] PROGMEM = {
	0xd8, 0xf8, 0x70, 0x20
};
// 'smiley', 5x4px
const unsigned char epd_bitmap_smiley [] PROGMEM = {
	0x50, 0x00, 0x88, 0x70
};

// Array of all bitmaps for convenience. 
const int epd_bitmap_allArray_LEN = 3;
const unsigned char* epd_bitmap_allArray[3] = {
	epd_bitmap_apple,
	epd_bitmap_heart,
	epd_bitmap_smiley
};

