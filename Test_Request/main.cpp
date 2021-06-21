#include"Tests.h"
#include<iostream>
int main()
{
  while (1)
  {
    switch (getAnswer())
    {
    case 'i':test_int();
      break;
    case 's':test_string();
      break;
    case'e':
      return 0;
    default:
      return 1;
    }
  }
}