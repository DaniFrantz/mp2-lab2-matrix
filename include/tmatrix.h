// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE) {
          throw out_of_range("Your size is too small or too large");
      }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE) {
          throw out_of_range("Your size is too small or too large");
      }
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      if (pMem != NULL) {
          delete[] pMem;
      }
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz) {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v)
          return *this;
      if (sz != v.sz) {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind >= sz) throw "bad index";
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw "bad index";
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) throw "bad index";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw "bad index";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      unsigned k = 0;
      if (sz == v.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) { k = 1; break; }
          }
      }
      else { k = 1; }
      if (k == 0) { return true; }
      else return false;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      unsigned k = 0;
      if (sz == v.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) { k = 1; break; }
          }
      }
      else { k = 1; }
      if (k == 0) { return false; }
      else return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "sizes are not identical";
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "sizes are not identical";
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw "sizes are not identical";
      T xd = T();
      for (size_t i = 0; i < sz; i++)
          xd += pMem[i] * v.pMem[i];
      return xd;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz <= 0 || sz > MAX_MATRIX_SIZE) {
          throw out_of_range("Your size is too small or too large");
      }
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(sz);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;

  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      unsigned k = 0;
      if (sz == m.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != m.pMem[i]) { k = 1; break; }
          }
      }
      else { k = 1; }
      if (k == 0) { return true; }
      else return false;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      unsigned k = 0;
      if (sz == m.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != m.pMem[i]) { k = 1; break; }
          }
      }
      else { k = 1; }
      if (k == 0) { return false; }
      else return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              tmp.pMem[i] += v.pMem[j] * pMem[i][j];
          }
      }
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "sizes are not identical";
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "sizes are not identical";
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              for (size_t k = 0; k < sz; k++) {
                  tmp.pMem[i][j] += pMem[k][j] * m.pMem[i][k];
              }
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              istr >> v.pMem[j][i];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << v.pMem[j][i] << ' ';
          }
          ostr << '\n';
      }
      return ostr;
  }
};

#endif
