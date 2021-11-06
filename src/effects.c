#include "sim.h"

void fade_effect(framebuffer_t *buffer)
{
    for (int i = 0; i < buffer->height * buffer->width; i++) {
        buffer->pixels[i * 4] = 0.95 * buffer->pixels[i * 4];
        buffer->pixels[i * 4 + 1] = 0.95 * buffer->pixels[i * 4 + 1];
        buffer->pixels[i * 4 + 2] = 0.95* buffer->pixels[i * 4 + 2];
    }
}

void blur_effect(framebuffer_t *buffer, gen_t *prm)
{
    int value;
    for (int x = 0; x < prm->w_size.x; x++) {
        for (int y = 0; y < prm->w_size.y; y++) {
            value = neighbour_average(buffer, x, y);
            put_pixel(buffer, (sfColor){value, value, value, 255}, x, y);
        }
    }
    return;
}

float neighbour_average(framebuffer_t *buffer, int x, int y)
{
    float value = 0;

    if (x < 1 || y < 1 || x >= buffer->width - 1 || y >= buffer->height - 1) {
        // printf("No  (%d|%d)\n", x, y);
        return 0;
    } else {
        // printf("Yes (%d|%d)\n", x, y);
        value += buffer->pixels[index_from_vec((vec2i){x, y}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x - 1, y}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x - 1, y - 1}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x - 1, y + 1}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x + 1, y}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x + 1, y - 1}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x + 1, y + 1}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x, y - 1}, buffer->width)];
        value += buffer->pixels[index_from_vec((vec2i){x, y + 1}, buffer->width)];
        // printf("\tdone %.2f / %d\n", value, count);
    }
    return (value / 8.0);
}