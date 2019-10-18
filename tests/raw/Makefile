
check: chain.passed projectile-0-0.passed projectile-0-1.passed projectile-1-0.passed projectile-1-1.passed projectile_nm-0-0.passed projectile_nm-0-1.passed projectile_nm-1-0.passed projectile_nm-1-1.passed

chain.passed: chain.exe
	./chain.exe > chain.out && touch chain.passed

chain.exe: chain.cxx
	g++ -std=c++17 chain.cxx -o chain.exe

projectile-0-0.passed: projectile-0-0.exe
	./projectile-0-0.exe > projectile-0-0.out && touch projectile-0-0.passed

projectile-0-0.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DK1=0. -DK2=0. -DN=100000 -o projectile-0-0.exe

projectile-0-1.passed: projectile-0-1.exe
	./projectile-0-1.exe > projectile-0-1.out && touch projectile-0-1.passed

projectile-0-1.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DK1=0. -DK2=1. -DN=100000 -o projectile-0-1.exe

projectile-1-0.passed: projectile-1-0.exe
	./projectile-1-0.exe > projectile-1-0.out && touch projectile-1-0.passed

projectile-1-0.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DK1=1. -DK2=0. -DN=100000 -o projectile-1-0.exe

projectile-1-1.passed: projectile-1-1.exe
	./projectile-1-1.exe > projectile-1-1.out && touch projectile-1-1.passed

projectile-1-1.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DK1=1. -DK2=1. -DN=100000 -o projectile-1-1.exe



projectile_nm-0-0.passed: projectile_nm-0-0.exe
	./projectile_nm-0-0.exe > projectile_nm-0-0.out && touch projectile_nm-0-0.passed

projectile_nm-0-0.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DUSE_MATH_FUNCTIONS=0 -DK1=0. -DK2=0. -DN=100000 -o projectile_nm-0-0.exe

projectile_nm-0-1.passed: projectile_nm-0-1.exe
	./projectile_nm-0-1.exe > projectile_nm-0-1.out && touch projectile_nm-0-1.passed

projectile_nm-0-1.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DUSE_MATH_FUNCTIONS=0 -DK1=0. -DK2=1. -DN=100000 -o projectile_nm-0-1.exe

projectile_nm-1-0.passed: projectile_nm-1-0.exe
	./projectile_nm-1-0.exe > projectile_nm-1-0.out && touch projectile_nm-1-0.passed

projectile_nm-1-0.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DUSE_MATH_FUNCTIONS=0 -DK1=1. -DK2=0. -DN=100000 -o projectile_nm-1-0.exe

projectile_nm-1-1.passed: projectile_nm-1-1.exe
	./projectile_nm-1-1.exe > projectile_nm-1-1.out && touch projectile_nm-1-1.passed

projectile_nm-1-1.exe: projectile.cxx
	g++ -std=c++17 projectile.cxx -DOUTPUT_INFO=0 -DUSE_MATH_FUNCTIONS=0 -DK1=1. -DK2=1. -DN=100000 -o projectile_nm-1-1.exe

clean:
	rm -f *.exe *.passed *.out
