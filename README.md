# Final Project Template using WiFi

Arduino reads a button on pin 2 and a potentiometer on pin A0 and passes those values on to the p5js sketch using a WiFi connection.

The object that is created and sent to p5js looks like this:

```
data = {
  A0: { value: integer },
  D2: {
    isPressed: boolean,
    count: integer
  }
}
```

In p5js ```A0.value``` is used to change ellipse position in X, ```D2.isPressed``` is used to change position in Y and ```D2.count``` is used to change the size of the ellipse.

## Important
Before uploading code to Arduino board, make sure to copy ```config.example.h``` to ```config.h``` and update it with a valid WiFi ID and password.

## Schematic
![](https://6063d.github.io/imgs/FinalProject_sch.jpg)

## Board
![](https://6063d.github.io/imgs/FinalProject_bb.jpg)
