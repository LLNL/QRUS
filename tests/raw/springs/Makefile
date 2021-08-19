
springs-1d: springs-1d.cxx
	g++ springs-1d.cxx -o springs-1d

springs-1d.csv: springs-1d
	./springs-1d > springs-1d.csv

springs-1d.svg: plot-1d.py springs-1d.csv
	python3 plot-1d.py springs-1d.csv springs-1d.svg

springs-2d: springs-2d.cxx
	g++ springs-2d.cxx -o springs-2d

springs-2d.csv: springs-2d
	./springs-2d > springs-2d.csv

springs-2d.mp4: movie-2d.py springs-2d.csv
	python3 movie-2d.py springs-2d.csv springs-2d.mp4

springs-3d: springs-3d.cxx
	g++ springs-3d.cxx -o springs-3d

springs-3d.csv: springs-3d
	./springs-3d > springs-3d.csv

springs-3d.mp4: movie-3d.py springs-3d.csv
	python3 movie-3d.py springs-3d.csv springs-3d.mp4
