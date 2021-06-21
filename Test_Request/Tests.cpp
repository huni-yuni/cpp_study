#include <cstdlib>
#include <ctime>
#include"CArray.h"
#include <algorithm>
#include<string>
#include<fstream>

#define NUMBER_COUNT 20
#define RANDOM_COUNT 10
#define STRING_COUNT 15
#define RANDOM_COUNT_STR 3

int getvalue_random(
    int _min,
    int _max
  )
{
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (_max - _min + 1) + _min);
}

int getStrNumber()
{
  std::ifstream inf("Test.txt");
  if (!inf)
    return 0;
  int i=-1;
  while (inf)
  {
    std::string temp;
    std::getline(inf, temp);
    i++;
  }
  inf.close();
  return i;

}
std::string getRandomword(
    int _max
  )
{
  std::ifstream inf("Test.txt");
  std::string temp;
  for (int i = 1; i <=getvalue_random(1, _max); i++)
  {
    std::getline(inf, temp);
  }
  inf.close();
  return temp;
}


void wait()
{
  std::string temp;
  std::cout << "Enter for continue:\n";
  std::getline(std::cin, temp);
}

void test_int()
{
  std::cout << "Work with numbers(int)\n";
  wait();
  srand(static_cast<unsigned int>(time(0)));
  rand();
  CArray<int>array;
  array.reserve(NUMBER_COUNT);

  std::cout << "Step 1:\n";
  wait();
  for (int i = 0; i < NUMBER_COUNT; i++)
    array.push_back(getvalue_random(0, 100));
  std::cout << array;

  std::cout << "Step 2:\n";
  wait();
  std::sort(&array[0], &array[0] + array.size());
  std::cout << array;

  std::cout << "Step 3:\n";
  wait();
  for (unsigned int i = 1; i < array.size(); ++i)
    array.erase(i);
  std::cout << array;

  std::cout << "Step 4:\n";
  wait();
  for (int i = 0; i < RANDOM_COUNT; i++)
    array.insert(getvalue_random(0, (array.size() - 1)), getvalue_random(0, 100));
  std::cout << array;

  std::cout << "Step 5:\n";
  wait();
  array.clear();
  std::cout << array;

  std::cout << "End of test.\n";
  wait();
}

void test_string()
{
  std::cout << "Work with objects(string)\n";
  wait();
  srand(static_cast<unsigned int>(time(0)));
  rand();
  CArray<std::string>array;
  array.reserve(STRING_COUNT);
  const int c_fileMax(getStrNumber());
  if (c_fileMax == 0)
  {
    std::cout << "Empty file!\n";
    wait();
    return;
  }

  std::cout << "Step 1:\n";
  wait();
  for (int i = 0; i < STRING_COUNT; i++)
    array.push_back(getRandomword(c_fileMax));
  std::cout << array;

  std::cout << "Step 2:\n";
  wait();
  std::sort(&array[0], &array[0] + array.size());
  std::cout << array;

  std::cout << "Step 3:\n";
  wait();
  for (int i = 0; i < array.size();)
  {
    if (array[i].find_first_of("abcde") != std::string::npos)
    {
      array.erase(i);
      continue;
    }
    ++i;
  }
  std::cout << array;

  std::cout << "Step 4:\n";
  wait();
  for (int i = 0; i < RANDOM_COUNT_STR; i++)
    array.insert(getvalue_random(0, (array.size() - 1)), getRandomword(c_fileMax));
  std::cout << array;

  std::cout << "End of test.\n";
  wait();
}

char getAnswer()
{
  while (1)
  {
    std::cout << "For Integer test enter[i], for String test enter[s], for exit enter[e]:\n";
    char answ;
    std::cin >> answ;
    std::cin.ignore(32767, '\n');

    if (answ == 'i' || answ == 's' || answ == 'e')
      return answ;
  }
}