
 # LMK 
 ## Let me Know: A Security-Alarming device using ESP32
#### A simple security system that notifies the user if his safe/drawer/door is opened. The project is built primarily using ESP32 microprocessor and Magnetic Reed Switch. 
![lmk.png](https://github.com/mashal02/tutorial/blob/main/lmk.png)
### Files integration Explanation:

#### Apart from committing changes and integrating different components in the same file, I maintained those different modules of the project into different files. So that while debugging, I can check functionality of each module separately.
#### Testing
+ The code in testing file was used to check the working of esp32, to light up and LED and confirm the pinout of my device.

#### WiFi
+ The file "WiFi" is used to simply connect the ESP32 to WiFi connection when it boots up. The code here contains a placeholder to enter your network SSID and password so it has to be replaced with your own before testing.

#### Email
+ This code now integrates the previous file, i.e WiFI connection as well, and its functionality is to send an email when ESP32 boots up. The content of email is a short html content.

####  door open alert
+ This is the main code file that contains all the modules combined. FIrstly I just included the code that would check if my reed switch is functioning properly or not. I used onboard LED to check that i.e. it turns on or off when the switch opens or closes.
Then in the same file, I integrated code for WiFi connection and sending email. 

```diff
- Note:
+ In order for this to work, you need to replace with your own credentials.
Add your own network SSID and password. And for email, add a sender email and the password
is not the actual email password, it is the one that is generated upon 2-step verification.
Then finally, also replace the receiver'e email address to your own.
Moreover, change gpio pin for reed switch according to how you connected the switch.
```
