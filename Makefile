oberon: oberon.cpp

oberon.cpp: hx-run viewer.h
viewer.h: hx-run

hx-run: index.x viewer.x
	hx
	date > hx-run

