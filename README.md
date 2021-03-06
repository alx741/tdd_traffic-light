# TDD (Test-Driven Development) Traffic Light

This is a physical toy traffic light to be used with software development TDD
(and testing in general) tools. It will not boost your productivity nor make you
a better programmer or TDD practitioner, but it looks cool :)

`Yellow`: Tests are running

`Red`: Tests failed

`Green`: Tests passed

![](gif.gif)

You can find more information on how it works in [this blog
post](http://www.sillybytes.net/2016/08/tdd-test-driven-development-physical.html).

It consists of

* An inexpensive hardware USB device that resembles a traffic light
    and that can rest on your desk or be attached to the side of your monitor.

* A software tool to control the hardware and decide which color light should be
    turned on.

The software is just a command line utility that takes the target color as
argument so is up to the programmer to invoke it in the appropriate place and
time so the `Yellow` lights is on while the test are executing, the `Red` light
turns on when the tests fail and `Green` light is turned on when the test pass.

This allows it be used with whatever language you like and whatever test
framework/tool you prefer.

*Note:* if you build it, please send me a picture! I would love to see it.


## Construction

The hardware is based on the popular *atmega328p* AVR microcontroller and a
cheap USB-UART converter.

The `src` directory contains the `firmware` for the *atmega328p* and the `host`
code of the command line utility. Each directory has its own **Makefile** for
compilation.


### Hardware

It is assumed that you know how and can flash the firmware in the *atmega328p*.

Any cheap USB-UART converter will work.

First connect your AVR programmer to both the computer and the target chip, then
build and flash the firmware:

    $ cd src/firmware
    $ make
    $ make fuses
    $ make flash

With the firmware already in the chip, build the circuit

![](schematic.png)

Now you can get creative with the casing.

![](shot.jpg)


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


#### Windows users

I feel sorry for you ¯\\\_(ツ)\_/¯

But if you port it and make it work, pull requests are very welcome!


## Usage

Once you have your hardware ready and the host software installed (or the binary
in the directory you want to use it), you may run `tddlight` and see the
commands it provides.

The host software assumes the hardware is at `/dev/ttyUSB0`, but if it's not in
your case, just provide the path as the last argument, or export the
`TDDLIGHT_COMPORT` environment variable:

    $ export TDDLIGHT_COMPORT = "/dev/ttyUSB1"

You can now attach a `tddlight` invocation in your tests. Take a look in the
`samples` directory to see how and to give it a first try. (If you can add a
sample for another programming language or improve the existing ones, please
send a pull request).


## Further

Just a though: If you work in a software company it would be really cool to
build this with a larger form factor so it can sit in a corner of the office
where everyone can see it. Then connect your continuous integration system to it
so it reflects the state of the CI tests. How cool is that?
