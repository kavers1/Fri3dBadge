#include "Fri3dAccelerometer.h"
#include "Arduino.h"

Fri3dAccelerometer::Fri3dAccelerometer() {
}

void 
Fri3dAccelerometer::begin() {
  adxl345 = Adafruit_ADXL345_Unified(12345);
  if(!adxl345.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Cannot find accelerometer!");
    while(1);
  }
  adxl345.setRange(ADXL345_RANGE_16_G);

  clearSettings();
}

bool 
Fri3dAccelerometer::getEvent(sensors_event_t *event) {
  return adxl345.getEvent( event );
}

void 
Fri3dAccelerometer::displaySensorDetails(void) {
  sensor_t sensor;
  adxl345.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void
Fri3dAccelerometer::displayDataRate(void) {
  Serial.print  ("Data Rate:    "); 
  
  switch(adxl345.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  }  
  Serial.println(" Hz");  
}

void
Fri3dAccelerometer::displayRange(void) {
  Serial.print  ("Range:         +/- "); 
  
  switch(adxl345.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  }  
  Serial.println(" g");  
}

void 
Fri3dAccelerometer::clearSettings(void)
{
    setRange(ADXL345_RANGE_2_G);
    setDataRate(ADXL345_DATARATE_100_HZ);

    writeRegister(ADXL345_REG_THRESH_TAP, 0x00);
    writeRegister(ADXL345_REG_DUR, 0x00);
    writeRegister(ADXL345_REG_LATENT, 0x00);
    writeRegister(ADXL345_REG_WINDOW, 0x00);
    writeRegister(ADXL345_REG_THRESH_ACT, 0x00);
    writeRegister(ADXL345_REG_THRESH_INACT, 0x00);
    writeRegister(ADXL345_REG_TIME_INACT, 0x00);
    writeRegister(ADXL345_REG_THRESH_FF, 0x00);
    writeRegister(ADXL345_REG_TIME_FF, 0x00);

    uint8_t value;

    value = readRegister(ADXL345_REG_ACT_INACT_CTL);
    value &= 0b10001000;
    writeRegister(ADXL345_REG_ACT_INACT_CTL, value);

    value = readRegister(ADXL345_REG_TAP_AXES);
    value &= 0b11111000;
    writeRegister(ADXL345_REG_TAP_AXES, value);
}

// Set Tap Threshold (62.5mg / LSB)
void 
Fri3dAccelerometer::setTapThreshold(float threshold)
{
    uint8_t scaled = constrain(threshold / 0.0625f, 0, 255);
    writeRegister(ADXL345_REG_THRESH_TAP, scaled);
}

// Get Tap Threshold (62.5mg / LSB)
float 
Fri3dAccelerometer::getTapThreshold(void)
{
    return readRegister(ADXL345_REG_THRESH_TAP) * 0.0625f;
}

// Set Tap Duration (625us / LSB)
void 
Fri3dAccelerometer::setTapDuration(float duration)
{
    uint8_t scaled = constrain(duration / 0.000625f, 0, 255);
    writeRegister(ADXL345_REG_DUR, scaled);
}

// Get Tap Duration (625us / LSB)
float 
Fri3dAccelerometer::getTapDuration(void)
{
    return readRegister(ADXL345_REG_DUR) * 0.000625f;
}

// Set Double Tap Latency (1.25ms / LSB)
void 
Fri3dAccelerometer::setDoubleTapLatency(float latency)
{
    uint8_t scaled = constrain(latency / 0.00125f, 0, 255);
    writeRegister(ADXL345_REG_LATENT, scaled);
}

// Get Double Tap Latency (1.25ms / LSB)
float 
Fri3dAccelerometer::getDoubleTapLatency()
{
    return readRegister(ADXL345_REG_LATENT) * 0.00125f;
}

// Set Double Tap Window (1.25ms / LSB)
void 
Fri3dAccelerometer::setDoubleTapWindow(float window)
{
    uint8_t scaled = constrain(window / 0.00125f, 0, 255);
    writeRegister(ADXL345_REG_WINDOW, scaled);
}

// Get Double Tap Window (1.25ms / LSB)
float 
Fri3dAccelerometer::getDoubleTapWindow(void)
{
    return readRegister(ADXL345_REG_WINDOW) * 0.00125f;
}

// Set Activity Threshold (62.5mg / LSB)
void 
Fri3dAccelerometer::setActivityThreshold(float threshold)
{
    uint8_t scaled = constrain(threshold / 0.0625f, 0, 255);
    writeRegister(ADXL345_REG_THRESH_ACT, scaled);
}

// Get Activity Threshold (65.5mg / LSB)
float 
Fri3dAccelerometer::getActivityThreshold(void)
{
    return readRegister(ADXL345_REG_THRESH_ACT) * 0.0625f;
}

// Set Inactivity Threshold (65.5mg / LSB)
void 
Fri3dAccelerometer::setInactivityThreshold(float threshold)
{
    uint8_t scaled = constrain(threshold / 0.0625f, 0, 255);
    writeRegister(ADXL345_REG_THRESH_INACT, scaled);
}

// Get Incactivity Threshold (65.5mg / LSB)
float 
Fri3dAccelerometer::getInactivityThreshold(void)
{
    return readRegister(ADXL345_REG_THRESH_INACT) * 0.0625f;
}

// Set Inactivity Time (s / LSB)
void 
Fri3dAccelerometer::setTimeInactivity(uint8_t time)
{
    writeRegister(ADXL345_REG_TIME_INACT, time);
}

// Get Inactivity Time (s / LSB)
uint8_t 
Fri3dAccelerometer::getTimeInactivity(void)
{
    return readRegister(ADXL345_REG_TIME_INACT);
}

// Set Free Fall Threshold (65.5mg / LSB)
void 
Fri3dAccelerometer::setFreeFallThreshold(float threshold)
{
    uint8_t scaled = constrain(threshold / 0.0625f, 0, 255);
    writeRegister(ADXL345_REG_THRESH_FF, scaled);
}

// Get Free Fall Threshold (65.5mg / LSB)
float 
Fri3dAccelerometer::getFreeFallThreshold(void)
{
    return readRegister(ADXL345_REG_THRESH_FF) * 0.0625f;
}

// Set Free Fall Duratiom (5ms / LSB)
void 
Fri3dAccelerometer::setFreeFallDuration(float duration)
{
    uint8_t scaled = constrain(duration / 0.005f, 0, 255);
    writeRegister(ADXL345_REG_TIME_FF, scaled);
}

// Get Free Fall Duratiom
float 
Fri3dAccelerometer::getFreeFallDuration()
{
    return readRegister(ADXL345_REG_TIME_FF) * 0.005f;
}

void 
Fri3dAccelerometer::setActivityX(bool state)
{
    writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 6, state);
}

bool 
Fri3dAccelerometer::getActivityX(void)
{
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 6);
}

void 
Fri3dAccelerometer::setActivityY(bool state)
{
    writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 5, state);
}

bool 
Fri3dAccelerometer::getActivityY(void)
{
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 5);
}

void 
Fri3dAccelerometer::setActivityZ(bool state)
{
    writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 4, state);
}

bool 
Fri3dAccelerometer::getActivityZ(void)
{
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 4);
}

void 
Fri3dAccelerometer::setActivityXYZ(bool state)
{
    uint8_t value;

    value = readRegister(ADXL345_REG_ACT_INACT_CTL);

    if (state)
    {
	value |= 0b00111000;
    } else
    {
	value &= 0b11000111;
    }

    writeRegister(ADXL345_REG_ACT_INACT_CTL, value);
}

bool 
Fri3dAccelerometer::getActivityAC(void){
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 7);
}

void 
Fri3dAccelerometer::setActivityAC(bool state)
{
  writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 7, state);
}

void 
Fri3dAccelerometer::setInactivityX(bool state) 
{
    writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 2, state);
}

bool 
Fri3dAccelerometer::getInactivityX(void)
{
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 2);
}

void 
Fri3dAccelerometer::setInactivityY(bool state)
{
    writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 1, state);
}

bool 
Fri3dAccelerometer::getInactivityY(void)
{
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 1);
}

void 
Fri3dAccelerometer::setInactivityZ(bool state)
{
    writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 0, state);
}

bool 
Fri3dAccelerometer::getInactivityZ(void)
{
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 0);
}

void 
Fri3dAccelerometer::setInactivityXYZ(bool state)
{
    uint8_t value;

    value = readRegister(ADXL345_REG_ACT_INACT_CTL);

    if (state)
    {
	value |= 0b00000111;
    } else
    {
	value &= 0b11111000;
    }

    writeRegister(ADXL345_REG_ACT_INACT_CTL, value);
}

bool 
Fri3dAccelerometer::getInActivityAC(void){
    return readRegisterBit(ADXL345_REG_ACT_INACT_CTL, 7);
}

void 
Fri3dAccelerometer::setInActivityAC(bool state)
{
  writeRegisterBit(ADXL345_REG_ACT_INACT_CTL, 7, state);
}

void 
Fri3dAccelerometer::setTapDetectionX(bool state)
{
    writeRegisterBit(ADXL345_REG_TAP_AXES, 2, state);
}

bool 
Fri3dAccelerometer::getTapDetectionX(void)
{
    return readRegisterBit(ADXL345_REG_TAP_AXES, 2);
}

void 
Fri3dAccelerometer::setTapDetectionY(bool state)
{
    writeRegisterBit(ADXL345_REG_TAP_AXES, 1, state);
}

bool 
Fri3dAccelerometer::getTapDetectionY(void)
{
    return readRegisterBit(ADXL345_REG_TAP_AXES, 1);
}

void 
Fri3dAccelerometer::setTapDetectionZ(bool state)
{
    writeRegisterBit(ADXL345_REG_TAP_AXES, 0, state);
}

bool 
Fri3dAccelerometer::getTapDetectionZ(void)
{
    return readRegisterBit(ADXL345_REG_TAP_AXES, 0);
}

void 
Fri3dAccelerometer::setTapDetectionXYZ(bool state)
{
    uint8_t value;

    value = readRegister(ADXL345_REG_TAP_AXES);

    if (state)
    {
	    value |= 0b00000111;
    } else
    {
	    value &= 0b11111000;
    }

    writeRegister(ADXL345_REG_TAP_AXES, value);
}

void 
Fri3dAccelerometer::setPowerConfig(byte cnfg)
{
  writeRegister(ADXL345_REG_POWER_CTL,cnfg);
}

byte 
Fri3dAccelerometer::getPowerConfig(void)
{
  return readRegister(ADXL345_REG_POWER_CTL);
}

void 
Fri3dAccelerometer::useInterrupt(adxl345_int_t interrupt)
{
    if (interrupt == 0)
    {
	writeRegister(ADXL345_REG_INT_MAP, 0x00);
    } else
    {
	writeRegister(ADXL345_REG_INT_MAP, 0xFF);
    }

    writeRegister(ADXL345_REG_INT_ENABLE, 0xFF);
}

Activites 
Fri3dAccelerometer::readActivites(void)
{
    uint8_t data = readRegister(ADXL345_REG_INT_SOURCE);

    a.isOverrun = ((data >> ADXL345_OVERRUN) & 1);
    a.isWatermark = ((data >> ADXL345_WATERMARK) & 1);
    a.isFreeFall = ((data >> ADXL345_FREE_FALL) & 1);
    a.isInactivity = ((data >> ADXL345_INACTIVITY) & 1);
    a.isActivity = ((data >> ADXL345_ACTIVITY) & 1);
    a.isDoubleTap = ((data >> ADXL345_DOUBLE_TAP) & 1);
    a.isTap = ((data >> ADXL345_SINGLE_TAP) & 1);
    a.isDataReady = ((data >> ADXL345_DATA_READY) & 1);

    data = readRegister(ADXL345_REG_ACT_TAP_STATUS);

    a.isActivityOnX = ((data >> 6) & 1);
    a.isActivityOnY = ((data >> 5) & 1);
    a.isActivityOnZ = ((data >> 4) & 1);
    a.isTapOnX = ((data >> 2) & 1);
    a.isTapOnY = ((data >> 1) & 1);
    a.isTapOnZ = ((data >> 0) & 1);

    return a;
}

// Write byte to register
void Fri3dAccelerometer::writeRegister8(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(ADXL345_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(reg);
        Wire.write(value);
    #else
        Wire.send(reg);
        Wire.send(value);
    #endif
    Wire.endTransmission();
}

// Read byte to register
uint8_t Fri3dAccelerometer::fastRegister8(uint8_t reg)
{
    uint8_t value;
    Wire.beginTransmission(ADXL345_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(reg);
    #else
        Wire.send(reg);
    #endif
    Wire.endTransmission();

    Wire.requestFrom(ADXL345_ADDRESS, 1);
    #if ARDUINO >= 100
        value = Wire.read();
    #else
        value = Wire.receive();
    #endif;
    Wire.endTransmission();

    return value;
}

// Read byte from register
uint8_t Fri3dAccelerometer::readRegister8(uint8_t reg)
{
    uint8_t value;
    Wire.beginTransmission(ADXL345_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(reg);
    #else
        Wire.send(reg);
    #endif
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.requestFrom(ADXL345_ADDRESS, 1);
    while(!Wire.available()) {};
    #if ARDUINO >= 100
        value = Wire.read();
    #else
        value = Wire.receive();
    #endif;
    Wire.endTransmission();

    return value;
}

// Read word from register
int16_t Fri3dAccelerometer::readRegister16(uint8_t reg)
{
    int16_t value;
    Wire.beginTransmission(ADXL345_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(reg);
    #else
        Wire.send(reg);
    #endif
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.requestFrom(ADXL345_ADDRESS, 2);
    while(!Wire.available()) {};
    #if ARDUINO >= 100
        uint8_t vla = Wire.read();
        uint8_t vha = Wire.read();
    #else
        uint8_t vla = Wire.receive();
        uint8_t vha = Wire.receive();
    #endif;
    Wire.endTransmission();

    value = vha << 8 | vla;

    return value;
}

void 
Fri3dAccelerometer::writeRegisterBit(uint8_t reg, uint8_t pos, bool state)
{
    uint8_t value;
    value = readRegister(reg);

    if (state)
    {
	value |= (1 << pos);
    } else 
    {
	value &= ~(1 << pos);
    }

    writeRegister(reg, value);
}

bool 
Fri3dAccelerometer::readRegisterBit(uint8_t reg, uint8_t pos)
{
    uint8_t value;
    value = readRegister(reg);
    return ((value >> pos) & 1);
}
