see http://waveypi.blogspot.co.uk/2012/09/2-raspberry-pis-communicating-via-morse.html

out.py
======

    python out.py hello world
    echo "hello world" | python out.py

build
=====
    pacman -S libbcm2835
    make

morse\_ACT
=========

this will morse blink via on-board "ACT" led, no GPIO wire needed.
note: "ACT" led used for SD card indication, `morse_ACT.py will restore the "ACT" function for SD card when exit or interruption.
