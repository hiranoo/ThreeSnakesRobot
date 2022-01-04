nt count;
void setup(){
  Serial.begin(115200);
  count = 0;
}

void loop(){
  Serial.println(count);
  count++;
  if(count > 20){
    count = 0;
  }
  delay(50);
}
/*
#include <SoftwareSerial.h>

int bluetoothRx = 1;  // RX-I of bluetooth
int bluetoothTx = 0;  // TX-O of bluetooth

int count = 0; //送信用カウンタ

SoftwareSerial mySerial(bluetoothRx, bluetoothTx); // RX, TX

void setup()  
{
  // Bluetooth用のシリアルオープン
  mySerial.begin(115200);
}

void loop()
{
    // Bluetoothへ送信
    mySerial.println(count);

    count++;

    delay(1000);
}
*/

