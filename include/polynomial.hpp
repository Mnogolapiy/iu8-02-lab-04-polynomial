// Copyright 2022 Daniil mnogolapiy@gmail.com

#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_
#include <cmath>
#include <vector>

template <class T>
class Polynomial {
 public:
  ~Polynomial() {
    PolyDegree = 0;
    Data.clear();
  }

  Polynomial() : PolyDegree(0), Data({}) {}

  Polynomial(const std::vector<T>& copy)
      : PolyDegree(copy.size() - 1), Data(copy) {}

  Polynomial(const Polynomial<T>& polycopy)
      : PolyDegree(polycopy.Data.size()), Data(polycopy.Data) {}

  const T operator[](size_t i) const { return Data[i]; }

  T& operator[](size_t i) { return Data[i]; }

  std::vector<T> get_data() { return Data; }

  Polynomial& operator=(const std::vector<T>& copy) {
    Data = copy;
    PolyDegree = copy.size() - 1;
    return *this;
  }

  Polynomial& operator=(const Polynomial& poly) {
    if (&poly != this) {
      PolyDegree = poly.PolyDegree;
      Data = poly.Data;
    }
    return *this;
  }

  bool operator==(const Polynomial& comparison) const {
    if (PolyDegree != comparison.PolyDegree) {
      return false;
    } else {
      for (size_t i = 0; i < PolyDegree; ++i) {
        if (Data[i] != comparison[i]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Polynomial& comparison) const {
    return !(*this == comparison);
  }

  Polynomial& operator+=(Polynomial addable) {
    int dif = PolyDegree - addable.PolyDegree;
    if (dif < 0) {
      dif = -dif;
      for (size_t i = 0; i < this->PolyDegree + 1; ++i) {
        addable[dif] += Data[i];
        ++dif;
      }
      *this = addable;
    } else {
      for (size_t i = 0; i < addable.PolyDegree + 1; ++i) {
        Data[dif] += addable.Data[i];
        ++dif;
      }
    }
    return *this;
  }

  Polynomial operator+(const Polynomial& sum) {
    Polynomial A = *this;
    return (A += sum);
  }

  Polynomial& operator-=(Polynomial addable) {
    int dif = PolyDegree - addable.PolyDegree;
    if (dif < 0) {
      for (size_t i = 0; i < this->PolyDegree; ++i) {
        addable[-dif] -= Data[i];
        --dif;
      }
      *this = (addable * (-1));
    } else {
      for (size_t i = 0; i < addable.PolyDegree; ++i) {
        Data[dif] -= addable[i];
        ++dif;
      }
    }
    return *this;
  }

  Polynomial operator-(const Polynomial& addable) const{
    Polynomial A = *this;
    return (A -= addable);
  }

  Polynomial& operator*=(const T& increase) {
    for (size_t i = 0; i < PolyDegree + 1; i++) {
      Data[i] *= increase;
    }
    return *this;
  }

  Polynomial operator*(const T& increase) const {
    Polynomial A = *this;
    return (A *= increase);
  }

  Polynomial& operator*=(const Polynomial& increase) {
    Polynomial copy = *this;
    Data.clear();
    PolyDegree += increase.PolyDegree;
    Data = std::vector<T>(PolyDegree);
    for (size_t i = 0; i < copy.PolyDegree; i++) {
      for (size_t j = 0; j < copy.PolyDegree; j++) {
        Data[i + j] += copy.Data[i] * increase.Data[j];
      }
    }
    return *this;
  }

  Polynomial operator*(const Polynomial<T>& increase) const{
    Polynomial A = *this;
    return (A *= increase);
  }

  /*Polynomial result;
    result = (*this);
    const Polynomial<T> divOne = div;
    int deg;
    deg = div.PolyDegree;
    result.DataPoly = data.size();
    Polynomial<T> copy;
    copy.data = data;
    copy.DataPoly = DataPoly;
    T lamb;
    if (copy.data[copy.data.size() - 1] == 0) {
      copy.data.pop_back();
    }
    result.data = {};
    while (copy.DataPoly >= deg) {
      if (copy.data[copy.data.size() - 1] == 0) {
        copy.data.pop_back();

  result.data.push_back(0);
  continue;
}
lamb =
    copy.data[copy.data.size() - 1] / divOne.data[divOne.data.size() - 1];
copy -= divOne * lamb;
result.data.push_back(lamb);
if (copy.data[copy.data.size() - 1] == 0) {
  copy.data.pop_back();
}
copy.DataPoly--;
}
return result;*/

  Polynomial& operator/=(const Polynomial& div) {
    size_t def = PolyDegree - div.PolyDegree;
    std::vector<T> res;
    for (size_t i = 0; i < def + 1; ++i) {
        double divine = 1.0/div.Data[0];
        res[i] = Data[i] * divine;
        *this -= *this * divine;
    }
    Data = res;
    PolyDegree = def;
    return *this;
  }

  Polynomial operator/(const Polynomial<T>& div) const {
    Polynomial A = *this;
    return A /= div;
  }

  Polynomial operator%(const Polynomial<T>& div) const {
    Polynomial A = *this - (div * (*this/div));
    return A;
  }

  size_t get_deg() const { return PolyDegree; }

  T count(T x) {
    T result = 0;
    for (size_t i = 0; i < PolyDegree; i++) {
      result += pow(x, PolyDegree - i - 1) * Data[i];
    }
    return result;
  }

 private:
  size_t PolyDegree;
  std::vector<T> Data;
};

template <>
bool Polynomial<double>::operator==(
    const Polynomial<double>& comparison) const {
  if (PolyDegree != comparison.PolyDegree) {
    return false;
  } else {
    for (size_t i = 0; i < PolyDegree; ++i) {
      if (std::abs(comparison[i] - Data[i]) >
          std::numeric_limits<double>::epsilon()) {
        return false;
      }
    }
  }
  return true;
}

#endif  // INCLUDE_POLYNOMIAL_HPP_
