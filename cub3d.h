/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:40:05 by gtskitis          #+#    #+#             */
/*   Updated: 2024/05/26 02:26:27 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BONUS
#  define BONUS 			0
#  define NUM_OF_SPRITES	1
# else
#  define NUM_OF_SPRITES	6
# endif

# define MAX_HEIGHT			250
# define MAX_WIDTH			250
# define MINI_MAX_HEIGHT	25
# define MINI_MAX_WIDTH		48

# define RENDER_SPEED		3

// MLX Includes
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx/mlx.h"

// C Includes
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

// Libft
# include "libft/libft.h"

// Parsing
# define BLANK_CHARS	" \t"
# define SPACE_CHARS	" \t\f\t\v\r\n"
# define COMPONENTS		" \n01NEWS"

enum	e_err_code
{
	MALLOC_ERR,
	WRONG_ARGV_ERR,
	BAD_EXT_ERR,
	OPEN_FILE_ERR,
	EMPTY_FILE_ERR,
	ID_NOT_FOUND_ERR,
	DUPLICATE_ID_ERR,
	MISSING_ID_ERR,
	ID_NOT_SPEC_ERR,
	SPACE_IN_PATH_ERR,
	EXT_NOT_XPM_ERR,
	TOO_FEW_PATH_ERR,
	TOO_MANY_PATH_ERR,
	BAD_COLOR_ERR,
	NO_MAP_ERR,
	EMPTY_LINE_ERR,
	UNRECOGNIZED_ERR,
	FOUND_TAB_ERR,
	NO_START_POS_ERR,
	MULTI_START_ERR,
	TOO_LARGE_ERR,
	SEPRT_MAPS_ERR,
	NOT_SURROUND_ERR,
	TEX_IMPORT_ERR,
	TEX_NOT_SQR_ERR,
	MLX_INIT_FAIL_ERR,
	NUM_OF_ERR
};

# define NO_ERROR			0
# define MALLOC_ERR_MSG		"Memory allocation failed. Program terminated\n"
# define WRONG_ARGV_MSG		"Program takes 1 argument in format *.cub\n"
# define BAD_EXT_MSG		": The map should be in format *.cub\n"
# define OPEN_FILE_MSG		": Cannot open file\n"
# define EMPTY_FILE_MSG		": Map file is empty\n"
# define ID_NOT_FOUND_MSG	"\nUnknown texture identifier\n"
# define DUPLICATE_ID_MSG	"\nFound duplicate texture identifier\n"
# define MISSING_ID_MSG		"Missing one or more texture identifier(s)\n"
# define ID_NOT_SPEC_MSG	"\nIdentifier is not specified\n"
# define SPACE_IN_PATH_MSG	"\nFound multiple paths to texture identifier\n"
# define EXT_NOT_XPM_MSG	": Texture file must be in *.xpm format\n"
# define TOO_FEW_PATH_MSG	"\nToo few paths to textures for animated wall\n"
# define TOO_MANY_PATH_MSG	"\nToo many paths to textures for animated wall\n"
# define BAD_COLOR_MSG		"\nUse RGB values from 0 to 255 separated by ','\n"
# define NO_MAP_MSG			"Map not found in map file\n"
# define EMPTY_LINE_MSG		"\nFound empty line in the middle of the map\n"
# define UNRECOGNIZED_MSG	"\nFound unrecognized character in the map\n"
# define FOUND_TAB_MSG		"\nMap cannot contain tabs (only spaces)\n"
# define NO_START_POS_MSG	"Map does not contain a starting position\n"
# define MULTI_START_MSG	"Map contains multiple starting positions\n"
# define TOO_LARGE_MSG		"Map is too large\n"
# define SEPRT_MAPS_MSG		"Found 2 or more separate maps in map file\n"
# define NOT_SURROUND_MSG	"Map not entirely surrounded by walls\n"
# define TEX_IMPORT_MSG		": Couldn't open this texture file\n"
# define TEX_NOT_SQR_MSG	": Texture file should be square\n"
# define MLX_INIT_FAIL_MSG	"Failed to initialize MLX. Aborting\n"

// MLX Binds
# define KEY_ESC    		65307
# define KEY_LEFT   		65361
# define KEY_UP     		65362
# define KEY_RIGHT  		65363
# define KEY_DOWN   		65364
# define KEY_W      		119
# define KEY_A      		97
# define KEY_S      		115
# define KEY_D      		100
# define KEY_M				109
# define MOUSE_HOOK			6

# define PATH_TO_PTR	"./assets/arrows/player.xpm"

// Properties
# define PTR_SIZE		18
# define S_WIDTH    	1920
# define S_HEIGHT   	1080
# define MINI_W			200
# define MINI_H			200
# define MINI_TILE		40
# define TILE_LEN		640
# define ROT_SPEED  	0.07
# define P_SPEED    	120
# define FOV        	60

enum	e_textures
{
	NORTH_WALL,
	SOUTH_WALL,
	WEST_WALL,
	EAST_WALL,
	FLOOR = 4 * NUM_OF_SPRITES,
	CEILING
};

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img[2];
	t_img		xpm_img[4 * NUM_OF_SPRITES];
	t_img		pointer_xpm;

	double		ray_angle;
	float		fov_rad;
	double		ray_dist;
	double		hor_x;
	double		hor_y;
	double		ver_x;
	double		ver_y;
	int			index;

	bool		is_hor;
	bool		wall_side_flag;

	double		p_angle;
	int			l_r;
	int			a_d;
	int			w_s;
	int			map_p_x;
	int			map_p_y;
	int			pix_p_x;
	int			pix_p_y;
	double		y;

	size_t		counter;
	bool		disp_map;
	char		**map_file;
	char		**map;
	int			map_width;
	int			map_height;
	bool		too_large;

	char		*texture_paths[4 * NUM_OF_SPRITES];
	int			floor_clr;
	int			ceiling_clr;
}	t_data;

// Map Init
void	init_data(t_data *game);
void	init_mlx(t_data *game);
void	hook_mlx(t_data *game);
void	calc_values(t_data *game);

// Parsing
void	parse_cub_file(t_data *game, char *argv);
int		check_texture_ids(t_data *data);
void	import_textures(t_data *data, int end);
int		get_texture_path(t_data *game, char *line, int texture_id);
int		parse_color(char *line, int *err_code);
void	check_map(t_data *game, int start);
void	normalize_map(t_data *game, char **map);
void	add_layer(t_data *game);
void	check_borders(t_data *game);
void	get_player_pos(t_data *game);

// Parsing Utils
bool	is_empty_line(char *line);
char	**trim_array(char **array);
int		count_chars(char *s, char *c);
bool	is_numerical(char *s);
char	**copy_array(char **array);
char	**split_mod(char const *s, char c);

// Player Moves
void	move_p(t_data *game, double x, double y);
int		mouse_move(int x, int y, t_data *game);
void	rotate_p(t_data *game, int i);
void	choose_rotation(t_data *game);

// Rendering
int		execute(t_data *game);
void	render_ray(t_data *data, int ray);
void	draw_square(t_data *data, int x, int y, int color);
void	render_pointer(t_data *game, int x_0, int y_0);
void	render_minimap(t_data *game);
void	render_map(t_data *game);
void	draw_frame(t_data *game);
void	fill_mini_img(t_data *game, int x, int y);
void	draw_square(t_data *game, int x, int y, int color);

// Raycasting
void	project_rays(t_data *game);
float	angle_lim(float angle);

// TRGB Utils
int		create_trgb(int t, int r, int g, int b);
void	img_pix_put(t_img *img, int x, int y, int color);
void	img_pix_put_c(t_img *img, int x, int y, char color);
void	put_pix_wall(t_data *game, t_img *ptr, int top_p, int x);

// Free and Exit
void	handle_error(t_data *data, int i, int err_code);
void	exit_code(t_data *data, int err_code, char *err_str);
void	free_data(t_data *game);
int		close_game(t_data *game);

#endif
