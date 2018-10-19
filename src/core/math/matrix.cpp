#include <math.h>
#include <iomanip>
#include "matrix.h"

namespace core {

#define MAT_SIMD 1

Matrix4f::Matrix4f()
{
#if MAT_SIMD
    __m128 zero = _mm_setzero_ps();
    row_0 = zero;
    row_1 = zero;
    row_2 = zero;
    row_3 = zero;
#else
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
#endif
}

void Matrix4f::identity()
{
#if MAT_SIMD
    row_0 = _mm_set_ps(0, 0, 0, 1);
    row_1 = _mm_set_ps(0, 0, 1, 0);
    row_2 = _mm_set_ps(0, 1, 0, 0);
    row_3 = _mm_set_ps(1, 0, 0, 0);
#else
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
#endif
}

void Matrix4f::translate( Vector3f* vec )
{
    //m13 += m00 * vec->x + m10 * vec->y + m20 * vec->z;
#if MAT_SIMD
    __m128 m0 = _mm_mul_ps( row_0, _mm_set_ps1(vec->vec.x));
    __m128 m1 = _mm_mul_ps( row_1, _mm_set_ps1(vec->vec.y));
    __m128 m2 = _mm_mul_ps( row_2, _mm_set_ps1(vec->vec.z));


    row_3 = _mm_add_ps(row_3, _mm_add_ps(_mm_add_ps(m0, m1), m2));
#else
    m30 += m00 * vec->vec.x + m10 * vec->vec.y + m20 * vec->vec.z;
    m31 += m01 * vec->vec.x + m11 * vec->vec.y + m21 * vec->vec.z;
    m32 += m02 * vec->vec.x + m12 * vec->vec.y + m22 * vec->vec.z;
    m33 += m03 * vec->vec.x + m13 * vec->vec.y + m23 * vec->vec.z;
#endif
}

void Matrix4f::rotate( float angle, Vector3f* axis )
{
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    float oneminusc = 1.0f - c;
    float xy = axis->vec.x * axis->vec.y;
    float yz = axis->vec.y * axis->vec.z;
    float xz = axis->vec.x * axis->vec.z;
    float xs = axis->vec.x * s;
    float ys = axis->vec.y * s;
    float zs = axis->vec.z * s;

    float f00 = axis->vec.x * axis->vec.x * oneminusc + c;
    float f01 = xy * oneminusc + zs;
    float f02 = xz * oneminusc - ys;
    float f10 = xy * oneminusc - zs;
    float f11 = axis->vec.y * axis->vec.y * oneminusc + c;
    float f12 = yz * oneminusc + xs;
    float f20 = xz * oneminusc + ys;
    float f21 = yz * oneminusc - xs;
    float f22 = axis->vec.z * axis->vec.z * oneminusc + c;

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
#if MAT_SIMD
    row_0 = _mm_mul_ps( row_0, _mm_set_ps1(scale));
    row_1 = _mm_mul_ps( row_1, _mm_set_ps1(scale));
    row_2 = _mm_mul_ps( row_2, _mm_set_ps1(scale));
#else
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
#endif
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
