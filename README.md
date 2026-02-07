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
