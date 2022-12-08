//Vinicius Fernandes - ex sem 7

#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// configura o nome da rede que será criada
const char *ssid = "Marii";

// configura a senha da rede sem fio criada
const char *password = "12345678";

#define LED_BUILTIN 2 // configura o pino do LED embutido
#define ledG 14
#define ledY 15
#define ledB 16
#define buzzer 47
#define botaoG 39
#define botaoY 40
#define botaoB 41

AsyncWebServer server(80);

// Variáveis globais
int sequencia[32] = {};
int botoes[3] = { botaoG, botaoB, botaoY};
int leds[3] = {ledG, ledB, ledY};
int tons[4] = {262, 294, 330, 349};
int rodada = 0;
int passo = 0;
int botao_pressionado = 0;
bool game_over = false;

void proximaRodada();
void reproduzirSequencia();
void aguardarJogador();
String html();

void setup()
{
    Serial.begin(9600);

    pinMode(ledG, OUTPUT);   // led1
    pinMode(ledY, OUTPUT);   // led2
    pinMode(ledB, OUTPUT);   // led3
    pinMode(buzzer, OUTPUT); // buzzer
    pinMode(botaoG, INPUT);  // botão2
    pinMode(botaoY, INPUT);  // botão3
    pinMode(botaoB, INPUT);  // botão4

    Serial.println("Conectando ao wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, password);
        delay(800);
        Serial.print(".");
    }

    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req)
              { req->send(200, "text/html; charset=UTF-8", html()); });

    server.begin();
}

String html()
{  
    String html = "";
    html += "<h1>Jogo semana 7 - Vinicius Fernandes </h1>";
    html += "</br>";
    html += "<h3>Genius</h3>";
    html += "</br>";
    html += "<h3>Pontuação: " + String(rodada) + " </h3> ";
    html += "</div>";
    return html;
}

void loop()
{
    proximaRodada();
    reproduzirSequencia();
    aguardarJogador();
    // estrutura para reiniciar todas as variáveis
    if (game_over == true)
    {
        sequencia[32] = {};
        rodada = 0;
        passo = 0;
        game_over = false;
    }
    delay(1000);
}

// Funções
void proximaRodada()
{
    int sorteio = random(4);
    sequencia[rodada] = sorteio;
    rodada = rodada + 1;
    // Serial.print(sorteio);
}

void reproduzirSequencia()
{
    for (int i = 0; i < rodada; i++)
    {
        tone(7, tons[sequencia[i]]);
        digitalWrite(leds[sequencia[i]], HIGH);
        delay(500);
        noTone(7);
        digitalWrite(leds[sequencia[i]], LOW);
        delay(100);
    }
}

void aguardarJogador()
{
    for (int i = 0; i < rodada; i++)
    {
        bool jogada_efetuada = false;
        while (!jogada_efetuada)
        {
            for (int i = 0; i <= 3; i++)
            {
                if (digitalRead(botoes[i]) == HIGH)
                {
                    botao_pressionado = i;
                    tone(7, tons[i]);
                    digitalWrite(leds[i], HIGH);
                    delay(300);
                    digitalWrite(leds[i], LOW);
                    noTone(7);
                    jogada_efetuada = true;
                }
            }
        }
        // verificar a jogada
        if (sequencia[passo] != botao_pressionado)
        {
            // efeito luminoso/sonoro indicando que o jogador perdeu
            for (int i = 0; i <= 3; i++)
            {
                tone(7, 70);
                digitalWrite(leds[i], HIGH);
                delay(100);
                digitalWrite(leds[i], LOW);
                noTone(7);
            }
            game_over = true;
            break;
        }
        passo = passo + 1;
    }
    passo = 0;
}