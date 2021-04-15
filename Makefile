include config.mak
HFILES = $(foreach part, hotspot, $(wildcard $(addprefix $(part)/,*.[ch])))
LFILES = $(foreach part, kglaunch, $(wildcard $(addprefix $(part)/,*.[ch])))
all	: hotspot/hotspot kglaunch/kglaunch 

hotspot/hotspot : $(HFILES)
		 cp config.mak hotspot/
		 make -C hotspot
kglaunch/kglaunch : $(LFILES)
		 cp config.mak kglaunch/
		 make -C kglaunch

clean	:
	 make -C hotspot clean
	 make -C kglaunch clean
install	: hotspot/hotspot kglaunch/kglaunch
	  make -C hotspot install
	  make -C kglaunch install
	mkdir -p /usr/share/kglaunch
	install -m 644  firefox.png /usr/share/kglaunch/firefox.png
	install -m 644  Launcher /usr/share/kglaunch
	install -m 644  launcher.conf /usr/share/kglaunch
	install -m 644  kglaunch.png /usr/share/kglaunch/kglaunch.png
	install -m 644  kglogout.png /usr/share/kglaunch/kglogout.png
	install -m 644  kglogout.png /usr/share/icons/red_light.png
	install -m 644  hotspot.png /usr/share/kglaunch/hotspot.png
	install -m 644  kglaunch.desktop /usr/share/applications
	install -m 644  kglogout.desktop /usr/share/applications
	install -m 644  hotspot.desktop /usr/share/applications
