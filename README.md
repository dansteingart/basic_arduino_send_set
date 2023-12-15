# Basic Arduino Send and Set

This is a code template that I forget and write again once a year. Trying to forestall this for 20XX.

This code sets the base of an Arduino program that:

1. Sends averaged samples out very quickly if need be while
2. Listens for JSON strings over the serial port

In a manner that allows both to occur reasonably quickly with minimal blocking.

We're using JSON on both the send and receive for predictability. The only required external library is [ArduinoJson](https://arduinojson.org/).

## How To Use

Copy the code to a new Arduino file. Make sure ArduinoJson is available. Edit it to do what you want to do. 

As written, the code will

1. Start a serial port at a baud rate of 115200.
2. Sample `a0` `samps` times (`samps` = 100 by default).
3. Average `samp'samples.
4. Send a JSON string of the average over serial when the above is done, along with the time it took to sample `samps` samples.
5. Listen for a JSON message over the serial port that allows you to set `samps` as required while running. There's no persistent storage; `samps` will revert to 100 on reset.
