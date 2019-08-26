oberon: oberon.cpp

oberon.cpp: hx-run viewer.h
	touch $@

viewer.h: hx-run
	touch $@

hx-run: index.x viewer.x
	hx
	date > hx-run

