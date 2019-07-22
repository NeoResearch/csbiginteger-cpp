all:  gmp

gmp:
	g++ -std=c++11 -Ofast --shared src/csBigIntegerLib.cpp src/BigIntegerGMP.cpp -lgmp -lgmpxx -o build/csbiginteger_gmp.so -fPIC


vendor:
	@echo "trying to install GNU lgmp library (debian-based systems)"
	sudo apt-get install libgmp-dev
	@echo "trying to configure libgtest on tests/"
	(cd tests/libgtest && mkdir -p build && cd build && cmake .. && make)

test:
	@echo "Performing basic tests now"
	@echo
	(cd tests && make test)
	@echo
	@echo "Generating coverage (see tests/reports/)"
	@echo
	#(cd tests && make test-coverage)

	@echo
	@echo "Performing hard tests now... this will take a while!"
	@echo
	#(cd tests && make test-hard)
clean:
	rm build/*.so 
