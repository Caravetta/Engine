#include <math.h>
#include <iomanip>
#include "matrix.h"

namespace core {

Matrix4f::Matrix4f()
{
    m00 = 0;
    m01 = 0;
    m02 = 0;
    m03 = 0;
    m10 = 0;
    m11 = 0;
    m12 = 0;
    m13 = 0;
    m20 = 0;
    m21 = 0;
    m22 = 0;
    m23 = 0;
    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 0;
}

void Matrix4f::identity()
{
    m00 = 1;
    m01 = 0;
    m02 = 0;
    m03 = 0;
    m10 = 0;
    m11 = 1;
    m12 = 0;
    m13 = 0;
    m20 = 0;
    m21 = 0;
    m22 = 1;
    m23 = 0;
    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 1;
}

void Matrix4f::translate( Vector3f* vec )
{
    //m13 += m00 * vec->x + m10 * vec->y + m20 * vec->z;
    m30 += m00 * vec->x + m10 * vec->y + m20 * vec->z;
    m31 += m01 * vec->x + m11 * vec->y + m21 * vec->z;
    m32 += m02 * vec->x + m12 * vec->y + m22 * vec->z;
    m33 += m03 * vec->x + m13 * vec->y + m23 * vec->z;
}

void Matrix4f::rotate( float angle, Vector3f* axis )
{
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    float oneminusc = 1.0f - c;
    float xy = axis->x * axis->y;
    float yz = axis->y * axis->z;
    float xz = axis->x * axis->z;
    float xs = axis->x * s;
    float ys = axis->y * s;
    float zs = axis->z * s;

    float f00 = axis->x * axis->x * oneminusc + c;
    float f01 = xy * oneminusc + zs;
    float f02 = xz * oneminusc - ys;
    float f10 = xy * oneminusc - zs;
    float f11 = axis->y * axis->y * oneminusc + c;
    float f12 = yz * oneminusc + xs;
    float f20 = xz * oneminusc + ys;
    float f21 = yz * oneminusc - xs;
    float f22 = axis->z * axis->z * oneminusc + c;

    float t00 = m00 * f00 + m10 * f01 + m20 * f02;
    float t01 = m01 * f00 + m11 * f01 + m21 * f02;
    float t02 = m02 * f00 + m12 * f01 + m22 * f02;
    float t03 = m03 * f00 + m13 * f01 + m23 * f02;
    float t10 = m00 * f10 + m10 * f11 + m20 * f12;
    float t11 = m01 * f10 + m11 * f11 + m21 * f12;
    float t12 = m02 * f10 + m12 * f11 + m22 * f12;
    float t13 = m03 * f10 + m13 * f11 + m23 * f12;
    m20 = m00 * f20 + m10 * f21 + m20 * f22;
    m21 = m01 * f20 + m11 * f21 + m21 * f22;
    m22 = m02 * f20 + m12 * f21 + m22 * f22;
    m23 = m03 * f20 + m13 * f21 + m23 * f22;
    m00 = t00;
    m01 = t01;
    m02 = t02;
    m03 = t03;
    m10 = t10;
    m11 = t11;
    m12 = t12;
    m13 = t13;
}

void Matrix4f::scale( float scale )
{
    m00 = m00 * scale;
    m01 = m01 * scale;
    m02 = m02 * scale;
    m03 = m03 * scale;
    m10 = m10 * scale;
    m11 = m11 * scale;
    m12 = m12 * scale;
    m13 = m13 * scale;
    m20 = m20 * scale;
    m21 = m21 * scale;
    m22 = m22 * scale;
    m23 = m23 * scale;
}

std::ostream& operator<<(std::ostream &strm, const Matrix4f &a)
{
    strm << "mat4: ( " << a.m00 << " , " << a.m01 << " , " << a.m02 << " , " << a.m03 << " )\n";
    strm << std::setw (55) << "( " << a.m10 << " , " << a.m11 << " , " << a.m12 << " , " << a.m13 << " )\n";
    strm << std::setw (55) << "( " << a.m20 << " , " << a.m21 << " , " << a.m22 << " , " << a.m23 << " )\n";
    strm << std::setw (55) << "( " << a.m30 << " , " << a.m31 << " , " << a.m32 << " , " << a.m33 << " )\n";

    return strm;
}

} //end namespace core
