all:  gmp dotnet

static_lib_with_gmp: # uses 'gmp' as basis
	#g++ --static -std=c++11 -Ofast lib/empty_main.cpp src/csBigIntegerLib.cpp src/BigIntegerGMP.cpp -lgmp -lgmpxx -o lib/libcsbiginteger.a
	g++          -std=c++11 -Ofast -c src/BigIntegerGMP.cpp   -lgmp -lgmpxx -o lib/libcsbiginteger_gmp.o
	g++ --static -std=c++11 -Ofast -c src/BigIntegerGMP.cpp   -lgmp -lgmpxx -o lib/libcsbiginteger_gmp.a
	g++          -std=c++11 -Ofast -c src/csBigIntegerLib.cpp -lgmp -lgmpxx -o lib/libcsbiginteger_cpp.o
	#g++ --static -std=c++11 -Ofast -c src/csBigIntegerLib.cpp -lgmp -lgmpxx -o lib/libcsbiginteger_cpp.a
	ar rvs lib/libcsbiginteger.a lib/libcsbiginteger_gmp.o lib/libcsbiginteger_cpp.o

gmp:
	g++ -std=c++11 -Ofast --shared src/csBigIntegerLib.cpp src/BigIntegerGMP.cpp -lgmp -lgmpxx -o build/csbiginteger_gmp.so -fPIC

dotnet:
	dotnet build src/dotnet/ -c Release
	cp src/dotnet/bin/Release/netstandard2.0/csbiginteger_dotnet.dll build/
	mono --aot -O=all build/csbiginteger_dotnet.dll
	g++ -std=c++11 -Ofast --shared src/BigIntegerMono.cpp src/csBigIntegerLib.cpp `pkg-config --cflags --libs mono-2` -o build/csbiginteger_mono.so -fPIC


vendor:
	@echo "verifying GNU lgmp library (debian-based systems)"
	./get_libgmp.sh
	@echo "============ finished 'make vendor' ============"

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
