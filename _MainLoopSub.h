#ifndef _MainLoopSub_H    // Put these two lines at the top of your file.
#define _MainLoopSub_H    // (Use a suitable name, usually based on the file name.)

char  msgPacket[] = "Empty";

bool SendUDPMsg(String msg) {
  int len = msg.length();  // Set relay and return a response
  //Serial.printf("ReplyInfo: %s   Length:  %d\n ", msg,len  );
  msg.toCharArray(msgPacket, len);
  // send back a reply, to the IP address and port we got the packet from
  IPAddress ip;
  ip.fromString(HH_IP);
  Udp.beginPacket(ip, localUdpPort); //Udp.remotePort() Udp.remoteIP()
  Serial.print("SendUDPMsg- To: ");
  Serial.print(HH_IP);
  Serial.print("  Messg: ");
  Serial.print(msg);
  Serial.print("\n");
  //Serial.printf("Reply: %s, Port %d, ", msg, localUdpPort);  //Udp.remoteIP().toString().c_str()  localUdpPort
  //Serial.print("To:" );
  //Serial.print(HH_IP);
  //Serial.print("\n");
  Udp.write(msgPacket);
  Udp.endPacket();
  return true;
}

String RecvUDPMsg(){
  char incomingPacket[255];  // buffer for incoming packets
  String recvString = "";
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    RecvMsgIP = Udp.remoteIP().toString().c_str();
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    //Serial.printf("UDP packet contents: %s\n", incomingPacket);
    recvString = String(incomingPacket);
  }
  recvString.trim();
  if (recvString.length() > 0) {
    Serial.print("Received Msg:");
    Serial.print(recvString);
    Serial.print("\n");
  }
  return recvString;
}

void HeartBeat(){
  unsigned long ElapsedTimeHeartBeat =0;
  Heartbeatinterval = 10000;  // send heart beat every 10 seconds
  if (HH_IP.length() > 0) {
    StopTimeHeartBeat = millis();
    ElapsedTimeHeartBeat = StopTimeHeartBeat - StartTimeHeartBeat;
    if (ElapsedTimeHeartBeat > Heartbeatinterval)
    {
      Serial.print("ElapsedTimeHeartBeat");
      Serial.print(ElapsedTimeHeartBeat);
      Serial.print("\n");
      Serial.print("Heartbeatinterval");
      Serial.print(Heartbeatinterval);
      Serial.print("\n");
      String msg = "OKHH:" + ControlBoard + " ";
      SendUDPMsg(msg);
      msg = "";
      StartTimeHeartBeat = millis();
    }
  }
}

/*
      //Serial.printf("getReplyString - ControlBoard: %s\n", ControlBoard);
      //Serial.printf("getReplyString - response: %s\n", response);
      //Serial.printf("Block: %s\n", blk);
      //Serial.printf("**RelayBefore**");
      //Serial.println(Data,BIN);
      //Serial.printf("PowerPacktest: %s\n", "ppk");
      //Serial.printf("PowerPack: %s\n", ppk);
      //Serial.println("********RelaySet********");
      //Serial.println(Data,BIN);
      //Serial.printf("Response %s\n" ,response);
*/
String ProcUDPMsg(String var) {
  //BLK01BTN0
  Serial.print("ProcMsg: ");
  Serial.print(var);
  Serial.print("\n");
  String response;
  String blk;
  String ppk;
  response = "";
  if (var.substring(0,2) == "OK") {
    response = "";
  } else if (var.substring(0,2) == "HH") {
      HH_IP = RecvMsgIP;
      response = "OKHH:" + ControlBoard + " ";
    } else if (var.substring(0,3) == "BLK") {
      blk = var.substring(3,5);
      ppk = var.substring(8,9);
      //Serial.printf("Block: %s\n", blk);
      //Serial.printf("PowerPack: %s\n", ppk);
      if (blk == BLKA) {
        response = ControlAOff(); // First turn everything off then turn on
        SetRelay();
        if (ppk == "0") {
          response = ControlAOff();
        }
        else if (ppk == "1") {
          response = ControlA1();
        }
        else if (ppk == "2") {
          response = ControlA2();
        }
        else if (ppk == "3") {
          response = ControlA3();
        } 
      } 
      if (blk == BLKB) {
        response = ControlBOff(); // First turn everything off then turn on
        SetRelay();
        if (ppk == "0") {
          response = ControlBOff();
        }
        else if (ppk == "1") {
          response = ControlB1();
        }
        else if (ppk == "2") {
          response = ControlB2();
        }
        else if (ppk == "3") {
          response = ControlB3();
        } 
      }      
      if (response.length() > 0) {
        SetRelay();
        response = "OK"+ var;
      }
    }
  //Serial.print("ProcMsg Response1: ");
  //Serial.print(response);
  //Serial.print("\n");
  return response;
}

#endif // _MainLoopSub_H    // Put this line at the end of your file.