ar header;
int num, arg;
int mode;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  num = -9; arg = -9;
  mode = -1;
  pinMode(13,OUTPUT);
  pinMode(5,OUTPUT);
  
}

void loop(){
  if(mode == 1){
    digitalWrite(13,HIGH);
  }else if(mode == 0){
    digitalWrite(13,LOW);
  }
  if(Serial.available() > sizeof(int)){
    header = Serial.read();
    delay(1);
    if(header == 'P'){
      num = Serial.read();
      arg = Serial.read();
 
      // send received data to processing      
      //num=1; arg = 120;
      Serial.print('A');
      Serial.print(",");
      Serial.print(num,DEC);
      Serial.print(",");
      Serial.println(arg,DEC);
    }
    if(num==arg){
      mode = num;
    }
    delay(10);
  }
}


