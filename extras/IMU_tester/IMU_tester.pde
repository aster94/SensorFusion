/*
This code is made for processing https://processing.org/
*/

import processing.serial.*;     // import the Processing serial library
Serial myPort;                  // The serial port
String my_port = "COM11";      	// choose your port
float xx, yy, zz;

void setup() {
  size(1024, 800, P3D);

  myPort = new Serial(this, my_port, 115200);
  myPort.bufferUntil('\n');

  smooth();
}

void draw() {
  background(0);
  noStroke();
  translate(width/2, height/2);
  pushMatrix();
  rotateX(xx);//pitch
  rotateY(zz);//yaw
  rotateZ(yy);//roll
  box(100, 50, 600);
  popMatrix();
}


void serialEvent(Serial myPort) {

  String myString = myPort.readStringUntil('\n');
  myString = trim(myString);
  float sensors[] = float(split(myString, ':'));
  
  xx = sensors[0];
  yy = sensors[1];
  zz = sensors[2];
  
  //println("roll: " + xx + " pitch: " + yy + " yaw: " + zz + "\n"); //debug

}