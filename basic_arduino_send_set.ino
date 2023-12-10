#include <ArduinoJson.h>

//this is the string that we buffer the received serial signals into
String inputString = "";        // A String to hold incoming data
bool stringComplete = false;    // Whether the string is complete

void setup()
{
    Serial.begin(115200);
    analogReadResolution(12); //for M0/M4 class uC
    inputString.reserve(200);     // Reserve 200 bytes for the inputString

}

//These initialize the vars for sampling samps samples and then averaging. 
//Samps can be changed later in runtime
long ts = millis();
int samps = 100;
int count = 0;
float runner = 0;

void sample_then_send()
{
    if (count < samps)  // if we haven't sampled samps yet, sample again
    {
        runner += analogRead(A0);
        count +=1;
    } 
    else //otherwise take the average and fire it out
    {
        StaticJsonDocument<200> odoc;
        float out = runner/samps;
        odoc["a0"] = out;
        odoc["td"] = millis()-ts; //a handy delta of the time it took between sends for cumsum
        String output;
        serializeJson(odoc, output);
        //reset counters
        Serial.println(output);
        count = 0;
        ts = millis();
        runner = 0;
    }
}


void listen_then_act()
{

    serialEvent(); //see if we have a complete string on
    if (stringComplete)  //if we do, try to act on it
    {
    StaticJsonDocument<200> idoc;

    // Parse JSON string
    DeserializationError error = deserializeJson(idoc, inputString);

    //this is where we can change whatever
    if (!error) {
        samps = idoc["samps"];
    }
    // Clear the string for new input
    inputString = "";
    stringComplete = false;
  }

}

void serialEvent() {
  while (Serial.available()) {
    // Get the new byte
    char inChar = (char)Serial.read();
    
    // Add it to the inputString
    inputString += inChar;

    // If the incoming character is a newline, set stringComplete to true
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


void loop()
{
    
    listen_then_act();
    sample_then_send();
}
