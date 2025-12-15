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
  size_t getting_lineX()
  {
      unsigned flag = 0;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i][0] == 0){
              flag = 1;
              for (size_t K = 0; K < sz - i; K++) {
                  if (pMem[i + K][K] == 0) {
                      flag = 1;
                  }
                  else {
                      flag = 0; break;
                  }
              }
          }
          else flag = 0;
          if (flag == 1) { return i; }
          
      }
      return sz;
  }
  size_t getting_lineX() const
  {
      unsigned flag = 0;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i][0] == 0) {
              flag = 1;
              for (size_t K = 0; K < sz - i; K++) {
                  if (pMem[i + K][K] == 0) {
                      flag = 1;
                  }
                  else {
                      flag = 0; break;
                  }
              }
          }
          else flag = 0;
          if (flag == 1) { return i; }
          
      }
      return sz;
  }
  size_t getting_lineY()
  {
      unsigned flag = 0;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[0][i] == 0){
              flag = 1;
              for (size_t K = 0; K < sz - i; K++) {
                  if (pMem[K][i + K] == 0) {
                      flag = 1;
                  }
                  else {
                      flag = 0; break;
                  }
              }
          }
          else flag = 0;
          if (flag == 1) { return i; }
          
      }
      return sz;
  }
  size_t getting_lineY() const
  {
      unsigned flag = 0;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[0][i] == 0) {
              flag = 1;
              for (size_t K = 0; K < sz - i; K++) {
                  if (pMem[K][i + K] == 0) {
                      flag = 1;
                  }
                  else {
                      flag = 0; break;
                  }
              }
          }
          else flag = 0;
          if (flag == 1) { return i; }
         
      }
      return sz;
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

template<typename T>
class TBendedMatrix : private TDynamicVector<T>
{
    using TDynamicVector<T>::pMem;
    using TDynamicVector<T>::sz;
    size_t lineX, lineY, oldsz;
    
public:
    TBendedMatrix(TDynamicMatrix<T> v) : lineX(v.getting_lineX()), lineY(v.getting_lineY())
    {
        oldsz = v.size();
        sz = 0;
        for (size_t i = 0; i < lineX; i++) {
            sz += v.size() - i;
        }
        for (size_t i = 1; i < lineY; i++) {
            sz += v.size() - i;
        }
        pMem = new T[sz];
        size_t l = 0;
        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = 0; j < v.size(); j++) {
                if (v[i][j] != 0 && l < sz) {
                    
                    pMem[l] = v[i][j];
                    l += 1;
                }
            }
        }
    }
    TDynamicMatrix<T> ReturnMatrix() const
    {
        TDynamicMatrix<T> tmp(oldsz);
        int temp = 0;
        size_t sdvigdown = 0, sdvigup = 0;;
        size_t num = 0;
        temp = temp * 0;
        for (size_t x = 0; x < oldsz; x++) {
            if (x >= lineX) {
                sdvigup += 1;
            }
            for (size_t y = 0; y < oldsz; y++) {
                
                if (sdvigup <= y && y < lineY + sdvigdown ) {
                    tmp[x][y] = pMem[num];

                    num += 1;

                }
            }
            sdvigdown += 1;
        }
        return tmp;
    }
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
    size_t size() { return sz; }

    friend istream& operator>>(istream& istr, TBendedMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        istr >> lineX;
        istr >> lineY;
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TBendedMatrix& v)
    {
        ostr << v.ReturnMatrix();
        return ostr;
    }
};

template<typename T>
class TSparseMatrix // CSR
{
private:
    size_t num_of_columns;
    size_t num_of_strings;
    size_t size;
    T* pMem1; // Скока переменных за прошедшие колонны
    T* pMem2; // Индекс столбца
    T* pMem3; // Че хранится

public:
    TSparseMatrix(TDynamicMatrix<T> m) : num_of_columns(m.size()), num_of_strings(m.size())
    {
        pMem1 = new T[num_of_strings];
        size_t counter = 0, goydaunter = 0;
        for (size_t i = 0; i < m.size(); i++) {
            for (size_t j = 0; j < m.size(); j++) {
                if (m[j][i] != 0) {
                    counter += 1;
                }
            }
            pMem1[goydaunter] = counter;
            goydaunter += 1;
        }
        pMem2 = new T[counter];
        pMem3 = new T[counter];
        size = counter;
        goydaunter = 0;
        for (size_t i = 0; i < m.size(); i++) {
            for (size_t j = 0; j < m.size(); j++) {
                if (m[j][i] != 0) {
                    pMem2[goydaunter] = j;
                    pMem3[goydaunter] = m[j][i];
                    goydaunter += 1;
                }
            }
        }


    }
    ~TSparseMatrix()
    {
        if (pMem1 != NULL) {
            delete[] pMem1;
        }
        if (pMem2 != NULL) {
            delete[] pMem2;
        }
        if (pMem3 != NULL) {
            delete[] pMem3;
        }
    }
    T& getRow(size_t ind)
    {
        if (ind < 0 || ind >= num_of_strings) throw out_of_range("no");
        return pMem1[ind];
    }
    T& getIndCol(size_t ind)
    {
        if (ind < 0 || ind >= size) throw out_of_range("no");
        return pMem2[ind];
    }
    T& getValue(size_t ind)
    {
        if (ind < 0 || ind >= size) throw out_of_range("no");
        return pMem3[ind];
    }
    size_t getSize() { return size; }
    size_t num_of_col() { return num_of_columns; }
    size_t num_of_str() { return num_of_strings; }
    TDynamicMatrix<T> ReturnMatrix() const
    {
        TDynamicMatrix<T> tmp(num_of_strings);
        int here = 0, itwas = 0;
        for (size_t i = 0; i < num_of_strings; i++) {
            if (i == 0) { here = pMem1[i]; }
            else { here = pMem1[i] - pMem1[i - 1]; }
            for (size_t j = 0; j < here; j++) {
                tmp[pMem2[j + itwas]][i] = pMem3[j + itwas];
            }
            itwas += here;
        }
        return tmp;
    }
    friend istream& operator>>(istream& istr, TSparseMatrix& v)
    {
        istr >> v.num_of_columns;
        istr >> v.num_of_strings;
        istr >> v.size;
        pMem1 = new T[v.num_of_strings];
        pMem2 = new T[v.size];
        pMem3 = new T[v.size];
        for (size_t i = 0; i < v.num_of_strings; i++) {
            istr >> v.pMem1[i];
        }
        for (size_t i = 0; i < v.size; i++) {
            istr >> v.pMem2[i];
        }
        for (size_t i = 0; i < v.size; i++) {
            istr >> v.pMem3[i];
        }

        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TSparseMatrix& v)
    {
        ostr << v.ReturnMatrix();
        return ostr;
    }
};
#endif
