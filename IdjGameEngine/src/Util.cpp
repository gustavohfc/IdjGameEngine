#include "pch.h"
#include "Util.h"

double Util::RadToDeg(double rad) {
    return rad * 180 / M_PI;
}

double Util::DegToRad(double deg) {
    return deg * M_PI / 180;
}