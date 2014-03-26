#include "Rcpp.h"
using namespace Rcpp;
using namespace std;

#ifndef uint
typedef unsigned int uint;
#endif

template <class T>
inline T quantile(const T* d, const uint size, const double q)
{
  if (size == 0) return T(0);
  if (size == 1) return d[0];
  if (q <= 0) return *std::min_element(d, d + size);
  if (q >= 1) return *std::max_element(d, d + size);

  double pos = (size - 1) * q;
  uint ind = uint(pos);
  double delta = pos - ind;
  vector<T> w(size); std::copy(d, d + size, w.begin());
  std::nth_element(w.begin(), w.begin() + ind, w.end());
  T i1 = *(w.begin() + ind);
  T i2 = *std::min_element(w.begin() + ind + 1, w.end());
  return i1 * (1.0 - delta) + i2 * delta;
}

template <class T>
inline T quantile(const vector<T>& v, const double q)
  { return quantile(&v[0], v.size(), q); }

// [[Rcpp::export]]
double elogLik(std::vector<double> model, std::vector<double> data, double min, double max, int breaks)
{
  std::vector<double> m;
  std::vector<double> d;
  for (unsigned int i=0; i<model.size(); i++)
    if (model[i]>=min && model[i]<=max)
      m.push_back(model[i]);
  for (unsigned int i=0; i<data.size(); i++)
    if (data[i]>=min && data[i]<=max)
      d.push_back(data[i]);
  std::vector<double> q(breaks+1);
  for (unsigned int i = 0; i <= breaks; ++i)
    q[i] = quantile(m, i / (breaks * 1.0));
  q[0] = min;
  q[breaks] = max;
  std::vector<double> p(breaks);
  double s = 0;
  for (unsigned int i = 0; i < breaks; ++i) {
    p[i] = 1 / (q[i+1] - q[i]);
    s += p[i];
  }
  for (unsigned int i = 0; i < breaks; ++i) {
    p[i] = p[i] / s;
  }
  double loglik = 0;
  for (unsigned int i = 0; i < data.size(); i++) {
    for (unsigned int j = 1; j < breaks+1; j++) {
      if (data[i]<=q[j]) {
        double z = log(p[j-1]);
        loglik += z;
        break;
      }
    }
  }
  return -loglik;
}