import processing.serial.*;
//Debe revisar el puerto COM al que está conectado el Arduino.
String portname = "COM3";
String SEPARATOR=";;;";

String ROSAS = "ROSAS";
String TULIPANES = "TULIPANES";

String TEMPERATURA = "TEMPERATURA";
String LUMINOSIDAD = "LUZ";
String NORMAL = "NORMAL";

String tipoPlanta = "";
String estadoRosas = NORMAL;
String estadoTulipanes = NORMAL;
String fechahora = "";

Serial port;
PImage fondo;
String message = ""; // Mensaje recibido desde el puerto serial

void setup() {
  port = new Serial(this, portname, 19200);
  fondo = loadImage("Background.jpg");
  size(380, 336);  
}

void draw() {
  //Si hay datos desde el puerto seria
  if (port.available()>0) {
    message= port.readStringUntil(10);  //Lee el String proveniente del puerto Serial hasta el caracter \n (salto de linea)
    String[] buffer = parseInput(message); // Se separa el String recibido para discernir entre valores
    tipoPlanta = buffer[0]; // Se obtiene el primer valor del mensaje que se asume que es el tipo de planta
    // Se asigna el tipo de alerta dependiendo de la planta 
    if (tipoPlanta.equals(ROSAS)) {
      estadoRosas = buffer[1].trim();
    } else if (tipoPlanta.equals(TULIPANES)) {
      estadoTulipanes = buffer[1].trim();
    }
  }
  fechahora = hour()+":"+minute();
  // Se verifica cuál es el estado de las rosas y acorde se le asigna el color
  if (estadoRosas.equals(TEMPERATURA)) {
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(255, 0, 0); // Se define que el relleno es de color rojo
    textSize(16);
    fill(255,255,255);
    text(fechahora, 50, 125, 80);
  
    
    rect(50, 110, 80, 80); // Se definen las dimensiones y la posición del cuadrado
  } else if (estadoRosas.equals(LUMINOSIDAD)) {
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(0, 0, 0); // Se define que el relleno es de color negro
    rect(50, 110, 80, 80); // Se definen las dimensiones y la posición del cuadrado
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(255, 0, 0); // Se define que el relleno es de color rojo  
  } else {
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(255, 255, 255); // Se define que el relleno es de color blanco
    rect(50, 110, 80, 80); // Se definen las dimensiones y la posición del cuadrado  
  }  
  textSize(32); // Tamaño del texto
  text(ROSAS, 40, 230); // Creación del texto con el escrito y la posición para las rosas
  fill(0, 102, 153); // Creación del texto con el color 
  
    // Se verifica cuál es el estado de los tulipanes y acorde se le asigna el color
  if (estadoTulipanes.equals(TEMPERATURA)) {
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(255, 0, 0); // Se define que el relleno es de color rojo
    rect(250, 110, 80, 80); // Se definen las dimensiones y la posición del cuadrado
    textSize(16);
    fill(255,255,255);
    text(fechahora, 250, 125, 100);
  } else if (estadoTulipanes.equals(LUMINOSIDAD)) {
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(0, 0, 0); // Se define que el relleno es de color negro
    rect(250, 110, 80, 80); // Se definen las dimensiones y la posición del cuadrado
    textSize(16);
    fill(255,255,255);
    text(fechahora, 250, 125, 100);       
  } else {
    stroke(0, 0, 0); // Se define que el borde es de color negro
    fill(255, 255, 255); // Se define que el relleno es de color blanco
    rect(250, 110, 80, 80); // Se definen las dimensiones y la posición del cuadrado  
  }  
  textSize(32); // Tamaño del texto
  text(TULIPANES, 210, 230); // Creación del texto con el escrito y la posición para las rosas
  fill(0, 102, 153); // Creación del texto con el color 
}

/**
 * Método que obtiene el mensaje enviado por el puerto serial y separa los valores individuales
 * del mensaje.
 */
String[] parseInput(String input) {
  String[] command = split(input, SEPARATOR); //Se separa el mensaje por el separador
  return command;
}
