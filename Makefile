all:
	make -C jcx
	make -C unittest
clean:
	make -C jcx 	clean
	make -C unittest	clean
