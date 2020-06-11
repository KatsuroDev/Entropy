//
//  Vector3f.cpp
//  Complex Number Manip
//
//  Created by Thomas Lessard on 2020-06-10.
//  Copyright © 2020 Thomas Lessard. All rights reserved.
//

#include "Vector3f.h"
#include "Quaternion.h"

#include <math.h>


Vector3f& Vector3f::Rotate(float angle, const Vector3f& axis)
{
    // Convert to radians
    angle = angle / 180.0f * (float)M_PI;
    
    float sinHalfAngle = sinf(angle / 2.0f);
    float cosHalfAngle = cosf(angle / 2.0f);
    
    Quaternion rotation
    (axis.X * sinHalfAngle,
     axis.Y * sinHalfAngle,
     axis.Z * sinHalfAngle,
     cosHalfAngle);
    
    // Since all imaginary components are inverses,
    // it 'cancels' the quaternion, leaving the real part
    Quaternion conjugate = rotation.conjugate();
    
    // Multiplies the quaternion with this vector
    // The x, y and z components of the rotated quaternion
    // are now the rotated vector
    Quaternion rotated = (rotation * *this) * conjugate;
    
    X = rotated.X;
    Y = rotated.Y;
    Z = rotated.Z;
    
    return *this;
}
