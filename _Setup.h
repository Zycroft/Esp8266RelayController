#ifndef _Setup_H    // Put these two lines at the top of your file.
#define _Setup_H    // (Use a suitable name, usually based on the file name.)

void setup() {
  Serial.begin(115200);
  delay(10);

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
  pinMode(clockPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  Data = R0F;
  Serial.println("Data Initialized");
  Serial.println(Data,BIN);
  relaysOff();

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  delay(500);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  }


#endif // _Setup_H    // Put this line at the end of your file.