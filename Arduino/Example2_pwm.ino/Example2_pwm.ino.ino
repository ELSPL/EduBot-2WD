

int mtr1_pin = 5;
int in1_pin = 6; 
int mtr2_pin = 9;
int in2_pin = 10;

int enc1_pin = 7;
int enc2_pin = 8;

int val = 0; 

int rotationCountR=0;
int stateCountR=0;
int stateCountTotalR=0;
int stateLastR=digitalRead(enc1_pin);
int stateCurrentR;
int rotationCountL=0;   
int stateCountL=0;
int stateCountTotalL=0;
int stateLastL=digitalRead(enc2_pin);

int stateCurrentL=0;
int wheel_circ=204.2;
int statesPerRotation=40;
int distancePerStep=wheel_circ/statesPerRotation;
int distanceL;
int distanceR;
int avgDistance;
void setup() {
  Serial.begin(9600);
  pinMode(in1_pin, OUTPUT);
  pinMode(mtr1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  pinMode(mtr2_pin, OUTPUT);
  pinMode(enc1_pin,INPUT);
  pinMode(enc2_pin,INPUT);
  
  
  

  analogWrite(in1_pin, 0);
  analogWrite(mtr1_pin, 0);
  analogWrite(in2_pin, 0);
  analogWrite(mtr2_pin, 0);
}

void loop() {
  
  
  for(val=50; val<=255; val+=50){
      analogWrite(mtr2_pin, val);
      analogWrite(mtr1_pin, val);
      for(int i= 0;i<=100; i++){
        stateCurrentL=digitalRead(enc1_pin);
         if(stateCurrentL!=stateLastL){
          stateLastL=stateCurrentL;
          stateCountL+=1;
          stateCountTotalL+=1;
         }

         if(stateCountL==statesPerRotation){
          rotationCountL +=1;
          stateCountL=0;
         }

         stateCurrentR=digitalRead(enc2_pin);
         if(stateCurrentR!=stateLastR){
          stateLastR=stateCurrentR;
          stateCountR+=1;
          stateCountTotalR+=1;
         }

         if(stateCountR==statesPerRotation){
          rotationCountR +=1;
          stateCountR=0;
         }

         distanceL=distancePerStep*stateCountTotalL;
         distanceR=distancePerStep*stateCountTotalR;
         float(avgDistance) = (float(distanceL)+float(distanceR)/2);

         Serial.print("Bot: Distance ");
         Serial.print(float(avgDistance));
         Serial.print("Steps");
         Serial.println((stateCountL+stateCountR)/2);
         
         
        
      }
  }
}
