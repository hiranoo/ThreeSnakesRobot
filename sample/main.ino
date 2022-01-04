nclude <Servo.h>
Servo servo1, servo2, servo3;

//DEFINE
float midArg1, midArg2, midArg3;
float ampArg1, ampArg2, ampArg3;
float minArg1, minArg2, minArg3;
float maxArg1, maxArg2, maxArg3;
float arg1, arg2, arg3;
int c1, c2, c3;
int count;
float cycle1, cycle2, cycle3;
int LOOPTIME = 200; //msec
int MODE; //0:modulate, 1:wave 
int header;
int num,arg,preNum,preArg;

void modurate(int,int);
void wavingArg(int,int,int);

void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);
  
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  pinMode(13,OUTPUT);

  midArg1 = 87;
  midArg2 = 90;
  midArg3 = 87;

  ampArg1 = 40;
  ampArg2 = 40;
  ampArg3 = 40;

  minArg1 = 5;
  minArg2 = 5;
  minArg3 = 5;

  maxArg1 = 175;
  maxArg2 = 175;
  maxArg3 = 175;

  arg1 = arg2 = arg3 = 90;
  c1 = midArg1; c2 = midArg2; c3 = midArg3;
  
  count = 0;

  cycle1 = 1000 / LOOPTIME * ampArg1 / 10.0;
  cycle2 = 1000 / LOOPTIME * ampArg2 / 10.0;
  cycle3 = 1000 / LOOPTIME * ampArg3 / 10.0;

  MODE = -1;
  
  initArg();
}

void loop() {
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
      MODE = num;
    }
    delay(10);
  }
  if(MODE == 0){
    modurate(-1,-1);
    digitalWrite(13,LOW);
  }else if(MODE==1){
    digitalWrite(13,HIGH);
    switch(num){
      case 1:
      c1 = arg;
      break;
      case 2:
      c2 = arg;
      break;
      case 3:
      c3 = arg;
      break;
    }
    wavingArg(c1,c2,c3);
  }
}

// initArg
void initArg(){
  arg1 = calcArg(1, midArg1, ampArg1, calcPhase(count, cycle1));
  arg2 = calcArg(2, midArg2, ampArg2, calcPhase(count, cycle2));
  arg3 = calcArg(3, midArg3, ampArg3, calcPhase(count, cycle3));
}
// check arg is appropriate or not
float checkArg(int servoNum, float arg){
  if(servoNum == 1){
    if(arg < minArg1){
      return minArg1;
    }else if(arg > maxArg1){
      return maxArg1;
    }
    return arg;
  }
  if(servoNum == 2){
    if(arg < minArg2){
      return minArg2;
    }else if(arg > maxArg2){
      return maxArg2;
    }
    return arg;
  }
  if(servoNum == 3){
    if(arg < minArg3){
      return minArg3;
    }else if(arg > maxArg3){
      return maxArg3;
    }
    return arg;
  }
}

//calculate phase
float calcPhase(int count, float cycle) {
  return 2 * PI * count / cycle;
}

//calculate waving arg
float calcArg(int servoNum, float coreArg, float ampArg, float phase) {
  return checkArg( servoNum, coreArg + ampArg * sin(phase) );
}

void wavingArg(int coreArg1, int coreArg2, int coreArg3){
  float phase1, phase2, phase3;
  count =0;

  while(MODE == 1){
    phase1 = calcPhase(count, cycle1);
    phase2 = calcPhase(count, cycle2);
    phase3 = calcPhase(count, cycle3);

    servo1.write( calcArg(1, coreArg1, ampArg1, phase1));
    servo2.write( calcArg(2, coreArg2, ampArg2, phase2));
    servo3.write( calcArg(3, coreArg3, ampArg3, phase3));

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
        MODE = num;
        if(MODE == 0){
          modurate(5,0);
          digitalWrite(13,LOW);
        }
      }else{
      delay(10);
      digitalWrite(13,HIGH);
      switch(num){
      case 1:
        c1 = arg;
        break;
      case 2:
        c2 = arg;
        break;
      case 3:
        c3 = arg;
        break;
      }
      wavingArg(c1,c2,c3);
      }
    }
    count++;
    if(count > 150000){
      count = 0;
    }
    delay(LOOPTIME);
  }
}

void modurate(int num, int arg){ 
  while(MODE == 0){
    switch(num){
      case 1:  
        servo1.write( arg );
        break;
      case 2:    
        servo2.write( arg );
        break; 
      case 3:
        servo3.write( arg );
        break;
    }
    // read processing command
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
     // mode change
     if(num==arg){
       MODE = num;
       if(MODE==1){
        digitalWrite(13,HIGH);
        wavingArg(c1,c2,c3);
        }
      }
      delay(10);
    }
    delay(LOOPTIME);
  }
}

