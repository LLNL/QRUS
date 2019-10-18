
check: chain.passed projectile-0-0.passed

chain.passed: chain.exe
	./chain.exe > chain.out && touch chain.passed

chain.exe: chain.cxx
	g++ -std=c++17 -I../../include chain.cxx -o chain.exe

projectile-0-0.passed: projectile-0-0.exe
	./projectile-0-0.exe > projectile-0-0.out && touch projectile-0-0.passed

projectile-0-0.exe: projectile.cxx
	g++ -std=c++17 -I../../include projectile.cxx -DOUTPUT_INFO=0 -DK0=0. -DK1=0. -o projectile-0-0.exe

clean:
	rm -f *.exe *.passed *.out
