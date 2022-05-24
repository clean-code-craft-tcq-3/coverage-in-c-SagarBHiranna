#include "typewise-alert.h"

char* messageMail = "";
mailAlert mailInfo [] = {{"Hi, the temperature is too low\n"},{"Hi, the temperature is too high\n"}};
coolingTypeProperties coolingTypes[] = {{PASSIVE_COOLING, 0, 35}, {HI_ACTIVE_COOLING, 0, 45}, {MED_ACTIVE_COOLING, 0, 45},};

void displayOnConsole(char message[100])
{
  printf("%s\n", message);
}

int checkValueInLowerLimit(int value, double lowerLimit)
{
  return ((value < lowerLimit) ? 1 : 0);
}

int checkValueInUpperLimit(int value, double upperLimit)
{
  return ((value > upperLimit) ? 1 : 0);
}

breachStatus initialiseSystem()
{
  messageMail = "";
  breachStatus breachIndicator = {0};  
  return breachIndicator;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  breachStatus breachIndicator = initialiseSystem();
  breachIndicator.statusLowLimit = checkValueInLowerLimit(value, lowerLimit);
  breachIndicator.statusHighLimit = checkValueInUpperLimit(value, upperLimit);
  if(breachIndicator.statusHighLimit){
    messageMail = mailInfo[1].mailAlertMessage;
    return TOO_HIGH;
  }
  if (breachIndicator.statusLowLimit)
  {
    messageMail = mailInfo[0].mailAlertMessage;
    return TOO_LOW;
  }
  breachIndicator.statusNormal = 3;
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingtype, double temperatureInC)
{
  return inferBreach(temperatureInC, coolingTypes[coolingtype].lowerLimit, coolingTypes[coolingtype].higherLimit);
}

void sendToEmail(BreachType breachType, void (*loggerFunPtr) (char*)) {
  char recepient[10] = "a.b@c.com";
  char to_template[10] = "To : ";
  if (breachType != NORMAL)
  {
    loggerFunPtr(strcat(to_template, recepient));
    loggerFunPtr(messageMail);
  }
}

void sendToController(BreachType breachType, void (*loggerFunPtr) (char*)) {
  char header[] = "0xfeed : ";
  char strBreach [8];
  sprintf(strBreach,"%d",breachType);
  loggerFunPtr(strcat(header,strBreach));
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, void (*loggerFunPtr) (char*)) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType, loggerFunPtr);
      break;
    case TO_EMAIL:
      sendToEmail(breachType, loggerFunPtr);
      break;
  }
}
