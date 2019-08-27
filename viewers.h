
#line 8 "viewers.x"

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
		);

		void Open_Track(
			int x, int width,
			Viewer *filler
		);

		void Close_Track(int x);

		void Open(
			Viewer *viewer,
			int x, int y
		);

		void Change(
			Viewer *viewer,
			int y
		);

		void Close(Viewer *viewer);

		Viewer *This(int x, int y);

		Viewer *Next(Viewer *viewer);

		void Recall(Viewer **viewer);

		void Locate(
			int x, int height,
			Viewer **fil, Viewer **bot,
			Viewer **alt, Viewer **max
		);

		void Broadcast(Viewer_Msg *msg);

		#if viewers_IMPL
			void Init_Track(
				int width, int height,
				Viewer *filler
			) {
			}

			void Open_Track(
				int x, int width,
				Viewer *filler
			) {
			}

			void Close_Track(int x) {
			}

			void Open(
				Viewer *viewer,
				int x, int y
			) {
			}

			void Change(
				Viewer *viewer,
				int y
			) {
			}

			void Close(Viewer *viewer) {
			}

			Viewer *This(int x, int y) {
				return nullptr;
			}

			Viewer *Next(Viewer *viewer) {
				return nullptr;
			}

			void Recall(Viewer **viewer) {
			}

			void Locate(
				int x, int height,
				Viewer **fil, Viewer **bot,
				Viewer **alt, Viewer **max
			) {
			}

			void Broadcast(Viewer_Msg *msg) {
			}

			struct Track: public Viewer {
				Display::Frame *under;
			};
		#endif
	}
