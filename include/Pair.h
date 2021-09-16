#pragma once

template <class T>
class Pair
{
public:
  Pair(T, T);
  T getFirst();
  T getSecond();

private:
  T _first;
  T _second;
};

template <class T>
Pair<T>::Pair(T first, T second)
    : _first(first), _second(second)
{
}

template <class T>
T Pair<T>::getFirst()
{
  return _first;
}

template <class T>
T Pair<T>::getSecond()
{
  return _second;
}
