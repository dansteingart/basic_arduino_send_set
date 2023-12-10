# Basic Arduino Send and Set
This is a code template that I end up forgetting and writing again once a year. Trying to forestall this for 20XX.

This code sets the base of an arduino program that can

1. Send averaged samples out very quickly if need be while
2. Listening for JSON strings over the serial port

In a manner that allows both to occur reasonably quickly with minimal blocking.

We're using JSON on both the send and receive for predictability. The only required external library is [ArduinoJson](https://arduinojson.org/).

