/* Copyright © 2019 Raheman Vaiya.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "warpd.h"

static uint8_t active_indices[2048];
static struct hint hints[2048];
static size_t nhints = 0;

/* 
 * Returns the number of matched hints. match contains the 
 * matching hint in the event that the return value is 1.
 */
static int filter(const char *s, struct hint **match)
{
	size_t n = 0;
	size_t i;

	for (i = 0; i < nhints; i++) {
		if (strstr(hints[i].label, s) == hints[i].label) {
			n++;
			if (match)
				*match = &hints[i];
			active_indices[i] = 1;
		 } else {
			active_indices[i] = 0;
		 }
	}

	return n;
}

void init_hint_mode() {
	int i, j;
	int sz = cfg->hint_size;

	int sw, sh;
	screen_get_dimensions(&sw, &sh);

	const char chars[] = "abcdefghijklmnopqrstuvwxyz./;[],\\";

	const int xoffset = sz;
	const int yoffset = sz;

	const int nr = strlen(chars);
	const int nc = strlen(chars);

	const int colgap = (sw - (xoffset*2)) / (nc-1);
	const int rowgap = (sh - (yoffset*2)) / (nr-1);

	nhints = nc*nr;

	size_t n = 0;

	for(i = 0; i < nc; i++)
		for(j = 0; j < nr; j++) {
			struct hint *hint = &hints[n++];

			hint->x = i*colgap + xoffset;
			hint->y = j*rowgap + yoffset;

			hint->label[0] = chars[i];
			hint->label[1] = chars[j];
			hint->label[2] = 0;
		}

	init_hint(hints, nhints, sz, cfg->hint_border_radius, cfg->hint_bgcolor, cfg->hint_fgcolor, cfg->hint_font);
	filter("", NULL);
}

static char code_to_char(uint8_t code)
{
	const char *s = input_lookup_name(code);

	if (strlen(s) == 1)
		return s[0];
	if (!strcmp(s, "comma"))
			return ',';
	if (!strcmp(s, "dot"))
			return '.';
	if (!strcmp(s, "slash"))
			return '/';
	if (!strcmp(s, "semicolon"))
			return ';';

	return 0;
}

int hint_mode()
{
	int rc = 0;
	char buf[32] = {0};
	input_grab_keyboard();

	filter("", NULL);
	hint_show(active_indices);
	mouse_hide();

	while (1) {
		struct hint *match;
		size_t nmatches;

		struct input_event *ev;
		ssize_t len = strlen(buf);

		ev = input_next_event(0);
		len = strlen(buf);

		if (!ev->pressed)
			continue;

		if (input_event_eq(ev, cfg->exit)) {
			rc = -1;
			break;
		} else if (input_event_eq(ev, "C-u")) {
			buf[0] = 0;
		} else if (input_event_eq(ev, "backspace")) {
			if (len)
				buf[len-1] = 0;
		} else {
			char c = code_to_char(ev->code);
			if (c)
				buf[len++] = c;
		}

		nmatches = filter(buf, &match);

		if (nmatches == 1) {
			mouse_move(match->x, match->y);
			break;
		} else if (nmatches == 0) {
			break;
		}

		hint_show(active_indices);
	}

	input_ungrab_keyboard();
	hint_hide();
	mouse_show();

	return rc;
}
