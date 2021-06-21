#pragma once
#include <cstddef>
#include <iostream>
template <typename TData>
class CArray
{
public:

  CArray();

  CArray(
      const CArray& _array
    );

  ~CArray();

  CArray& operator=(
      const CArray& _array
    );

  void reserve(
      unsigned int _capacity
    );

  void push_back(
      const TData& _value
    );

  void insert(
      unsigned int _index,
      const TData& _value
    );

  void erase(
      unsigned int _index
    );

  void clear();

  unsigned int size() const;

  unsigned int capacity() const;

  TData& operator[](
      unsigned int _index
    );

  template<typename FData>
  friend std::ostream& operator<< (
      std::ostream& out, 
      const CArray<FData>& _array
    );

protected:

  unsigned int m_lenght;
  unsigned int m_capacity;
  TData* m_data;
};

#include"CArray.inl"