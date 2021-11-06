#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System.h>

#define ADD_VEC(A, B) A.x += B.x; \
A.y += B.y;

typedef struct {
    double x;
    double y;
} vec2f;

typedef struct {
    int x;
    int y;
} vec2i;

typedef struct {
    int width;
    int height;
    sfUint8 *pixels;
}framebuffer_t;

typedef struct {
    vec2f pos;
    vec2f dir;
} particle_t;

typedef struct {
    vec2i w_size;
    int spark_count;
    particle_t *spark;
    sfEvent event;
    sfClock *timer;
    sfSprite *render;
    sfTexture *matrix;
    framebuffer_t *buffer;
    sfRenderWindow *window;
} gen_t;


//src/helpers/math_random.c
int random_gen(int max);

//src/hitbox.c
void check_collision(particle_t *spark, vec2i size);

//src/helpers/csfml_utils.c
sfRenderWindow *window_creator(int x, int y);
framebuffer_t *framebuffer_create(int width, int height);
int index_from_vec(vec2i vec, int width);

//src/helpers/math_trigo.c
double tange(double x);
double cosinus(double x);
double sinus(double x);
vec2f normalize_vector(float x, float y);
float get_angle(vec2f dir);

//src/main.c
void manage_events(gen_t *prm);
void refresh_window(gen_t *prm);
void put_pixel(framebuffer_t *buffer, sfColor rgba, int x, int y);
int main(void);

//src/particle.c
void particle_update(gen_t *prm);
particle_t *init_spark(gen_t *prm);
void particle_steer(framebuffer_t *buffer, particle_t *spark);


//src/effects.c
void fade_effect(framebuffer_t *buffer);
void blur_effect(framebuffer_t *buffer, gen_t *prm);
float neighbour_average(framebuffer_t *buffer, int x, int y);
