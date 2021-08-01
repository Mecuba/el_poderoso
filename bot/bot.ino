// DEFINICIONES
#define DERF 5
#define DERB 6
#define IZQF 11
#define IZQB 3
#define EN   10
#define TORETTO 255
#define MEDIA 128
#define VIERNESENLACDMX 10
#define AGRESIVO true
#define EVASIVO false
#define RC false
#define AUTO true

// Variables generales
bool conexionBT = false;
bool modo = false;      //false = RC, true = AUTO
bool rotatingLeft = false;
bool rotatingRight = false;
bool forward = false;
bool backwards = false;
byte cmd;

void setup() {
  int timeUp = millis();
  // put your setup code here, to run once:
  //Iniciamos la comunicación serial
  Serial.begin(9600);
  //Checar conexión con BT, los módulos HC-05/06 resonden al comando "AT" con "OK"
  delayMicroseconds(10);
  Serial.print("AT");
  Serial.print('\r');
  Serial.print('\n');
  while(Serial.available()<= 0){
  ;
  }
  if (Serial.available() > 0){
    String cmd = Serial.readStringUntil('\n');
    Serial.println(cmd);
    if(cmd == "OK"){
      conexionBT = true;
    }
}
 
  //Se usará el TIMER1 para llevar a cabo tareas dependientes de tiempo
  TCCR1A = 0;
  TCCR1B = 0x01;
  TCNT1 = 0;

}

void loop() {
  cmd = 0x00;
  //Serial.println("h");
  // Si se está conectado el módulo BT entonces
  if (/*!ordenador && ConexionModuloBT*/true) {
    //Si está en modo RC
    if(!modo){
      //cmd[0] = 0;
      if(Serial.available()>0){
        Serial.readBytes(&cmd,1);
        //lee bytes restantes en el puerto serie y los descarta, no debería de haber, pero por si las moscas
        int dump = Serial.read();
      }
      
      switch (cmd){
        //no hay nada
        case 'z':
            Serial.println('z');
            stopMotion();
          break;
        //Adelante
        case 'a':
        Serial.println('a');
            goForward(128);
          break; 
        //Atras
        case 'b':
        Serial.println('b');
            goBackwards(128);        
          break;
        //Derecha
        case 'd':
        Serial.println('d');
            StartRightRotation(128);
          break;
        //Izquierda
        case 'i':
        Serial.println('i');
            StartLeftRotation(128);
          break;
        default:
            //No se hace nada
          break;
      }
    }
    
    
  }
}

////// Como no se requiere alta velocidad se usarán funciones básicas de librería en vez de acceso directo a puertos //////

//Función para rotar a la derecha
void StartRightRotation(int velocidad) {
  rotatingRight = true;
  //Si se encuentra moviendose de alguna forma, detenlo
  if (rotatingLeft || forward || backwards ) stopMotion();
  //derecha hacia atrás
  digitalWrite(DERF, LOW);
  analogWrite(DERB, velocidad);
  
  //izquierda hacia adelante
  digitalWrite(IZQB, LOW);
  analogWrite(IZQF, velocidad);

  digitalWrite(EN, HIGH);
}

//Función para rotar a la izquierda
void StartLeftRotation( int velocidad  ) {
  rotatingLeft = true;
  //Si se encuentra moviendose de alguna forma, detenlo
  if (rotatingRight || forward || backwards ) stopMotion();
  //derecha hacia adelante
  digitalWrite(DERB, LOW);
  analogWrite(DERF, velocidad);
  
  //izquierda hacia atrás
  digitalWrite(IZQF, LOW);
  analogWrite(IZQB, velocidad);

  digitalWrite(EN, HIGH);                                 
}

//Función para avanzar hacia adelante
void goForward(int velocidad) {
  forward = true;
  //Si se encuentra moviendose de alguna forma, detenlo
  if (rotatingLeft || rotatingRight || backwards ) stopMotion();
  //derecha e izquierda adelante
  digitalWrite(DERB, LOW);
  digitalWrite(IZQB, LOW);
  analogWrite(DERF, velocidad);
  analogWrite(IZQF, velocidad);
  digitalWrite(EN, HIGH);
}

//Función para avanzar hacia atrás
void goBackwards(int velocidad) {
  backwards = true;
  //Si se encuentra moviendose de alguna forma, detenlo
  if (rotatingLeft || rotatingRight || forward ) stopMotion();
  //derecha e izquierda atrás
  digitalWrite(DERF, LOW);
  digitalWrite(IZQF, LOW);
  analogWrite(DERB, velocidad);
  analogWrite(IZQB, velocidad);
  digitalWrite(EN, HIGH);
}

//Función para detener el movimiento
void stopMotion() {
  digitalWrite(DERF, LOW);
  digitalWrite(IZQF, LOW);
  digitalWrite(DERB, LOW);
  digitalWrite(IZQB, LOW);
  backwards = false;
  forward = false;
  rotatingLeft = false;
  rotatingRight = false;
  
}

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
/*

//Función para buscar enemigos
void LookForPussies(){
  //Analizará los sensores IR en busca de alguien (código de mi servicio social)
}

//Función para atacar a los enemigos
void beatTheCrapOutOfThePussies(byte posEnemigo){
  // 0 - al frente
  // 1 - izquierda
  // 2 - atrás
  // 3 - derecha
  // Alinea el carrito para tener alos enemigos de frente y luego le mete todo el acelerador
  switch (posEnemigo){
    case 0:
        goForward(TORETTO);
      break;
    case 1:
        StartLeftRotation(MEDIA);
        
      break;
    case 2:

      break;
    case 3:

      break;
  }
}

//Función para huir de los enemigod
void runBiiiitch(){
  //Toma acciones evasivas a toda velocidad
}
*/
