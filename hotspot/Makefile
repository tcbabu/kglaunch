include config.mak
#CC	=g++ -pthread
CC	=cc -pthread
hotspot	: hotspot.o hotspotCallbacks.o main.o
	 $(CC) -o hotspot hotspot.o hotspotCallbacks.o main.o -lkulina -lgm -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread 
	 cp hotspot $(KULINA)/TARBALL/
hotspot.o	: hotspot.c 
	 $(CC) -c hotspot.c
hotspotCallbacks.o	: hotspotCallbacks.c 
	 $(CC) -c hotspotCallbacks.c
main.o	: main.c 
	 $(CC) -c main.c
clean	:  
	   rm -f *.o hotspot
	   rm -f $(KULINA)/TARBALL/hotspot
install	: hotspot
	  install -m 755 -s hotspot $(PREFIX)/bin
