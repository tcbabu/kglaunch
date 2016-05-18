include config.mak
#CC	=g++ -pthread
CC	=cc -pthread
hotspot	: hotspot.o hotspotCallbacks.o main.o
	 $(CC) -o hotspot hotspot.o hotspotCallbacks.o main.o -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread 
hotspot.o	: hotspot.c 
	 $(CC) -c hotspot.c
hotspotCallbacks.o	: hotspotCallbacks.c 
	 $(CC) -c hotspotCallbacks.c
main.o	: main.c 
	 $(CC) -c main.c
clean	:  
	   rm -f *.o hotspot
install	: hotspot
	  install -m 755 -s hotspot $(PREFIX)/bin
