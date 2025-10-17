#define SENSOR_PIN 15  // Usa el GPIO que hayas conectado

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int estado = digitalRead(SENSOR_PIN);
  Serial.println(estado == HIGH ? "No hay luz" : "Hay luz");
  delay(500);
}
