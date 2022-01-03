#include <SwitchDenGoMascon.h>
#include <usbhub.h>
#include <SPI.h>

USB Usb;
//USBHub Hub(&Usb);
SwitchDenGoMascon SwitchDenGo(&Usb);

void setup() {
  Serial.begin(115200); 

  if (Usb.Init() == -1){
    Serial.println("OSC did not start.");
    while(1){
      
    }
  }
  delay(500);
}

void loop() {
  Usb.Task();
  
  Serial.println("Connected:" + String(SwitchDenGo.connected()));
  Serial.println("Handle Position:" + String(SwitchDenGo.getMascon()));
  Serial.println("Power:" + String(SwitchDenGo.getMascon(PowerLevel)));
  Serial.println("Brake:" + String(SwitchDenGo.getMascon(BrakeLevel)));
  
  Serial.println("A:" + String(SwitchDenGo.isPressed(BtnA)));
  Serial.println("B:" + String(SwitchDenGo.isPressed(BtnB)));
  Serial.println("X:" + String(SwitchDenGo.isPressed(BtnX)));
  Serial.println("Y:" + String(SwitchDenGo.isPressed(BtnY)));

  Serial.println("L:" + String(SwitchDenGo.isPressed(BtnL)));
  Serial.println("ZL:" + String(SwitchDenGo.isPressed(BtnZl)));
  Serial.println("R:" + String(SwitchDenGo.isPressed(BtnR)));
  Serial.println("ZR:" + String(SwitchDenGo.isPressed(BtnZr)));

  Serial.println("PLUS:" + String(SwitchDenGo.isPressed(BtnPlus)));
  Serial.println("MINUS:" + String(SwitchDenGo.isPressed(BtnMinus)));
  Serial.println("HOME:" + String(SwitchDenGo.isPressed(BtnHome)));
  Serial.println("CAPTURE:" + String(SwitchDenGo.isPressed(BtnCapture)));
  
  Serial.println("UP:" + String(SwitchDenGo.isPressed(HatUp)));
  Serial.println("RIGHT:" + String(SwitchDenGo.isPressed(HatRight)));
  Serial.println("DOWN:" + String(SwitchDenGo.isPressed(HatDown)));
  Serial.println("LEFT:" + String(SwitchDenGo.isPressed(HatLeft))); 
  
  Serial.println(" ");
  delay(500);
}
