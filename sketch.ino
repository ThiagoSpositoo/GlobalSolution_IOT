```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_SOLO 34
#define PIN_BOTAO 27
#define LED_VERMELHO 25
#define LED_VERDE 26

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int umidadeSolo = 0;
bool irrigacaoManual = false;
bool soloSeco = false;
bool irrigacaoAtiva = false;

void atualizarSensores() {
  int leituraAnalogica = analogRead(PIN_SOLO);

  // Sensor simulado: 0 = 0% e 4095 = 100%
  umidadeSolo = map(leituraAnalogica, 0, 4095, 0, 100);

  int estadoBotao = digitalRead(PIN_BOTAO);

  if (estadoBotao == LOW) {
    irrigacaoManual = true;
  } else {
    irrigacaoManual = false;
  }

  soloSeco = umidadeSolo < 40;
  irrigacaoAtiva = soloSeco || irrigacaoManual;

  if (irrigacaoAtiva) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  Serial.print("Umidade do solo: ");
  Serial.print(umidadeSolo);
  Serial.print("% | Solo seco: ");
  Serial.print(soloSeco ? "SIM" : "NAO");
  Serial.print(" | Irrigacao manual: ");
  Serial.print(irrigacaoManual ? "SIM" : "NAO");
  Serial.print(" | Irrigacao ativa: ");
  Serial.println(irrigacaoAtiva ? "SIM" : "NAO");
}

void atualizarLCD() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Solo: ");
  lcd.print(umidadeSolo);
  lcd.print("%");

  lcd.setCursor(0, 1);

  if (irrigacaoManual) {
    lcd.print("Manual: ON");
  } else if (soloSeco) {
    lcd.print("Auto: Seco");
  } else {
    lcd.print("Status: OK");
  }
}

void enviarCors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

void handleDados() {
  atualizarSensores();

  String json = "{";
  json += "\"projeto\":\"AeroNet Agro\",";
  json += "\"umidadeSolo\":";
  json += umidadeSolo;
  json += ",\"soloSeco\":";
  json += soloSeco ? "true" : "false";
  json += ",\"irrigacaoManual\":";
  json += irrigacaoManual ? "true" : "false";
  json += ",\"irrigacaoAtiva\":";
  json += irrigacaoAtiva ? "true" : "false";
  json += "}";

  enviarCors();
  server.send(200, "application/json", json);
}

void handleStatus() {
  atualizarSensores();

  String status = soloSeco ? "CRITICO" : "NORMAL";

  String json = "{";
  json += "\"status\":\"";
  json += status;
  json += "\",\"mensagem\":\"";

  if (soloSeco) {
    json += "Umidade do solo abaixo do ideal";
  } else {
    json += "Solo em condicao adequada";
  }

  json += "\"}";

  enviarCors();
  server.send(200, "application/json", json);
}

void handleIrrigacao() {
  atualizarSensores();

  String json = "{";
  json += "\"irrigacaoAtiva\":";
  json += irrigacaoAtiva ? "true" : "false";
  json += ",\"modo\":\"";

  if (irrigacaoManual) {
    json += "MANUAL";
  } else if (soloSeco) {
    json += "AUTOMATICO";
  } else {
    json += "DESLIGADO";
  }

  json += "\"}";

  enviarCors();
  server.send(200, "application/json", json);
}

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>AeroNet Agro - Dashboard IoT</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #0f172a;
      color: #f8fafc;
      margin: 0;
      padding: 20px;
    }

    .container {
      max-width: 900px;
      margin: auto;
    }

    h1 {
      color: #38bdf8;
      margin-bottom: 5px;
    }

    .subtitle {
      color: #cbd5e1;
      margin-bottom: 25px;
    }

    .cards {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
      gap: 15px;
    }

    .card {
      background: #1e293b;
      padding: 20px;
      border-radius: 12px;
      border: 1px solid #334155;
    }

    .card h2 {
      margin-top: 0;
      font-size: 18px;
      color: #93c5fd;
    }

    .value {
      font-size: 32px;
      font-weight: bold;
      margin: 10px 0;
    }

    .ok {
      color: #22c55e;
    }

    .alerta {
      color: #ef4444;
    }

    .manual {
      color: #facc15;
    }

    .endpoints {
      margin-top: 25px;
      background: #020617;
      padding: 15px;
      border-radius: 12px;
      border: 1px solid #334155;
    }

    a {
      color: #38bdf8;
    }

    footer {
      margin-top: 25px;
      color: #94a3b8;
      font-size: 14px;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>AeroNet Agro - Dashboard IoT</h1>
    <p class="subtitle">
      Monitoramento inteligente de umidade do solo com ESP32, LCD, LEDs, botão e WebServer.
    </p>

    <div class="cards">
      <div class="card">
        <h2>Umidade do Solo</h2>
        <div class="value" id="umidade">--%</div>
        <p>Entrada analógica simulando sensor de solo.</p>
      </div>

      <div class="card">
        <h2>Status do Solo</h2>
        <div class="value" id="statusSolo">--</div>
        <p>Solo seco quando a umidade fica abaixo de 40%.</p>
      </div>

      <div class="card">
        <h2>Irrigação</h2>
        <div class="value" id="irrigacao">--</div>
        <p>Ativada automaticamente ou pelo botão manual.</p>
      </div>

      <div class="card">
        <h2>Modo</h2>
        <div class="value" id="modo">--</div>
        <p>Manual, automático ou desligado.</p>
      </div>
    </div>

    <div class="endpoints">
      <h2>Endpoints JSON</h2>
      <ul>
        <li><a href="/dados">/dados</a> - dados gerais dos sensores</li>
        <li><a href="/status">/status</a> - status do solo</li>
        <li><a href="/irrigacao">/irrigacao</a> - estado da irrigação</li>
      </ul>
    </div>

    <footer>
      Global Solution 2026/1 - Disruptive Architectures: IoT, IoB & Generative IA
    </footer>
  </div>

  <script>
    async function carregarDados() {
      try {
        const dados = await fetch('/dados').then(res => res.json());
        const status = await fetch('/status').then(res => res.json());
        const irrigacao = await fetch('/irrigacao').then(res => res.json());

        document.getElementById('umidade').innerText = dados.umidadeSolo + '%';

        const statusSolo = document.getElementById('statusSolo');
        statusSolo.innerText = status.status;
        statusSolo.className = 'value ' + (status.status === 'CRITICO' ? 'alerta' : 'ok');

        const irrigacaoEl = document.getElementById('irrigacao');
        irrigacaoEl.innerText = irrigacao.irrigacaoAtiva ? 'ATIVA' : 'INATIVA';
        irrigacaoEl.className = 'value ' + (irrigacao.irrigacaoAtiva ? 'alerta' : 'ok');

        const modoEl = document.getElementById('modo');
        modoEl.innerText = irrigacao.modo;

        if (irrigacao.modo === 'MANUAL') {
          modoEl.className = 'value manual';
        } else if (irrigacao.modo === 'AUTOMATICO') {
          modoEl.className = 'value alerta';
        } else {
          modoEl.className = 'value ok';
        }
      } catch (erro) {
        console.log('Erro ao carregar dados:', erro);
      }
    }

    carregarDados();
    setInterval(carregarDados, 1000);
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleNotFound() {
  enviarCors();
  server.send(404, "application/json", "{\"erro\":\"Endpoint nao encontrado\"}");
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_SOLO, INPUT);
  pinMode(PIN_BOTAO, INPUT_PULLUP);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("AeroNet Agro");
  lcd.setCursor(0, 1);
  lcd.print("Conectando...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi conectado");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  delay(2000);

  server.on("/", handleRoot);
  server.on("/dados", handleDados);
  server.on("/status", handleStatus);
  server.on("/irrigacao", handleIrrigacao);
  server.onNotFound(handleNotFound);

  server.begin();

  Serial.println("Servidor iniciado!");
  Serial.println("Endpoints disponiveis:");
  Serial.println("/");
  Serial.println("/dados");
  Serial.println("/status");
  Serial.println("/irrigacao");
}

void loop() {
  atualizarSensores();
  atualizarLCD();

  server.handleClient();

  delay(1000);
}
```
