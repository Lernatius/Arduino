
#define usft A0         		//defining the pins that we are gonna use
#define usfe A1

float frontdistance;

void setup() {
  
  Serial.begin(9600);
  pinMode(usfe, INPUT);              // defining pins modes
  pinMode(usft, OUTPUT);

}

void measure()
{
  
  digitalWrite(usft, LOW);			//sending pulse to sensor 
  delayMicroseconds(5);
  digitalWrite(usft, HIGH);								
  delayMicroseconds(10);	
  digitalWrite(usft, LOW);
  frontdistance = pulseIn(usfe, HIGH) / 58.2;   //reading the answer time of the pulse 
  delay(1);										//from the sensor
  
}

void loop()
{
  measure();
  Serial.println(frontdistance);				//watching values by serial monitor
  delay(400);
}
//Thanks to my dear frien Eray Tuncan