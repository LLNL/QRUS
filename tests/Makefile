
check: check_raw check_qrus projectiles.svg

check_raw:
	make -C raw check
check_qrus:
	make -C qrus check

raw/projectile-0-0.out:
	make -C raw projectile-0-0.out
raw/projectile-1-0.out:
	make -C raw projectile-1-0.out
raw/projectile-0-1.out:
	make -C raw projectile-0-1.out
raw/projectile-1-1.out:
	make -C raw projectile-1-1.out

raw/projectile_nm-0-0.out:
	make -C raw projectile_nm-0-0.out
raw/projectile_nm-1-0.out:
	make -C raw projectile_nm-1-0.out
raw/projectile_nm-0-1.out:
	make -C raw projectile_nm-0-1.out
raw/projectile_nm-1-1.out:
	make -C raw projectile_nm-1-1.out

qrus/projectile-0-0.out:
	make -C qrus projectile-0-0.out
qrus/projectile-1-0.out:
	make -C qrus projectile-1-0.out
qrus/projectile-0-1.out:
	make -C qrus projectile-0-1.out
qrus/projectile-1-1.out:
	make -C qrus projectile-1-1.out

qrus/projectile_nm-0-0.out:
	make -C qrus projectile_nm-0-0.out
qrus/projectile_nm-1-0.out:
	make -C qrus projectile_nm-1-0.out
qrus/projectile_nm-0-1.out:
	make -C qrus projectile_nm-0-1.out
qrus/projectile_nm-1-1.out:
	make -C qrus projectile_nm-1-1.out

projectiles.svg: projectiles.gplot \
                 raw/projectile-0-0.out raw/projectile-1-0.out raw/projectile-0-1.out raw/projectile-1-1.out \
                 qrus/projectile-0-0.out qrus/projectile-1-0.out qrus/projectile-0-1.out qrus/projectile-1-1.out \
                 raw/projectile_nm-0-0.out raw/projectile_nm-1-0.out raw/projectile_nm-0-1.out raw/projectile_nm-1-1.out \
                 qrus/projectile_nm-0-0.out qrus/projectile_nm-1-0.out qrus/projectile_nm-0-1.out qrus/projectile_nm-1-1.out
	gnuplot projectiles.gplot


clean: clean_raw clean_qrus
	rm -f projectiles.svg

clean_raw:
	make -C raw clean
clean_qrus:
	make -C qrus clean
