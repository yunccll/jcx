all:
	make -C base  	
	make -C thread  
	make -C logger  
	make -C other  	
	make -C plugin 
	make -C perf

clean:
	make -C base  	clean
	make -C logger  clean
	make -C other  	clean
	make -C thread  clean
	make -C plugin  clean
	make -C perf 	clean


ut: all
	make -C base  	ut
	make -C thread  ut
	make -C logger  ut
	make -C other  	ut
	make -C plugin  ut
	make -C perf	ut
