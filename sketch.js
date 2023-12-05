// WiFi 参数
let SERVER_ADDRESS = "http://192.168.1.174/data";

// WiFi 变量
let readyToLoad = true;

// 项目变量
let mPlayer = {
  x: 50,  // 初始 X 位置
  y: 50,  // 初始 Y 位置
  diameter: 40,  // 初始直径
};

function parseData(res) {
  console.log("Received data:", res); // 打印接收到的整个响应数据

  let data = res.data;
  let d3 = data.D3.isPressed;
  let d4 = data.D4.isPressed;

  console.log('D3:', d3, 'D4:', d4); // 打印具体的按钮状态

  if (d3) {
    mPlayer.x -= 10; // 向左移动
  } 
  if (d4) {
    mPlayer.x += 10; // 向右移动
  }

  mPlayer.x = constrain(mPlayer.x, 0, width); // 确保圆形不会离开画布边界

  readyToLoad = true; // 设置为 true，以便在下一次 draw 循环中再次加载数据
}

function setup() {
  // 初始化项目
  createCanvas(windowWidth, windowHeight);
  mPlayer.y = height / 2;  // 将方块的 Y 位置设置在画布中间
  console.log('Setup completed');  // 打印初始化完成信息
}

function draw() {
  background(220, 20, 120);
  ellipse(mPlayer.x, mPlayer.y, mPlayer.diameter);
  // console.log(readyToLoad);
  if (readyToLoad) {
    readyToLoad = false;
    console.log("Requesting data..."); // 打印请求发出的信息
    loadJSON(SERVER_ADDRESS, parseData, function(err) {
      console.error("Error loading JSON: ", err); // 错误处理
    });
  }
}
