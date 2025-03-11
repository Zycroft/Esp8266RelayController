#ifndef _BitOps_H    // Put these two lines at the top of your file.
#define _BitOps_H    // (Use a suitable name, usually based on the file name.)

String ControlAOff() {
          Serial.printf("A-0");
          //Data = Data & R0F;
          Data = Data | RG1;
          //Data = Data & ~R00;
          //Data = Data & ~R01;
          //Data = Data & ~R02;
          //Data = Data & ~R03;
          //Data = Data & ~R04;
          //Data = Data & ~R05;
          return "OK";
}
String ControlA1() {
          Serial.printf("A-1");
          Data = Data & ~R00;
          Data = Data & ~R01;
          //Data = Data | R00;
          //Data = Data | R01;
          //Data = Data & ~R02;
          //Data = Data & ~R03;
          //Data = Data & ~R04;
          //Data = Data & ~R05;
          return "OK";
}
String ControlA2() {
          Serial.printf("A-2");
          Data = Data & ~R02;
          Data = Data & ~R03;          
          //Data = Data & ~R00;
          //Data = Data & ~R01;
          //Data = Data | R02;
          //Data = Data | R03;
          //Data = Data & ~R04;
          //Data = Data & ~R05;
          return "OK";
}
String ControlA3() {
          Serial.printf("A-3");
          Data = Data & ~R04;
          Data = Data & ~R05;           
          //Data = Data & ~R00;
          //Data = Data & ~R01;
          //Data = Data & ~R02;
          //Data = Data & ~R03;
          //Data = Data | R04;
          //Data = Data | R05;
          return "OK";
}
String ControlBOff() {
          Serial.printf("B-0");
          Data = Data | RG2;
          //Data = Data & ~R15;
          //Data = Data & ~R14;
          //Data = Data & ~R13;
          //Data = Data & ~R12;
          //Data = Data & ~R11;
          //Data = Data & ~R10;
          return "OK";
}
String ControlB1() {
          Serial.printf("B-1");
          Data = Data & ~R15;
          Data = Data & ~R14; 
          //Data = Data | R15;
          //Data = Data | R14;
          //Data = Data & ~R13;
          //Data = Data & ~R12;
          //Data = Data & ~R11;
          //Data = Data & ~R10;
          return "OK";
}
String ControlB2() {
          Serial.printf("B-2");
          Data = Data & ~R13;
          Data = Data & ~R12;           
          //Data = Data & ~R15;
          //Data = Data & ~R14;
          //Data = Data | R13;
          //Data = Data | R12;
          //Data = Data & ~R11;
          //Data = Data & ~R10;
          return "OK";
}
String ControlB3() {
          Serial.printf("B-3");
          Data = Data & ~R11;
          Data = Data & ~R10;
          //Data = Data & ~R15;
          //Data = Data & ~R14;
          //Data = Data & ~R13;
          //Data = Data & ~R12;
          //Data = Data | R11;
          //Data = Data | R10;
          return "OK";
}




#endif // _BitOps_H    // Put this line at the end of your file.