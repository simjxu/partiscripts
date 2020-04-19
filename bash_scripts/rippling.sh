#!/bin/bash

if [ `id -u` -ne 0 ]; then
    echo "Rippling uninstall must be run by root"
    exit 1
fi

sudo launchctl unload /Library/LaunchDaemons/com.rippling.*
sudo rm -rf /Library/LaunchDaemons/com.rippling.*
sudo rm -rf /opt/rippling
sudo defaults write /Library/Preferences/com.apple.loginwindow LoginwindowText ""
sudo profiles -R -p com.rippling.password

# Merciless uninstall of munki.

launchctl unload /Library/LaunchDaemons/com.googlecode.munki.*
rm -rf '/Applications/Utilities/Managed Software Update.app'
rm -rf '/Applications/Managed Software Center.app'
rm -rf '/Applications/msc.app'
rm -f /Library/LaunchDaemons/com.googlecode.munki.*
rm -f /Library/LaunchAgents/com.googlecode.munki.*
rm -rf '/Library/Managed Installs'
rm -rf /usr/local/munki
pkgutil --forget com.googlecode.munki.core
pkgutil --forget com.googlecode.munki.admin
pkgutil --forget com.googlecode.munki.app
pkgutil --forget com.googlecode.munki.launchd
pkgutil --forget com.googlecode.munki
sudo profiles -R -p com.rippling.munki