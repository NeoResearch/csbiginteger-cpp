
#include <assert.h>
#include <iostream>

#include "HandBigInt.hpp"

int
main()
{
   std::cout << "demonstration for HandBigInt" << std::endl;
   std::cout << "usage: <operation> <enter> <number> <enter> <number <enter>" << std::endl;
   std::cout << "avaliable operations are: + - / * % ^ > < 0x 0b (0x and 0b are conversions to hex big endian and binary)" << std::endl;
   while (true) {
      std::cout << "please type the operation: ";

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

      HandBigInt big1;
      if ((sbig.length() >= 2) && (sbig[0] == '0') && (sbig[1] == 'x'))
         big1 = HandBigInt::fromUnsignedHex(sbig);
      else if ((sbig.length() >= 2) && (sbig[0] == '0') && (sbig[1] == 'b'))
         big1 = HandBigInt::fromUnsignedBin(sbig);
      else
         big1 = HandBigInt(sbig);
      std::cout << "number is (decimal) '" << big1.toString() << "'" << std::endl;

      if (num > 1) {
         std::cout << "please type second number (in decimal):";
         std::string sbig2;
         std::cin >> sbig2;

         HandBigInt big2(sbig2);
         std::cout << "number is '" << big2.toString() << "'" << std::endl;

         std::cout << "result: ";

         if (op == "+")
            std::cout << (big1 + big2).toString() << std::endl;
         if (op == "-")
            std::cout << (big1 - big2).toString() << std::endl;
         if (op == "/")
            std::cout << (big1 / big2).toString() << std::endl;
         if (op == "*")
            std::cout << (big1 * big2).toString() << std::endl;
         if (op == "%")
            std::cout << (big1 % big2).toString() << std::endl;
         if (op == "^")
            std::cout << HandBigInt::pow(big1, big2.get_ui()).toString() << std::endl;
         if (op == ">")
            std::cout << (big1 > big2) << std::endl;
         if (op == "<")
            std::cout << (big1 < big2) << std::endl;

         continue;
      }

      std::cout << "conversion: ";
      if (op == "0x")
         std::cout << big1.get_str(16) << std::endl;
      if (op == "0b")
         std::cout << big1.get_str(2) << std::endl;
   }

   return 0;
}
