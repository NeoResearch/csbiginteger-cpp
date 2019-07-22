
SRC_PATH=../src
# gtest
GTEST_PATH=./libgtest/build/googletest
GMOCK_PATH=./libgtest/build/googlemock
GTEST_INCLUDE=./libgtest/googletest/include
GMOCK_INCLUDE=./libgtest/googlemock/include

all:
	@echo "please type 'make test'"

test: clean csBigIntegerGMP.test
	@echo "Executing tests"
	./csBigIntegerGMP.test

test-hard: test csBigIntegerGMP-hard.test
	@echo "Executing hard tests"
	./csBigIntegerGMP-hard.test

csBigIntegerGMP.test : csBigInteger.Test.cpp
	g++ --coverage -g -O0 --std=c++11 -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerGMP.cpp -lgmp -lgmpxx -lpthread -ldl

csBigIntegerGMP-hard.test : csBigInteger-hard.Test.cpp
	g++ -Ofast --std=c++11 -I$(SRC_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(SRC_PATH)/BigIntegerGMP.cpp -lgmp -lgmpxx -lpthread -ldl


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
