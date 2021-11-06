#include "sim.h"

void manage_events(gen_t *prm)
{
    if (prm->event.type == sfEvtClosed) {
        sfRenderWindow_close(prm->window);
    }
    if (prm->event.type == sfEvtKeyPressed) {
        free(prm->spark);
        prm->spark = init_spark(prm);
    }
}

void refresh_window(gen_t *prm)
{
    sfRenderWindow_clear(prm->window, sfBlack);
    sfTexture_updateFromPixels(prm->matrix, prm->buffer->pixels, prm->w_size.x, prm->w_size.y, 0, 0);
    sfSprite_setTexture(prm->render, prm->matrix, sfTrue);
}

void put_pixel(framebuffer_t *buffer, sfColor rgba, int x, int y)
{
    buffer->pixels[4 * (y * buffer->width + x)] = rgba.r;
    buffer->pixels[4 * (y * buffer->width + x) + 1] = rgba.g;
    buffer->pixels[4 * (y * buffer->width + x) + 2] = rgba.b;
    buffer->pixels[4 * (y * buffer->width + x) + 3] = rgba.a;
}

int main(void)
{
    int fps = 60;
    gen_t *prm = malloc(sizeof(gen_t));
    prm->w_size = (vec2i){480, 320};
    // prm->w_size = (vec2i){960, 640};
    // prm->w_size = (vec2i){1170, 1170};
    prm->timer = sfClock_create();
    prm->window = window_creator(prm->w_size.x, prm->w_size.y);
    prm->buffer = framebuffer_create(prm->w_size.x, prm->w_size.y);

    prm->render = sfSprite_create();
    prm->matrix = sfTexture_create(prm->w_size.x, prm->w_size.y);

    prm->spark_count = 14400 * 5;
    printf("Init not done\n");
    prm->spark = init_spark(prm);
    printf("Init done\n");

    sfRenderWindow_setFramerateLimit(prm->window, fps);
    while (sfRenderWindow_isOpen(prm->window)) {
        while (sfRenderWindow_pollEvent(prm->window, &prm->event)) {
            manage_events(prm);
        }
        if (sfClock_getElapsedTime(prm->timer).microseconds > 1000000 / fps) {
            sfClock_restart(prm->timer);
            fade_effect(prm->buffer);
            // blur_effect(prm->buffer, prm);
            particle_update(prm);
            refresh_window(prm);
            sfRenderWindow_drawSprite(prm->window, prm->render, NULL);
            sfRenderWindow_display(prm->window);
            printf("process time: %lldms\n", sfClock_getElapsedTime(prm->timer).microseconds / 1000);
        }
    }
    sfRenderWindow_destroy(prm->window);
    sfClock_destroy(prm->timer);
    free(prm);
    return 0;
}

