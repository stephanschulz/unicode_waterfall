#pragma once

#include "UWF.h"

class Ray : public OrientedHyperplane
{
public:
    Ray(ofVec2f pos, ofVec2f direction);
    ~Ray();

// Data fields.
private:
    ofVec2f position;
    ofVec2f direction;

// Public interface.
public:
    // Returns true iff this ray intersects the given line segment.
    bool detect_intersection(LineSegment seg);
    float dist_to_intersection(LineSegment seg);

    virtual ofVec2f getPoint1();
    virtual ofVec2f getPoint2();


    virtual ofVec2f getDirection();

    // 0 <= time <= 1.
    // For out purposes, collisions at endpoints are important for OBB - OBB intersections.
    virtual bool timeInBounds(float time);
};