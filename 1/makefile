test.exe: test.o
	g++ test.o -o test.exe
test.o: 2_0.cpp
	g++ -std=c++11 -O2 -c 2_0.cpp -o test.o
clean:
	del *.o