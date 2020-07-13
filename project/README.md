
To get started: 
plugin in device
run make,
run make load to install program to msp430

Clean msp430:
make clean
make tiddyup

reset msp430
mspdebug rf2500 "reset"

In order to play the song,
simply press the first switch on the bottom board (S1). This will trigger the
song to play and also change the LED lights from red to green. Red signifies
that no note/music is playing and green signifies that a note is currently playing.

Press (S1) to stop the it from playing. if the S1 or S2 are held the led light should change to red and play a note until either button is released.


The second switch on the bottom board (S2) will make the LED lights switch
mimicking a police car. To stop the LED lights from flickering, pressing the
top switch (S2) or (S1) on the top board will stop it and the LED light will only
light up GREEN, RED if the switches are still pressed.

Switch 3 (S3) on the top board will dim the GREED led light. To interrupt it, the
bottom switch (S1) must be pressed.

Switch 4 (S4) on the top board will display the numbers in binary from 0 -
3. When pressed for the first time, non of the led lights will show,
representing 00. If pressed again, the GREEN led light will show, representing
01, when pressed again, the RED led light will show, representing
10, once pressed again, both RED and GREEN led lights will light up
representing 11. Once pressed again, it will restart the count from 0.