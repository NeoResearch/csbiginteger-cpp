
#include <assert.h>
#include <iostream>

#include "BigInteger.h"

using namespace csbiginteger;

int
main()
{
   std::cout << "demonstration for csBigInteger (Engine: '" << BigInteger::getEngine() << "')" << std::endl;
   std::cout << "usage: <operation> <enter> <number> <enter> <number <enter>" << std::endl;
   std::cout << "avaliable operations are: + - / * % ^ > < 0x 0b (0x and 0b are conversions to hex big endian and binary)" << std::endl;
   while (true) {
      std::cout << std::endl << "please type the operation: ";

      std::string op;
      std::cin >> op;

      int num = 0;
      if ((op == "+") || (op == "-") || (op == "/") || (op == "*") || (op == "%") || (op == "^") || (op == ">") || (op == "<"))
         num = 2;
      if ((op == "0x") || (op == "0b"))
         num = 1;
      assert(num > 0);
      std::cout << "expects " << num << " number(s)" << std::endl;

      std::cout << "please type first number (in decimal, or unsigned hex with prefix 0x, or binary prefix 0b):";
      std::string sbig;
      std::cin >> sbig;

      BigInteger big1(sbig);
      std::cout << "number is (decimal) '" << big1.ToString(10) << "'" << std::endl;

      if (num > 1) {
         std::cout << "please type second number (in decimal):";
         std::string sbig2;
         std::cin >> sbig2;

         BigInteger big2(sbig2);
         std::cout << "number is '" << big2.ToString(10) << "'" << std::endl;

         std::cout << "result: ";

         if (op == "+")
            std::cout << (big1 + big2).ToString(10) << std::endl;
         if (op == "-")
            std::cout << (big1 - big2).ToString(10) << std::endl;
         if (op == "/")
            std::cout << (big1 / big2).ToString(10) << std::endl;
         if (op == "*")
            std::cout << (big1 * big2).ToString(10) << std::endl;
         if (op == "%")
            std::cout << (big1 % big2).ToString(10) << std::endl;
         if (op == "^")
            std::cout << BigInteger::Pow(big1, big2.toInt()).ToString(10) << std::endl;
         if (op == ">")
            std::cout << (big1 > big2) << std::endl;
         if (op == "<")
            std::cout << (big1 < big2) << std::endl;

         continue;
      }

      std::cout << "conversion: ";
      if (op == "0x")
         std::cout << big1.ToString(16) << std::endl;
      if (op == "0b")
         std::cout << big1.ToString(2) << std::endl;
   }

   return 0;
}
