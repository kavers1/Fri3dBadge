#include <Fri3dAccelerometer.h>
#include <Fri3dBuzzer.h>
#include <Fri3dButtons.h>
#include <Fri3dMatrix.h>

Fri3dAccelerometer accel = Fri3dAccelerometer();
Fri3dBuzzer buzzer = Fri3dBuzzer();
Fri3dButtons buttons = Fri3dButtons();
Fri3dMatrix matrix = Fri3dMatrix();

#define LeftEye 0
#define RightEye 7


// RENDER FOX EYES WITH ACCELEROMETER

int frame = 0;
int frame_blink = 40;
void renderFoxEyes() {
  // render eyes based on accelerometer
  sensors_event_t event; 
  accel.getEvent(&event);
  matrix.clear();
  int x = 1 + 5 * ( event.acceleration.y + 12 ) / 24;
  if( frame_blink - 2 > frame ) {
    matrix.setPixel( x    , 0, 1 );
    matrix.setPixel( x + 7, 0, 1 );
    matrix.setPixel( x    , 4, 1 );
    matrix.setPixel( x + 7, 4, 1 );
  }
  if( frame_blink - 1 > frame ) {
    matrix.setPixel( x - 1, 1, 1 );
    matrix.setPixel( x    , 1, 1 );
    matrix.setPixel( x + 1, 1, 1 );
    matrix.setPixel( x + 6, 1, 1 );
    matrix.setPixel( x + 7, 1, 1 );
    matrix.setPixel( x + 8, 1, 1 );
    
    matrix.setPixel( x - 1, 2, 1 );
    matrix.setPixel( x + 1, 2, 1 );
    matrix.setPixel( x + 6, 2, 1 );
    matrix.setPixel( x + 8, 2, 1 );

    matrix.setPixel( x - 1, 3, 1 );
    matrix.setPixel( x    , 3, 1 );
    matrix.setPixel( x + 1, 3, 1 );
    matrix.setPixel( x + 6, 3, 1 );
    matrix.setPixel( x + 7, 3, 1 );
    matrix.setPixel( x + 8, 3, 1 );
  }
  if( frame_blink == frame ) {
    matrix.setPixel( x - 1, 2, 1 );
    matrix.setPixel( x    , 2, 1 );
    matrix.setPixel( x + 1, 2, 1 );
    matrix.setPixel( x + 6, 2, 1 );
    matrix.setPixel( x + 7, 2, 1 );
    matrix.setPixel( x + 8, 2, 1 );
    frame_blink = frame_blink + rand() % 90 + 30;
  }
  frame++;
  if( frame > frame_blink )
    frame_blink = frame + rand() % 90 + 30;
  delay(50);
}

void blinkEye(int eye,int cnt){
  sensors_event_t event; 
  accel.getEvent(&event);
  int x = 1 + 5 * ( event.acceleration.y + 12 ) / 24;
  for(int i = 0; i < cnt;i++){
    matrix.setPixel( x     + eye, 0, 0 );
    matrix.setPixel( x     + eye, 4, 0 );
    matrix.setPixel( x - 1 + eye, 1, 0 );
    matrix.setPixel( x     + eye, 1, 1 );
    matrix.setPixel( x + 1 + eye, 1, 0 );
    matrix.setPixel( x - 1 + eye, 2, 1 );
    matrix.setPixel( x     + eye, 2, 1 );
    matrix.setPixel( x + 1 + eye, 2, 1 );
    matrix.setPixel( x - 1 + eye, 3, 0 );
    matrix.setPixel( x     + eye, 3, 0 );
    matrix.setPixel( x + 1 + eye, 3, 0 );
    delay(100);
  
    matrix.setPixel( x     + eye, 0, 1 );
    matrix.setPixel( x     + eye, 4, 1 );
    matrix.setPixel( x - 1 + eye, 1, 1 );
    matrix.setPixel( x     + eye, 1, 1 );
    matrix.setPixel( x + 1 + eye, 1, 1 );
    matrix.setPixel( x - 1 + eye, 2, 1 );
    matrix.setPixel( x + 1 + eye, 2, 1 );
    matrix.setPixel( x - 1 + eye, 3, 1 );
    matrix.setPixel( x     + eye, 3, 1 );
    matrix.setPixel( x + 1 + eye, 3, 1 );
    matrix.setPixel( x - 1 + eye, 2, 1 );
    matrix.setPixel( x     + eye, 2, 1 );
    matrix.setPixel( x + 1 + eye, 2, 1 );
    delay(100);
  }
}


void setup() {
  accel.begin();
  accel.setPowerConfig( 0b00101000);  
  Serial.begin(115200);
  accel.displaySensorDetails();

   // Set tap detection on Z-Axis
  accel.setTapDetectionX(0);       // Don't check tap on X-Axis
  accel.setTapDetectionY(0);       // Don't check tap on Y-Axis
  accel.setTapDetectionZ(1);       // Check tap on Z-Axis
  // or
  // accelerometer.setTapDetectionXYZ(1);  // Check tap on X,Y,Z-Axis

  accel.setTapThreshold(2.5);      // Recommended 2.5 g
  accel.setTapDuration(0.02);      // Recommended 0.02 s
  accel.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accel.setDoubleTapWindow(0.30);  // Recommended 0.30 s

  accel.setActivityThreshold(2.0);    // Recommended 2 g
  accel.setInactivityThreshold(2.0);  // Recommended 2 g
  accel.setTimeInactivity(5);         // Recommended 5 s

  // Set activity detection only on X,Y,Z-Axis
  accel.setActivityXYZ(1);         // Check activity on X,Y,Z-Axis
  accel.setActivityAC(1);          // activity AC decoupled
  // or
  // accelerometer.setActivityX(1);        // Check activity on X_Axis
  // accelerometer.setActivityY(1);        // Check activity on Y-Axis
  // accelerometer.setActivityZ(1);        // Check activity on Z-Axis

  // Set inactivity detection only on X,Y,Z-Axis
  accel.setInactivityXYZ(1);       // Check inactivity on X,Y,Z-Axis
  accel.setInactivityAC(1);        // inactivity AC decoupled
  // or
  // accelerometer.setInactivityX(1);      // Check inactivity on X_Axis
  // accelerometer.setInactivityY(1);      // Check inactivity on Y-Axis
  // accelerometer.setInactivityZ(1);      // Check inactivity on Z-Axis

  // Select INT 1 for get activities
  accel.useInterrupt(ADXL345_INT1);

  // Select INT 1 for get activities
  accel.useInterrupt(ADXL345_INT1);

  
  // Check settings
  checkSetup();
  buzzer.setVolume( 255 );
  buzzer.setFrequency( 600 );
  delay( 120 );
  buzzer.setFrequency( 500 );
  delay( 120 );
  buzzer.setVolume(0);
  
}
void checkSetup()
{
  Serial.print("Look tap on axis = "); 
  if (accel.getTapDetectionX()) { Serial.print(" X "); }
  if (accel.getTapDetectionY()) { Serial.print(" Y "); }
  if (accel.getTapDetectionZ()) { Serial.print(" Z "); }
  Serial.println();

  Serial.print("Tap Threshold = "); Serial.println(accel.getTapThreshold());
  Serial.print("Tap Duration = "); Serial.println(accel.getTapDuration());
  Serial.print("Double Tap Latency = "); Serial.println(accel.getDoubleTapLatency());
  Serial.print("Double Tap Window = "); Serial.println(accel.getDoubleTapWindow());

  Serial.print("Activity Threshold = "); Serial.println(accel.getActivityThreshold());
  Serial.print("Inactivity Threshold = "); Serial.println(accel.getInactivityThreshold());
  Serial.print("Time Inactivity = "); Serial.println(accel.getTimeInactivity());

  Serial.print("Look activity on axis = "); 
  if (accel.getActivityX()) { Serial.print(" X "); }
  if (accel.getActivityY()) { Serial.print(" Y "); }
  if (accel.getActivityZ()) { Serial.print(" Z "); }
  if (accel.getActivityAC()) {Serial.print(" AC ");} else {Serial.print(" DC ");}
  Serial.println();

  Serial.print("Look inactivity on axis = "); 
  if (accel.getInactivityX()) { Serial.print(" X "); }
  if (accel.getInactivityY()) { Serial.print(" Y "); }
  if (accel.getInactivityZ()) { Serial.print(" Z "); }
  if (accel.getInactivityAC()) {Serial.print(" AC ");} else {Serial.print(" DC ");}
  Serial.println();  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print("====");
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500);
  // Read activities
  Activites activ = accel.readActivites();

  if (activ.isDoubleTap)
  {
    Serial.println("Double Tap Detected");
    pixels.setPixelColor(1, pixels.Color(0,128,0));
  } else
  if (activ.isTap)
  {
    Serial.println("Tap Detected");
    pixels.setPixelColor(1, pixels.Color(128,0,0));
  }
  if (activ.isActivity)
  {
    Serial.println("Activity Detected");
    pixels.setPixelColor(0, pixels.Color(128,0,128));

  }
  if (activ.isInactivity)
  {
    Serial.println("Inactivity Detected");
    pixels.setPixelColor(0, pixels.Color(0,128,128));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
  }

  pixels.show();
  renderFoxEyes();

}
