#include <PS2X_lib.h>
#include <Servo.h>
PS2X ps2x;

Servo direcao;
int direcaoPos = 95; 

int error = 0;
int type = 0;
byte vibrate = 0;

// Motor A
int IN1 = 4;
int IN2 = 5;
int velocidadeA = 3; 

// Motor B
int IN3 = 6;
int IN4 = 7;
int velocidadeB = 0; 
int velocidade = 0;

int busina = 9;


void movimentarMotores();
void setup()
{
  
  error = ps2x.config_gamepad(13,11,10,12, true, true);
  ps2x.enableRumble(); 
  ps2x.enablePressures(); 
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(velocidadeA, OUTPUT);
  pinMode(busina, OUTPUT);
  //direcao.attach(9); // Pino do servo motor
 
}
void loop()
{
       error = 0; 
       type = 1; 
       ps2x.read_gamepad(false, vibrate);
       if(ps2x.ButtonPressed(PSB_RED)){
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        delay(300);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        }
      
        if(ps2x.ButtonPressed(PSB_GREEN)){tone(busina, 100, 300); }// Buzina 
        
       // Inicio do codigo de andar para frente e para trás 
        if(ps2x.Analog(PSS_LY) >= 0 && ps2x.Analog(PSS_LY) <= 124){
          velocidade = map(ps2x.Analog(PSS_LY),124,20,0,255);
          Serial.print("para frente : ");
          Serial.println(velocidade);
          movimentarMotores(velocidade,1,0);
       }
       if(ps2x.Analog(PSS_LY) > 130 && ps2x.Analog(PSS_LY) <= 255){
        velocidade =  map(ps2x.Analog(PSS_LY),131,255,0,255);
        Serial.print("para tras : ");
        Serial.println(velocidade);
        movimentarMotores(velocidade,2,0);
        
       }
       if(ps2x.Analog(PSS_LX) > 131 && ps2x.Analog(PSS_LX) <= 255){
        
            velocidade = map(ps2x.Analog(PSS_LX),131,255,0,255);
            Serial.println(velocidade);
            movimentarMotores(velocidade,3,0);
       }
       if(ps2x.Analog(PSS_LX) >= 0 && ps2x.Analog(PSS_LX) <= 124){
            velocidade = map(ps2x.Analog(PSS_LX),124,0,0,255);
            Serial.println(velocidade);
            movimentarMotores(velocidade,4,0);
       }
       if(ps2x.Analog(PSS_LX) >= 125 && ps2x.Analog(PSS_LX) <= 130 && ps2x.Analog(PSS_LY) >= 125 && ps2x.Analog(PSS_LY) <= 130){
            movimentarMotores(0,5,0);
       }
        // fim cod vira tanque direita e esquerda
      
       
        if(ps2x.Analog(PSS_RX) > 130 && ps2x.Analog(PSS_RX) <= 255){
          int direcaoPos =map(ps2x.Analog(PSS_RX),131 , 255, 93 , 47); 
          direcao.write (direcaoPos); 
        }else if(ps2x.Analog(PSS_RX) >= 0 && ps2x.Analog(PSS_RX) <= 126){
          int direcaoPos =map(ps2x.Analog(PSS_RX),127 , 0, 87 , 137); 
          direcao.write (direcaoPos); 
        }else {
          direcao.write(direcaoPos);
        }
      delay(30);
}

void movimentarMotores(int velocidade, int modo, int tempo){
  if(modo == 1){//para frente
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(velocidadeA,velocidade);
    }
  if(modo == 2){//para tras
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(velocidadeA,velocidade);
    }
  if(modo == 3){//para a direita
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(velocidadeA,velocidade);
    }
  if(modo == 4){//para a esquerda 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(velocidadeA,velocidade);
    }
   if(modo == 5){//parado
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW); 
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
}
