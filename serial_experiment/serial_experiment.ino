void setup(){
  Serial.begin(9600);
}

void loop()
{
  Serial.write(45); // send a byte with the value 45
}
