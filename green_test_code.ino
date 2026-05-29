
#define s0  44       //Module pins wiring
#define s1  45
#define s2  42
#define s3  41
#define out 43

int data=0;        //This is where we're going to stock our values

void  setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and  LOW/HIGH is  2%
   
}

void loop()                  //Every 2s we select  a photodiodes set and read its data
{



   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green value= ");
   GetData();

   Serial.println();

   delay(2000);
}

void GetData(){
   data=pulseIn(out,LOW);       //here  we wait until "out" go LOW, we start measuring the duration and stops when "out"  is HIGH again
   Serial.print(data);          //it's a time duration measured,  which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\	");          //The higher the frequency the lower the duration
   delay(20);
}

