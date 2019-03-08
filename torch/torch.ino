//neopixel stuff
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS      12

#define PIN            9
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//#define LEDPOWER       7 

#define VIBE1          5
#define VIBE2          6
#define BUTTON        3


//long record;
int invert = 0;
int rate = 30;
int buttonFlag = 0;
int record[500];
int record2[500];
long startPoint;
int recEnd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
  setupPixels();
}


void loop() {
 
  
  
  Serial.print("light 1:");
  Serial.println(analogRead(A0));
  int lightIn =  map(analogRead(A0), 0, 1023, 0, 255);
  lightIn = constrain((lightIn) * 1.2, 0, 255);
  Serial.print("test ");
  Serial.println(lightIn);
  int lightIn2 =  map(analogRead(A1), 0, 1023, 0, 255);
  lightIn2 = constrain((lightIn2) * 1.2, 0, 255);
  

 unsigned long currentMillis = millis() - startPoint;
  

if (buttonFlag == 1) {
  analogWrite(VIBE1, lightIn);
  analogWrite(VIBE2, lightIn2);
  //Serial.println("hello");
  if ((currentMillis % rate) == 0){
   
   record[(currentMillis / rate)] = lightIn;
   record2[(currentMillis / rate)] = lightIn2;
   Serial.println((currentMillis / rate));
   Serial.print("A0: ");
   Serial.println(lightIn);
   Serial.print("A1: ");
   Serial.println(lightIn2);


  for (int k=0; k<6; k++){
    pixels.setPixelColor(0, pixels.Color(0, 0, lightIn));  
    pixels.setPixelColor(7, pixels.Color(0, 0, lightIn2));  
    pixels.show();  
  }
   
  }
  //Serial.println(lightIn);
} else {
  int output = record[(currentMillis / rate) % recEnd];
  int output2 = record2[(currentMillis / rate) % recEnd];
  analogWrite(VIBE1, output);
  analogWrite(VIBE2, output2);
  Serial.println((currentMillis / rate) % recEnd);

  for (int k=0; k<6; k++){
    pixels.setPixelColor(k, pixels.Color(output, output, output));  
    pixels.setPixelColor(k+6, pixels.Color(output2, output2, output2));  
    pixels.show();  
  }
  
}

int button = digitalRead(BUTTON);
  if (button != buttonFlag) {
     buttonFlag = button;
     if (button == 1) {
      Serial.println("on");
      startPoint = millis();

      for (int k=0; k<12; k++){
    pixels.setPixelColor(k, pixels.Color(0, 0, 0));  
    pixels.show();  
  }
      
     } else {
      Serial.println("off");
      recEnd = (currentMillis / rate);
     }
    
  }
  
  // put your main code here, to run repeatedly:
 // analogWrite(6, lightIn);
//  delay(50);
//  analogWrite(6, 0);
//  delay(50);
}


void setupPixels(){
    pixels.begin();
pixels.setBrightness(255); 
  for (int i = 0; i<NUMPIXELS; i++)
       {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
       }
pixels.show();

  delay(100);

for (int i = 0; i<NUMPIXELS; i++)
       {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
       }
pixels.show();

}

