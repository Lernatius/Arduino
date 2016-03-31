// OTOKON 2014-2015 Güz Dönemi
//  4. Gelenksek Çizleyen Yarışması Birincisi Boomerang isimli robotun kodlarını ihtiva eder.
int sondaki;
// tanımlar 
#define sensor01  A3
#define sensor03  A5
#define sensor05  A4

int motorSag1 = 9;
int motorSag2 = 10;
int motorSagEn = 11;
int motorSol1 = 5;
int motorSol2 = 6;
int motorSolEn = 3;
int motorSolPWM, motorSagPWM;
int bailout;
// Sensör verilerini tutan değişkenler
int sensor01Durum, sensor03Durum, sensor05Durum ;
// motor süren fonksiyon

void setup() {
  sensorOku();
 digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
  //input output ayarı
pinMode(sensor01, INPUT);
pinMode(sensor03, INPUT);
pinMode(sensor05, INPUT);

pinMode(motorSag1, OUTPUT);
pinMode(motorSag2, OUTPUT);
pinMode(motorSagEn, OUTPUT);

pinMode(motorSol1, OUTPUT);
pinMode(motorSol2, OUTPUT);
pinMode(motorSolEn, OUTPUT);

}


//sensorden durum okuma
void sensorOku() {
  sensor01Durum = digitalRead(sensor01);

  sensor03Durum = digitalRead(sensor03);

  sensor05Durum = digitalRead(sensor05);
}
void motorSur(int motorSagPWM, int motorSolPWM) {
analogWrite(motorSagEn, motorSagPWM);
analogWrite(motorSolEn, motorSolPWM);
}

void loop(){
   sensorOku();
  if ( sensor01Durum == 1 &&  sensor03Durum == 0 &&  sensor05Durum == 0){ //Sol sensör siyah üzerinde sola dön
    digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
    motorSur( 240, 45);
    sondaki = 2;
   
  }
 
    
  else if ( sensor01Durum == 0 &&  sensor03Durum == 0 && sensor05Durum == 1 ){ //sağ sensör siyah üzerinde sağa dön
     digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
    motorSur(45,240);
    sondaki = 1;

  }

  else if ( sensor01Durum == 0 &&  sensor03Durum == 1 && sensor05Durum == 1 ){ //sağ sensör siyah üzerinde sağa dön
     digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
    motorSur(35,240);
    sondaki = 1;
  }
  else if ( sensor01Durum == 1 &&  sensor03Durum == 1 && sensor05Durum == 0 ){ //sağ sensör siyah üzerinde sağa dön
    digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
    motorSur(240,35);
    sondaki = 1;
  }
  else  if ( sensor01Durum == 0 && sensor03Durum == 1 && sensor05Durum == 0){ //orta  sensör siyah üzerinde düz git
   digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
   motorSur(200, 200);
    sondaki = 0;
  
  }
  else  if ( sensor01Durum == 0 &&  sensor03Durum == 0  && sensor05Durum == 0){
    //beyaza kaçtı 

    if(sondaki == 0){
     digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
      motorSur(90,90);
     sondaki = 0;
    }
    else if (sondaki == 1){
     digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, LOW);
  digitalWrite(motorSag2, HIGH);
      motorSur(45,210);
     sondaki = 1;
    }
    else if (sondaki == 2){
   digitalWrite(motorSol1, HIGH);
  digitalWrite(motorSol2, LOW);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
  motorSur(210,45);
      sondaki = 2;
    }
    else{
      digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW); 
      motorSur(0,0);
      sondaki = 0;
    }
  }
  else{digitalWrite(motorSol1, LOW);
  digitalWrite(motorSol2, HIGH);
  digitalWrite(motorSag1, HIGH);
  digitalWrite(motorSag2, LOW);
    motorSur(0,0);
    sondaki = 0;
  }     
}




