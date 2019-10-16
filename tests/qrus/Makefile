
check: test-0.passed test-1.passed

test-0.passed: test-0.exe
	./test-0.exe > test-0.out && touch test-0.passed

test-0.exe: test-0.cxx
	g++ -std=c++17 -I../../include test-0.cxx -o test-0.exe

test-1.passed: test-1.exe
	./test-1.exe > test-1.out && touch test-1.passed

test-1.exe: test-1.cxx
	g++ -std=c++17 -I../../include test-1.cxx -DOUTPUT_INFO=0 -o test-1.exe

clean:
	rm -f *.exe *.passed *.out
