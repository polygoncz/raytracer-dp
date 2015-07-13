#include "film.h"

using namespace tracer;

Film::Film(const Film& film)
    : width(film.width),
      height(film.height),
      size(film.size),
      gamma(film.gamma),
      invGamma(film.invGamma)
{

}

Film::Film(int width, int height, Real size, Real gamma /* = 1.f */, Real invGamma /* = 1.f */)
    : width(width),
      height(height),
      size(size),
      gamma(gamma),
      invGamma(1.f / gamma)
{

}

Film::~Film()
{
}
