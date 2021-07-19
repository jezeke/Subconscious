#pragma once

class uiBlinker
{
  private:

  public:
    //default constructor

    /*
    blinkerType() #works out what blinker is needed to lightup
    {
      if impactArea is in a directory/list/other of all impact areas:
        specificBlinkerType = true                #eg. damage alert -> hull breach -> blinkerHull = true
        if specificBlinkerType:
          check for additional effects caused by damage #(or we create a function that runs seperate eg. hullBreach() which starts a timer till fully flooded ect.) 
      else:
        exception boi -> "ahhhh shiiiiit" #yea i don't remember how to do exceptions in python lol
    }
    

    */

    uiBlinker()
    {
      /*
        blinker = false    #starting state



        while blinker = true: 
          blinkerLightOn(blinkerName):
          if alarm is [damage, flood, fire, hazard]:
            alarmSound()
            sleep(2)       #stops alarms from going over the top of one another (alarms are two or three kinda bu-beep) 
          elif alarm is [lifeSupp, reactor]:            #eg. life support warnings/rector warning
            warningSound() #(goes on for a longer period of time because its more important (long and continuous & overlapping sounds potential))
          else:
            if damageFixed or dangerFixed:
              blinker = false
            else:
              exception: 'help.' but also set blinker to false




      */ 
    }

    void render(float elapsedTime, World world, SubSystems sub)
    {

    }
};
