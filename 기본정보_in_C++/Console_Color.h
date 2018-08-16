#pragma once
#pragma once
#ifndef _CONSOLE_COLOR_H_
#define _CONSOLE_COLOR_H_
namespace option {
	namespace console_color {
#define SET_CONSOLE_COLOR(X) (SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),(X)))
#define SET_CONSOLE_COLOR_DEFAULT (SET_CONSOLE_COLOR(console_color::normal_color))
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
			normal_color = white,
			order_color = red,
			zero_selection = green,
			site_name_color = yellow,
			account_attribute_color = dark_yellow
		};
	}// namespace console_color
}//namespace option
#endif // !_ADD_H_
