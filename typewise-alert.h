#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
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

typedef enum{
  E_OK,
  E_NOT_OK
}status;

typedef struct 
{
  status statusSendToEmail;
  status statusSendToController;
}statusLog;


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



void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, void (*loggerFunPtr) (char*));
BreachType classifyTemperatureBreach(CoolingType coolingtype, double temperatureInC);
status sendToController(BreachType breachType, void (*loggerFunPtr) (char*));
status sendToEmail(BreachType breachType, void (*loggerFunPtr) (char*));
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
breachStatus initialiseSystem();
int checkValueInUpperLimit(int value, double upperLimit);
int checkValueInLowerLimit(int value, double lowerLimit);
void displayOnConsole(char message[100]);
