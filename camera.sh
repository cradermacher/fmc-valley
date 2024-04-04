#!/bin/bash

#eine Variable fuellen fuer die Datumsausgabe
DATE=$(date  +"%H:%M Uhr %d.%m.%Y")

#ein Bild der Kamera erzeugen
fswebcam --skip 2 -F 30 -r 1920x1080  --no-banner /root/bild-orig.jpg

#Bild umbauen und Infos reinschreiben
convert /root/bild-orig.jpg -geometry 1000x557 -quality 50 -gravity North -background black -extent 1000x577 -gravity SouthEast -fill white -font /usr/share/fonts/ttf-dejavu/DejaVuSans.ttf -pointsize 16 -draw "text 0,0 '- Schmidham -  `echo $DATE` '" /root/bild.jpg

#Bild auf den Server kopieren
scp /root/bild.jpg  root@192.168.114.231:/var/www/html
