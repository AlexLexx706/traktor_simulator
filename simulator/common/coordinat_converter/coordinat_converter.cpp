#include "coordinat_converter.h"
#include <math.h>
#include <iostream>

const double a = 6378160.000;
const double aa = a * a;
const double b = a * (1.0 - 1.0/298.25);
const double bb = b * b;
const double ee = 1 - (bb / aa);


// рассчёт по формуле из https://en.wikipedia.org/wiki/Geographic_coordinate_conversion
SVec ecef_to_ned(double X, double Y, double Z) {
    double ZZ = Z * Z;
    double r = sqrt(X * X + Y * Y);
    double rr = r * r;
    double EE = aa - bb;
    double F = 54.0 * bb * ZZ;
    double G = rr + (1.0 - ee) * ZZ - ee * EE;
    double C = (ee * ee * F * rr) / pow(G, 3);
    double S = cbrt(1.0 + C + sqrt(C * C + 2.0 * C));
    double P = F / (3.0 * pow(S + 1.0 / S + 1.0, 2) * pow(G, 2 ));
    double Q = sqrt(1.0 + 2.0 * ee * ee * P);
    double r0 = (-(P * ee * r) / (1.0 + Q)) + sqrt(0.5 * aa * (1.0 + 1.0 / Q) - (P * (1.0 - ee) * ZZ) / (Q * (1.0 + Q)) - 0.5 * P * rr);
    double U = sqrt(pow(r - ee * r0, 2) + ZZ);
    double V = sqrt(pow(r - ee * r0, 2) + (1.0 - ee) * ZZ);
    double Z0 = (bb * Z) / (a * V);
    double h = U * (1.0 - bb / (a * V));
    double fi = atan((Z + ee * Z0) / r);
    double lambda = atan2(Y, X);
    //std::cout << "r:" << r << " U:" << U << " V:" << V << std::endl;
    return SVec(fi, lambda, h);
}
