#ifndef _PERLIN_H_
#define _PERLIN_H_

class Perlin {
private:
    int *p;
    float *Gx;
    float *Gy;
    float *Gz;
public:
    Perlin();
    ~Perlin();
    float noise(float sample_x, float sample_y, float sample_z);
};

#endif
