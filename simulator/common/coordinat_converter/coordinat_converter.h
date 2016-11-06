#ifndef __COORDINAT_CONVERTER__
#define __COORDINAT_CONVERTER__
#include "../SMat.h"

//преобразует xyz (метры) d широту, долготу и высоту
SVec ecef_to_ned(double X, double Y, double Z);

#endif // __COORDINAT_CONVERTER__