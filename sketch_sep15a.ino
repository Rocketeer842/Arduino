int i;

void setup() {
    Serial.begin(9600);
    i= 0;
}
 
void loop(){
  if(i>50000){
int sensorVal=analogRead(A1);
Serial.print("Sensor Value: ");
Serial.print(sensorVal);

float voltage = (voltage - 0.5) * (100.0) / (4.5 - 0.5);
    Serial.print("Volts: ");
    Serial.print(voltage);
   
  float pressure_pascal = (3.0*((float)voltage-0.47))*1000000.0;
  float pressure_psi = pressure_pascal/10e5;
    Serial.print("Pressure = ");
    Serial.print(pressure_psi);
    Serial.println(" psi");
    Serial.print("Pressure = ");
    i=0;
  }
  i++;

}
