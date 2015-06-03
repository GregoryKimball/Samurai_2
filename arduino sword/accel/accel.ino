// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int integration_time = 1;
//int x_offset = -345, y_offset = -336, z_offset = -450;
int x_offset = 0, y_offset = 0, z_offset = 0;

// the setup routine runs once when you press reset:
void setup() 
{                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
//  UCSR0C = UCSR0C | B00001000;
 Serial.begin (9600);
 
}


char *Output(int n)
{

if (n<10) return "00";
if (n<100) return "0";
return ""; 

}

void loop() 
{

    int s = 0;
    int x_accel, y_accel, z_accel;
    
    int x_accel_max =0 , y_accel_max=0, z_accel_max =0;
    
//    Serial.print(sensor_value);
    
    s=0;
    for( int i = 0;i<integration_time;i++)
    {
    
      x_accel = analogRead(A0);
      y_accel = analogRead(A1);
      z_accel = analogRead(A2);
      
      if (x_accel > x_accel_max) x_accel_max = x_accel;
      if (y_accel > y_accel_max) y_accel_max = y_accel;
      if (z_accel > z_accel_max) z_accel_max = z_accel;

      s++;
      delay(1);
    }//*/



   /*  x_accel_max = analogRead(A0);
      y_accel_max = analogRead(A1);
      z_accel_max = analogRead(A2);//*/

 /*   Serial.print("x");
    Serial.print(itoa(x_accel_max));
    Serial.print("y");
    Serial.print(itoa(y_accel_max));
    Serial.print("z");
    Serial.println(itoa(z_accel_max));//*/
    
    Serial.print("x");
    Serial.print(Output(x_accel_max+x_offset));
    Serial.print((x_accel_max+x_offset));
    Serial.print("y");
    Serial.print(Output(y_accel_max+y_offset));
    Serial.print((y_accel_max+y_offset));
    Serial.print("z");
    Serial.print(Output(z_accel_max+z_offset));
    Serial.print((z_accel_max+z_offset));
    Serial.print(':');
    
    



    

    
    //*/
    
  


}


