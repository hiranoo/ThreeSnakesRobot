mport processing.serial.*;
Serial port;
int NUM = 3;
int[] data = new int[NUM]; //preserve read serial data from arduino
String[] sdata = new String[3];
int offsetX,offsetY;
int rodWidth, rodHeight;
int barWidth, barHeight;
int scaleNum;
int MODE;

void setup(){
  size(600,600);
  background(0);
  //port = new Serial(this, "COM5", 9600);
  port = new Serial(this, "COM3", 115200);
  textSize(15);
  offsetX = width/4; offsetY = 100;
  rodWidth = 50; rodHeight = 360;
  barWidth = rodWidth; barHeight = 5;
  scaleNum = 9;
  MODE= 0;
  
  //init data
  for(int i = 0; i < NUM; i++){
    data[i] = -100;
  }
  sdata[0] = "   "; sdata[1]="   "; sdata[2] = "    ";
  
  // draw all rods
  drawRod(1); drawRod(2); drawRod(3);
  // draw buttons
  drawButton(MODE);
  // draw scale
  fill(255);
  for(int i = 0; i <= scaleNum; i++){
    text(180-180*i/scaleNum,offsetX-40, offsetY+rodHeight*i/scaleNum);
  }
}

void draw(){
  // print data
  fill(0);
  rect(offsetX+rodWidth*6,offsetY,200,300);
  fill(200,0,0);
  text("num:"+ data[1] + " arg:" + data[2], offsetX+rodWidth*6,offsetY+ 30);
  text("sdata num:"+ sdata[1] + " arg:" + sdata[2], offsetX+rodWidth*6,offsetY+ 200);
  text("header: " + sdata[0], offsetX+rodWidth*6, offsetY+ 100);
}

// send value to arduino & print the value
void mousePressed(){
   int x,y,n;
   x = mouseX; y = mouseY;  
   n = touchRod(x,y);  
   if(n > 0){
     port.clear();
     port.write("P");
     port.write(n);
     port.write(arg(y));

     drawRod(n);
     drawBar(n,y);
     printArg(n,y);
   }else if(touchButton(x,y)!=-1){
     port.clear();
     port.write("P");
     port.write(MODE);
     port.write(MODE);
     
     drawButton(MODE);
   }
}

void drawRod(int num){
  fill(220);
  rect(offsetX+rodWidth*2*(num-1),offsetY,rodWidth,rodHeight);
}

void drawBar(int num, int y){
  switch(num){
    case 1:
    fill(255,0,0);
    break;
    case 2:
    fill(0,255,0);
    break;
    case 3:
    fill(0,0,255);
    break;
  }
  rect(offsetX+rodWidth*2*(num-1),y,barWidth,barHeight);
}

void drawButton(int mode){
  switch(mode){
    case 0:
    fill(100,0,220);
    rect(offsetX,offsetY/3,rodWidth*3/2,offsetY/3);
    fill(220);
    rect(offsetX+rodWidth*2,offsetY/3, rodWidth*3/2, offsetY/3);
    break;
    case 1:
    fill(100,0,220);
    rect(offsetX+rodWidth*2,offsetY/3,rodWidth*3/2,offsetY/3);
    fill(220);
    rect(offsetX,offsetY/3, rodWidth*3/2, offsetY/3);
    break;
  }
  text("modurate",offsetX,offsetY/3);
  text("waving", offsetX+rodWidth*2,offsetY/3);
}  

int touchButton(int x, int y){
  if(offsetY/3<y && y<offsetY/3*2){
    if(offsetX<x && x<offsetX+rodWidth*3/2){
      MODE = 0;
      return 0;
    }else if(offsetX+rodWidth*2<x && x<offsetX+rodWidth*2+rodWidth*3/2){
      MODE = 1;
      return 1;
    }
  }
  return -1;   
}

void printArg(int num, int y){
  // delete the previous arg
  fill(200,130,0);
  rect(offsetX+rodWidth*2*(num-1),offsetY+rodHeight,rodWidth*2, 30);
  
  //write arg value
  fill(255);
  text(arg(y), offsetX+rodWidth*2*(num-1),offsetY+rodHeight+20);
}

int touchRod(int x, int y){
  if(offsetY<y && y<offsetY+rodHeight){
    if(offsetX<x && x <offsetX+rodWidth){
      return 1;
    }else if(offsetX+rodWidth*2<x && x <offsetX+rodWidth*3){
      return 2;
    }else if(offsetX+rodWidth*4<x && x <offsetX+rodWidth*5){
      return 3;
    }
  }
  return -1;
}
      
int arg(int y){
  return (int)((float)(offsetY+rodHeight-y)/(float)rodHeight*180);
}

void serialEvent(Serial port){
  String stringData = port.readStringUntil(10);
  
  if(stringData != null){
    stringData = trim(stringData);
    String[] buf = split(stringData, ',');
    sdata[0] = buf[0];
    if(buf[0].equals("A")){
      data = int(split(stringData,','));
      sdata[1] = buf[1];
      sdata[2] = buf[2];
      port.write(0);
    }
  }
}
