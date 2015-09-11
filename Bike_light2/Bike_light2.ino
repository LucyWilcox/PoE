  const int buttonPin = 9;//pin the button is on
  bool buttonState = 0;//keeps track is button is high or low and alternates between the two
  int mode = 0; //mode dictates what mode the light is on: on, flash, off, or pulsing
  long previousMillis = 0; //last time the button  was pressed
  long interval = 1000; //one second: how long the light default to flashing
  int secondCounter = 0; //used to track seconds to determine which light is on in pulsing mode
  int blinkCounter = 0; //used to determine if lights are on or off in blink mode
  long lastPress = 0; //tracks the time (millis) that the button was last pressed
  const int potentiometer = 3; //the pin the potentiometer is on
  long lastDebounceTime = 0; // keeps track of the last time the button was pressed
  long debounceDelay = 100; // .1 second
  int potentiometerScaling = 500; //adjustes the potentiometer reading to a reasonable number for flash/pulse control

void setup() { //setup pins
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(potentiometer, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop(){ 
    
  float potentiometerReading = analogRead(potentiometer); //gets an analog reading that depends on how the potentiometer is set
  if (buttonState == HIGH){
    lastPress = millis(); // if the button is being pressed get the current time
    if((lastPress - lastDebounceTime)>debounceDelay){ //check if the last time the reading changed was longer ago than the debounceDelay
      lastDebounceTime = millis();
      ++ mode; //changes the mode that the lights are on
    }
  } 
  int reading = digitalRead(buttonPin); //gets now reading from the button
  if (reading != buttonState){
    lastDebounceTime = millis(); //if the reading changes get the current time
  }
    
  if (mode == 0){ //all lights on
      digitalWrite(13, HIGH); 
      digitalWrite(12, HIGH);   
      digitalWrite(11, HIGH); 
  } 
  
  if (mode == 1){ // blinking
    unsigned long currentMillis = millis(); //gets current time
    if(currentMillis - previousMillis > potentiometerReading * interval / potentiometerScaling ){ //controls rate of blinking
      previousMillis = currentMillis; 
      if (blinkCounter == 0){
        blinkCounter = 1;}
      else if (blinkCounter == 1) {
        blinkCounter = 0;}  
    }
    if (blinkCounter == 0){
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);   
      digitalWrite(11, HIGH);}
    if (blinkCounter == 1){
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);}
  }
     
  if (mode == 2){ //all off      
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
  }
  
  if (mode == 3){ //pulsing
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval * potentiometerReading / potentiometerScaling){ //controls rate of pulsing
    previousMillis = currentMillis; //resets previous
    if (secondCounter == 0){ //this section loops though the different modes
      secondCounter = 1;}
    else if (secondCounter == 1){
      secondCounter = 2;}
    else if (secondCounter == 2){
      secondCounter = 0;}
  }
    if (secondCounter == 0){ //this section is determined the the previous block and determines which light is on
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);}
    if (secondCounter == 1){
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);}
    if (secondCounter == 2){
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);}
  }   
  if (mode > 3){
      mode = 0; //We only have four settings: 0, 1, 2, and 3 so when it gets to 4 this sets it back to 0
  }  
  buttonState = digitalRead(buttonPin); //gets button state so we can check next time through the loop if it's different
}
