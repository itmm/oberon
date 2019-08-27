
#line 4 "display.x"

	#pragma once

	namespace Display {
		struct Frame_Msg { };

		struct Frame {
			Frame *next, *descendant;
			int x, y, width, height;
			virtual void handle(
				const Frame_Msg &
			) { }
		};
	}
