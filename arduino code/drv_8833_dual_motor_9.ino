








int led_status;
const byte stepSequence[4][4] = {
  {HIGH, LOW, HIGH, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH}
};
int x_motor_pin_1 = 1;
int x_motor_pin_2 = 2;
int x_motor_pin_3 = 3;
int x_motor_pin_4 = 4;

int y_motor_pin_1 = A2;
int y_motor_pin_2 = A3;
int y_motor_pin_3 = A4;
int y_motor_pin_4 = A5;

# define x_stop 9
# define x2_stop 10
# define y_stop A1

# define x_step_pin 3//5//1
# define x_dir_pin 2//3
# define y_step_pin 1//5//1

# define xy_enable A0//4//2

int currentStep_x = 0; // Keeps track of where we are in the sequence
int currentStep_y = 0; // Keeps track of where we are in the sequence
int ledpin = 11;//10;
bool ledState = false;
int blinkDelay = 1000;
unsigned long previousMillisMotor = 0;
int moveCount = 0;
int countDelay = 0;
int buttonState = 0;
int buttonState_2 = 0;
const int buttonPin = 5;
const int buttonPin2 = 6;
unsigned long MoveDelay = 59710;//60000;
int step_delay_slow = 1255;
int step_delay_fast = 1500;
int x_count = 0;
int y_count = 0;

unsigned long previousMillis = 0;
boolean x_homestate = false;
boolean y_homestate = false;
// steps per mm for motor = 18 degrees/360 * 16 micrstepping
// 360/18 * 16 = 320
// gear ratio 1:100
// final steps per trun = 320 * 100 = 32000
// gear ratio in clock= 12:30 = 1:2.5
// one ful turn = 32000 * 2.5 = 80000
// number of digit stops = 10
// step per digit = 8000
int gear_ratio = 99; // error in tooth count
long one_turn_x = 20 * gear_ratio * 2.5; //79200
int one_digit_x = one_turn_x / 10;
int set_count = 0;
long one_turn_y = 20 * gear_ratio * 2; //63360 before it was 320* gear_ratio * 2(16 microstepping
int one_digit_y = one_turn_y / 12;//one_turn / 12;the cam has 12 parts
int set_count_y = 0;
unsigned long blinkMillis_delay = 0;
boolean dual_button_state = false;

int home_x_positon = 0;
int home_y_positon = 0;
boolean count_time = false;
unsigned long previousMillis_button = 0;
unsigned long previousMillis_button_y = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(x_motor_pin_1, OUTPUT);
  pinMode(x_motor_pin_2, OUTPUT);
  pinMode(x_motor_pin_3, OUTPUT);
  pinMode(x_motor_pin_4, OUTPUT);

  pinMode(y_motor_pin_1, OUTPUT);
  pinMode(y_motor_pin_2, OUTPUT);
  pinMode(y_motor_pin_3, OUTPUT);
  pinMode(y_motor_pin_4, OUTPUT);


  pinMode(ledpin, OUTPUT);

  pinMode(y_step_pin, OUTPUT);
  pinMode(x_step_pin, OUTPUT);
  pinMode(x_dir_pin, OUTPUT);
  pinMode(x_stop, INPUT);
  pinMode(y_stop, INPUT);
  pinMode(x2_stop, INPUT);
  pinMode(xy_enable, OUTPUT);

  //digitalWrite(x_dir_pin, LOW);
  enable_motor();
  home_x_new();
  home_y_new();


}

void loop() {






  time_step();
  time_step_y2();
  //move_motor_one_circle();
  //delay(2000);
  // move_motor_one_circle_y();
  reset_blink();
}



void time_step() {

  buttonState = digitalRead(buttonPin);
  int x2_state = digitalRead(x2_stop);
  blinkk();
  if (buttonState == HIGH) {
    enable_motor();
    move_motor();

    digitalWrite(ledpin, HIGH);
    unsigned long currentMillis_button = millis();
    if ( currentMillis_button - previousMillis_button > 6000) {

      previousMillis_button = currentMillis_button;

      dual_button_state = !dual_button_state;
      set_led_time();
    }

  }
  else {

    unsigned long currentMillisMotor = millis();

    if ((unsigned long)(currentMillisMotor - previousMillisMotor) >= MoveDelay) {
      previousMillisMotor += MoveDelay;
      enable_motor();

      move_motor();

    }
    motoroff();

  }


  motoroff();

}


void set_led_time() {
  if (dual_button_state == true) {
    blinkDelay = 100;
    count_time = true;
  }
  else blinkDelay = 1000;

}

void reset_blink() {
  if (count_time == true) {
    unsigned long currentMillis_delay = millis();

    if (currentMillis_delay - blinkMillis_delay > 30000) {
      blinkDelay = 1000;
      MoveDelay = 59710;
      blinkMillis_delay = currentMillis_delay;
      count_time = false;
    }



  }

}




void time_step_y() {

  buttonState_2 = digitalRead(buttonPin2);
  blinkk();
  if (buttonState_2 == HIGH) {
    enable_motor();
    move_motor_y();
    digitalWrite(ledpin, HIGH);

    unsigned long currentMillis_button_y = millis();
    if ( currentMillis_button_y - previousMillis_button_y > 2000) {

      previousMillis_button_y += MoveDelay;


      MoveDelay = 59710;
    }


  }
  else {

    unsigned long currentMillisMotor = millis();

    if ((unsigned long)(currentMillisMotor - previousMillisMotor) >= MoveDelay) {
      previousMillisMotor = currentMillisMotor;
      enable_motor();
      set_count_y = set_count_y + 1;
      move_motor_y();

    }
    motoroff();

  }


  motoroff();

}

void time_step_y2() {

  buttonState_2 = digitalRead(buttonPin2);

  if (buttonState_2 == HIGH) {
    enable_motor();
    move_motor_y();
    digitalWrite(ledpin, HIGH);
  }



  motoroff();

}
void home_x_new() {
  while (digitalRead(x_stop) == HIGH) {
    onestep();
  }
}
void home_y_new() {
  while (digitalRead(y_stop) == HIGH) {
    onestep_y();
    
  }
  move_back_y();
}

void motoroff() {
  digitalWrite(xy_enable, LOW);

}
void enable_motor() {
  digitalWrite(xy_enable, HIGH);
}




void move_motor() {



  //x_count = x_count + 1;
  //if (x_count >= 10) {
   // home_x_new();
  //  x_count = 0;

  //}
  //else {
    stepMotor_x(one_digit_x);
 //}

  int x2_state = digitalRead(x2_stop);
  set_count = set_count + 1;
  if (set_count > 9 && x2_state == 0 ) {
    move_motor_y();
    set_count = 0;
  }
}


void move_motor_y() {

  y_count = y_count + 1;
  if (y_count >= 12) {
    home_y_new();
    y_count = 0;
  }
  else {
    stepMotor_y(one_digit_y);
  }
}





void move_motor_one_circle() {
  stepMotor_x(one_turn_x);

  delay(2000);
}

void move_motor_one_circle_y() {

  stepMotor_y(one_turn_y);
  delay(2000);
}


void test_home_x() {
  int x_home = digitalRead(x_stop);
  if (x_home == HIGH) {
    digitalWrite(11, LOW);

  }
  else {
    digitalWrite(11, HIGH);
  }

}

void home_x() {

  x_homestate = false;

  int x_home = digitalRead(x_stop);
  digitalWrite(x_dir_pin, LOW);



  while (x_home == 1 ) {
    int x_home = digitalRead(x_stop);

    if (x_homestate == true) {
      //motor_disable();
      break;
    }
    if (x_home == 0) {

      //move_back();
      x_homestate = true;
      break;
    }
    onestep();

  }
}



void home_y() {

  y_homestate = false;

  int y_home = digitalRead(y_stop);
  digitalWrite(x_dir_pin, LOW);



  while (y_home == 1 ) {
    int y_home = digitalRead(y_stop);

    if (y_homestate == true) {
      //motor_disable();
      break;
    }
    if (y_home == 0) {

      //move_back_y();
      y_homestate = true;
      break;
    }
    onestep_y();

  }
}

void onestep_y() {


  stepMotor_y(1);
}


void onestep() {


  stepMotor_x(1);
}

void move_back() {
  stepMotor_x_reverse(1500);

}

void move_back_y() {
  stepMotor_y_reverse(170);
  stepMotor_y(80);
}

void blinkk() {

  unsigned long currentMillis = millis();
  //motoroff();
  if ((unsigned long)(currentMillis - previousMillis) >= blinkDelay) {

    ledState = !ledState;
    digitalWrite(ledpin, ledState);

    previousMillis = currentMillis;
  }

}

void motor_on() {
  digitalWrite(xy_enable, HIGH);

}







void stepMotor_x(int steps) {
  for (int x = 0; x < steps; x++) {
    // Apply the states from the array to the pins
    digitalWrite(x_motor_pin_1, stepSequence[currentStep_x][0]);
    digitalWrite(x_motor_pin_2, stepSequence[currentStep_x][1]);
    digitalWrite(x_motor_pin_3, stepSequence[currentStep_x][2]);
    digitalWrite(x_motor_pin_4, stepSequence[currentStep_x][3]);

    // Increment the step and loop back to 0 if it exceeds 3
    currentStep_x++;
    if (currentStep_x > 3) {
      currentStep_x = 0;
    }

    delayMicroseconds(step_delay_fast);
  }
}

void stepMotor_y(int steps) {
  for (int x = 0; x < steps; x++) {
    // Apply the states from the array to the pins
    digitalWrite(y_motor_pin_1, stepSequence[currentStep_y][0]);
    digitalWrite(y_motor_pin_2, stepSequence[currentStep_y][1]);
    digitalWrite(y_motor_pin_3, stepSequence[currentStep_y][2]);
    digitalWrite(y_motor_pin_4, stepSequence[currentStep_y][3]);

    // Increment the step and loop back to 0 if it exceeds 3
    currentStep_y++;
    if (currentStep_y > 3) {
      currentStep_y = 0;
    }

    delayMicroseconds(step_delay_fast);
  }
}



void stepMotor_x_reverse(int steps) {
  for (int x = 0; x < steps; x++) {

    // Energize the coils based on the current step
    digitalWrite(x_motor_pin_1, stepSequence[currentStep_x][0]);
    digitalWrite(x_motor_pin_2, stepSequence[currentStep_x][1]);
    digitalWrite(x_motor_pin_3, stepSequence[currentStep_x][2]);
    digitalWrite(x_motor_pin_4, stepSequence[currentStep_x][3]);

    // Move backward through the sequence array
    currentStep_x--;
    if (currentStep_x < 0) {
      currentStep_x = 3; // Wrap back to the end
    }

    delayMicroseconds(step_delay_slow);
  }
}



void stepMotor_y_reverse(int steps) {
  for (int x = 0; x < steps; x++) {

    // Energize the coils based on the current step
    digitalWrite(y_motor_pin_1, stepSequence[currentStep_y][0]);
    digitalWrite(y_motor_pin_2, stepSequence[currentStep_y][1]);
    digitalWrite(y_motor_pin_3, stepSequence[currentStep_y][2]);
    digitalWrite(y_motor_pin_4, stepSequence[currentStep_y][3]);

    // Move backward through the sequence array
    currentStep_y--;
    if (currentStep_y < 0) {
      currentStep_y = 3; // Wrap back to the end
    }

    delayMicroseconds(step_delay_slow);
  }
}
