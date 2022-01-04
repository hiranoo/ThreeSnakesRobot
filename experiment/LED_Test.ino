etup() {
  
}

void loop() {
  int t = 128;
  while(t <= 1000){
    analogWrite(0,t);
    delay(500);
    analogWrite(0,0);
    delay(500);
    //t += 10;
  }

}

