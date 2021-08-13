
springs-1d: springs-1d.cxx
	g++ springs-1d.cxx -o springs-1d

springs-1d.csv: springs-1d
	./springs-1d > springs-1d.csv

springs-1d.svg: springs-1d.csv
	python3 plot-1d.py springs-1d.csv springs-1d.svg

springs-2d: springs-2d.cxx
	g++ springs-2d.cxx -o springs-2d

springs-2d.csv: springs-2d
	./springs-2d > springs-2d.csv

springs-2d.svg: springs-2d.csv
	python3 plot-1d.py springs-2d.csv springs-2d.svg
