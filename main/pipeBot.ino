/*
   Skills 2018 Pipe Bot Code v2
   @authour Josh Dhori

   Change Log:
   +initPipeBot()
   +updatePWM()
   +updateServos()
   +updateServos(int, bool)
   +moveServos(int, bool)

   Note:
   The majority of this code is theoretical and has not been yet tested.
   Most bytes and ints have not yet been assigned as the values have not been found via testing,
   so they need to be found and the code needs to be updated before this will work

*/

//Servos
Servo gripper, upperClaw, lowerClaw, base;

//Servo pins
byte gripperPin;
byte upperClawPin;
byte lowerClawPin;
byte basePin;

//Radio PWM input pins
byte gipperInputPin;
byte upperClawInputPin;
byte lowerClawInputPin;
byte baseInputPin;

//Radio PWM input
int gripperInput;
int upperClawInput;
int lowerClawInput;
int baseInput;
int toggleGripper;
int toggleUpperClaw;
int toggleLowerClaw;
int toggleBase;

//Servo values
bool gripperPos, upperClawPos, lowerClawPos, basePos; //which value the servos are currently at
byte maxGripper = 150;
byte minGripper = 50;
byte maxUpperClaw;
byte minUpperClaw;
byte maxLowerClaw;
byte minLowerClaw;
byte maxBase;
byte minBase;

int servoDelay;

//initialize the pipe bot
void initPipeBot(bool maxmin) {
  //init console
  Serial.begin(115200);

  //set the PWM input pins
  pinMode(gipperInputPin, INPUT);
  pinMode(upperClawInputPin, INPUT);
  pinMode(lowerClawInputPin, INPUT);
  pinMode(baseInputPin, INPUT);

  //attach the servos
  gripper.attach(gripperPin);
  upperClaw.attach(upperClawPin);
  lowerClaw.attach(lowerClawPin);
  base.attach(basePin);

  //move *all* them to the max or min value
  if (maxmin) {
    gripper.write(maxGripper);
    upperClaw.write(maxUpperClaw);
    lowerClaw.write(maxLowerClaw);
    base.write(maxBase);

    gripperPos = true;
    upperClawPos = true;
    lowerClawPos = true;
    basePos = true;

  } else {
    gripper.write(minGripper);
    upperClaw.write(minUpperClaw);
    lowerClaw.write(minLowerClaw);
    base.write(minBase);

    gripperPos = false;
    upperClawPos = false;
    lowerClawPos = false;
    basePos = false;
  }
}

//Update the PWM values
void updatePWM() {
  gripperInput = pulseIn(gipperInputPin, HIGH);
  upperClawInput = pulseIn(upperClawInputPin, HIGH);
  lowerClawInput = pulseIn(lowerClawInputPin, HIGH);
  baseInput = pulseIn(baseInputPin, HIGH);
}

void updateServos() {
  if (baseInput == toggleBase) {
    updateServos(4, !basePos);
  } else if (lowerClawInput == toggleLowerClaw) {
    updateServos(3, !lowerClawPos);

  } else if (upperClawInput == toggleUpperClaw) {
    updateServos(2, !upperClawPos);

  } else if (gripperInput == toggleGripper) {
    updateServos(1, !gripperPos);
  }
}

void updateServos(int servoNum, bool dir) {
  if (servoNum == 4) {
    basePos = dir;
    moveServos(servoNum, basePos);
  }
  else if (servoNum == 3) {
    lowerClawPos = dir;
    moveServos(servoNum, lowerClawPos);
  }
  else if (servoNum == 2) {
    upperClawPos = dir;
    moveServos(servoNum, upperClawPos);
  }
  else if (servoNum == 1) {
    gripperPos = dir;
    moveServos(servoNum, griperPos);
  }
  updateServos(servoNum - 1, dir);
}

void moveServos(int servoNum, bool dir) {
  if (dir) {
    if (servoNum == 4) {
      base.write(maxBase);
      delay(servoDelay);
    }
    else if (servoNum == 3) {
      lowerClaw.write(maxLowerClaw);
      delay(servoDelay);
    }
    else if (servoNum == 2) {
      upperClaw.write(maxUpperClaw);
      delay(servoDelay);
    }
    else if (servoNum == 1) {
      gripper.write(maxGripper);
      delay(servoDelay);
    }
  }
  else {
    if (servoNum == 4) {
      base.write(minBase);
      delay(servoDelay);
    }
    else if (servoNum == 3) {
      lowerClaw.write(minLowerClaw);
      delay(servoDelay);
    }
    else if (servoNum == 2) {
      upperClaw.write(minUpperClaw);
      delay(servoDelay);
    }
    else if (servoNum == 1) {
      gripper.write(minGripper);
      delay(servoDelay);
    }
  }
  updateServos(servoNum - 1, dir);
}

