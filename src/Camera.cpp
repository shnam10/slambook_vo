#include "myslam/Camera.h"

namespace myslam
{
    Camera::Camera()
    {
    }

    Vector3d Camera::world2camera(const Vector3d& p_w, const SE3d& T_c_w)
    {
        return T_c_w*p_w;
    }

    Vector3d Camera::camera2world(const Vector3d& p_c, const SE3d& T_c_w)
    {
        return T_c_w.inverse()*p_c;
    }

    Vector2d Camera::camera2pixel(const Vector3d& p_c)
    {
        return Vector2d(_fx * p_c(0) / p_c(2) + _cx, _fy * p_c(1) / p_c(2) + _cy);
    }

    Vector3d Camera::pixel2camera(const Vector2d& p_p, double depth)
    {
        return Vector3d( (p_p(0) - _cx ) * depth /_fx,
                         (p_p(1) - _cy ) * depth /_fy,
                         depth);
    }
    Vector3d Camera::pixel2word(const Vector2d& p_p, const SE3d& T_c_w, double depth)
    {
        return camera2world(pixel2camera(p_p, depth), T_c_w);
    }

    Vector2d Camera::world2pixel(const Vector3d& p_w, const SE3d& T_c_w)
    {
        return camera2pixel( world2camera(p_w, T_c_w));
    }
}