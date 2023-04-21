#!/bin/bash
install -m 755   kglaunch  /usr/bin/kglaunch
install -m 755   kglogout  /usr/bin/kglogout
install -m 755   configlauncher  /usr/bin/configlauncher
install -m 755   hotspot  /usr/bin/hotspot
install -m 755  kglogout /usr/bin/kgLogout
chmod +s /usr/bin/kgLogout
mkdir -p /usr/share/kglaunch
install -m 644  kglaunch.png /usr/share/kglaunch/kglaunch.png
install -m 644  kglaunch.desktop /usr/share/applications
install -m 644  kglogout.png /usr/share/kglaunch/kglogout.png
install -m 644  kglogout.png /usr/share/icons/red_light.png
install -m 644  default.png /usr/share/icons/default.png
install -m 644  kglogout.desktop /usr/share/applications
install -m 644  hotspot.png /usr/share/kglaunch/hotspot.png
install -m 644  hotspot.desktop /usr/share/applications
install -m 644  firefox.png /usr/share/kglaunch/firefox.png
install -m 644  Launcher /usr/share/kglaunch
install -m 644  launcher.conf /usr/share/kglaunch
