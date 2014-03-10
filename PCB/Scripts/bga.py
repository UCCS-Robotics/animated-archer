#!/usr/bin/env python
# -*- coding: utf-8 -*-

from math import floor

WIDTH = 10 # balls across
HEIGHT = 10 # balls down
PITCH = 0.65 # mm between center of adjacent balls
PAD = 0.25 # mm diameter for pads (smaller than the ball diameter of 0.3mm)
CREAM = 0.27 # mm diameter for paste/cream
STOP = 0.36 # mm diameter for solder expansion stop

# -- STOP HERE --

XSTART = -1 * floor(WIDTH / 2) * PITCH
YSTART = floor(HEIGHT / 2) * PITCH

if (WIDTH % 2) == 0:
	XSTART += PITCH / 2

if (HEIGHT % 2) == 0:
	YSTART -= PITCH / 2

print "grid mm 0.5 lines on alt mm 0.05 mm;"

for y in range(HEIGHT):
	for x in range(WIDTH):
		# For some reason we skip "I"
		name = chr(ord('A') + y)
		if y > 7:
			name = chr(ord('A') + y + 1)

		print "layer 1;" # Top
		print "smd %.3f %.3f -100 NOSTOP NOTHERMALS NOCREAM '%s%d' " \
			"(%.3f %.3f);" % (PAD, PAD, name, x + 1, XSTART + x * PITCH, \
			YSTART - y * PITCH)
		print "layer 29;" # tStop
		print "circle 0 (%.3f %.3f) (%.3f %.3f);" % (XSTART + x * PITCH, \
			YSTART - y * PITCH, XSTART + x * PITCH + STOP / 2, \
			YSTART - y * PITCH)
		print "layer 31;" # tCream
		print "circle 0 (%.3f %.3f) (%.3f %.3f);" % (XSTART + x * PITCH, \
			YSTART - y * PITCH, XSTART + x * PITCH + CREAM / 2, \
			YSTART - y * PITCH)
