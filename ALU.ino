 int A = 0;
int B = 0;
int operacion = 0;

// Pines de los botones
int btnOperacion1 = 4; // Primer boton para seleccionar operacion
int btnOperacion2 = 5; // Segundo boton para seleccionar operacion
int btnOperacion3 = 6; // Tercer boton para seleccionar operacion
int btnOperacion4 = 7; // Cuarto boton para seleccionar operacion
int btnA = 2;          // Boton para seleccionar A (0 o 1)
int btnB = 3;          // Boton para seleccionar B (0 o 1)

// Pines de los LEDs
int ledResultado = 10;  // LED 1: Resultado de operaciones
int ledAndSignoIndefinido = 11;  // LED 2: Acarreo, signo, indefinido
int ledInfinito = 12;  // LED 3: Infinito (para división por 0)
int ledError = 13;     // LED 4: Error

void setup() {
  // Configurar pines de botones como entradas
  pinMode(btnOperacion1, INPUT);
  pinMode(btnOperacion2, INPUT);
  pinMode(btnOperacion3, INPUT);
  pinMode(btnOperacion4, INPUT);
  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);

  // Configurar pines de LEDs como salidas
  pinMode(ledResultado, OUTPUT);
  pinMode(ledAndSignoIndefinido, OUTPUT);
  pinMode(ledInfinito, OUTPUT);
  pinMode(ledError, OUTPUT);

  Serial.begin(9600);  // Para depuración si es necesario
}

void loop() {
  // Leer los botones para seleccionar A y B
  A = digitalRead(btnA);
  B = digitalRead(btnB);

  // Leer botones para seleccionar la operacion
  int estadoOperacion1 = digitalRead(btnOperacion1);
  int estadoOperacion2 = digitalRead(btnOperacion2);
  int estadoOperacion3 = digitalRead(btnOperacion3);
  int estadoOperacion4 = digitalRead(btnOperacion4);

  // Determinar la operacion: 
  // Combinaciones para 4 botones (0000 - 1111)
  if (estadoOperacion1 == LOW && estadoOperacion2 == LOW && estadoOperacion3 == LOW && estadoOperacion4 == LOW) {
    operacion = 0; // No hacer nada
  } else if (estadoOperacion1 == HIGH && estadoOperacion2 == LOW && estadoOperacion3 == LOW && estadoOperacion4 == LOW) {
    operacion = 1; // Suma (0001)
  } else if (estadoOperacion1 == LOW && estadoOperacion2 == HIGH && estadoOperacion3 == LOW && estadoOperacion4 == LOW) {
    operacion = 2; // Resta (0010)
  } else if (estadoOperacion1 == HIGH && estadoOperacion2 == HIGH && estadoOperacion3 == LOW && estadoOperacion4 == LOW) {
    operacion = 3; // Multiplicacion (0011)
  } else if (estadoOperacion1 == LOW && estadoOperacion2 == LOW && estadoOperacion3 == HIGH && estadoOperacion4 == LOW) {
    operacion = 4; // Division (0100)
  } else if (estadoOperacion1 == HIGH && estadoOperacion2 == LOW && estadoOperacion3 == HIGH && estadoOperacion4 == LOW) {
    operacion = 5; // AND (0101)
  } else if (estadoOperacion1 == LOW && estadoOperacion2 == HIGH && estadoOperacion3 == HIGH && estadoOperacion4 == LOW) {
    operacion = 6; // OR (0110)
  } else if (estadoOperacion1 == HIGH && estadoOperacion2 == HIGH && estadoOperacion3 == HIGH && estadoOperacion4 == LOW) {
    operacion = 7; // NOT (0111)
  } else if (estadoOperacion1 == LOW && estadoOperacion2 == LOW && estadoOperacion3 == LOW && estadoOperacion4 == HIGH) {
    operacion = 8; // XOR (1000)
  } else if (estadoOperacion1 == HIGH && estadoOperacion2 == LOW && estadoOperacion3 == LOW && estadoOperacion4 == HIGH) {
    operacion = 9; // XNOR (1001)
  } else if (estadoOperacion1 == HIGH && estadoOperacion2 == HIGH && estadoOperacion3 == LOW && estadoOperacion4 == HIGH) {
    operacion = 10; // NAND (1011)
  }

  // Apagar todos los LEDs antes de realizar la operacion
  apagarTodosLosLEDs();

  // Ejecutar la operación seleccionada
  switch (operacion) {
    case 0:  
      // No hacer nada en caso de operacion 0000
      break;

    case 1:  // Suma
      digitalWrite(ledResultado, A ^ B);  // XOR para la suma
      digitalWrite(ledAndSignoIndefinido, A & B);  // AND para el acarreo
      break;

    case 2:  // Resta
      digitalWrite(ledResultado, A ^ B);  // XOR para la resta
      digitalWrite(ledAndSignoIndefinido, (!A) & B);  // Signo de la resta
      break;

    case 3:  // Multiplicacion
      digitalWrite(ledResultado, A & B);  // AND para multiplicacion
      break;

    case 4:  // Division
      if (A == 0 && B == 0) {
        // 0 / 0 -> Indefinido
        digitalWrite(ledAndSignoIndefinido, HIGH);  // LED 2: Indefinido
        digitalWrite(ledError, HIGH);  // LED 4: Error
      } else if (A == 1 && B == 0) {
        // 1 / 0 -> Infinito
        digitalWrite(ledInfinito, HIGH);  // LED 3: Infinito
        digitalWrite(ledError, HIGH);     // LED 4: Error
      } else if (A == 0 && B == 1) {
        // 0 / 1 -> Todos los LEDs apagados
        apagarTodosLosLEDs();  // Apagar todos los LEDs
      } else if (A == 1 && B == 1) {
        // 1 / 1 -> Resultado normal
        digitalWrite(ledResultado, HIGH);  // LED 1: Resultado (1)
      }
      break;

    case 5:  // AND
      digitalWrite(ledResultado, A & B);  // Resultado de AND
      break;

    case 6:  // OR
      digitalWrite(ledResultado, A | B);  // Resultado de OR
      break;

    case 7:  // NOT (solo aplica a A)
      digitalWrite(ledResultado, !A);  // Resultado de NOT en A
      break;

    case 8:  // XOR
      digitalWrite(ledResultado, A ^ B);  // Resultado de XOR
      break;

    case 9:  // XNOR
      digitalWrite(ledResultado, !(A ^ B));  // Resultado de XNOR
      break;

    case 10:  // NAND
      digitalWrite(ledResultado, !(A & B));  // Resultado de NAND
      break;


  }

  delay(1000); // Añadir un pequeño retraso
}

// Para apagar todos los LEDs
void apagarTodosLosLEDs() {
  digitalWrite(ledResultado, LOW);
  digitalWrite(ledAndSignoIndefinido, LOW);
  digitalWrite(ledInfinito, LOW);
  digitalWrite(ledError, LOW);
}

