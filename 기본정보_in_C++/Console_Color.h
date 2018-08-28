#pragma once
#ifndef _CONSOLE_COLOR_H_
#define _CONSOLE_COLOR_H_
#include <Windows.h>
namespace option {
	namespace parameters {
		namespace console_color {
#define SET_CONSOLE_COLOR(X) (SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),(X)))
#define SET_CONSOLE_COLOR_DEFAULT (SET_CONSOLE_COLOR(option::parameters::console_color::default_console_color))
			enum color_number {
				black = 0,
				purple = 5,
				dark_yellow = 6,
				white = 7,
				gray = 8,
				blue = 9,
				green = 10,
				sky = 11,
				red = 12,
				pink = 13,
				yellow = 14,
			};
			enum color_situation {
				default_console_color = white,
				order_color = red,
				zero_selection = green,
				site_name_color = yellow,
				history_color = pink,
				account_attribute_color = dark_yellow
			};
		}// namespace console_color
	}// namespace parameters
}//namespace option
#endif // !_CONSOLE_COLOR_H_
