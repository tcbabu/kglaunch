include config.mak
#CC	=g++ -pthread
CC	=cc -pthread
all	:kglaunch kglogout configlauncher 
kglaunch	: kglaunch.o kglaunchCallbacks.o main.o additem.o \
 	 additemCallbacks.o edititem.o edititemCallbacks.o  \
	 import.o importCallbacks.o
	 $(CC) -o kglaunch kglaunch.o kglaunchCallbacks.o main.o \
	 additem.o additemCallbacks.o \
	 edititem.o edititemCallbacks.o \
	 import.o importCallbacks.o \
	 -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread  
kglaunch.o	: kglaunch.c 
	 $(CC) -c kglaunch.c
kglaunchCallbacks.o	: kglaunchCallbacks.c 
	 $(CC) -c kglaunchCallbacks.c
import.o	: import.c 
	 $(CC) -c import.c
importCallbacks.o	: importCallbacks.c 
	 $(CC) -c importCallbacks.c
main.o	: main.c 
	 $(CC) -c main.c
configlauncher	: configlauncher.o configlauncherCallbacks.o main.o
	 $(CC) -o configlauncher configlauncher.o configlauncherCallbacks.o  -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread -lz 
configlauncher.o	: configlauncher.c 
	 $(CC) -c configlauncher.c
configlauncherCallbacks.o	: configlauncherCallbacks.c 
	 $(CC) -c configlauncherCallbacks.c
kglogout	: kglogout.c
		 cc -okglogout kglogout.c -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread
clean	:  
	   rm -f *.o kglaunch kglogout configlauncher
install	: kglaunch kglogout configlauncher
	 install -m 755 -s kglaunch $(PREFIX)/bin
	 install -m 755 -s configlauncher $(PREFIX)/bin
	 install -m 755 -s kglogout $(PREFIX)/bin
	 install -m 755 -s kglogout $(PREFIX)/bin/kgLogout
	 chmod +s $(PREFIX)/bin/kgLogout
