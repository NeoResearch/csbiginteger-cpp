all:
	g++ -std=c++11 -Ofast --shared src/csBigIntegerLib.cpp src/BigInteger.cpp -lgmp -lgmpxx -o build/csbiginteger.so -fPIC


vendor:
	@echo "trying to install GNU lgmp library (debian-based systems)"
	sudo apt-get install libgmp-dev
	@echo "trying to configure libgtest on tests/"
	(cd tests/libgtest && mkdir -p build && cd build && cmake .. && make)

test:
	(cd tests && make test)
clean:
	rm build/*.so 
