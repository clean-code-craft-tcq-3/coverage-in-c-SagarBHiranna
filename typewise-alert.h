#pragma once

typedef enum {
  PASSIVE_COOLING = 0,
  HI_ACTIVE_COOLING = 1,
  MED_ACTIVE_COOLING = 2
} CoolingType;

typedef enum {
  NORMAL = 3,
  TOO_LOW = 1,
  TOO_HIGH = 2
} BreachType;

typedef struct
{
  int statusLowLimit;
  int statusHighLimit;
  int statusNormal;
} breachStatus;

typedef struct
{
  CoolingType userCoolerTypeInput ;
  double lowerLimit ;
  double higherLimit ;
} coolingTypeProperties;


coolingTypeProperties passiveCooling = {PASSIVE_COOLING, 0, 35};
coolingTypeProperties highActiveCooling = {HI_ACTIVE_COOLING, 0, 45};
coolingTypeProperties midActiveCooling = {MED_ACTIVE_COOLING, 0, 45};

coolingTypeProperties coolingTypes[] = {{PASSIVE_COOLING, 0, 35}, {HI_ACTIVE_COOLING, 0, 45}, {MED_ACTIVE_COOLING, 0, 45},}; 

BreachType inferBreach(double value, double lowerLimit, double upperLimit);

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

char* mesageMail = "";
typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct 
{
  char mailAlertMessage[100];
}mailAlert;

mailAlert mailInfo [] = {{"Hi, the temperature is too low\n"},{"Hi, the temperature is too high\n"}};

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, void (*loggerFunPtr) (char*));

void sendToController(BreachType breachType, void (*displayFunPtr) (char*));
void sendToEmail(BreachType breachType, void (*displayFunPtr) (char*));
