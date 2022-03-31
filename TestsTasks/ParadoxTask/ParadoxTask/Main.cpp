#ifdef ONE_WAVE

#include "src/PathFinder_OneWave.h"

#endif

#ifdef TWO_WAVES

#include "src/PathFinder_TwoWaves.h"

#endif // 

#include <iostream>
#include <sstream>

void Print (
    const std::vector<int> & _Container
  )
{
  std::cout << "{ ";
  for (const int Member : _Container)
  {
    std::cout << Member << ' ';
  }
  std::cout << '}' << std::endl;
}


int main(int argc, char* argv[])
{
  std::vector<bool> Map = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 };
  std::vector<int> OutPath;

  bool Result = FindPath({ 2, 1 }, { 3, 4 }, Map, { 6, 6 }, OutPath);

  std::cout << (Result ? "TRUE" : "FALSE") << std::endl;;

  Print(OutPath);

  std::string tmp;
  std::getline(std::cin, tmp);

  return 0;
}