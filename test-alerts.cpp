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

TEST_CASE(" Cooling Properties: Check and Alert Verification") {
  BatteryCharacter batterProperties ;
  batterProperties.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER, batterProperties, 20, displayOnConsole);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5)==TOO_LOW);
	checkAndAlert(TO_EMAIL, batterProperties, -5, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5) == TOO_LOW);
	checkAndAlert(TO_CONTROLLER, batterProperties, 70, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 70) == TOO_HIGH);
	batterProperties.coolingType = HI_ACTIVE_COOLING;
	checkAndAlert(TO_EMAIL, batterProperties, 22, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 22) == NORMAL);
	checkAndAlert(TO_EMAIL, batterProperties, -6, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -6) == TOO_LOW);
	checkAndAlert(TO_CONTROLLER, batterProperties, 80, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 80) == TOO_HIGH);
  batterProperties.coolingType = MED_ACTIVE_COOLING;
	checkAndAlert(TO_CONTROLLER, batterProperties, 21, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 21) == NORMAL);
	checkAndAlert(TO_CONTROLLER, batterProperties, -9, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -9) == TOO_LOW);
	checkAndAlert(TO_EMAIL, batterProperties, 90, displayOnConsole);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 90) == TOO_HIGH);
}

TEST_CASE("Check for Mail sending functionality") {
  REQUIRE(sendToEmail(NORMAL, displayOnConsole)==E_NOT_OK);
  REQUIRE(sendToEmail(TOO_LOW, displayOnConsole)==E_OK);
  REQUIRE(sendToEmail(TOO_HIGH, displayOnConsole)==E_OK);
}

