# TDD (Test-Driven Development) Traffic Light

This is a physical toy traffic light to be used with software development TDD
(and testing in general) tools.

It consists of

* An inexpensive hardware USB device that resembles a traffic light
    and that can rest on your desk or be attached to the side of your monitor.

* A software tool to control the hardware and decide which color light should be
    turned on.

The software is just a command line utility that takes the target color as
argument so is up to the programmer to invoke it in the appropriate place and
time so the `Yellow` lights is on while the test are executing, the `Red` light
turns on when the tests fail and `Green` light is turned on when the test pass.

This allows it be used in whatever language you are using and whatever test
framework/tool you prefer.

## Using

The hardware is based on the popular *atmega328p* AVR microcontroller and a
cheap USB-UART converter.

The `src` directory contains the `firmware` for the *atmega328p* and the `host`
code of the command line utility. Each directory has its own **Makefile** for
compilation.

### Hardware

It is assumed that you know how and can flash the firmware in the *atmega328p*.
(Hint: You may want to buy a cheap "usbasp" on Ebay)

Any cheap USB-UART converter will work (take a look on Ebay as well).

First connect your AVR programmer to both the computer and the target chip, then
build and flash the firmware:

    $ cd src/firmware
    $ make
    $ make fuses
    $ make flash

With the firmware already in the chip, build the circuit

![](schematics.png)

Now you can get artistic with the casing

![](shot.png)


### Software

#### GNU/Linux users

    $ cd src/host
    $ make

If you want it installed in your system run

    $ sudo make install


#### OSX users

Should be mostly the same as GNU/Linux users (?)

If you try please let me know, and if you make it work by tweaking it a bit,
pull requests are welcome.


#### Window's users

I feel sorry for you ¯\\_(ツ)_/¯

But if you port it and make it work, pull request are very welcome!
