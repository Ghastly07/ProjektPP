# Projekt_PP
Ustawienie VisualStudio
Project-->Propries-->System w SubSystem dajemy Windows (/SUBSYSTEM:WINDOWS)
Project Properties -> Linker -> Advanced ->  w polu Entry point wpisujemy: main

Konfiguracja Opencv:
http://opencv-srf.blogspot.com/2013/05/installing-configuring-opencv-with-vs.html

dla biblioteki w wersji 3.20 robimy to samo z tą różnicą, że linkujemy tylko jedną biblioteke :
opencv_world320d.lib