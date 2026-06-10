# Global Solution IoT - AeroNet Agro

## Descrição do Projeto

O **AeroNet Agro** é um protótipo IoT desenvolvido para a **Global Solution 2026/1**, utilizando o **ESP32** no ambiente de simulação **Wokwi**.

A proposta do projeto é simular um sistema de **monitoramento agrícola inteligente**, capaz de acompanhar a umidade do solo e indicar quando a irrigação deve ser acionada. A solução utiliza sensores, atuadores, display LCD, comunicação Wi-Fi e endpoints JSON para visualização dos dados em tempo real.

O projeto está alinhado ao contexto da Global Solution ao aplicar Internet das Coisas no agronegócio, contribuindo para o uso de tecnologia no monitoramento ambiental, na tomada de decisão e na automação de processos agrícolas.

---

## Links da Entrega

### Link do Projeto no Wokwi

https://wokwi.com/projects/321525495180034642

### Link do Vídeo

https://youtu.be/2gtQSFjhlhc

### Link do GitHub

https://github.com/ThiagoSpositoo/GlobalSolution_IOT

---

## Tecnologias Utilizadas

* ESP32
* Wokwi
* Arduino/C++
* Wi-Fi
* WebServer
* LCD 16x2 I2C
* Endpoints JSON
* Git e GitHub

---

## Componentes Utilizados

* ESP32 DevKit
* Potenciômetro simulando sensor de umidade do solo
* Botão para acionamento manual da irrigação
* LED vermelho para alerta/irrigação ativa
* LED verde para status normal
* Display LCD 16x2 I2C
* Resistores para os LEDs
* Jumpers de conexão

---

## Funcionamento da Solução

O sistema realiza a leitura da umidade do solo por meio de um potenciômetro, que simula um sensor analógico.

A lógica principal funciona da seguinte forma:

* Quando a umidade do solo está abaixo de 40%, o sistema identifica o solo como seco.
* Quando o solo está seco, o LED vermelho é acionado.
* Quando a umidade está adequada, o LED verde permanece aceso.
* O botão permite ativar a irrigação manualmente.
* O LCD exibe a umidade do solo e o status atual do sistema.
* O ESP32 se conecta ao Wi-Fi e disponibiliza um WebServer com dashboard e endpoints JSON.

---

## Entradas e Saídas

### Entradas

| Entrada           | Componente    | Função                          |
| ----------------- | ------------- | ------------------------------- |
| Entrada analógica | Potenciômetro | Simula a umidade do solo        |
| Entrada digital   | Botão         | Acionamento manual da irrigação |

### Saídas

| Saída           | Componente   | Função                            |
| --------------- | ------------ | --------------------------------- |
| Saída digital   | LED vermelho | Indica alerta ou irrigação ativa  |
| Saída digital   | LED verde    | Indica condição normal            |
| Interface local | LCD 16x2 I2C | Exibe umidade e status do sistema |

---

## Pinos Utilizados

| Componente                      | Pino no ESP32 |
| ------------------------------- | ------------- |
| Sensor de umidade/potenciômetro | GPIO 34       |
| Botão manual                    | GPIO 27       |
| LED vermelho                    | GPIO 25       |
| LED verde                       | GPIO 26       |
| LCD SDA                         | GPIO 21       |
| LCD SCL                         | GPIO 22       |

---

## Endpoints JSON

O ESP32 disponibiliza três endpoints JSON principais:

### `/dados`

Retorna os dados gerais do sistema.

Exemplo de resposta:

```json
{
  "projeto": "AeroNet Agro",
  "umidadeSolo": 35,
  "soloSeco": true,
  "irrigacaoManual": false,
  "irrigacaoAtiva": true
}
```

---

### `/status`

Retorna o status do solo.

Exemplo de resposta:

```json
{
  "status": "CRITICO",
  "mensagem": "Umidade do solo abaixo do ideal"
}
```

---

### `/irrigacao`

Retorna o estado da irrigação.

Exemplo de resposta:

```json
{
  "irrigacaoAtiva": true,
  "modo": "AUTOMATICO"
}
```

---

## Dashboard Web

Além dos endpoints JSON, o projeto possui uma página inicial no WebServer do ESP32, funcionando como um dashboard simples para visualização dos dados.

O dashboard exibe:

* Umidade do solo;
* Status do solo;
* Estado da irrigação;
* Modo de funcionamento;
* Links para os endpoints JSON.

---

## Bibliotecas Utilizadas

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

---

## Estrutura do Repositório

```txt
GlobalSolution_IOT/
├── sketch.ino
├── diagram.json
├── libraries.txt
├── wokwi-project.txt
└── README.md
```

---

## Como Executar o Projeto

### Pelo Wokwi

1. Acesse o link do projeto no Wokwi:

```txt
https://wokwi.com/projects/321525495180034642
```

2. Clique em **Start Simulation**.

3. Observe o funcionamento dos componentes:

   * LCD exibindo informações;
   * LED vermelho indicando alerta;
   * LED verde indicando status normal;
   * Botão ativando modo manual;
   * Potenciômetro alterando a umidade do solo.

4. Abra o Serial Monitor para visualizar a conexão Wi-Fi e os dados do sistema.

---

## Regras de Funcionamento

| Condição              | Resultado                                |
| --------------------- | ---------------------------------------- |
| Umidade abaixo de 40% | Solo seco                                |
| Solo seco             | LED vermelho aceso                       |
| Solo adequado         | LED verde aceso                          |
| Botão pressionado     | Irrigação manual ativada                 |
| Irrigação ativa       | Sistema indica modo manual ou automático |

---

## Relação com a Global Solution

O projeto se conecta ao tema da Global Solution ao utilizar IoT para apoiar o monitoramento agrícola inteligente.

A solução pode ser aplicada em cenários de agricultura de precisão, onde sensores coletam dados ambientais e auxiliam produtores na tomada de decisão sobre irrigação, economia de recursos e prevenção de perdas.

O uso do ESP32 permite comunicação via Wi-Fi, disponibilizando dados em tempo real por meio de endpoints JSON e dashboard web.

---

## Requisitos Atendidos

| Requisito                           | Status   |
| ----------------------------------- | -------- |
| Uso de ESP32                        | Atendido |
| Protótipo no Wokwi                  | Atendido |
| 2 entradas                          | Atendido |
| 2 saídas                            | Atendido |
| Interface local                     | Atendido |
| Comunicação Wi-Fi                   | Atendido |
| WebServer/API                       | Atendido |
| 3 endpoints JSON                    | Atendido |
| Dashboard/interface de visualização | Atendido |
| GitHub público                      | Atendido |
| Vídeo de demonstração               | Atendido |
| Documentação no README              | Atendido |

---

## Roteiro Resumido do Vídeo

No vídeo de demonstração, são apresentados:

1. A proposta do projeto AeroNet Agro;
2. O circuito montado no Wokwi;
3. Os componentes utilizados;
4. O código do ESP32;
5. A leitura da umidade do solo;
6. O acionamento dos LEDs;
7. O funcionamento do botão manual;
8. A exibição das informações no LCD;
9. O WebServer e os endpoints JSON;
10. A relação da solução com IoT e agronegócio.

---

## Integrantes

| Nome                       | RM     | Turma |
| -------------------------- | ------ | ----- |
| Thiago Sposito             | 561694 | 2TDSA |
| Vitor Madrigrano           | 564191 | 2TDSR |
| Pedro Henrique Gomes Silva | 562606 | 2TDSA |
| Murilo Macedo Silva        | 566462 | 2TDSA |
| Lucas Lopes Rodrigues      | 563544 | 2TDSA |

---

## Considerações Finais

O projeto **AeroNet Agro** demonstra uma aplicação prática de Internet das Coisas no contexto agrícola.

A solução utiliza o ESP32 para coletar dados simulados de umidade do solo, processar essas informações, acionar indicadores visuais, exibir dados localmente em um LCD e disponibilizar informações via WebServer.

Com isso, o protótipo atende aos requisitos da disciplina de IoT ao integrar sensores, atuadores, comunicação Wi-Fi, endpoints JSON, dashboard e documentação técnica.

