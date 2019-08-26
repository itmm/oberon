
#line 4 "viewer.x"

	#pragma once

	struct ViewerMsg {
	};

	struct Viewer {
		int x, y, w, h;
		void (*handler)(Viewer &, ViewerMsg &);
		int state;
	};
