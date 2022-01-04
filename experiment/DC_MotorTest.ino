
at VCC = 5;
//float VCC = 3.3;
int refPin = 5;
int IN1 = 6;
int IN2 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(refPin, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
   if ( Serial.available() > 0 ) {
        //delay(10);
        char arg = Serial.read();
        Serial.println(arg);
        Serial.write(0);
        // change ref
        if(arg=='r'){
          int ref;
          while(1){
            if(Serial.available() > 0){
              ref = Serial.parseInt();
              ref = (int)( (float)ref/VCC * 255 );
              Serial.println(ref);
              break;
            }
          }
          analogWrite(refPin, ref);
        }
        // stop
        if(arg=='s'){
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
        }
        // roll right direction
        if(arg == 'h'){
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
        }
        // roll inversed direction
        if(arg == 'i'){
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          Serial.println("done");
        }
        // leave motor alone
        if(arg == 'l'){
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
        }
        // clear serial buffer
        Serial.write(0);
    } 
}

