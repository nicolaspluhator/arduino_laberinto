// Definimos los ultrasonicos por cada lado
/*
  Todos las posiciones es en base al robot.
    Ej:
      Derecha -> Derecha del robot 
        (En nuestro caso sera izquierda)
*/
// Derecha
#define trig_der 7
#define echo_der 8

// Frente
#define trig_frente 3
#define echo_frente 2

// Izquierda 
#define trig_izq 5
#define echo_izq 4

// Definimos los motores
#define in1 11
#define in2 9
#define in3 10
#define in4 6

// Velocidad
#define velocidad 80

// Definimos una variable p/ valor anterior
int valor_anterior = 0;
int distancia_muro = 10;

int sensorFrente = 0;
int sensorDerecha = 0;
int sensorIzquierda = 0;
  
void setup()
{
  // Definimos los componentes a ocupar
  /* 
      Ultrasonicos 
  */
  
  // DERECHA
  pinMode(trig_der, OUTPUT);
  pinMode(echo_der, INPUT);
  // FRENTE
  pinMode(trig_frente, OUTPUT);
  pinMode(echo_frente, INPUT);
  // IZQUIERDA
  pinMode(trig_izq, OUTPUT);
  pinMode(echo_izq, INPUT);
  
  /*
      Motores
  */
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  /*
      Monitor Serial
  */
  Serial.begin(9600);

  avanzar();
  delay(2000);
}

void loop()
{ 
  sensorDerecha = distanciaDerecha();
  sensorFrente = distanciaFrente();
  sensorIzquierda = distanciaIzquierda();
  
  if (sensorDerecha > distancia_muro) {
    // Gira a la derecha
    if(sensorFrente < distancia_muro){
        girarDerecha();
    }else{
      girarDerecha();
      avanzar();
    }
    delay(150);
  } else if (sensorFrente > distancia_muro) {
    // Sigue recto
    if((sensorDerecha > sensorIzquierda) or (sensorIzquierda > sensorDerecha)){
      int velocidadDerecha = map(sensorDerecha, 10, 0 , 80, 100);
      int velocidadIzquierda = map(sensorIzquierda, 10, 0 , 80, 100);
      avanzar(velocidadDerecha, velocidadIzquierda);
    }else{
      avanzar();  
    }
  } else {
    // Gira a la izquierda
    if(sensorFrente < distancia_muro){
        girarIzquierda();
    }else{
      girarIzquierda();
      avanzar();
    }
    delay(150); 
  }
}

long u_distancia(int trigger_pin, int echo_pin) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  long microseconds = pulseIn(echo_pin , HIGH);
  long u_distancia;
  u_distancia = microseconds / 29 / 2;
  if(u_distancia != 0){
   valor_anterior = u_distancia; 
  }
  if (u_distancia == 0) {
    u_distancia = valor_anterior;
  }
  return u_distancia;
}

long distanciaDerecha(){
  return u_distancia(trig_der, echo_der);
}

long distanciaFrente(){
  return u_distancia(trig_frente, echo_frente);
}

long distanciaIzquierda(){
  return u_distancia(trig_izq, echo_izq);
}

// Funciones de movimiento
void avanzar(){
  analogWrite(in2, 0);
  analogWrite(in4, 0); 
  delay(150);
  Serial.println("Avanzar ");
  analogWrite(in1, velocidad);
  analogWrite(in3, velocidad);  
}

void avanzar(int velocidadDerecha, int velocidadIzquierda){
  analogWrite(in2, 0);
  analogWrite(in4, 0); 
  delay(150);
  Serial.println("Avanzar ");
  analogWrite(in1, velocidadDerecha);
  analogWrite(in3, velocidadIzquierda);  
}

void detener(){
  //Serial.println("Detener");
  analogWrite(in1, 0);
  analogWrite(in3, 0); 
  analogWrite(in2, 0);
  analogWrite(in4, 0); 
}

void girarIzquierda(){
  analogWrite(in2, 0);
  analogWrite(in3, 0); 
  delay(150);
  Serial.print("Izquierda ");
  Serial.println(distanciaIzquierda());
  analogWrite(in1, velocidad);
  analogWrite(in4, velocidad);  
}

void girarDerecha(){
  analogWrite(in1, 0);
  analogWrite(in4, 0); 
  delay(150);
  Serial.print("Derecha ");
  Serial.println(distanciaDerecha());
  analogWrite(in2, velocidad);
  analogWrite(in3, velocidad);  
}
