#ifndef _MainLoop_H    // Put these two lines at the top of your file.
#define _MainLoop_H    // (Use a suitable name, usually based on the file name.)



void loop() {
  //Serial.print("Connected! ");
  String incMsg = "";
  if ((WiFi.status() == WL_CONNECTED)) {      // Check On WiFi
    incMsg = RecvUDPMsg();                    // Recv any UDP msgs
    if (incMsg.length() > 0) {
      String msgHdlrRslt = ProcUDPMsg(incMsg);  // Process msgs
      String incMsg = "";
      if (msgHdlrRslt.length() > 0) {
        SendUDPMsg(msgHdlrRslt);  // send back reply
        msgHdlrRslt = "";               
        }
    }
    HeartBeat();
  }
  //delay(10);
}
#endif // _MainLoop_H    // Put this line at the end of your file.