  
bool direcao;

void setup() {
  pinMode(A0,INPUT);  //LinhaDireito
  pinMode(A1,INPUT);  //LinhaEsquerdo

  pinMode(A2,INPUT);  //IRDireito
  pinMode(A3,INPUT);  //IRMeio
  pinMode(A4,INPUT);  //IREsquerdo
  
  pinMode(11,OUTPUT); //pwmB -- motor esquerdo
  pinMode(10,OUTPUT); //Bin
  pinMode(9,OUTPUT);  //Bin

  pinMode(8,OUTPUT);  //STBY
  digitalWrite(8,0);  //Seta o STBY para desativado

  pinMode(7,OUTPUT);  //Ain
  pinMode(6,OUTPUT);  //Ain
  pinMode(5,OUTPUT);  //pwmA -- motor direito
  
  //DIP Switch:
  //---------------------Ajustar qual laddo é 1 e qual lado e 0------------------------ 
  pinMode(4,INPUT); //Direção de giro da busca-- 1 == esquerda -- 0 == direita
  pinMode(3,INPUT); //Inicia retao quando 1
  pinMode(2,INPUT); //Inicia fazendo um drift
  //-----------------------------------------------------------------------------------
  
  pinMode(13,INPUT);  //Botao de start 

  while(digitalRead(13)==1){} //Aguarda o botao onofre ser pressionado

  delay(5000);      //Aguarda os 5 segunndos 
  digitalWrite(8,1);    //Seta o STBY para ativado

  if(digitalRead(4)==1){
    direcao = true;      //-Seta para girar para esquerda-//
  }else{
    direcao = false;    //-Seta para girar para direita-//
  }
  /*ao longo da luta a variavel direcao é alterada 
  dinamicamente para o robo sempre buscar
  o adversario para o ultimo lado que ele o encontrou*/

  
  if(digitalRead(3)==0){  //---------FRENTAO----------//
    digitalWrite(10,0);
    digitalWrite(9,1);
    digitalWrite(7,0);
    digitalWrite(6,1);
    analogWrite(11,210); //---essa diferenca compensa a diferenca de 
    analogWrite(5,255); //---potencia dos motores e desbalanceamento no robo
    delay(750);
  }
  else if(digitalRead(2)==0){  //---------DRIFT---------//

    //por algum motivo desconhecido temos que usar direção ao contrario aqui

    if (direcao) {  //----------direita----------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,125);
      analogWrite(5,255);
      delay(1000);

    }else{  //----------esquerda----------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,255);
      analogWrite(5,170);
      delay(900);

    }
  }
}
  
void loop() {
  while(analogRead(A0)>800 && analogRead(A1)>800){

    if((analogRead(A3)>40) || ((analogRead(A3)>40) && (analogRead(A4)>40) && (analogRead(A2)>40))){
    //--------Ataca totalmente para frente---------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,255);
      analogWrite(5,255);

    }else if((analogRead(A4)>25) && (analogRead(A3)>25)){
    //--------Ataca ligeiramente para a esquerda---------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,215);
      analogWrite(5,250);
      direcao = false;

    }else if((analogRead(A2)>25) && (analogRead(A3)>25)){
    //--------Ataca ligeiramente para a direita---------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,250);
      analogWrite(5,215);
      direcao = true;

    }else if(analogRead(A4)>25){
    //--------Ataca para a esquerda---------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,255);
      analogWrite(5,75);
      direcao = false;

    }else if(analogRead(A2)>25){
    //--------Ataca para a direita---------//

      digitalWrite(10,0);
      digitalWrite(9,1);
      digitalWrite(7,0);
      digitalWrite(6,1);
      analogWrite(11,75);
      analogWrite(5,255);
      direcao = true;

    }else{  //--------PROCURA ADVERSARIO--------//

      if(direcao){  //--------esquerda--------//

        digitalWrite(10,1);
        digitalWrite(9,0);
        digitalWrite(7,0);
        digitalWrite(6,1);
        analogWrite(11,100);
        analogWrite(5,100);

      }else{  //--------direita--------//

        digitalWrite(10,0);
        digitalWrite(9,1);
        digitalWrite(7,1);
        digitalWrite(6,0);
        analogWrite(11,100);
        analogWrite(5,100);
      }
    }

  }   //---------rotina de linha---------//

  if (analogRead(A0)>800) {  //------Sensor da Direita------//

    digitalWrite(10,1);
    digitalWrite(9,0);
    digitalWrite(7,1);
    digitalWrite(6,0);
    analogWrite(11,200);
    analogWrite(5,125);
    delay(400);
  }
  else if (analogRead(A1)>800) {  //------Sensor da Esquerda------//
    digitalWrite(10,1);
    digitalWrite(9,0);
    digitalWrite(7,1);
    digitalWrite(6,0);
    analogWrite(11,125);
    analogWrite(5,200);
    delay(400);
  }
}
