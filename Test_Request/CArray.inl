#ifndef CARRAY_INL
#define CARRAY_INL
#include "CArray.h"
#include <assert.h>
template <typename TData>
CArray<TData>::CArray()
{
  m_lenght = 0;
  m_capacity = 0;
  m_data = nullptr;
}

template <typename TData>
CArray<TData>::CArray(
    const CArray& _array
  )
{
  m_lenght = _array.m_lenght;
  m_capacity = _array.m_capacity;

  if (m_capacity)
  {
    m_data = new TData[m_capacity];

    for (unsigned int i = 0; i < m_lenght; i++)
      m_data[i] = _array.m_data[i];
  }
  else
    m_data = nullptr;
}

template <typename TData>
CArray<TData>::~CArray()
{
  delete[] m_data;
}

template <typename TData>
CArray<TData>& CArray<TData>::operator=(
    const CArray& _array
  )
{
  if (this == &_array)
    return *this;

  delete[] m_data;

  m_lenght = _array.m_lenght;

  if (m_capacity < m_lenght)
    m_capacity = m_lenght;

  if (m_capacity)
  {

    m_data = new TData[m_capacity];

    for (unsigned int i = 0; i < m_lenght; ++i)
      m_data[i] = _array.m_data[i];
  }
  else
    m_data = nullptr;

  return *this;
}

template <typename TData>
void CArray<TData>::reserve(
    unsigned int _capacity
  )
{
  if (_capacity > m_capacity)
  {
    CArray temp(*this);
    m_capacity = _capacity;
    *this = temp;
  }
}

template <typename TData>
void CArray<TData>::push_back(
    const TData& _value
  )
{
  if ((m_lenght + 1) > m_capacity)
    this->reserve((m_capacity + 1) * 2);

  m_data[m_lenght] = _value;
  m_lenght++;
}

template <typename TData>
void CArray<TData>::insert(
    unsigned int _index,
    const TData& _value
  )
{
  if (_index >= m_lenght)
    return;
  else
  {
    TData temp = m_data[m_lenght - 1];
    this->push_back(temp);
    for (unsigned int i = (m_lenght - 2); i > _index; i--)
      m_data[i] = m_data[i - 1];
    m_data[_index] = _value;
  }
}

template <typename TData>
void CArray<TData>::erase(
    unsigned int _index
  )
{
  if (_index >= m_lenght)
    return;
  else
  {
    m_lenght--;
    for (unsigned int i = _index; i < m_lenght; i++)
      m_data[i] = m_data[i + 1];
  }
}

template <typename TData>
void CArray<TData>::clear()
{
  m_lenght = 0;
}

template <typename TData>
unsigned int CArray<TData>::size() const
{
  return m_lenght;
}

template <typename TData>
unsigned int CArray<TData>::capacity() const
{
  return m_capacity;
}

template <typename TData>
TData& CArray<TData>::operator[](
    unsigned int _index
  )
{
  assert(_index < m_lenght);
  return m_data[_index];
}

template <typename TData>
std::ostream& operator<< (
    std::ostream& out,
    const CArray<TData>& _array
  )
{
  if (_array.m_lenght)
  {
    for (unsigned int i = 0; i < _array.m_lenght; i++)
      out << "[" << i << "] = " << _array.m_data[i] << '\n';
  }
  else
    out << "Array is empty\n";

  return out;
}



#endif