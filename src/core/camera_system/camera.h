#if !defined(CAMERA_H)

#include "../core_common.h"
#include "../math/vector.h"
#include "../math/matrix.h"

namespace core {

    class CORE_API Camera {
    public:
    Vector3f position;
    Vector3f l_position;
    Matrix4f projection_matrix;
    Matrix4f view_matrix;
    Matrix4f transformation_matrix;
    Matrix4f ortho_matrix;
    float pitch;
    float yaw;
    float roll;
    float fov;
    float near_plane;
    float far_plane;

    Camera( Vector3f position, Vector2f frame_dimesions );
    void set_transformation( Vector3f* translation, float rx, float ry, float rz, float scale );
    void set_view_matrix();
    void move( float dx, float dy, float dz );
    void rotate( float dyaw, float dpitch );
    void update_projection_matrix( Vector2f frame_dimesions );
    void update_ortho_matrix( Vector2f frame_dimesions );

    private:
    void set_projection_matrix( float width, float height );
    void set_ortho_matrix( float width, float height );
    void look_at( float eyeX, float eyeY, float eyeZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ );
    };

} //end namespace core

#define CAMERA_H
#endif
