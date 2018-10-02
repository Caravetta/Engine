#ifndef __PERLIN_H__
#define __PERLIN_H__

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

#endif //__PERLIN_H__
