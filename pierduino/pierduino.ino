#include "DHT.h"
int temp;
DHT dht;
char play;

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

int speakerPin = 9;

void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) 
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) 
  {
    if (names[i] == note) 
    {
      playTone(tones[i], duration);
    }
  }
}


void setup()
  {
    dht.setup(4);
    pinMode(speakerPin, OUTPUT);
    Serial.begin(9600);
  }

void loop() //main loop
{
  float temperature = dht.getTemperature();
  Serial.println(temperature, 1);
  delay(dht.getMinimumSamplingPeriod());

  if (Serial.available() > 0) //serial communication with LabView
    play = Serial.read();

  if(play=='1') //playing music
  {
    for (int i = 0; i < length; i++) 
    {
      if (notes[i] == ' ') 
      {
        delay(beats[i] * tempo); // rest
      } 
      else 
      {
        playNote(notes[i], beats[i] * tempo);
      }
      // pause between notes
      delay(tempo / 2); 
    }
  }

  
}
