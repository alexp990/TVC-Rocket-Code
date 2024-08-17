#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion {
public:
    double w, x, y, z;

    Quaternion();
    Quaternion(double w, double x, double y, double z);
    static Quaternion fromEuler(double roll, double pitch, double yaw);
};

#endif
