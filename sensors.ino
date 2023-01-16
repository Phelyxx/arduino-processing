#define PIN_SENAL_TEMPERATURA A0 // Se define la constante que indica el pin donde se recibe la señal del sensor de temperatura
#define PIN_LED_ALERTA_TEMPERATURA 5 // Se define el pin del LED que va a alertar sobre la alerta de niveles atípicos de temperatura
double temperatura; // Este atributo se declara para almancenar el valor de la temperatura medido en °C

// DECLARACIONES SENSOR DE LUZ
#define PIN_SENAL_LUZ A1 // Se define la constante que indica el pin donde se recibe la señal del sensor de luz
#define PIN_LED_ALERTA_LUZ 6 // Se define el pin del LED que va a alertar sobre la alerta de niveles altos de luz
double luzRecibida; // Este atributo se declara para almancenar el valor de la luz medido en lux


// DECLARACIONES BUZZER
#define PIN_ALARMA_BUZZER 8 // Se define el pin de salida para el buzzer de las alertas
#define FREQ_TEMPERATURA 300
#define FREQ_LUZ 700

// DECLARACIONES DE MENSAJES
String SEPARADOR = ";;;";
String ROSAS = "ROSAS";
String TULIPANES = "TULIPANES";
String TEMPERATURA = "TEMPERATURA";
String LUZ = "LUZ";
String NORMAL = "NORMAL";

//Configuración inicial
void setup() {
  Serial.begin(19200); // Se indica la tasa de transmisión en bauds para la comunicación entre el computador y el Arduino

  // INICIALIZACIÓN SENSOR DE TEMPERATURA
  temperatura = 0.0;
  pinMode(PIN_SENAL_TEMPERATURA, INPUT); // Se declara que el puerto de temperatura va a ser exclusivamente utilizado como entrada
  pinMode(PIN_LED_ALERTA_TEMPERATURA, OUTPUT); // Se declara que el puerto del LED de alerta de luminosidad es solo para salida de señales

  // INICIALIZACIÓN SENSOR DE LUZ
  luzRecibida = 0.0; // Se inicializa el valor de la luz recibida por la planta en 0 por defecto
  pinMode(PIN_SENAL_LUZ, INPUT); // Se declara que el puerto de luz va a ser exclusivamente utilizado como entrada
  pinMode(PIN_LED_ALERTA_LUZ, OUTPUT); // Se declara que el puerto del LED de alerta de luminosidad es solo para salida de señales

  // INICIALIZACIÓN DEL BUZZER
  pinMode(PIN_ALARMA_BUZZER, OUTPUT); // Se declara que el pin es exclusivamente de salida de señales
}

//Bucle
void loop() {

  // LÓGICA SENSOR DE TEMPERATURA 
  temperatura = analogRead(PIN_SENAL_TEMPERATURA); // Se lee la información de temperatura del sensor
  temperatura = (temperatura * 5000.0) / (10240); // Se hace la conversión de la lectura a °C
  if (temperatura < 10.0 || temperatura > 23.0) {
    digitalWrite(PIN_LED_ALERTA_TEMPERATURA, HIGH); // Si la temperatura percibida por la planta tiene valores atípicos, se genera una alarma
    tone(PIN_ALARMA_BUZZER, FREQ_TEMPERATURA); // Si la temperatura percibida por la planta tiene valores atípicos, se genera una alarma auditiva
    Serial.println(ROSAS + SEPARADOR + TEMPERATURA); // Se envía la alerta a Processing
  } else {
    digitalWrite(PIN_LED_ALERTA_TEMPERATURA, LOW); // En caso de que los niveles de temperatura sean los adecuados no se genera la alarma
    noTone(PIN_ALARMA_BUZZER); // Se apaga la alarma
    Serial.println(ROSAS + SEPARADOR + NORMAL); // Se envía la condición normal al Processing
  }

  delay(1000);

  // LÓGICA SENSOR DE LUZ
  luzRecibida = (double) analogRead(PIN_SENAL_LUZ); // Le lee la información del pin del Arduino destinado al sensor de luz
  luzRecibida = (luzRecibida / 1024.0) * 5; // Se convierte el valor obtenido en bits para obtener el voltaje medido
  if (luzRecibida < 4.0 || luzRecibida > 4.8) {
    digitalWrite(PIN_LED_ALERTA_LUZ, HIGH); // Si la luz recibida por la planta tiene valores diferentes a los permitidos se genera una alarma
    tone(PIN_ALARMA_BUZZER, FREQ_LUZ); // Si la luz percibida por la planta tiene valores atípicos, se genera una alarma auditiva
    Serial.println(TULIPANES + SEPARADOR + LUZ); // Se envía la alerta a Processing
  } else {
    digitalWrite(PIN_LED_ALERTA_LUZ, LOW); // En caso de que los niveles de luz sean los adecuados no se genera la alarma
    noTone(PIN_ALARMA_BUZZER); // Se apaga la alarma
    Serial.println(TULIPANES + SEPARADOR + NORMAL); // Se envía la condición normal a Processing
  }

  delay(1000);
}
