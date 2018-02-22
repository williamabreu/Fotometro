#define pinLDR A0
#define pinBuzz 7

void setup() {
    Serial.begin(9600);
    
    pinMode(pinBuzz, OUTPUT);
    
    digitalWrite(pinBuzz, LOW);
    delay(500);
    digitalWrite(pinBuzz, HIGH);
    delay(500);
    digitalWrite(pinBuzz, LOW);
    delay(500);
    digitalWrite(pinBuzz, HIGH);
    delay(500);
    digitalWrite(pinBuzz, LOW);
}

void loop() {
    Serial.print("LDR = ");
    Serial.println(analogRead(pinLDR));
    delay(500);
}

