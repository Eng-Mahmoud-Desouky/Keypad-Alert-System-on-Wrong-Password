#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial (11,12);
LiquidCrystal_I2C lcd(0x27,16,2); 

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
  
  };
byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String input_pass = "";
String mypass = "135A";
int pos = 0;
void setup(){
  Serial.begin(9600);
    lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Enter your pass");
  mySerial.begin(9600);
  
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    if(key == '#'){
      if(input_pass==mypass){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Done");
        delay(3000);
        }
        else{
          call ();

          
          lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Wrong pass");
        delay(3000);
          }
          home();
      }
      else if (key == 'C'){
       
        if(pos>0){
           pos--;
        lcd.setCursor(pos,1);
        lcd.print(" ");
        input_pass.remove(pos);
        }
        }
        else{
          input_pass+=key;
           lcd.setCursor(pos,1);
          lcd.print(key);
          delay(150);
         
          lcd.setCursor(pos,1);
          lcd.print('*');
           pos++;
          }
         
  }
}


void home (){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter your pass");
  input_pass = "";
  pos=0;
  }

  void call (){
    mySerial.println("ATD+201203258202;");
    }
