#!/usr/bin/python

import sys

def play(note, length):
	sys.stdout.write("%d[%d]" % (note, length))

def playnote(note):
	play(note, 200)
	play(0, 10) # 10 ms pause

def theme(thm, start):
	for t in thm:
		playnote(start + t)
		playnote(start - 5)

theme1 = [0, 2, 3, 2, 0, 5, 3, 2]
theme2 = [0, 2, 3, 5, 7, 5, 3, 2]
theme3 = [-1, 0, 2, 3, 5, 7, 3, 2]

for start in [70, 72]:
	for t in [[26, theme1], [28, theme2], [30, theme1], [31, theme3]]:
		play(start - t[0] + 2, 0) # base
		theme(t[1], start) # theme
