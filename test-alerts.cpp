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

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(-12, 0, 35) == TOO_LOW);
  REQUIRE(inferBreach(101,100,105) == NORMAL);
  REQUIRE(inferBreach(25,20,30)==NORMAL);
  REQUIRE(inferBreach(0, 0, 35) == TOO_LOW);
  REQUIRE(inferBreach(105,100,105) == TOO_HIGH);
  REQUIRE(inferBreach(120,100,105) == TOO_HIGH);
}

TEST_CASE("Check the value and alert for Passive Cooling") {
	BatteryCharacter batteryCharacter;
	batteryCharacter.coolingType = PASSIVE_COOLING;
	checkAndAlert(TO_CONTROLLER, batteryCharacter, 15, printf);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 15) == NORMAL);

	checkAndAlert(TO_EMAIL, batteryCharacter, -10, printf);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -10) == TOO_LOW);

	checkAndAlert(TO_CONTROLLER, batteryCharacter, 40, printf);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
}
