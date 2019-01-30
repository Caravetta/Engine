#include <math.h>
#include "Engine.h"
#include "math_utils.h"
#include "core_common.h"

namespace Engine {

void generate_perspective_matrix( Camera* camera )
{
    //camera->projection_matrix = perspective(to_radians(90.0f), (float)width / (float)height, 0.01f, 1000.0f);
    camera->projection_matrix = perspective(to_radians(camera->field_of_view),
                                            camera->aspect_ratio,
                                            camera->near_plane,
                                            camera->far_plane );
}

void generate_FPS_view_matrix( Camera* camera )
{
    float cos_pitch = cos(camera->transform.rotation.y);
    float sin_pitch = sin(camera->transform.rotation.y);
    float cos_yaw = cos(camera->transform.rotation.x);
    float sin_yaw = sin(camera->transform.rotation.x);

    Vector3f eye (camera->transform.position.x,
                  camera->transform.position.y,
                  camera->transform.position.z);

    Vector3f x_axis( cos_yaw, 0, -sin_yaw );
    Vector3f y_axis( sin_yaw * cos_pitch, cos_pitch, cos_yaw * sin_pitch);
    Vector3f z_axis( sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw);

    camera->view_matrix.m00 = x_axis.x;
    camera->view_matrix.m10 = x_axis.y;
    camera->view_matrix.m20 = x_axis.z;

    camera->view_matrix.m01 = y_axis.x;
    camera->view_matrix.m11 = y_axis.y;
    camera->view_matrix.m21 = y_axis.z;

    camera->view_matrix.m02 = z_axis.x;
    camera->view_matrix.m12 = z_axis.y;
    camera->view_matrix.m22 = z_axis.z;

    camera->view_matrix.m30 = -dot( x_axis, eye );
    camera->view_matrix.m31 = -dot( y_axis, eye );
    camera->view_matrix.m32 = -dot( z_axis, eye );
    camera->view_matrix.m33 = 1;


}

} //end namespace core
