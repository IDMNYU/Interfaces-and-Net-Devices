let url = "http://192.168.43.34/"; // string to hold URL
let servoVal = 0; // variable that holds the potVal

function setup() {
  createCanvas(720, 256);
  frameRate(10);
}

function draw() {
  background(map(mouseX, 0, width, 0, 255));
  servoVal= map(mouseX, 0, width, 1, 10);
  if (mouseIsPressed) {
    servoPos();
  }
}

function servoPos() {
  let cmd;
  cmd ="servo?params=";
  httpGet(url+cmd+servoVal, 'json');
  console.log(url+cmd+servoVal);
}
