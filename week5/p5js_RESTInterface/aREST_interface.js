let button1, button2, button3;
let brightSlide, slideSend;
let IPAddress, IPsub;
let getPot;
let url = "http://";
let potVal = 0;

function setup() {
  createCanvas(windowWidth, windowHeight);
  button1 = createButton("set pin 15 to output");
  button2 = createButton("pin 15 on");
  button3 = createButton("pin 15 off");
  IPsub = createButton("submit");
  slideSend = createButton("send analog val");
  getPot = createButton("get pot value");

  IPAddress = createInput('enter IP address');
  brightSlide = createSlider(0, 255, 0);

  IPAddress.position(200, 10);
  
  brightSlide.position(10, 110);
  
  getPot.position(10, 140);

  slideSend.position(150, 110);
  IPsub.position(IPAddress.x + IPAddress.width, 10);
  button1.position(10, 10);
  button2.position(10, 45);
  button3.position(10, 80);

  slideSend.mousePressed(sendAnalog);
  IPsub.mousePressed(setIP);
  button1.mousePressed(mode);
  button2.mousePressed(ledOn);
  button3.mousePressed(ledOff);
  getPot.mousePressed(getA0);
  background(255);

}

function draw() {
  background(255);
text(potVal, getPot.x + getPot.width+5, 150);
}

function getA0(){
  let pin, cmd, state;
  state = 'r';
  pin = "0";
  cmd ="analog";
  httpGet(url+cmd+"/"+pin+"/"+state, 'json', parseText);
}

function sendAnalog(){
  let pin, cmd, state;
  state = brightSlide.value();
  pin = "15";
  cmd ="analog";
  httpGet(url+cmd+"/"+pin+"/"+state, printResp);
}

function setIP(){
  const IPaddr = IPAddress.value();
  url = "http://" + IPaddr + "/";
}

function mode() {
  let pin, cmd, state;
  state = "o";
  pin = "15";
  cmd ="mode";
  httpGet(url+cmd+"/"+pin+"/"+state, printResp);
}

function ledOn() {
  let pin, cmd, state;
  state = "1";
  pin = "15";
  cmd ="digital";
  httpGet(url+cmd+"/"+pin+"/"+state, printResp);
}

function ledOff() {
  let pin, cmd, state;
  state = "0";
  pin = "15";
  cmd ="digital";
  httpGet(url+cmd+"/"+pin+"/"+state, printResp);
}


function printResp(data) {
  console.log(data);
}

function parseText(data){
  console.log(data);
  potVal = data.return_value;
}
