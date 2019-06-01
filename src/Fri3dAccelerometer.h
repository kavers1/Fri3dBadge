// ensure this library description is only included once
// 
// expanded based on the ADXL library https://github.com/jarzebski/Arduino-ADXL345
// Version: 1.1.0
//
#ifndef Fri3dAccelerometer_h
#define Fri3dAccelerometer_h

#include "Adafruit_ADXL345_U.h"
#include "Adafruit_Sensor.h"

typedef enum
{
    ADXL345_INT2 = 0b01,
    ADXL345_INT1 = 0b00
} adxl345_int_t;

typedef enum
{
    ADXL345_DATA_READY         = 0x07,
    ADXL345_SINGLE_TAP         = 0x06,
    ADXL345_DOUBLE_TAP         = 0x05,
    ADXL345_ACTIVITY           = 0x04,
    ADXL345_INACTIVITY         = 0x03,
    ADXL345_FREE_FALL          = 0x02,
    ADXL345_WATERMARK          = 0x01,
    ADXL345_OVERRUN            = 0x00
} adxl345_activity_t;

struct Activites
{
    bool isOverrun;
    bool isWatermark;
    bool isFreeFall;
    bool isInactivity;
    bool isActivity;
    bool isActivityOnX;
    bool isActivityOnY;
    bool isActivityOnZ;
    bool isDoubleTap;
    bool isTap;
    bool isTapOnX;
    bool isTapOnY;
    bool isTapOnZ;
    bool isDataReady;
};

// library interface description
class Fri3dAccelerometer {
protected:
  Adafruit_ADXL345_Unified adxl345;
public:
  Fri3dAccelerometer();
  
  void begin();
  
  bool getEvent(sensors_event_t *event);

  void displaySensorDetails(void);
  void displayDataRate(void);
  void displayRange(void);

  void clearSettings(void);
  
  Activites readActivites(void);

  Vector lowPassFilter(Vector vector, float alpha = 0.5);

  void setTapThreshold(float threshold);
  float getTapThreshold(void);

  void setTapDuration(float duration);
  float getTapDuration(void);

  void setDoubleTapLatency(float latency);
  float getDoubleTapLatency(void);

  void setDoubleTapWindow(float window);
  float getDoubleTapWindow(void);

  void setActivityThreshold(float threshold);
  float getActivityThreshold(void);

  void setInactivityThreshold(float threshold);
  float getInactivityThreshold(void);

  void setTimeInactivity(uint8_t time);
  uint8_t getTimeInactivity(void);

  void setFreeFallThreshold(float threshold);
  float getFreeFallThreshold(void);

  void setFreeFallDuration(float duration);
  float getFreeFallDuration();

  void setActivityX(bool state);
  bool getActivityX(void);
  void setActivityY(bool state);
  bool getActivityY(void);
  void setActivityZ(bool state);
  bool getActivityZ(void);
  void setActivityXYZ(bool state);

  void setInactivityX(bool state);
  bool getInactivityX(void);
  void setInactivityY(bool state);
  bool getInactivityY(void);
  void setInactivityZ(bool state);
  bool getInactivityZ(void);
  void setInactivityXYZ(bool state);

  void setTapDetectionX(bool state);
  bool getTapDetectionX(void);
  void setTapDetectionY(bool state);
  bool getTapDetectionY(void);
  void setTapDetectionZ(bool state);
  bool getTapDetectionZ(void);
  void setTapDetectionXYZ(bool state);

  void useInterrupt(adxl345_int_t interrupt);

  private:
  Activites a;
  range_t _range;

};

#endif
