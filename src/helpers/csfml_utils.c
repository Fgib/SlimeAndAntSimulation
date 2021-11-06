#include "sim.h"

sfRenderWindow *window_creator(int x, int y)
{
    sfRenderWindow *window;
    sfVideoMode video_mode;

    video_mode.height = y;
    video_mode.width = x;

    window = sfRenderWindow_create(video_mode, "Simulation", sfDefaultStyle, NULL);
    return (window);
}

framebuffer_t *framebuffer_create(int width, int height)
{
    framebuffer_t *frame = malloc(sizeof(framebuffer_t));
    frame->height = height;
    frame->width = width;
    frame->pixels = malloc(width * (height + 1) * 4);
    return (frame);
}

int index_from_vec(vec2i vec, int width)
{
    return (4 * (vec.y * width + vec.x));
}