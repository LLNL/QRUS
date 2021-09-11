
springs-3d: springs-3d.cxx
	g++ springs-3d.cxx -o springs-3d

springs-3d.csv: springs-3d
	./springs-3d > springs-3d.csv

springs-3d.mp4: movie-3d.py springs-3d.csv
	python3 movie-3d.py springs-3d.csv springs-3d.mp4
