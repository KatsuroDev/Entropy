//
//  Vector3f.h
//  Complex Number Manip
//
//  Created by Thomas Lessard on 2020-06-10.
//  Copyright © 2020 Thomas Lessard. All rights reserved.
//

#pragma once

class Vector3f
{
public:
    float X, Y, Z;
    
    Vector3f(float x, float y, float z)
        : X(x), Y(y), Z(z)
    {
    }
    
    float Length();
    
    // Modifies the instance
    Vector3f& Normalize();
    
    // Modifies the instance
    Vector3f& Rotate(float angle, const Vector3f& axis);
};
