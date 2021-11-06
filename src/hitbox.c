#include "sim.h"

void check_collision(particle_t *spark, vec2i size)
{
    if (spark->pos.x <= 0) {
        spark->dir.x *= -1;
        ADD_VEC(spark->pos, spark->dir);
    }
    if (spark->pos.x >= size.x - 1) {
        spark->dir.x *= -1;
        ADD_VEC(spark->pos, spark->dir);
    }
    if (spark->pos.y <= 0) {
        spark->dir.y *= -1;
        ADD_VEC(spark->pos, spark->dir);
    }
    if (spark->pos.y >= size.y - 1) {
        spark->dir.y *= -1;
        ADD_VEC(spark->pos, spark->dir);
    }
}