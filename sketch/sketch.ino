// Definição dos códigos de funções
// Cada função deve ter um código único
#define f_debug                  0
#define f_getObjectHandle        1
#define f_movimenta              2
#define f_virar                  3

// Variáveis globais para os handlers da juntas dos motores
int motorDireito, motorEsquerdo;

void setup() {
  // Inicia porta de comunicação serial
  // A velocidade de comunicação deve ser a mesma que a configurada no VREP
  Serial.begin(9600);

  // Envia o comando de sincronização
  // O comando de sincronização é obrigatório
  Serial.println("start");

  // Adquire os handlers das juntas que serão controladas
  // A função de adquirir handlers pode ser executada apenas uma vez no inicio do programa
  // Vamos salvar os handles em variaveis globais
  
  // Adquire handler do motor direito
  motorDireito = getObjectHandle("Roda_D");

  // Adquire handler do motor esquerdo
  motorEsquerdo = getObjectHandle("Roda_E");
}

// Função de Debug
void debug(String value){
  // Imagine o Debug como o Serial Monitor da Arduino IDE
  // Uma vez que a porta de comunicação Serial está sendo utilizada para se comunicar com o VREP,
  // se desejar debugar algum texto ou o valor de uma variável, é necessário exibir esse valor no VREP
  // Pois não é possível utilizar o Serial Monitor da Arduino IDE
  // Então, criamos uma extensão do Serial Monitor diretamente no VREP

  // Monta mensagem do protocolo de comunicação
  String protocolo = String(f_debug) + '#' + String(value);

  // Envia mensagem
  Serial.println(protocolo);
}

// Função para adquirir um Handler de um objeto no VREP
int getObjectHandle(String nome){
  // Para manipular objetos no VREP, como alterar posição de juntas, ou velocidade de motores,
  // é necessário passar como parâmetro o código do "Handle" desse objeto
  // Essa função existe para adquirir o handle de um objeto de "nome" especificado via parametro
  
  // Define o protocolo da mensagem
  String protocolo = String(f_getObjectHandle) + '#' + nome;

  // Envia requisição com o protocolo gerado
  Serial.println(protocolo);

  // Aguarda pela leitura do valor retornado pelo VREP
  String handle = Serial.readStringUntil('#');

  // Retorna o valor do handler do objeto
  return handle.toInt();
}

// Função para movimentar o carrinho
void movimenta(int handleMotorD, int handleMotorE, float velocidade){
  // Para movimentar o carrinho, vamos acionar os dois motores ao mesmo tempo
  // Enviamos a velocidade para o VREP, e então o VREP realiza o acionamento ao mesmo tempo

  // Poderíamos enviar a velocidade para cada motor individualmente
  // Mas se fizessemos isso, um motor seria acionado alguns milisegundos antes do outro
  // E assim, o carrinho não iria andar para a frente ...

  // Montar Protocolo
  String protocolo = String(f_movimenta) + '#' + String(handleMotorD) + '#' + String(handleMotorE) + '#' + String(velocidade);

  // Enviar protocolo
  Serial.println(protocolo);
}

// Função para virar o carrinho
void virar(int handle, float velocidade){
  // A função de virar irá aplicar a velocidade especificada na junta especifica

  // Montar mensagem do protocolo
  String protocolo = String(f_virar) + '#' + String(handle) + '#' + String(velocidade);

  // Enviar protocolo
  Serial.println(protocolo);
}

void loop() {

  // Primeira mensagem
  debug("Executando Loop");

  // Andar carrinho para frente (velocidade em deg/s)
  movimenta(motorDireito, motorEsquerdo, 3);
  delay(1000);

  // Virar Carrinho para um lado (velocidade em deg/s)
  virar(motorDireito, 1);
  delay(100);

  // Andar carrinho para frente (velocidade em deg/s)
  movimenta(motorDireito, motorEsquerdo, 3);
  delay(1000);

  // Parar carrinho (mesma função de movimentar, porém com velocidade 0)
  movimenta(motorDireito, motorEsquerdo, 0);
  delay(1000);
  
  // Andar carrinho para trás (velocidade em deg/s)
  movimenta(motorDireito, motorEsquerdo, -3);
  delay(1000); 

  // Virar Carrinho para um lado (velocidade em deg/s)
  virar(motorDireito, -1);
  delay(100);

  // Andar carrinho para trás (velocidade em deg/s)
  movimenta(motorDireito, motorEsquerdo, -3);
  delay(1000); 

  // Parar carrinho (mesma função de movimentar, porém com velocidade 0)
  movimenta(motorDireito, motorEsquerdo, 0);
  delay(1000);
  
}
