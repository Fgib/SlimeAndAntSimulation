#include "sim.h"

double tange(double x)
{
    double in_rad = x * M_PI / 180;
    return (tan(in_rad));
}

double cosinus(double x)
{
    double in_rad = x * M_PI / 180;
    return (cos(in_rad));
}

double sinus(double x)
{
    double in_rad = x * M_PI / 180;
    return (sin(in_rad));
}

vec2f normalize_vector(float x, float y)
{
    vec2f res;
    double length = sqrt((x * x) + (y * y));

    res.x = x / length;
    res.y = y / length;
    return res;
}

float get_angle(vec2f dir)
{
    return atan2(dir.y, dir.x) * 180 / M_PI;
}