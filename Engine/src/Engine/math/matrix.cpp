#include <math.h>
#include <iomanip>
#include "Engine.h"

namespace Engine {

//#define MAT_SIMD 1

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
    __m128 m0 = _mm_mul_ps( row_0, _mm_set_ps1(vec->x));
    __m128 m1 = _mm_mul_ps( row_1, _mm_set_ps1(vec->y));
    __m128 m2 = _mm_mul_ps( row_2, _mm_set_ps1(vec->z));


    row_3 = _mm_add_ps(row_3, _mm_add_ps(_mm_add_ps(m0, m1), m2));
#else
    m30 += m00 * vec->x + m10 * vec->y + m20 * vec->z;
    m31 += m01 * vec->x + m11 * vec->y + m21 * vec->z;
    m32 += m02 * vec->x + m12 * vec->y + m22 * vec->z;
    m33 += m03 * vec->x + m13 * vec->y + m23 * vec->z;
#endif
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

Matrix4f Matrix4f::generate_transform( Vector3f scale, Vector3f position )
{
    Matrix4f scale_mat;
    scale_mat.identity();
    Matrix4f position_mat;
    position_mat.identity();

    scale_mat.m00 = scale.x;
    scale_mat.m11 = scale.y;
    scale_mat.m22 = scale.z;

    position_mat.m03 = position.x;
    position_mat.m13 = position.y;
    position_mat.m23 = position.z;

    return position_mat * scale_mat;
}

std::ostream& operator<<(std::ostream &strm, const Matrix4f &a)
{
    strm << "mat4: ( " << a.m00 << " , " << a.m01 << " , " << a.m02 << " , " << a.m03 << " )\n";
    strm << std::setw (55) << "( " << a.m10 << " , " << a.m11 << " , " << a.m12 << " , " << a.m13 << " )\n";
    strm << std::setw (55) << "( " << a.m20 << " , " << a.m21 << " , " << a.m22 << " , " << a.m23 << " )\n";
    strm << std::setw (55) << "( " << a.m30 << " , " << a.m31 << " , " << a.m32 << " , " << a.m33 << " )\n";

    return strm;
}

Matrix4f Matrix4f::operator*( const Matrix4f &other ) const
{
    Matrix4f tmp;

    tmp.m00 = (m00 * other.m00) + (m01 * other.m10) + (m02 * other.m20) + (m03 * other.m30);
    tmp.m01 = (m00 * other.m01) + (m01 * other.m11) + (m02 * other.m21) + (m03 * other.m31);
    tmp.m02 = (m00 * other.m02) + (m01 * other.m12) + (m02 * other.m22) + (m03 * other.m32);
    tmp.m03 = (m00 * other.m03) + (m01 * other.m13) + (m02 * other.m23) + (m03 * other.m33);

    tmp.m10 = (m10 * other.m00) + (m11 * other.m10) + (m12 * other.m20) + (m13 * other.m30);
    tmp.m11 = (m10 * other.m01) + (m11 * other.m11) + (m12 * other.m21) + (m13 * other.m31);
    tmp.m12 = (m10 * other.m02) + (m11 * other.m12) + (m12 * other.m22) + (m13 * other.m32);
    tmp.m13 = (m10 * other.m03) + (m11 * other.m13) + (m12 * other.m23) + (m13 * other.m33);

    tmp.m20 = (m20 * other.m00) + (m21 * other.m10) + (m22 * other.m20) + (m23 * other.m30);
    tmp.m21 = (m20 * other.m01) + (m21 * other.m11) + (m22 * other.m21) + (m23 * other.m31);
    tmp.m22 = (m20 * other.m02) + (m21 * other.m12) + (m22 * other.m22) + (m23 * other.m32);
    tmp.m23 = (m20 * other.m03) + (m21 * other.m13) + (m22 * other.m23) + (m23 * other.m33);

    tmp.m30 = (m30 * other.m00) + (m31 * other.m10) + (m32 * other.m20) + (m33 * other.m30);
    tmp.m31 = (m30 * other.m01) + (m31 * other.m11) + (m32 * other.m21) + (m33 * other.m31);
    tmp.m32 = (m30 * other.m02) + (m31 * other.m12) + (m32 * other.m22) + (m33 * other.m32);
    tmp.m33 = (m30 * other.m03) + (m31 * other.m13) + (m32 * other.m23) + (m33 * other.m33);

    return tmp;
}

} //end namespace Engine

