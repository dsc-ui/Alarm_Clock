#include <LiquidCrystal.h>                          // includes the LiquidCrystal Library DOCUMENTATION can be found here -> https://www.arduino.cc/reference/en/libraries/liquidcrystal/
// #include <DHT.h>


/*================================
    LCD, BUZZER AND BUTTON INPUTS
  ================================*/
#define rs 7
#define en 8
#define d4 9
#define d5 10
#define d6 12
#define d7 13
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);           // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7) 
#define ALARM 5
#define BUZZPIN 6


/*==================================
    DEFINE VARIABLES
  ===================================*/
int secs = 0;
int mins = 0;
int hour = 0;
String time;   
String time_alarm;
int hour_alarm = 12;
int mins_alarm = 0;


/*==================================
    SETUP FUNCTION (run once)
  ===================================*/
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(16, 2);                         // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
  pinMode(BUZZPIN, OUTPUT);
  digitalWrite(BUZZPIN, LOW);
  pinMode(ALARM, INPUT_PULLUP);
  starter();
}


/*==================================
    LOOP FUNCTION (runs continuously)
  ===================================*/
void loop() {
  // put your main code here, to run repeatedly:
  clock();  
  if(digitalRead(ALARM)==LOW)
  {
    Serial.println("SETTING ALARM ...");
    alarmset(); 
  }
  check();
}


/*==================================
    WELCOME SCREEN AND READ CURRENT TIME
  ===================================*/
void starter()
{
  for (int i = 0; i < 5; i++)
  {
    lcd.setCursor(0, 0);                    // Sets the location at which subsequent text written to the LCD will be displayed 
    lcd.print("PLEASE WAIT");               // Prints "PLEASE WAIT" on the LCD
    if (i % 3 == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("/");
      delay(1000);
    }
    else if (i % 3 == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print("-");
      delay(1000);
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("\\");
      delay(1000);
    }
    lcd.clear();                            // Clears the display 
  }
  lcd.print("HEYY THERE!!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  lcd.print("Enter the time");
  lcd.setCursor(0, 1);
  lcd.print("HH:MM:SS");  
  Serial.println("Enter the time in this format HH:MM:SS: ");
  delay(10000);
  
  if (Serial.available() > 0) {
    // read the incoming string:
    time = Serial.readString();
    Serial.println(time);
  }

  // split the time read into hours, minutes and seconds
  hour = time.substring(0,2).toInt();
  mins = time.substring(3,5).toInt();
  secs = time.substring(6,8).toInt();
 
  lcd.setCursor(0, 0);
  lcd.print("The time set is:");
  lcd.setCursor(0, 1);
  lcd.print(time);
  delay(3000);      
  lcd.clear();
  secs = secs + 3;
}


/*==================================
    INCREMENTS TIME BY 1 SECOND   07:53:09
  ===================================*/
void clock()
{
  updatetime();
  lcd.setCursor(0,0);
  lcd.print("TIME:");
  lcd.setCursor(3, 1);
  if (hour < 10){
    lcd.print("0");
  }
  lcd.println(hour);
  lcd.setCursor(5, 1);
  lcd.print(":");
  if (mins < 10){
    lcd.print("0");
  }
  lcd.print(mins);
  lcd.setCursor(8, 1);
  lcd.print(":");
  if (secs < 10){
    lcd.print("0");
  }
  lcd.print(secs);
  secs = secs + 1;
  delay(1000);
  lcd.clear();
}


/*==================================
    SETS ALARM
  ===================================*/
void alarmset()
{
  lcd.print("Setting Alarm");
  delay(1000);
  lcd.clear();
  lcd.print("Set the alarm");
  lcd.setCursor(0, 1);
  lcd.print("HH:MM");  
  Serial.println("Enter the time in this format HH:MM : ");
  delay(10000);
  
  if (Serial.available() > 0) {
    // read the incoming string:
    time_alarm = Serial.readString();
    Serial.println(time_alarm);
  }
  // split the time read into hours and minutes
  hour_alarm = time_alarm.substring(0,2).toInt();
  mins_alarm = time_alarm.substring(3,5).toInt();
 
  lcd.setCursor(0, 0);
  lcd.print("The time set is:");
  lcd.setCursor(0, 1);
  lcd.print(time_alarm);
  delay(3000);      
  lcd.clear();

  secs=secs+14;
}


/*==================================
    INCREMENTS MINUTE (when second > 60)
    INCREMENTS HOUR (when minute > 60)     
  ===================================*/
void updatetime()
{
  if (secs >= 60)
  {
    mins = mins + 1;
    secs = secs - 60;;
  }
  if (mins >= 60)
  {
    hour = hour + 1;
    mins = mins - 60;
  }
  if (hour >= 24)
  {
    hour = hour - 24;
    mins = 0;
    secs = 0;
  }
}


/*==================================
    COMPARE CURRENT TIME AND ALARM SET
  ===================================*/
void check()
{
  if(hour_alarm==hour && mins_alarm==mins)
  {
    lcd.clear();
    lcd.print("ALARM!!!");
    tone(BUZZPIN,1915);           // Read more here -> https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
    delay(1000);                  // Wait for 1000 millisecond(s)
    tone(BUZZPIN,1700);
    delay(1000);                  // Wait for 1000 millisecond(s)
    tone(BUZZPIN,1519);
    delay(1000);
    tone(BUZZPIN,1432);
    delay(1000);
    tone(BUZZPIN,1275);
    delay(1000);
    tone(BUZZPIN,1136);
    delay(1000);
    tone(BUZZPIN,1014);
    delay(1000);
    tone(BUZZPIN,0);
    delay(1000);
    secs=secs+8;
  }
  else
  {
    noTone(BUZZPIN);
  }
}