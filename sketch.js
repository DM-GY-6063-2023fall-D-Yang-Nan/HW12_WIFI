// WiFi parameter
let SERVER_ADDRESS = "http://10.10.81.101/data";

// WiFi variable
let readyToLoad;

// project variables
let mPlayer = {
  x: 0,
  y: 0,
  diameter: 0,
};

function parseData(res) {
  // get data from WiFi response
  let data = res.data;
  let a0 = data.A0;
  let d2 = data.D2;

  // use data to update project variables
  mPlayer.x = map(a0.value, 0, 4095, 0, width);
  mPlayer.diameter = map(d2.count, 0, 20, 20, 80);

  if (d2.isPressed) {
    mPlayer.y -= 100;
  } else if (mPlayer.y < height - 100) {
    mPlayer.y += 16;
  }

  // WiFi update
  readyToLoad = true;
}

function setup() {
  // project setup
  createCanvas(windowWidth, windowHeight);
  mPlayer = {
    x: 0,
    y: height - 100,
    diameter: 20,
  };

  // WiFi setup
  readyToLoad = true;
}

function draw() {
  // project code
  background(220, 20, 120);
  ellipse(mPlayer.x, mPlayer.y, mPlayer.diameter, mPlayer.diameter);

  // WiFi update
  if (readyToLoad) {
    readyToLoad = false;
    loadJSON(SERVER_ADDRESS, parseData);
  }
}
