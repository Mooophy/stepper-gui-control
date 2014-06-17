void setup(){
  Serial.begin(9600);
}

void loop()
{
  Serial.write("84\r\n"); // send a byte with the value 45
}
