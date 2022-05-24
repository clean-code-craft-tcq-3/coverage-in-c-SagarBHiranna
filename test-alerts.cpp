#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(-12, 0, 35) == TOO_LOW);
  REQUIRE(inferBreach(101,100,105) == NORMAL);
  REQUIRE(inferBreach(25,20,30)==NORMAL);
  REQUIRE(inferBreach(0, 0, 35) == TOO_LOW);
  REQUIRE(inferBreach(105,100,105) == TOO_HIGH);
  REQUIRE(inferBreach(120,100,105) == TOO_HIGH);
}

TEST_CASE("Check for Upper limit check functionality") {
  REQUIRE(checkValueInUpperLimit(100, 99) == 1);
  REQUIRE(checkValueInUpperLimit(100,100) == 1);
  REQUIRE(checkValueInUpperLimit(-98,100) == 0);
}

TEST_CASE("Check for lower limit check functionality") {
  REQUIRE(checkValueInLowerLimit(10, 0) == 0);
  REQUIRE(checkValueInLowerLimit(10,-100) == 0);
  REQUIRE(checkValueInLowerLimit(-98,100) == 1);
  REQUIRE(checkValueInLowerLimit(-102,-100) == 1);
}

TEST_CASE("Cooling Properties : Check and Alert TestCases") {
  BatteryCharacter batteryProp1 = {PASSIVE_COOLING, "ABCD"};
  BatteryCharacter batteryProp2 = {HI_ACTIVE_COOLING, "BCDE"};
  BatteryCharacter batteryProp3 = {MED_ACTIVE_COOLING, "PQRS"};
  checkAndAlert(TO_CONTROLLER, batteryProp1, 20.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20.0)==NORMAL);
  checkAndAlert(TO_EMAIL, batteryProp1, -5.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5.0)==TOO_LOW);
  checkAndAlert(TO_CONTROLLER, batteryProp1, 70.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 70.0)==TOO_HIGH);
  checkAndAlert(TO_CONTROLLER, batteryProp2, 22.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 22.0)==NORMAL);
  checkAndAlert(TO_EMAIL, batteryProp2, -6.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -6.0)==TOO_LOW);
  checkAndAlert(TO_CONTROLLER, batteryProp2, 80.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 80.0)==TOO_HIGH);
  checkAndAlert(TO_CONTROLLER, batteryProp3, 20.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20.0)==NORMAL);
  checkAndAlert(TO_CONTROLLER, batteryProp3, -9.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -9.0)==TOO_LOW);
  checkAndAlert(TO_EMAIL, batteryProp3, 90.0, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 90)==TOO_HIGH);
}

TEST_CASE("Test to check controller informing functionality") {
  REQUIRE(sendToController(NORMAL, displayOnConsole)==E_OK);
  REQUIRE(sendToController(TOO_LOW, displayOnConsole)==E_OK);
  REQUIRE(sendToController(TOO_HIGH, displayOnConsole)==E_OK);
}

TEST_CASE("Check for Display Functionality") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 0) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 37) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 48) == TOO_HIGH);
}

