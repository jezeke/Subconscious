#pragma once
#include <cmath>
#include <algorithm>

struct Room {
  std::string name; //pretty name printed on UI
  float floodLevel; //0 - 100
  float damageLevel; //0 - 100
  bool onFire;
  float suppressionRemaining; //remaining time units until fire is suppressed
  float malfunctionRemaining; //remaining time units until malfunction ends
};

struct SystemValue {
  std::string name; //print name printed on UI
  float value;
  float max;
  float min;
  float warningMax; //warning if above this value
  float warningMin; //warning if below this value
  float displayIncrement; //gauges show this value with new values at each increment. e.g. rolling 1, 2, 3 vs 1.0, 1.1, 1.2 . .
};

class SubSystems
{
  private:

  public:
    std::map<Room> rooms;
    std::map<SystemValue> values;

    float reactorLevel; //reactor power setting. reactor is off if reactorLevel < 20.0
    float reactorStartRemaining; //milliseconds until reactor starts. if at 0, reactor is running or has not been commanded to restart

    bool torpedos[5] = {};

    std::string bilge; //set to the key name of the location, if enabled; otherwise ""
    std::string fireSuppression; //as above
    std::string prevFireSuppression; //set to last location suppressed - used to reset suppressionRemaining timer if changed early.

    bool oxyGen; //if the oxygen generator is on or not
    bool heater; //if life support heater is on or not
    bool volcano; //if volcanic oxygen is present outside

    //default constructor
    SubSystems()
    {
      //defines key name and printed names for each room on the submarine. printed names should be safe to change without causing code errors
      roomNames = [["lifesupport", "reactor", "bridge","torpedobay","hold","engine"],["Life Support Components", "Reactor", "Bridge", "Torpedo Bay", "Hold", "Engine Room"]];

      for(int i = 0; i < roomNames[0].length; i++)
      { //set to initial values - no damage or fire, etc.
        rooms[roomNames[0][i]] = {roomNames[1][i], 0.0, 0.0, false, 0.0};
      }

      //defines key name and printed names for each system value. printed names should be safe to change without causing code errors
      valueNames = [["water", "oxygen", "fuel", "battery", "temp", "hull"],["External PSI", "Oxygen \%", "Fuel \%", "Battery \%", "Temperature °C", "Hull \%"]];

      for(int i = 0; i < valueNames[0].length; i++)
      { //set to initial values
        SystemValue val;
        val.name = valueNames[1][i];

        switch(valueNames[0][i])
        {
          "water": //AKA depth. mostly controlled by World; this just reflects that.
            val.value = 16.70; //just below surface
            val.max = INFINITY;
            val.min = 14.70; //surface level. should never go above this anyway
            val.warningMin = 15.00;
            val.warningMax = INFINITY; //can tweak later; will probably get annoying if an alarm is going on for the last half of the game
            val.displayIncrement = 1.0;
            break;
          "oxygen":
            val.value = 19.00;
            val.max = 100.00;
            val.min = 0.00;
            val.warningMin = 10.00;
            val.warningMax = 30.5;
            val.displayIncrement = 0.01;
            break;
          "fuel":
            val.value = 100;
            val.max = 100;
            val.min = 0;
            val.warningMin = -1;
            val.warningMax = INFINITY;
            val.displayIncrement = 0.01;
            break;
          "battery": //AKA energy or power
            val.value = 100.0;
            val.max = 100.0;
            val.min = 0.0;
            val.warningMin = 25.0;
            val.warningMax = INFINITY;
            val.displayIncrement = 0.5;
            break;
          "temp": //temperature
            val.value = 23.0;
            val.max = 300.0;
            val.min = -100.0;
            val.warningMin = -20.0; //petrol freezes at -50 C
            val.warningMax = 35.0; //humans die at about 45 C
            val.displayIncrement = 0.1;
            break;
          "hull":
            val.value = 100.0;
            val.max = 100.0;
            val.min = 0.0;
            val.warningMin = 25.0;
            val.warningMax = INFINITY;
            val.displayIncrement = 1.0;
            break;
        }

        values[valueNames[0][i]] = val;

        reactorLevel = 20.0;
        reactorStartRemaining; = 0.0;

        std::fill_n(torpedos, sizeof(torpedos)/sizeof(*torpedos), 1);

        fireSuppression = "";
        bilge = "";

        oxyGen = false;
        heater = false;
        volcano = false;
      }
    }

    void simulate(float fElapsedTime)
    { //make sure every change to a value is capped to its max/min!
      //check if fire / flooding spreads to other areas

      //calculate damage & value changes from flooding, fire, etc.

      //reduce fire / flooding with bilge and suppression. remember - check prevFireSuppression and reset suppressionRemaining if changed early!

      //calculate other value changes

      //check if torpedos explode from damage / fire, apply sub damage

      //check if any systems are forced to stop running (e.g. lack of fuel, lack of power)

      //update hull value based on current room damage
    }
};
