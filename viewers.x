# Viewer Source Code

```
@inc(display.x)
```

```
@Def(file: viewers.h)
	#pragma once

	#include "display.h"

	namespace Viewers {

		enum {
			restore = 0,
			modify = 1,
			suspend = 2
		};

		struct Viewer:
			public Display::Frame
		{
			int state;
		};

		struct Viewer_Msg:
			public Display::Frame_Msg
		{
			int id;
			int x, y, width, height;
			int state;
		};

		#if viewers_IMPL
			int cur_width = 0;
		#else
			extern int cur_width;
		#endif

		void Init_Track(
			int width, int height,
			Viewer *filler
		)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Open_Track(
			int x, int width,
			Viewer *filler
		)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Close_Track(int x)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Open(
			Viewer *viewer,
			int x, int y
		)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Change(
			Viewer *viewer,
			int y
		)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Close(Viewer *viewer)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		Viewer *This(int x, int y)
		#if viewers_IMPL
			{
				return nullptr;
			}
		#else
			;
		#endif

		Viewer *Next(Viewer *viewer)
		#if viewers_IMPL
			{
				return nullptr;
			}
		#else
			;
		#endif

		void Recall(Viewer **viewer)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Locate(
			int x, int height,
			Viewer **fil, Viewer **bot,
			Viewer **alt, Viewer **max
		)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		void Broadcast(Viewer_Msg *msg)
		#if viewers_IMPL
			{
			}
		#else
			;
		#endif

		#if viewers_IMPL
			struct Track: public Viewer {
				Display::Frame *under;
			};
		#endif
	}
@End(file: viewers.h)
```

```
@Def(file: viewers.cpp)
	#define viewers_IMPL 1
	#include "viewers.h"
@End(file: viewers.cpp)
```

