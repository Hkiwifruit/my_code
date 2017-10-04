#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <ncurses.h>

class window{
	public:
		window();
		void refreshMyWindow(WINDOW* win);
		void putStringToWin(WINDOW* win, int start_y, int start_x, std::string &msg);

		void getStringFromWin(WINDOW* win, std::string &outString);
		void clrNumsLines(WINDOW *win, int begin, int nums);
		void createHeader();
		void createOutput();
		void createFriendList();
		void createInput();
		~window();

	public:
			WINDOW *header;
			WINDOW *output;
			WINDOW *friend_list;
			WINDOW *input;
};

#endif
