const int pinLED1 = 2;
const int pinLED2 = 3;
const int pinLED3 = 4;
const int pinLED4 = 6;

const int buzzerPin = 7;

const int button_01 = 19;
const int button_02 = 20;

int contagem = 0;
int salva_button[524] = {};

void outra_funcao(int n);

int pinLDR = 9;


void setup() {
  // put your setup code here, to run once:

    pinMode(pinLED1, OUTPUT);
    pinMode(pinLED2, OUTPUT);
    pinMode(pinLED3, OUTPUT);
    pinMode(pinLED4, OUTPUT);

    pinMode(buzzerPin, OUTPUT);

    pinMode(button_01, INPUT);
    pinMode(button_02, INPUT);


    Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  int readLDR = analogRead(pinLDR);

  // int n = (readLDR - 64) / (8126 - 64 / 15);
  int n = (readLDR - 64) / (537);

  Serial.println(n);

  int b = 0;
  
  // while (b > 1) {

  int button_read01 = digitalRead(button_01);
  int button_read02 = digitalRead(button_02);

  if(button_read01 == HIGH){
    outra_funcao(n);
    salva_button[contagem] = n;
    contagem = contagem + 1;
  }

  if(button_read02 == HIGH){
   
    for(int i = 0; i < contagem; i++){
      outra_funcao(salva_button[i]);
    }
  }
}


void outra_funcao (int n) {

    if(n % 2 > 0) {

      digitalWrite(pinLED1, HIGH);

    }

    else{
      digitalWrite(pinLED1, LOW);

    }

    if(n % 4 > 1){
      digitalWrite(pinLED2, HIGH);

    }

    else{
      digitalWrite(pinLED2, LOW);
    }

    if(n % 8 > 3){
      digitalWrite(pinLED3, HIGH);
    }

    else{
      digitalWrite(pinLED3, LOW);

    }

    if(n % 16 > 7){
      digitalWrite(pinLED4, HIGH);
    }

    else{
      digitalWrite(pinLED4, LOW);
    }


  tone(buzzerPin, 200 * n, 500);
  delay(1000);
  digitalWrite(pinLED1, LOW);
  digitalWrite(pinLED2, LOW);
  digitalWrite(pinLED3, LOW);
  digitalWrite(pinLED4, LOW);


}
  //  if(n <= 1){
     
  //  }

  //  else{
  //   (n / 2 != 0) {
  //     ConvertToBinary(n / 2);
  //  }



