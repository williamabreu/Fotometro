#define pinLdr A0
#define pinBuzz 7


// Som que mostra que o sistima acabou de ser ligado:
// [2 apitos rápidos]
void sinalLigar();      

// Som que mostra que o sistema terminou de coletar os
// dados iniciais e o processo de titulação pode iniciar:
// [2 apitos lentos]
void sinalIniciar();    

// Som que mostra que a titulação chegou ao fim, pois a
// solução mudou de cor:
// [apita sem parar]
void sinalMudouCor();



// Variáveis de estado:
float mean = 0; // média
float var = 0;  // variância
int count = 0;  // contagem

// Variável auxiliar para leitura do ldr:
int dadoLido;

// Função para atualizar a média e a variância:
void add(int dado) {
    // Algoritmos de Estimação Recursiva:
    // http://www.mfap.com.br/pesquisa/arquivos/20081212090656-31608.pdf
    count++;
    var = var + ((count - 1) * (dado - mean) * (dado - mean)  / count - var) / count; 
    mean = mean + (dado - mean) / (count);
}



void setup() {
    Serial.begin(9600);    
    pinMode(pinBuzz, OUTPUT);
    
    sinalLigar();

    // Monta o estado inicial a partir dos 30 primeiros dados:
    while (count < 30) {
        dadoLido = analogRead(pinLdr);
        Serial.println(dadoLido);
        add(dadoLido);
        delay(300);
    }

    sinalIniciar();
}


void loop() {
    dadoLido = analogRead(pinLdr);
    Serial.println(dadoLido);
    
    // Detecta o ponto de interesse:
    // Heurística - valor lido deve ser maior que 4x desvio padrão em cima da média recursiva.
    if (abs(dadoLido - mean) > 4*sqrt(var)) {
        sinalMudouCor();
    }
    else {
        add(dadoLido);
    }
    
    delay(300);
}



void sinalLigar() {
    for (int i = 0; i < 2; i++) {
        digitalWrite(pinBuzz, HIGH);
        delay(100);
        digitalWrite(pinBuzz, LOW);
        delay(100);
    }
}

void sinalIniciar() {
    for (int i = 0; i < 2; i++) {
        digitalWrite(pinBuzz, HIGH);
        delay(250);
        digitalWrite(pinBuzz, LOW);
        delay(250);
    }
}

void sinalMudouCor() {
    while (true) {
        digitalWrite(pinBuzz, HIGH);
        delay(100);
        digitalWrite(pinBuzz, LOW);
        delay(100);
    }
}