#ifndef ANSI_ESCAPE_CODE_H
# define ANSI_ESCAPE_CODE_H

/*******************************************/
/*            fore ground color            */
/*******************************************/

# define F_BLACK "\033[30m"
# define F_RED "\033[31m"
# define F_GREEN "\033[32m"
# define F_YELLOW "\033[33m"
# define F_BLUE "\033[34m"
# define F_MAGENTA "\033[35m"
# define F_CYAN "\033[36m"
# define F_WHITE "\033[37m"
# define F_BRIGHT_BLACK "\033[90m"
# define F_BRIGHT_RED "\033[91m"
# define F_BRIGHT_GREEN "\033[92m"
# define F_BRIGHT_YELLOW "\033[93m"
# define F_BRIGHT_BLUE "\033[94m"
# define F_BRIGHT_MAGENTA "\033[95m"
# define F_BRIGHT_CYAN "\033[96m"
# define F_BRIGHT_WHITE "\033[97m"

# define F_RESTET "\033[39m"

/*******************************************/
/*            back ground color            */
/*******************************************/

# define B_BLACK "\033[40m"
# define B_RED "\033[41m"
# define B_GREEN "\033[42m"
# define B_YELLOW "\033[43m"
# define B_BLUE "\033[44m"
# define B_MAGENTA "\033[45m"
# define B_CYAN "\033[46m"
# define B_WHITE "\033[47m"
# define B_BRIGHT_BLACK "\033[100m"
# define B_BRIGHT_RED "\033[101m"
# define B_BRIGHT_GREEN "\033[102m"
# define B_BRIGHT_YELLOW "\033[103m"
# define B_BRIGHT_BLUE "\033[104m"
# define B_BRIGHT_MAGENTA "\033[105m"
# define B_BRIGHT_CYAN "\033[106m"
# define B_BRIGHT_WHIT "\033[107m"

# define B_RESTET "\033[49m"

/*******************************************/
/*            graphic rendition            */
/*******************************************/

# define GR_BOLD "\033[1m"
# define GR_FAINT "\033[2m"
# define GR_ITALIC "\033[3m"
# define GR_UNDER_LINE "\033[4m"
# define GR_BLINK "\033[5m"
# define GR_RAPID_BLINK "\033[6m"
# define GR_REVERSE "\033[7m"
# define GR_CONCEAL "\033[8m"

/*******************************************/
/*                  reset                  */
/*******************************************/

# define RESET_COLOR "\033[39;49m"
# define ALL_RESET "\033[0m"

#endif
