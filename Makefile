all:
	g++ --shared src/csBigIntegerLib.cpp src/BigInteger.cpp -lgmp -lgmpxx -o build/csbiginteger.so -fPIC

clean:
	rm build/*.so 
