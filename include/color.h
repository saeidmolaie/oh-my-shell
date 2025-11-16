#pragma once

#define COLOR(r, g, b)  "\033[38;2;" #r ";" #g ";" #b "m"

namespace color
{

	constexpr const char* GRUVBOX_BRIGHT_RED = COLOR(251, 73, 52);
	constexpr const char* GRUVBOX_BRIGHT_YELLOW = COLOR(250, 189, 47);
	constexpr const char* GRUVBOX_BRIGHT_CYAN = COLOR(142, 192, 124);

}