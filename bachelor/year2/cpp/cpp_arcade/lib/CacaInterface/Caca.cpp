/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Internal functions
*/

#include <iostream>
#include <stdio.h> // BUFSIZ
#include <stdarg.h> // va_*
#include "Caca.hpp"

uint32_t caca::Charset::utf8ToUtf32(char const *s, size_t *read)
{
	return caca_utf8_to_utf32(s, read);
}

size_t caca::Charset::utf32ToUtf8(char *buf, uint32_t ch)
{
	return caca_utf32_to_utf8(buf, ch);
}

uint8_t caca::Charset::utf32ToCp437(uint32_t ch)
{
	return caca_utf32_to_cp437(ch);
}

uint32_t caca::Charset::cp437ToUtf32(uint8_t ch)
{
	return caca_cp437_to_utf32(ch);
}

caca::Canvas::Canvas()
{
	cv = caca_create_canvas(0, 0);
	if (!cv)
		throw -1;
}

caca::Canvas::Canvas(int width, int height)
{
	cv = caca_create_canvas(width, height);
	if (!cv)
		throw -1;
}

caca::Canvas::~Canvas()
{
	if (cv)
		caca_free_canvas(cv);
}

caca_canvas_t *caca::Canvas::get_caca_canvas_t()
{
	return cv;
}

void caca::Canvas::setSize(unsigned int width, unsigned int height)
{
	caca_set_canvas_size(cv, width, height);
}

unsigned int caca::Canvas::getWidth(void)
{
	return caca_get_canvas_width(cv);
}

unsigned int caca::Canvas::getHeight(void)
{
	return caca_get_canvas_height(cv);
}

int caca::Canvas::setColorANSI(uint8_t f, uint8_t b)
{
	return caca_set_color_ansi(cv, f, b);
}

int caca::Canvas::setColorARGB(unsigned int f, unsigned int b)
{
	return caca_set_color_argb(cv, f, b);
}

void caca::Canvas::putChar(int x, int y, uint32_t ch)
{
	caca_put_char(cv, x, y, ch);
}

uint32_t caca::Canvas::getChar(int x, int y)
{
	return caca_get_char(cv, x, y);
}

void caca::Canvas::putStr(int x, int y, char *str)
{
	caca_put_str(cv, x, y, str);
}

void caca::Canvas::Printf(int x, int y, char const *format, ...)
{
	char tmp[BUFSIZ];
	char *buf = tmp;
	va_list args;

	va_start(args, format);
	#if defined(HAVE_VSNPRINTF)
	vsnprintf(buf, getWidth() - x + 1, format, args);
	#else
	vsprintf(buf, format, args);
	#endif
	buf[getWidth() - x] = '\0';
	va_end(args);

	putStr(x, y, buf);
}

void caca::Canvas::Clear(void)
{
	caca_clear_canvas(cv);
}

void caca::Canvas::Blit(int x, int y, caca::Canvas *c1, caca::Canvas *c2)
{
	caca_blit(cv, x, y, c1->get_caca_canvas_t(), c2 ? c2->get_caca_canvas_t() : NULL);
}

void caca::Canvas::Invert()
{
	caca_invert(cv);
}

void caca::Canvas::Flip()
{
	caca_flip(cv);
}

void caca::Canvas::Flop()
{
	caca_flop(cv);
}

void caca::Canvas::Rotate180()
{
	caca_rotate_180(cv);
}

void caca::Canvas::RotateLeft()
{
	caca_rotate_left(cv);
}

void caca::Canvas::RotateRight()
{
	caca_rotate_right(cv);
}

void caca::Canvas::drawLine(int x1, int y1, int x2, int y2, uint32_t ch)
{
	caca_draw_line(cv, x1, y1, x2, y2, ch);
}

void caca::Canvas::drawPolyline(int const x[], int const y[], int f, uint32_t ch)
{
	caca_draw_polyline(cv, x, y, f, ch);
}

void caca::Canvas::drawThinLine(int x1, int y1, int x2, int y2)
{
	caca_draw_thin_line(cv, x1, y1, x2, y2);
}

void caca::Canvas::drawThinPolyline(int const x[], int const y[], int f)
{
	caca_draw_thin_polyline(cv, x, y, f);
}

void caca::Canvas::drawCircle(int x, int y, int d, uint32_t ch)
{
	caca_draw_circle(cv, x, y, d, ch);
}

void caca::Canvas::drawEllipse(int x, int y, int d1, int d2, uint32_t ch)
{
	caca_draw_ellipse(cv, x, y, d1, d2, ch);
}

void caca::Canvas::drawThinEllipse(int x, int y, int d1, int d2)
{
	caca_draw_thin_ellipse(cv, x, y, d1, d2);
}

void caca::Canvas::fillEllipse(int x, int y, int d1, int d2, uint32_t ch)
{
	caca_fill_ellipse(cv, x, y, d1, d2, ch);
}

void caca::Canvas::drawBox(int x, int y, int w, int h, uint32_t ch)
{
	caca_draw_box(cv, x, y, w, h, ch);
}

void caca::Canvas::drawThinBox(int x, int y, int w, int h)
{
	caca_draw_thin_box(cv, x, y, w, h);
}

void caca::Canvas::drawCP437Box(int x, int y, int w, int h)
{
	caca_draw_cp437_box(cv, x, y, w, h);
}

void caca::Canvas::fillBox(int x, int y, int w, int h, uint32_t ch)
{
	caca_fill_box(cv, x, y, w, h, ch);
}

void caca::Canvas::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t ch
)
{
	caca_draw_triangle(cv, x1, y1, x2, y2, x3, y3, ch);
}

void caca::Canvas::drawThinTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	caca_draw_thin_triangle(cv, x1, y1, x2, y2, x3, y3);
}

void caca::Canvas::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t ch
)
{
	caca_fill_triangle(cv, x1, y1, x2, y2, x3, y3, ch);
}

void caca::Canvas::fillTriangleTextured(int coords[6], caca::Canvas *tex, float uv[6])
{
	caca_fill_triangle_textured(cv, coords, tex->cv, uv);
}

int caca::Canvas::Rand(int min, int max)
{
	return caca_rand(min, max);
}

const char *caca::Canvas::getVersion()
{
	return caca_get_version();
}

int caca::Canvas::setAttr(uint32_t attr)
{
	return caca_set_attr(cv, attr);
}

uint32_t caca::Canvas::getAttr(int x, int y)
{
	return caca_get_attr(cv, x, y);
}

int caca::Canvas::setBoundaries(caca_canvas_t *, int x, int y, unsigned int w, unsigned int h
)
{
	return caca_set_canvas_boundaries(cv, x, y, h, w);
}

unsigned int caca::Canvas::getFrameCount()
{
	return caca_get_frame_count(cv);
}

int caca::Canvas::setFrame(unsigned int f)
{
	return caca_set_frame(cv, f);
}

int caca::Canvas::createFrame(unsigned int f)
{
	return caca_create_frame(cv, f);
}

int caca::Canvas::freeFrame(unsigned int f)
{
	return caca_create_frame(cv, f);
}

char const *const *caca::Canvas::getImportList(void)
{
	return caca_get_import_list();
}

long int caca::Canvas::importFromMemory(void const *buf, size_t len, char const *fmt)
{
	return caca_import_canvas_from_memory(cv, buf, len, fmt);
}

long int caca::Canvas::importFromFile(char const *file, char const *fmt)
{
	return caca_import_canvas_from_file(cv, file, fmt);
}

char const *const *caca::Canvas::getExportList(void)
{
	return caca_get_export_list();
}

void *caca::Canvas::exportToMemory(char const *fmt, size_t *len)
{
	return caca_export_canvas_to_memory(cv, fmt, len);
}

caca::Dither::Dither(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5,
	unsigned int v6, unsigned int v7, unsigned int v8
)
{
	dither = caca_create_dither(v1, v2, v3, v4, v5, v6, v7, v8);
}

caca::Dither::~Dither()
{
	caca_free_dither(dither);
}

void caca::Dither::setPalette(uint32_t r[], uint32_t g[], uint32_t b[], uint32_t a[])
{
	caca_set_dither_palette(dither, r, g, b, a);
}

void caca::Dither::setBrightness(float f)
{
	caca_set_dither_brightness(dither, f);
}

void caca::Dither::setGamma(float f)
{
	caca_set_dither_gamma(dither, f);
}

void caca::Dither::setContrast(float f)
{
	caca_set_dither_contrast(dither, f);
}

void caca::Dither::setAntialias(char const *cv)
{
	caca_set_dither_antialias(dither, cv);
}

char const *const *caca::Dither::getAntialiasList()
{
	return caca_get_dither_antialias_list(dither);
}

void caca::Dither::setColor(char const *cv)
{
	caca_set_dither_color(dither, cv);
}

char const *const *caca::Dither::getColorList()
{
	return caca_get_dither_color_list(dither);
}

void caca::Dither::setCharset(char const *cv)
{
	caca_set_dither_charset(dither, cv);
}

char const *const *caca::Dither::getCharsetList()
{
	return caca_get_dither_charset_list(dither);
}

void caca::Dither::setMode(char const *cv)
{
	caca_set_dither_algorithm(dither, cv);
}

char const *const *caca::Dither::getModeList(void)
{
	return caca_get_dither_algorithm_list(dither);
}

void caca::Dither::Bitmap(Canvas *cv, int x, int y, int w, int h, void *v)
{
	caca_dither_bitmap(cv->get_caca_canvas_t(), x, y, w, h, dither, v);
}

caca::Font::Font(void const *s, unsigned int v)
{
	font = caca_load_font(s, v);
	if (!font)
		throw -1;
}

char const *const *caca::Font::getList(void)
{
	return caca_get_font_list();
}

unsigned int caca::Font::getWidth()
{
	return caca_get_font_width(font);
}

unsigned int caca::Font::getHeight()
{
	return caca_get_font_height(font);
}

void caca::Font::renderCanvas(Canvas *cv, uint8_t *buf, unsigned int x, unsigned int y, unsigned int w
)
{
	caca_render_canvas(cv->get_caca_canvas_t(), font, buf, x, y, w);
}

uint32_t const *caca::Font::getBlocks()
{
	return caca_get_font_blocks(font);
}

caca::Font::~Font()
{
	caca_free_font(font);
}

caca::Caca::Caca(Canvas *cv)
{
	dp = caca_create_display(cv->get_caca_canvas_t());
	if (!dp)
		throw -1;
}

caca::Caca::~Caca()
{
	caca_free_display(dp);
}

void caca::Caca::Attach(Canvas *cv)
{
	dp = caca_create_display(cv->get_caca_canvas_t());
	if (!dp)
		throw -1;
}

void caca::Caca::Detach()
{
	caca_free_display(dp);
}

void caca::Caca::setDisplayTime(unsigned int d)
{
	caca_set_display_time(dp, d);
}

void caca::Caca::Display()
{
	caca_refresh_display(dp);
}

unsigned int caca::Caca::getDisplayTime()
{
	return caca_get_display_time(dp);
}

unsigned int caca::Caca::getWidth()
{
	return caca_get_display_width(dp);
}

unsigned int caca::Caca::getHeight()
{
	return caca_get_display_height(dp);
}

int caca::Caca::setTitle(char const *s)
{
	return caca_set_display_title(dp, s);
}

int caca::Caca::getEvent(unsigned int g, Event *n, int aa)
{
	return caca_get_event(dp, g, n ? &n->e : NULL, aa);
}

const caca_event_t &caca::Event::getE() const
{
	return e;
}

unsigned int caca::Caca::getMouseX()
{
	return caca_get_mouse_x(dp);
}

unsigned int caca::Caca::getMouseY()
{
	return caca_get_mouse_x(dp);
}

void caca::Caca::setMouse(int v)
{
	caca_set_mouse(dp, v);
}

const char *caca::Caca::getVersion()
{
	return caca_get_version();
}
