#include "typewise-alert.h"

char* messageMail = "";
mailAlert mailInfo [] = {{"Hi, the temperature is too low\n"},{"Hi, the temperature is too high\n"}};
coolingTypeProperties coolingTypes[] = {{PASSIVE_COOLING, 0, 35}, {HI_ACTIVE_COOLING, 0, 45}, {MED_ACTIVE_COOLING, 0, 40},};
statusLog statusInfo = {E_NOT_OK, E_NOT_OK};

void displayOnConsole(char message[100])
{
  printf("%s\n", message);
}

int checkValueInLowerLimit(int value, double lowerLimit)
{
  return ((value <= lowerLimit) ? 1 : 0);
}

int checkValueInUpperLimit(int value, double upperLimit)
{
  return ((value >= upperLimit) ? 1 : 0);
}


BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  messageMail = "";
  breachStatus breachIndicator = {0};
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

status sendToEmail(BreachType breachType) {
  char recepient[100] = "a.b@c.com";
  char to_template[100] = "To : ";
  statusInfo.statusSendToEmail = E_NOT_OK;
  if (breachType != NORMAL)
  {
    displayOnConsole(to_template);
    displayOnConsole(recepient);
    displayOnConsole(messageMail);
    statusInfo.statusSendToEmail = E_OK;
    printf("am here");
    return E_OK;
  }
  return E_NOT_OK;
}

status sendToController(BreachType breachType) {
  statusInfo.statusSendToController = E_NOT_OK;
  char header[] = "0xfeed : ";
  char strBreach [8];
  sprintf(strBreach,"%d",breachType);
  displayOnConsole(strcat(header,strBreach));
  statusInfo.statusSendToController = E_OK;
  return E_OK;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  statusLog statusInfo;
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}
