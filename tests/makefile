
SRC_PATH=../src
# gtest
GTEST_PATH=./libgtest/build/googletest
GMOCK_PATH=./libgtest/build/googlemock
GTEST_INCLUDE=./libgtest/googletest/include
GMOCK_INCLUDE=./libgtest/googlemock/include

all:
	@echo "please type 'make test'"

test: clean csBigIntegerGMP.test run_test_gmp csBigIntegerMono.test run_test_mono
	@echo "Finished tests"

test-hard: test csBigIntegerGMP-hard.test csBigIntegerMono-hard.test
	@echo "Executing hard tests"
	./csBigIntegerGMP-hard.test
	./csBigIntegerMono-hard.test

csBigIntegerGMP.test : csBigInteger.Test.cpp
	@echo "Building tests using GMP library (requires 'libgmp')"
	g++ --coverage -g -O0 --std=c++11 -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerGMP.cpp -lgmp -lgmpxx -lpthread -ldl

run_test_gmp: csBigIntegerGMP.test
	./csBigIntegerGMP.test

run_test_mono: csBigIntegerMono.test
	./csBigIntegerMono.test

csBigIntegerMono.test : csBigInteger.Test.cpp
	@echo "Building tests with Mono/Dotnet (requires 'dotnet')" 
	dotnet build ../src/dotnet/ -c Release
	cp ../src/dotnet/bin/Release/netstandard2.0/csbiginteger_dotnet.dll .
	mono --aot -O=all csbiginteger_dotnet.dll
	g++ --coverage -g -O0 --std=c++11 `pkg-config --cflags --libs mono-2` -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerMono.cpp -lgmp -lgmpxx -lpthread -ldl


csBigIntegerGMP-hard.test : csBigInteger-hard.Test.cpp
	g++ -Ofast --std=c++11 -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerGMP.cpp -lgmp -lgmpxx -lpthread -ldl


csBigIntegerMono-hard.test : csBigInteger-hard.Test.cpp
	dotnet build ../src/dotnet/ -c Release
	cp ../src/dotnet/bin/Release/netstandard2.0/csbiginteger_dotnet.dll .
	mono --aot -O=all csbiginteger_dotnet.dll
	g++ --coverage -g -O0 --std=c++11 `pkg-config --cflags --libs mono-2` -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerMono.cpp -lgmp -lgmpxx -lpthread -ldl


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
