#ifndef MLX_DEFINES_H
# define MLX_DEFINES_H

# ifdef LOCAL_MACHINE

#  define ARROW_UP 65362
#  define ARROW_DOWN 65364
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363

#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_W 119

#  define KEY_Q 113
#  define KEY_E 101

#  define KEY_ESC 65307

# else 

#  define ARROW_UP 126
#  define ARROW_DOWN 125
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124

#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13

#  define KEY_Q 12
#  define KEY_E 14

#  define KEY_ESC 53

# endif 
#endif