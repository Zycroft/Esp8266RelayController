#ifndef _Relay_H    // Put these two lines at the top of your file.
#define _Relay_H    // (Use a suitable name, usually based on the file name.)

//---------------------------------------------Relay Communication
  void SetRelay(){
      //ground latchPin and hold low for as long as you are transmitting
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, (Data >> 8));
      shiftOut(dataPin, clockPin, MSBFIRST, Data);
      //return the latch pin high to signal chip that it
      //no longer needs to listen for information
      digitalWrite(latchPin, HIGH);
  }

String getReplyString(String var) {
  String response;
  String blk;
  String ppk;
  
  if (var.substring(0,2) == "HH")
  {
    //Serial.printf("getReplyString - ControlBoard: %s\n", ControlBoard);
    response = "OKHH:" + ControlBoard + " ";
    //Serial.printf("getReplyString - response: %s\n", response);
  } else if (var.substring(0,3) == "BLK")
  {
    blk = var.substring(7,9);
    ppk = var.substring(10,11);
    //Serial.printf("Block: %s\n", blk);
    //Serial.printf("**RelayBefore**");
    //Serial.println(Data,BIN);
    if (blk == "01")
    {
      //Serial.printf("PowerPacktest: %s\n", "ppk");
      //Serial.printf("PowerPack: %s\n", ppk);

      if (ppk == "0")
      {
        Serial.printf("1-0");  // All off
        Data = Data & ~R00;    // Off
        Data = Data & ~R01;
        Data = Data & ~R02;
        Data = Data & ~R03;
        Data = Data & ~R04;
        Data = Data & ~R05;
        response = "BLK01:0 ";
      }
      else if (ppk == "1")
      {
        Serial.printf("1-1");  // power pack 1 On
        Data = Data | R00;     // On
        Data = Data | R01;
        Data = Data & ~R02;
        Data = Data & ~R03;
        Data = Data & ~R04;
        Data = Data & ~R05;
        response = "BLK01:1 ";
      }
      else if (ppk == "2")
      {
        Serial.printf("1-2");  // power pack 2 On
        Data = Data & ~R00;
        Data = Data & ~R01;
        Data = Data | R02;     // On
        Data = Data | R03;
        Data = Data & ~R04;
        Data = Data & ~R05;
        response = "BLK01:2 ";
      }
      else if (ppk == "3")
      {
        Serial.printf("1-3");   // power pack 3 On
        Data = Data & ~R00;
        Data = Data & ~R01;
        Data = Data & ~R02;
        Data = Data & ~R03;
        Data = Data | R04;
        Data = Data | R05;
        response = "BLK01:3 ";      
      } 
    }      
  }
  SetRelay();
  //Serial.println("********RelaySet********");
  //Serial.println(Data,BIN);
  //Serial.printf("Response %s\n" ,response);
  return response;
}

void relaysOff() {
  Data = Data | R0G;
  //Data = Data & R0F;
  //Serial.println("********RelayOff********");
  //Serial.println(Data,BIN);
  SetRelay();
}

  
#endif // _Relay_H    // Put this line at the end of your file.