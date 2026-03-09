/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjozefzo <cjozefzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:21:05 by cjozefzo          #+#    #+#             */
/*   Updated: 2024/07/12 18:48:16 by cjozefzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define PI 3.1415926
# define X_AXIS 1
# define Z_AXIS 3
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_object {SPHERE, PLANE, CYLINDER, END}	t_enum_obj;

typedef struct s_all	t_all;
typedef struct s_ray	t_ray;
typedef struct s_obj	t_obj;

typedef struct s_data_vars
{
	void	*connect;
	void	*window;
}		t_mlx_id;

typedef struct s_pair
{
	int	a;
	int	b;
}		t_pair;

typedef struct s_data_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_data_img;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	w;
}		t_point;

typedef struct s_point	t_vector;
typedef struct s_point	t_color;

typedef struct s_camera
{
	int			flag_move;
	t_point		centre;
	t_vector	orientation_vector;
	t_vector	up;
	t_vector	right;
	t_vector	*screen;
	float		fov;
	float		cam_to_world[16];
	float		world_to_cam[16];
}	t_camera;

typedef struct s_ambiant
{
	float	brightness;
	int		color;
}	t_ambiant;

typedef struct s_light
{
	t_point	centre;
	float	brightness;
	int		color;
}	t_light;

typedef struct s_ray
{
	float		length;
	t_point		origin;
	t_vector	dir;
	t_vector	normal;
}		t_ray;

typedef struct s_obj
{
	t_enum_obj	type;
	int			(*collision)(t_ray *, struct s_obj *);
	void		(*rotation)(int, struct s_all *);
	void		(*resize)(int, struct s_all *);
	int			(*hit_box)(t_vector *, struct s_obj *);
	int			color;
	t_point		centre;
	t_vector	rot_y;
	t_vector	rot_x;
}		t_obj;

typedef struct s_sphere
{
	t_obj		obj;
	float		diameter;
	float		*cam_to_world;
	t_vector	normal;
	t_vector	right;
}		t_sphere;

typedef struct s_plane
{
	t_obj		obj;
	float		*cam_to_world;
	t_vector	normal;
	t_vector	right;
}		t_plane;

typedef struct s_cylinder
{
	t_obj		obj;
	float		diameter;
	float		height;
	t_vector	quaternion;
	t_vector	normal;
	t_vector	right;
}		t_cylinder;

typedef struct s_all_data
{
	t_camera	*cam;
	t_ambiant	*ambiant;
	t_light		*light;
	t_obj		**all_obj;
}		t_all_data;

typedef struct s_norm
{
	int		index;
	float	len;
	t_pair	*pix;
}	t_norm;

typedef struct s_all
{
	int				select;
	t_pair			screen_size;
	t_all_data		*variable;
	t_mlx_id		*id;
	t_data_img		*img;
}		t_all;

typedef struct s_normj
{
	bool	a;
	bool	c;
	bool	l;
	bool	sp;
	bool	pl;
	bool	cy;
	int		i;
}		t_normj;

bool		ft_atoi(char *str, int *nb);
t_plane		*initialize_plane(void);
t_cylinder	*build_cy(char *str);
bool		build_struc(t_all_data *data, char **map);
bool		build_ambient_data(t_all_data *data, char *line);
bool		build_camera_data(t_all_data *data, char *line);
bool		build_light_data(t_all_data *data, char *line);
bool		build_sphere_data(t_all_data *data, char *line, int *j);
bool		build_plane_data(t_all_data *data, char *line, int *j);
bool		ft_chckfrr(t_point point);
t_light		*build_light(char *str);
void		calcul_cam(t_camera *cam);
t_camera	*build_camera(char *str);
void		calcul_plane(t_plane *plane, t_camera *cam);
t_plane		*build_pl(char *str, t_camera *cam);
int			ft_nbofform(char **map);
t_point		build_point(char *ch);
t_sphere	*build_sp(char *str, t_camera *cam);
t_ambiant	*build_amb(char *str);
char		**extract(char *str);
int			ft_nbofform(char **map);
t_point		build_point(char *ch);
t_sphere	*build_sp(char *str, t_camera *cam);
t_ambiant	*build_amb(char *str);
bool		validspace(char *str);
bool		checkingvalid(char **map);
bool		ft_strncmp(char *s1, char *s2, int n);
bool		allineedisnorm(t_normj n);
bool		allineedisall(char **map);
bool		ft_strcmp(char *str, char *str2);
bool		ft_dotrt(char *str, char *str2);
int			ft_strlen(char *str);
char		*ft_strjoin(char *str, char *str2);
bool		validchar(char c);
bool		allineedisnorm(t_normj n);
int			rgbtoint(char *colorStr);
char		**ft_frft(char **ptr);
char		**ft_split(char *s, char c);
void		parsing(t_all_data *data, char *str, t_all *to_pass);
char		*get_next_line(int fd, int tofree);
char		*gn_strdel(char **str);
int			gn_strlen(char *str);
char		*gn_strjoin(char *str, char *buf, int r);
char		*gn_strcpy(char *dest, char *src);
char		*gn_strchr(char *str, char c);
char		*gn_strdup(char *src);
double		ft_atof(char *str);
void		out_of_object(t_all *data);
void		check_mandatory(t_all *data);

int			color_brightness(int light_color, int color, float brightness,
				float specular);
float		specular_light(t_ray *light_dir, t_ray *view_dir);
int			handle_click(int click, int x, int y, void *data);
void		object_movement(int key, t_all *data);
int			check_collision(t_ray *ray, t_obj **obj);
int			to_world_coord(t_vector *coord, t_all *data);
int			quit_struct(void *data);
int			quit_serveur(void *data);
int			handle_cross(void *data);
void		free_tab(char **to_free);
int			handle_key_press(int key_number, void *data);
void		ft_bzero(void *src, unsigned int n);

t_vector	new_vector(float x, float y, float z);
void		plus_vector(t_vector *result, t_vector *a, t_vector *b);
void		minus_vector(t_point *result, t_point *a, t_point *b);
void		scalar_time_vect(t_vector *v, float scalar, t_vector *u);
void		cross_product(t_vector *u, t_vector *v, t_vector *w);
float		dot_product(t_vector *u, t_vector *v);
void		normalize(t_vector *u);
t_vector	max_vertex(t_vector *arr);
t_vector	vector_time_matrix(t_vector *u, float *v);
t_vector	min_vertex(t_vector *arr);
int			cam_hit_object(t_vector max, t_vector min, t_vector *cam);
t_vector	hit(t_ray *ray);
float		quadratic_equation(float a, float b, float c);
float		vect_len(t_vector *vect);
void		vector_time_vector(t_vector *result, t_vector *a, t_vector *b);
void		rotation_quaternion(t_vector *result, t_vector *quaternion,
				t_vector *u);
void		rotation_inv_quaternion(t_vector *result, t_vector *quaternion,
				t_vector *u);
void		normalize_quat(t_vector *q);
float		matrix_determinant4(float *mat);
float		matrix_determinant3(float *m);
float		*fill_mat3(float *m, float *m4, int del_a, int del_b);

void		resize_plane(int key, t_all *data);
void		rotation_plane(int key, t_all *data);
void		rotation_sphere(int key, t_all *data);
void		resize_sphere(int key, t_all *data);
void		resize_cylinder(int key, t_all *data);
void		cylinder_rotation(int key, t_all *data);
int			hit_box_cyl(t_vector *cam_pos, t_obj *obj);
int			hit_box_plane(t_vector *cam_pos, t_obj *obj);
int			hit_box_sphere(t_vector *cam_pos, t_obj *obj);
void		rotation_x(t_vector *vect, t_vector *right,
				t_vector *up, float angle);
void		rotation_y(t_vector *vect, t_vector *right,
				t_vector *up, float angle);
int			color_pixel(t_vector *coord_pixel, t_all *data,
				t_pair *screen_pixel);
int			draw(t_all *data, t_pair *screen_size);
int			check_object(t_obj **obj, t_vector *u, t_vector *v,
				void (*op)(t_vector *, t_vector *, t_vector *));
int			make_cam_to_world(t_camera *cam);
int			make_cylinder_matrix(t_cylinder *cyl);
int			make_world_to_cam(t_camera *cam);

int			pixel_put(t_all *p, int x, int y, int color);
int			collision_plane(t_ray *ray, t_obj *to_cast);
int			check_disk(t_ray *temp, t_plane *disk, float r);
void		create_plane(t_plane *new, t_cylinder *old);
int			collision_sphere(t_ray *ray, t_obj *to_cast);
int			collision_cylinder(t_ray *ray, t_obj *to_cast);
int			shortest_ray(float a, float b, t_ray *ray);
#endif