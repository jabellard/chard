# top level makefile

.PHONY: all
all: drv app


.PHONY: drv	
drv:
	cd drv; make
	

.PHONY: drv-clean	
drv-clean:
	cd drv; make clean

.PHONY: app
app:
	cd app; make

	
.PHONY: app-clean
app-clean:
	cd app; make clean
	
	
.PHONY: clean
clean: drv-clean app-clean
