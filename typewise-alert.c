#include "typewise-alert.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
  return ((value > upperLimit) ? 2 : 0);
}

void updateMailMessage(int msgIndex)
{
  mesageMail = mailInfo[msgIndex-1].mailAlertMessage;
}

void initialiseSystem()
{
  mesageMail = "";
  breachStatus breachIndicator = {0};  
}
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  mesageMail = "";
  breachStatus breachIndicator = {0};
  printf("%f, %f, %f\n", value, lowerLimit, upperLimit);
  breachIndicator.statusLowLimit = checkValueInLowerLimit(value, lowerLimit);
  breachIndicator.statusHighLimit = checkValueInUpperLimit(value, upperLimit);
  if (breachIndicator.statusHighLimit + breachIndicator.statusLowLimit == 0)
  {
    breachIndicator.statusNormal = 3;
  }
  updateMailMessage(breachIndicator.statusHighLimit+breachIndicator.statusLowLimit+breachIndicator.statusNormal);
  return (breachIndicator.statusHighLimit+breachIndicator.statusLowLimit+breachIndicator.statusNormal);
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
    loggerFunPtr(mesageMail);
  }
}

void sendToController(BreachType breachType, void (*loggerFunPtr) (char*)) {
  char header[] = "0xfeed : ";
  char strBreach [8];
  sprintf(strBreach,"%d",breachType);
  loggerFunPtr( strcat(header,strBreach));
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

int main ()
{
  printf("\n**************************\n");
  BatteryCharacter batteryCharacter;
	batteryCharacter.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL, batteryCharacter, 38, displayOnConsole);
  return 0;
}
