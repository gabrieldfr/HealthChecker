# Sistema de monitoramento de sinais vitais de um paciente

> Status: Finalizado ✔️

## Responsável do projeto:
- Gabriel Diegues Figueiredo Rocha
- Linkedin: www.linkedin.com/in/gabrieldiegues

![image](https://github.com/gabrieldfr/GlobalSolution_Edge/assets/127216244/09836462-0fab-4659-bbf3-d6b6f66dcd16)


Este é um código para um sistema de monitoramento de saúde baseado utilizando um ESP32. O sistema mede os batimentos cardíacos, a oxigenação no sangue e a temperatura corporal, enviando esses dados para um servidor MQTT para posterior consulta através de um site. O código utiliza sensores de oxímetro, sensor de batimentos cardíacos e um sensor de temperatura/humidade.

## Componentes Utilizados
- Sensor de Oxímetro (Pino: 34)
- Sensor de Batimentos Cardíacos (Pino: 35)
- Sensor de Temperatura/Humidade DHT22 (Pino: 4)

## Bibliotecas Necessárias
- WiFi.h: para conexão Wi-Fi
- PubSubClient.h: para comunicação MQTT
- DHT.h: para interação com o sensor de temperatura/humidade

## Configuração do MQTT
- Broker: 46.17.108.113
- Porta: 1883
- Tópicos:
  - Subscribe: /TEF/Hosp108/cmd
  - Publish (Oxímetro): /TEF/Hosp108/attrs/o
  - Publish (Batimentos Cardíacos): /TEF/Hosp108/attrs/h
  - Publish (Temperatura): /TEF/Hosp108/attrs/t
- Cliente MQTT: fiware_108

## Configuração da Rede Wi-Fi
- SSID: Wokwi-GUEST
- Senha: ""

## Configuração dos Pinos
- Oxímetro: Pino 34
- Batimentos Cardíacos: Pino 35
- Sensor DHT22: Pino 4

## Inicialização
1. Inicialização da conexão Wi-Fi.
2. Inicialização da conexão MQTT.
3. Inicialização dos sensores.

## Loop Principal
1. Verifica se está conectado ao servidor MQTT. Se não estiver, tenta reconectar.
2. Publica os dados dos sensores no servidor MQTT.

## Funções Principais
- `initWiFi()`: Inicializa a conexão Wi-Fi.
- `initMQTT()`: Inicializa a conexão MQTT.
- `reconnectMQTT()`: Tenta reconectar ao servidor MQTT em caso de desconexão.
- `publishSensorData()`: Publica os dados dos sensores no servidor MQTT.

## Sensores
1. Oxímetro:
   - Lê o valor analógico do sensor.
   - Converte e publica a oxigenação no sangue em porcentagem.
2. Batimentos Cardíacos:
   - Lê o valor analógico do sensor.
   - Converte e publica a frequência cardíaca.
3. Temperatura e Humidade:
   - Lê os valores do sensor DHT22.
   - Publica a temperatura corporal.

**Nota:** Certifique-se de ajustar as configurações de Wi-Fi e MQTT para corresponder ao seu ambiente.
# Link para um vídeo explicando com mais detalhes o projeto:
https://youtu.be/5Oj7pZV8qNo
