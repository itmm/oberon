# Viewer Source Code

```
@Def(file: display.h)
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
@End(file: display.h)
```
