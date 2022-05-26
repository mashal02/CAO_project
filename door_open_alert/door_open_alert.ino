#include <WiFi.h>
#include <ESP_Mail_Client.h>

// Set GPIOs for LED and reedswitch
const int reedSwitch = 13;
const int led = 2; //optional

// Detects whenever the door changed state
bool changeState = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

// Auxiliary variables (it will only detect changes that are 1500 milliseconds apart)
unsigned long previousMillis = 0; 
const long interval = 1500;


// Runs whenever the reedswitch changes state
ICACHE_RAM_ATTR void changeDoorStatus() {
  Serial.println("State changed");
  changeState = true;
}


//requirements for email:
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "replace@gmail.com"
#define AUTHOR_PASSWORD "replace"

/* Recipient's email*/
#define RECIPIENT_EMAIL "replace@gmail.com"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);


void setup() {

  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);

  // Set LED state to match door state
  pinMode(led, OUTPUT);
  digitalWrite(led, !state);
  
  // Set the reedswitch pin as interrupt, assign interrupt function and set CHANGE mode
  attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

//connecting to wifi
  Serial.begin(115200);
  WiFi.begin("ssid", "pass");  

}


void loop() {
  if (changeState){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      // If a state has occured, invert the current door state   
      state = !state;
      String htmlMsg=" empty";

      if(state) {
        doorState = "closed";
        htmlMsg = "<div style=\"color:red;\"><h1>Alert!!</h1><p style=\"color: black;\">- Your safe is now closed.</p></div>";

      }
      else{
        doorState = "open";
          htmlMsg = "<div style=\"color:red;\"><h1>Alert!!</h1><p style= \"color: black;\">- Your safe was opened by someone!</p></div>";

      }
      digitalWrite(led, !state);
      changeState = false;
      Serial.println(state);
      Serial.println(doorState);



      /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);



  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "ESP32 LMK by Mashal";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Just to Let You Know";
  message.addRecipient("User", RECIPIENT_EMAIL);

  /*Send HTML message*/
  
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason()); 

    }  
  }
}
