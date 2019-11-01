#include <virtuabotixRTC.h>                                                             

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);// CLK, DAT, RST

void setup()  {      
  Serial.begin(9600);
  myRTC.setDS1302Time(00, 11, 17, 4, 23, 10, 2019); // seconds, minutes, hours, dayofweek, dayofmonth, month, years
}

void loop()  {                                                                                           
// This allows for the update of variables for time or accessing the individual elements.                
  myRTC.updateTime();                                                                                    
                                                                                                         
//Print                                                               
  Serial.print("Current Date / Time: ");                                                                 
  Serial.print(myRTC.dayofmonth);                                                                        
  Serial.print("/");                                                                                     
  Serial.print(myRTC.month);                                                                             
  Serial.print("/");                                                                                     
  Serial.print(myRTC.year);                                                                             
  Serial.print("  ");                                                                                    
  Serial.print(myRTC.hours);                                                                              
  Serial.print(":");                                                                                    
  Serial.print(myRTC.minutes);                                                                           
  Serial.print(":");                                                                                     
  Serial.println(myRTC.seconds);                                                                         
                                                                                                         
// Delay so the program doesn't print non-stop                                                           
  delay(1000);                                                                                          
}                                                                                                        


  
