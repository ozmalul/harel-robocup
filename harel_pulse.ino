#include <NewPing.h>

// Pin definitions
#define LEFT_S0 44
#define LEFT_S1 45
#define LEFT_S2 42
#define LEFT_S3 41
#define LEFT_sensorOut 43

// Pin definitions
#define RIGHT_S0 36
#define RIGHT_S1 37
#define RIGHT_S2 34
#define RIGHT_S3 35
#define RIGHT_sensorOut 33

#define FRONT_TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define FRONT_ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


#define SIDE_TRIGGER_PIN  17  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define SIDE_ECHO_PIN     16  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing front_sonar(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

NewPing side_sonar(SIDE_TRIGGER_PIN, SIDE_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// pins
#define ena 5
#define in1 6
#define in2 7
#define in3 8
#define in4 9
#define enb 10

#define leftSensor 4
#define centerSensor 3
#define rightSensor 2


const int ledPin = LED_BUILTIN;  
int isOn = false;  
unsigned long previousMillis = 0; 

const long intervalOn = 15;
const long intervalOff = 35;  

int speed=255;
int slowSpeed=190;
int leftSpeed = 0;
int rightSpeed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);

  Serial.begin(9600);

}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

 leftSpeed = speed;
 rightSpeed = speed;
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  leftSpeed = speed;
 rightSpeed = 0;
}

void hardright() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

 leftSpeed = speed;
 rightSpeed = speed;
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

 leftSpeed = 0;
 rightSpeed = speed;

}


void hardleft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

 leftSpeed = speed;
 rightSpeed = speed;
}
void stop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

    
 leftSpeed = speed;
 rightSpeed = speed;

}

void loop() {
  //forward();
  //return;
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int front_distance = front_sonar.ping_cm();
  Serial.print("front_distance: ");
  Serial.print(front_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("cm ");
/*
  if (front_distance > 0 && front_distance < 15)
  {

    stop();
    delay(50);

    int side_distance = side_sonar.ping_cm();
    Serial.print("side_distance: ");
    Serial.print(side_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");

    while (side_distance == 0 || side_distance > 65) {
      //  while(true){
      delay(50);
      side_distance = side_sonar.ping_cm();
      hardright();
      Serial.print("side_distance: ");
      Serial.print(side_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
      Serial.println("cm");
    }
    while (digitalRead(centerSensor) == HIGH) {
      while (side_distance > 0 && side_distance < 75 && digitalRead(centerSensor) == HIGH) {
        //  while(true){
        delay(50);
        side_distance = side_sonar.ping_cm();
        forward();
        Serial.print("side_distance: ");
        Serial.print(side_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
        Serial.println("cm");
      }
      while (side_distance == 0 || side_distance > 75 && digitalRead(centerSensor) == HIGH) {
        //  while(true){
        delay(50);
        side_distance = side_sonar.ping_cm();
        hardright();
        Serial.print("side_distance: ");
        Serial.print(side_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
        Serial.println("cm");
      }

    }
    Serial.println("stop");
  }
  */
  Serial.print(digitalRead(leftSensor));
  Serial.print("\t");
  Serial.print(digitalRead(centerSensor));
  Serial.print("\t");
  Serial.println(digitalRead(rightSensor));

  if (digitalRead(leftSensor) == LOW && digitalRead(centerSensor) == HIGH && digitalRead(rightSensor) == HIGH)
  {
    left();
  }
  else if (digitalRead(leftSensor) == HIGH && digitalRead(centerSensor) == HIGH && digitalRead(rightSensor) == LOW)
  {
    right();
  }
  else if (digitalRead(leftSensor) == HIGH && digitalRead(centerSensor) == LOW && digitalRead(rightSensor) == LOW)
  {
    hardright();

  }
  else if (digitalRead(leftSensor) == HIGH && digitalRead(centerSensor) == LOW && digitalRead(rightSensor) == HIGH)
  {
    forward();

  }
  else if (digitalRead(leftSensor) == LOW && digitalRead(centerSensor) == LOW && digitalRead(rightSensor) == HIGH)
  {
    hardright();

  }

  else {
    // stop();
  }

  
  unsigned long currentMillis = millis();
  if(isOn == false){
    if (currentMillis - previousMillis >= intervalOn) {
      previousMillis = currentMillis;
        isOn = true;
      analogWrite(ena, 0);
      analogWrite(enb, 0);
     
    }
  }
  else{
    if (currentMillis - previousMillis >= intervalOff) {
      previousMillis = currentMillis;
        isOn = false;

       analogWrite(enb, leftSpeed);
       analogWrite(ena, rightSpeed);

       
    }
  }
}