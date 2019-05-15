#include "pch.h"
#include "Util.h"

float Util::RadToDeg(float rad) {
    return float(rad * 180 / M_PI);
}

float Util::DegToRad(float deg) {
    return float(deg * M_PI / 180);
}