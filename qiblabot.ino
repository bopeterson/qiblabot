/* 
This is an Arduino sketch for the official Arduino Robot, http://arduino.cc/en/Main/Robot
The robot points out the direction of Mecca.
Two images, a_intro.bmp and allah.bmp must be transfered to the sd-card (although a_intro is not used at the moment).

license: Public domain

*/

#include <ArduinoRobot.h>

int key;
int city;
boolean citySelected;

int cityOrientation[]={138,139,148,119,119,58};
char* cityName[]={"Malmo", "Lund", "Stockholm","London", "Paris","New York"};
int noOfCities=6; //must match number of elements in city arrays

void setup() {
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  Robot.displayLogos();

  city=0;
  citySelected=false;
  boolean buttonPressedBefore=false;
  showCity(city);
  while (!citySelected) {
    key = Robot.keyboardRead();
    switch(key) {
      case BUTTON_UP:
        break;
      case BUTTON_LEFT:
        if (!buttonPressedBefore) {
          city=city--; if (city<0) city=noOfCities-1;
          buttonPressedBefore=true;
          showCity(city);
        }
        break;
      case BUTTON_DOWN:
        break;
      case BUTTON_RIGHT:
        if (!buttonPressedBefore) {
          city=city++; if (city>(noOfCities-1)) city=0;
          showCity(city);
          buttonPressedBefore=true;
        }    
        break;
      case BUTTON_MIDDLE:
        citySelected=true;
        break;
      default:
       buttonPressedBefore=false;
       break;
    }
  }


  //Robot.drawBMP("a_intro.bmp",0,0);
  //Robot.waitContinue();
  Robot.drawBMP("allah.bmp",0,0);

}

void loop() {
  Robot.pointTo(cityOrientation[city]);
  delay(2000);
}

void showCity(int city) {
  Robot.clearScreen();
  Robot.text("Select city with",5,10);
  Robot.text("left and right",5,20);
  Robot.text("button",5,30);
  Robot.text("Press middle button",5,50);
  Robot.text("when done",5,60);
  Robot.text(cityName[city],5,80);
}
