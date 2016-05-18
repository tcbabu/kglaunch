#!/bin/bash
install -m 755 -s  kglaunch  /usr/bin/kglaunch
install -m 755 -s  kglogout  /usr/bin/kglogout
install -m 755 -s  configlauncher  /usr/bin/configlauncher
install -m 755 -s  hotspot  /usr/bin/hotspot
install -m 755 -s kglogout /usr/bin/kgLogout
chmod +s $(PREFIX)/bin/kgLogout
mkdir -p /usr/share/kglaunch
install -m 644 -s kglaunch.png /usr/share/kglaunch/kglaunch.png
install -m 644 -s kglaunch.desktop /usr/share/applications
install -m 644 -s kglogout.png /usr/share/kglaunch/kglogout.png
install -m 644 -s kglogout.desktop /usr/share/applications
install -m 644 -s hotspot.png /usr/share/kglaunch/hotspot.png
install -m 644 -s hotspot.desktop /usr/share/applications
install -m 644  firefox.png /usr/share/kglaunch/firefox.png
install -m 644  Launcher /usr/share/kglaunch
install -m 644  launcher.conf /usr/share/kglaunch
