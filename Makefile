all:
	g++ --shared src/csBigIntegerLib.cpp -o build/csbiginteger.so -fPIC

# test python
#run:
#	export LD_LIBRARY_PATH=. && ./test.py

clean:
	rm *.so