
int sensorPin = 0; 
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()                     
{
 int input = analogRead(sensorPin);  
 float voltage = input * 5.0;
 voltage /= 1024.0; 
 
 Serial.print(voltage); Serial.println(" Напряжение");
 
 float temperatureC = (voltage - 0.5) * 100 ;
 Serial.print(temperatureC); Serial.println(" Температура");
 
 delay(2000);
}