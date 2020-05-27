
SRC_PATH=../src
# gtest
GTEST_PATH=./libgtest/build/googletest
GMOCK_PATH=./libgtest/build/googlemock
GTEST_INCLUDE=./libgtest/googletest/include
GMOCK_INCLUDE=./libgtest/googlemock/include

all:
	@echo "please type 'make test'"

test: clean csBigIntegerHAND.test run_test_hand csBigIntegerGMP.test run_test_gmp csBigIntegerLib.test run_test_lib #csBigIntegerMono.test run_test_mono
	@echo "Finished tests"

# only run Mono tests in 'hard' mode
test-hard: test csBigIntegerMono.test run_test_mono csBigIntegerGMP-hard.test csBigIntegerMono-hard.test
	@echo "Executing hard tests"
	./csBigIntegerGMP-hard.test
	./csBigIntegerMono-hard.test

# $(SRC_PATH)/BigIntegerGMP.cpp
csBigIntegerGMP.test : csBigInteger.Test.cpp
	@echo "Building tests using GMP library (requires 'libgmp')"
	g++ -DCATCH_CONFIG_MAIN -DGMP_CSBIG --coverage -g -O0 --std=c++11 -I$(SRC_PATH) -I../thirdparty $< -o $@ -lgmp -lgmpxx

csBigIntegerHAND.test : csBigInteger.Test.cpp
	@echo "Building tests using HAND library"
	g++ -DCATCH_CONFIG_MAIN -DHAND_CSBIG --coverage -g -O0 --std=c++11 -I$(SRC_PATH) -I../thirdparty $< -o $@

run_test_hand: csBigIntegerHAND.test
	./csBigIntegerHAND.test -d yes ~*Online_Pack_Divisor*

run_test_gmp: csBigIntegerGMP.test
	./csBigIntegerGMP.test -d yes

csBigIntegerLib.test : csBigInteger.Test.cpp
	@echo "Building LIBRARY tests using GMP library (requires 'libgmp')"
	g++ -DCATCH_CONFIG_MAIN -DGMP_CSBIG -DTEST_CSBIGINTEGER_LIB --coverage -g -O0 --std=c++11 -I$(SRC_PATH) -I../thirdparty $< -o $@ $(SRC_PATH)/csBigIntegerLib.cpp -lgmp -lgmpxx

run_test_lib: csBigIntegerLib.test
	./csBigIntegerLib.test -d yes

run_test_mono: csBigIntegerMono.test
	./csBigIntegerMono.test -d yes

csBigIntegerMono.test : csBigInteger.Test.cpp
	@echo "Building tests with Mono/Dotnet (requires 'dotnet')" 
	dotnet build ../src/dotnet/ -c Release
	cp ../src/dotnet/bin/Release/netstandard2.0/csbiginteger_dotnet.dll .
	mono --aot -O=all csbiginteger_dotnet.dll
	g++ --coverage -g -O0 -I../thirdparty --std=c++11 `pkg-config --cflags --libs mono-2` -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerMono.cpp -lgmp -lgmpxx -lpthread -ldl


csBigIntegerGMP-hard.test : csBigInteger-hard.Test.cpp
	g++ -Ofast --std=c++11 -I$(SRC_PATH) -I../thirdparty -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerGMP.cpp -lgmp -lgmpxx -lpthread -ldl


csBigIntegerMono-hard.test : csBigInteger-hard.Test.cpp
	dotnet build ../src/dotnet/ -c Release
	cp ../src/dotnet/bin/Release/netstandard2.0/csbiginteger_dotnet.dll .
	mono --aot -O=all csbiginteger_dotnet.dll
	g++ --coverage -g -O0  -I../thirdparty --std=c++11 `pkg-config --cflags --libs mono-2` -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerMono.cpp -lgmp -lgmpxx -lpthread -ldl


test-coverage:
	mkdir -p reports
	lcov --directory . --capture --output-file reports/app.info
	(cd reports && genhtml app.info)

# cleaning tests
clean:
	rm -f *.test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
