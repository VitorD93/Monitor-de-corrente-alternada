# Monitor de corrente alternada

Repositório do projeto de monitor de corrente alternada de Projeto integrado de computação.

## Sumário
* [Sumário](#sumario)
* [Resumo](#resumo)
* [Descrição](#descrição)
* [Demonstração](#demonstração)
* [Componentes e materiais](#componentes-e-materiais)
* [Alunos](#alunos)

## Resumo
O projeto é um dispositivo capaz de ler, processar e enviar todos os dados de energia coletados de um fio ligado a um sistema de corrente alternada. Este protótipo auxilia no maior controle, principalmente, do consumo de energia de determinada carga, podendo essa ser até mesmo uma casa inteira.

## Descrição
O projeto consiste em um medidor de energia inteligente que une hardware de medição e conectividade IoT. O módulo PZEM-004T atua como o sensor principal, medindo a tensão da rede, corrente, potência e até consumo de energia. O ESP32 processa as informações e utiliza seu Wi-Fi nativo para transmiti-las à internet, por protocolo MQTT. Assim, o usuário pode monitorar o consumo elétrico em tempo real por aplicativos ou dashboards. É uma solução de baixo custo para transformar painéis elétricos comuns em sistemas inteligentes. O resultado final permite o controle de gastos e a análise de eficiência energética de aparelhos.
Utilizamos dois softwares principais para ler os dados via web. Um é o Ubidots (https://pt.ubidots.com/platform), que proporciona uma visualização gráfica das variáveis do sistema. É somente necessário adicionar o token da sua conta ao código. O outro software utilizado é o HiveMQ MQTT Websocket Client (https://www.hivemq.com/demos/websocket-client/), que fornece uma visualização rápida dos dados em texto, atualizados a cada envio de dados feito pelo ESP32. 

![WhatsApp Image 2026-02-09 at 16 59 50](https://github.com/user-attachments/assets/14bd3af3-010b-4ad9-88d4-417e1703e69c)
Impressões do código no Serial Monitor da Arduino IDE.

![WhatsApp Image 2026-02-09 at 16 59 50 (1)](https://github.com/user-attachments/assets/cd58deaa-0a74-4733-aca2-a4e7ad372a02)
Visualizações das mensagens enviadas por MQTT ao HiveMQ.

![WhatsApp Image 2026-02-09 at 16 59 49](https://github.com/user-attachments/assets/e2dff36a-4df6-40c0-9eb9-0c45041efa73)
Visualiação das variáveis pelo UbiDots, com a representação gráfica.

![WhatsApp Image 2026-02-09 at 17 05 29 (1)](https://github.com/user-attachments/assets/d17794df-85f7-4962-9c18-b9b72166cd77)
![WhatsApp Image 2026-02-09 at 17 05 29](https://github.com/user-attachments/assets/3e3bb0cb-68e2-48e6-b596-62cab19e11e3)
Conexões internas do dispositivo e da bobina.

## Demonstração
Veja o funcionamento em:  [(video de demonstração)](https://youtu.be/4osq0E-oIqU)

## Componentes e materiais
* 1 ESP32
* Modulo PZEM-004t v1.0
* Resistores
* Jumpers
* Cabos
* 1 extensão
* Plug de tomada

## Alunos
* Pedro Sergio Falcao Fabres
* Pedro Guisso Magdinier
* Vitor Dimas Trindade Carvalho Barbara
