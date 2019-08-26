
#line 4 "viewer.x"

	#pragma once

	struct ViewerMsg {
	};

	struct Viewer {
		int x, y, w, h;
		void (*handler)(Viewer &, ViewerMsg &);
		int state;
	};

	struct InputMsg: public ViewerMsg {
		int id;
		int x, y;
		int keys;
		char ch;
	};

	struct ControlMsg: public ViewerMsg {
		int id;
		int x, y;
	};
