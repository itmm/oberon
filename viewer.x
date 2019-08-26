# Viewer Source Code

```
@Def(file: viewer.h)
	#pragma once

	struct ViewerMsg {
	};

	struct Viewer {
		int x, y, w, h;
		void (*handler)(Viewer &, ViewerMsg &);
		int state;
	};
@End(file: viewer.h)
```
