#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"

class Quaternion {
public:
    double w, x, y, z;

    Quaternion(); 
    Quaternion(double w, double x, double y, double z); 
    

    void normalize(); 

    Quaternion normalized() const;

    Quaternion operator*(const Quaternion& q) const;
    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, double t);

    static Quaternion fromEuler(double roll, double pitch, double yaw); 
    Vector3 toEuler() const; 
};

#endif
