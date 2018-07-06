#include <math.h>
#include "camera.h"

namespace core {

#define PI 3.14159265

float _to_radians( float angle ) //TODO: need to move this into math lib
{
    return (float)((angle * PI) / 180);
}

Camera::Camera( Vector3f position, Vector2f frame_dimesions )
{
    this->position = position;
    pitch = 0;
    yaw = 0;
    fov = 70;
    near_plane = 2.0f;
    far_plane = 10000;

    set_projection_matrix(frame_dimesions.x, frame_dimesions.y);
    l_position.x = sin(yaw);
    l_position.z = -cos(yaw);
}

void Camera::update_projection_matrix( Vector2f frame_dimesions )
{
    set_projection_matrix(frame_dimesions.x, frame_dimesions.y);
}

void Camera::update_ortho_matrix( Vector2f frame_dimesions )
{
    set_ortho_matrix(frame_dimesions.x, frame_dimesions.y);
}

void Camera::set_transformation( Vector3f* translation, float rx, float ry, float rz, float scale )
{
    Vector3f vec_x(1, 0, 0);
    Vector3f vec_y(0, 1, 0);
    Vector3f vec_z(0, 0, 1);

    transformation_matrix.identity();
    transformation_matrix.translate(translation);
    transformation_matrix.rotate(_to_radians(rx), &vec_x);
    transformation_matrix.rotate(_to_radians(ry), &vec_y);
    transformation_matrix.rotate(_to_radians(rz), &vec_z);
    transformation_matrix.scale(scale);
}

void Camera::set_view_matrix()
{
    look_at(position.x,
            position.y,
            position.z,
            position.x + l_position.x,
            position.y + l_position.y, position.z + l_position.z,
            0.0f, 1.0f, 0.0f);
    Vector3f neg_pos;
    neg_pos.x = -position.x;
    neg_pos.y = -position.y;
    neg_pos.z = -position.z;
    view_matrix.translate(&neg_pos);
}

void Camera::move( float dx, float dy, float dz )
{
    if (dz != 0) {
        position.x += l_position.x * dz;
        position.z += l_position.z * dz;
    }

    if (dx > 0) {
        Vector3f up(0.0f, 1.0f, 0.0f);
        Vector3f cross = l_position.cross(up);
        Vector3f n_cross = cross.normalize();
        position.x += n_cross.x * (0.08f);
        position.z += n_cross.z * 0.08f;
    }
    else if (dx < 0) {
        Vector3f up(0.0f, 1.0f, 0.0f);
        Vector3f cross = l_position.cross(up);
        Vector3f n_cross = cross.normalize();
        position.x -= n_cross.x * 0.08f;
        position.z -= n_cross.z * 0.08f;
    }

    if (dy != 0) {
        position.y += dy;
    }
}

void Camera::rotate( float dyaw, float dpitch )
{
    if (dyaw != 0) {
        yaw += dyaw;
        l_position.x = sin(yaw);
        l_position.z = -cos(yaw);
    }
    if (dpitch != 0) {
        pitch += dpitch;
        if ( pitch > 0.89f ) {
            pitch = 0.89f;
        }
        if (pitch < -0.89f) {
            pitch = -0.89f;
        }
        l_position.y = sin(pitch);
    }
}

void Camera::set_projection_matrix( float width, float height )
{
    float aspectRatio = width / height;
    float y_scale = (float)((1.0f / tan(_to_radians(fov / 2.0f))) * aspectRatio);
    float x_scale = y_scale / aspectRatio;
    float frustum_length = far_plane - near_plane;

    projection_matrix.identity();
    projection_matrix.m00 = x_scale;
    projection_matrix.m11 = y_scale;
    projection_matrix.m22 = -((far_plane + near_plane) / frustum_length);
    projection_matrix.m23 = -1;
    projection_matrix.m32 = -((2 * near_plane * far_plane) / frustum_length);
    projection_matrix.m33 = 0;
}

#if 0
void ortho(float left, float right, float bottom, float top, float f_, float n_, core::Matrix4f* m) {
    m->m00 = 2 / (right - left);
    m->m11 = 2 / (top - bottom);
    m->m30 = -(right + left) / (right - left);
    m->m31 = -(top + bottom) / (top - bottom);
    m->m20 = 0;
    m->m21 = 0;
    m->m22 = -2 / (f_ - n_);
    m->m32 = - (f_ + n_)/ (f_ - n_);
    m->m33 = 1;
}
#endif

void Camera::set_ortho_matrix( float width, float height )
{
    ortho_matrix.m00 = 2 / (width - 0);
    ortho_matrix.m11 = 2 / (height - 0);
    ortho_matrix.m30 = -(width + 0) / (width - 0);
    ortho_matrix.m31 = -(height + 0) / (height - 0);
    ortho_matrix.m20 = 0;
    ortho_matrix.m21 = 0;
    ortho_matrix.m22 = -2 / (1 - (-1));
    ortho_matrix.m32 = - (1 + (-1))/ (1 - (-1));
    ortho_matrix.m33 = 1;
}

void _cross_prod( float x1, float y1, float z1, float x2, float y2, float z2, float res[3] )
{
    res[0] = y1*z2 - y2*z1;
    res[1] = x2*z1 - x1*z2;
    res[2] = x1*y2 - x2*y1;
}

void Camera::look_at( float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ )
{
    float f[3];

    // calculating the viewing vector
    f[0] = lookAtX - eyeX;
    f[1] = lookAtY - eyeY;
    f[2] = lookAtZ - eyeZ;

    float fMag, upMag;
    fMag = sqrtf(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    upMag = sqrtf(upX*upX + upY*upY + upZ*upZ);

    // normalizing the viewing vector/
    if (fMag != 0)
    {
        f[0] = f[0] / fMag;
        f[1] = f[1] / fMag;
        f[2] = f[2] / fMag;
    }

    // normalising the up vector
    if (upMag != 0)
    {
        upX = upX / upMag;
        upY = upY / upMag;
        upZ = upZ / upMag;
    }

    float s[3], u[3];

    _cross_prod(f[0], f[1], f[2], upX, upY, upZ, s);
    _cross_prod(s[0], s[1], s[2], f[0], f[1], f[2], u);

    view_matrix.m00 = s[0];
    view_matrix.m01 = u[0];
    view_matrix.m02 = -f[0];
    view_matrix.m03 = 0;
    view_matrix.m10 = s[1];
    view_matrix.m11 = u[1];
    view_matrix.m12 = -f[1];
    view_matrix.m13 = 0;
    view_matrix.m20 = s[2];
    view_matrix.m21 = u[2];
    view_matrix.m22 = -f[2];
    view_matrix.m23 = 0;
    view_matrix.m30 = 0;
    view_matrix.m31 = 0;
    view_matrix.m32 = 0;
    view_matrix.m33 = 1;
}

} //end namespace core
