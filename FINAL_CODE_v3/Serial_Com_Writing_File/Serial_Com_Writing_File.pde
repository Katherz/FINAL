import processing.serial.*;
Serial myPort;
PrintWriter output; 
int r;
int g;
int b;

void setup() {
  output = createWriter("data/data.txt");
  myPort = new Serial(this, "/dev/tty.usbmodemfa121", 9600);
  myPort.bufferUntil('\n');
}

void draw(){
  write();
}

void serialEvent(Serial myPort){
  
  String myString = myPort.readStringUntil('\n');
  int data [] = int(split(myString,','));
  if (myString! = null){
    r = data[0];
    g = data[1];
    b = data[2];
    println("Printing RGB Vals to File");
    
  }
}
 void write(){
   output.println(r+","+g+","+b);
   output.flush();
   
void stop(){
  output.close();
  super.stop();
}
