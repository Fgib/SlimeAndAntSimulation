#include "sim.h"

particle_t *init_spark(gen_t *prm)
{
    particle_t *list_spark = malloc(sizeof(particle_t) * prm->spark_count);
    double angle = (double)360 / (double){prm->spark_count};

    for (int i = 0; i < prm->spark_count; i++) {
        printf("Init spark %d\n", i);
        list_spark[i].pos = (vec2f){prm->w_size.x / 2, prm->w_size.y / 2};
        list_spark[i].dir = (vec2f){cosinus(angle * i), sinus(angle * i)};
    }
    return list_spark;
}

void particle_update(gen_t *prm)
{
    for (int i = 0; i < prm->spark_count; i++) {
        particle_steer(prm->buffer, &prm->spark[i]);
        ADD_VEC(prm->spark[i].pos, prm->spark[i].dir);
        check_collision(&prm->spark[i], prm->w_size);
        put_pixel(prm->buffer, sfWhite, (int)prm->spark[i].pos.x, (int)prm->spark[i].pos.y);
    }
}

float sense(framebuffer_t *buffer, vec2f pos, float angle)
{
    vec2f dir = normalize_vector(cosinus(angle), sinus(angle));
    int x = (int){pos.x + 4.0 * dir.x};
    int y = (int){pos.y + 4.0 * dir.y};
    // printf("\nangle %.1f go(%d|%d)\n", angle, x, y);

    return neighbour_average(buffer, x, y);
}

void particle_steer(framebuffer_t *buffer, particle_t *spark)
{
    float angle = get_angle(spark->dir);
    float weight_forward = sense(buffer, spark->pos, angle);
    float weight_left = sense(buffer, spark->pos, angle + 35);
    float weight_right = sense(buffer, spark->pos, angle - 35);

    if (weight_right > weight_left) {
        spark->dir = normalize_vector(cosinus(angle - 20), sinus(angle - 20));
    } else if (weight_right < weight_left) {
        spark->dir = normalize_vector(cosinus(angle + 20), sinus(angle + 20));
    } else {
        spark->dir = normalize_vector(cosinus(angle), sinus(angle));
    }
}