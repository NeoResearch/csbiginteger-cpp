# csBigInteger.cpp

## csBigInteger for C++

This project is part of the [csBigInteger](https://github.com/neoresearch/csBigInteger) macro project, a C# BigInteger implementation on C++ (portable format desired)

This project is an ongoing port of csBigInteger.js project: https://github.com/neoresearch/csBigInteger.js



### Why chosing C/C++ language for that?
Existing frameworks use high-level languages that may not be suitable for very lightweight architectures,
such as microcontrollers with very limited computing capabilities.

C/C++ is interoperable with nearly all existing languages, so the idea is to provide modules that can be
reused on other projects (on other languages too).

## How to Use

The project is very flexible, but still very simple to use.

### Using Hand Implementation

Just include the Single Header solution [src/HandBigInt.hpp](src/HandBigInt.hpp).

```{.cpp}
#include<iostream>
#include "HandBigInt.hpp"

int main() {
   HandBigInt big(10);
   big = big + 1;
   std::cout << big.toString() << std::endl;
   // output is 11

   return 0;
}
```

This is VERY innefficient, but it is tested against all BigInteger tests (except Online_Pack test, which takes so long...).
The BigInteger layer can be implemented with HandBigInt, GMP or Mono.

### Using BigInteger on C++ projects

If you have a C++ project and want to use csBigInteger, just:
```cpp
#include "BigInteger.h"
using namespace csbiginteger;
// ...
BigInteger big{"123456789123456789"};
big.ToString(); // prints '123456789123456789' in base 10
//
BigInteger big1{1};
BigInteger big2{2};
BigInteger big3 = big1 + big2;
big3.ToString(); // prints '3' in base 10
```

To compile this using GNU MP library (install its libs `-lgmp -lgmpxx`), just include flag `GMP_CSBIG` (or link together with `BigIntegerGMP.cpp`). Example with `GCC`: `g++ -DGMP_CSBIG yourfile.cpp -o output -lgmp -lgmpxx`.

Other options is to use `MONO_CSBIG` (or link against `BigIntegerMono.cpp`).
With Mono you may have an "equivalent" version of "original" C#.
It may be more efficient, but it's harder to build (requires `dotnet` and mono dependencies).

### Using the C-library on other languages (Python, etc)

To use this library on other languages, you need to build a static (`.a`) or shared library (`.dll`,`.so`). You can find some experimental versions on `build` folder, but it's safer to build by yourself.

The process is similar, using C header `csBigIntegerLib.h` and also`csBigIntegerLib.cpp` (see `makefile` for an example).

### One final option: using C-library to import code from other languages

It may look crazy, but `csBigIntegerLib.h` is also useful to "get external implementations" from other languages (like javascript, for example). In this case, your C++ code should `#include "csBigIntegerLibClass.hpp"` and `using namespace csbigintegerlib`.
The implementation may be provided by C++ itself (via `csBigIntegerLib.cpp`) or any other language you like.

## Build Instructions
There are currently two implementations for `BigInteger.h`: `BigIntegerGMP.cpp` or `BigIntegerMono.cpp`.

Getting submodules: `git submodule update --init --recursive` and `git pull --recurse-submodules`

### GNU MP implementation
On debian-based systems (or ubuntu), just type `make vendor` (it will install `libgmp-dev` package). 

### Mono implementation

Mono implementation will generate a `csbiginteger_dotnet.dll` and load it through `csbiginteger_mono.so`. It is much more complex process, but it guarantees that __original__ BigInteger C# library is being used. 
Right now, tests are passing for both gmp and mono implementations, so gmp C++ native implementation is much preferred (and more lightweight) on practice.

If you want to go this way, you will need mono:

```
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
sudo apt install apt-transport-https ca-certificates
echo "deb https://download.mono-project.com/repo/ubuntu stable-xenial main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
sudo apt update
sudo apt install mono-complete
```

### tests

It will also configure test library (as long as you cloned this project with `--submodules` too).
To test, just run `make test`.


## C++ Standard
Currently, C++11 is adopted, in order to keep the best compatibility between conversors and compilers. However, it is recommended to migrate to C++17 as soon as possible, if this does not break compatibility with any existing modules and tools.

Let's please follow the [CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines).

#### vscode IDE
If using vscode IDE, it is recommended to install the following extensions:
* C/C++ (currently 0.23.0-insiders2)
* C++ Intellisense (currently 0.2.2)
* GoogleTest Adapter (currently 1.8.3)

#### C++ Format Style
The currently adopted style for C++ is `Mozilla`, with indentation level set to 3.
Recommended configuration for vscode:
```json
{
    "[cpp]": {
        "editor.tabSize" : 3,
        "editor.detectIndentation": false
    },
    "C_Cpp.clang_format_fallbackStyle": "{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}"
}
```

#### Variable Naming Style
The naming style for variables and methods is based on `C#` language. 
So, CamelCase is used and `public` variables start with upper-case letters, while `private` and `local` variables start with lower-case.
The idea is to preseve maximum compatibility with reference project (which is on C#).

Anything that is beyond the scope of the reference project can use classic CamelCase `C++` naming (for example, starting variables with lower-case).

### License

Code follows `MIT License`.

Implementation `BigIntegerGMP.cpp` (class implementation of standard `BigInteger.h`) is `LGPLv3`. The reason is that this implementation depends on GNU MP Bignum Library (licensed LGPLv3 since version 6), what means that all modifications of `BigIntegerGMP.cpp`, or usage of its code (even partially) on other projects should also adopt `LGPLv3` (not MIT License). 

Implementation `BigIntegerMono.cpp` depends on Mono license, which is also MIT License.

The binaries generated by this project (`csbiginteger_gmp.so` or `csbiginteger_mono.so`) can be freely used on other projects, regardless of license.
