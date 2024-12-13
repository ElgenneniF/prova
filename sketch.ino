#include <WiFi.h>
#include <HTTPClient.h>

#define led_amaerelo 9 // Pino utilizado para controle do led amaerelo
#define led_verde 41 // Pino utilizado para controle do led verda
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amaerelo

const int pinoBotao = 18;  // pino do botão 
int estadoBotao = 0;  // variavel que guarda o estado do botão

int estadoSemaforo = 0;

unsigned long ultimoMilissegundo = 0;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_amaerelo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(pinoBotao, INPUT); // inicializa o pino do botao como input

  digitalWrite(led_amaerelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

}

void loop() {
  unsigned long millisAtual = millis();
  
  // Verifica estado do botão
  estadoBotao = digitalRead(pinoBotao);
  if (estadoBotao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }
  // Controle do semáforo
    switch (estadoSemaforo) {
        case 0: // LED vermelho ligado
            if (millisAtual - ultimoMilissegundo >= 5000) {
                ultimoMilissegundo = millisAtual;
                estadoSemaforo = 1;
            }
            digitalWrite(led_vermelho, HIGH);
            digitalWrite(led_amaerelo, LOW);
            digitalWrite(led_verde, LOW);
            break;

        case 1: // LED amarelo ligado
            if (millisAtual - ultimoMilissegundo >= 2000) {
                ultimoMilissegundo = millisAtual;
                estadoSemaforo = 2;
            }
            digitalWrite(led_vermelho, LOW);
            digitalWrite(led_amaerelo, HIGH);
            digitalWrite(led_verde, LOW);
            break;

        case 2: // LED verde ligado
            if (millisAtual - ultimoMilissegundo >= 3000) {
                ultimoMilissegundo = millisAtual;
                estadoSemaforo = 0;
            }
            digitalWrite(led_vermelho, LOW);
            digitalWrite(led_amaerelo, LOW);
            digitalWrite(led_verde, HIGH);
            break;
    }
}