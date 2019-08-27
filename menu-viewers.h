
#line 12 "menu-viewers.x"

	#pragma once

	#include "viewers.h"
	#include "display.h"

	namespace Menu_Viewers {

		enum {
			extend = 0,
			reduce = 1,
			move = 2
		};

		struct Viewer:
			public Viewers::Viewer
		{
			int menu_height;

			Viewer(Display::Frame *menu, Display::Frame *main, int menu_height, int x, int y);
			void handle(const Display::Frame_Msg &msg) override;
		};

		#if menu_viewers_IMPL
			Viewer::Viewer(Display::Frame *menu, Display::Frame *main, int menu_height, int x, int y) {
			}

			void Viewer::handle(const Display::Frame_Msg &msg) {
			}
		#endif

		struct Modify_Msg:
			public Display::Frame_Msg
		{
			int id;
			int delta_y, y, height;
		};

	}

