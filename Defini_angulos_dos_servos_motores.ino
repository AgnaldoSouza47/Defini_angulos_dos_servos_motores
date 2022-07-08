/*Defini_angulos_dos_servos_motores
Aguinaldo Alves de Souza 
Analise e desenvolvimento de sistemas e Técnico mecatrônica
03/06/2022  Definição dos graus dos servos motores através das letras do teclado
Controle dos servos do robozinho em tempo real via serial monitor
INSTRUÇÕES
  G-g - (0 - 180 GRAUS) : MOVIMENTA A GARRA
  C-c - (0 - 180 GRAUS) : MOVIMENTA O COTOVELO
  O-o - (0 - 180 GRAUS) : MOVIMENTA O OMBRO
  B-b - (0 - 180 GRAUS) : MOVIMENTA A BASE
*/

// Bibliotecas de auxilio
 #include Arduino.h
#include Servo.h

//Definições das variáveis constantes
#define servoGarra       8    
#define servoCotovelo    6
#define servoOmbro       5
#define servoBase        3

//Funções de auxilio

void dividString(char* Entrada);
void definiPosition(char* grau);

// Atribuição de objetos (servos do braço)

Servo servo_Base, servo_Cotovelo, servo_Ombro,servo_Garra ;

//Variáveis
//vetor para armazenar string de texto evitar estouros de buffer
char buffer[18];

void setup() {
 Serial.begin(9600);
//inicia comunicação serial a 9600bps
//libera caracteres que estejam na linha
    //serial, deixando-a pronta para in/outs
  //configura os pinos dos servos como saída digital

Serial.flush();{ 
   
 //inicio dos servos a angulos pré definidos
 servo_Base.write(90);
  servo_Ombro.write(30  );
  servo_Cotovelo.write(160);
   servo_Garra.write(50);

  // definição dos pinus de saida
  pinMode(servoGarra, OUTPUT);
  pinMode(servoOmbro, OUTPUT); 
 pinMode(servoCotovelo, OUTPUT); 
 pinMode(servoBase, OUTPUT); 

//Anexa os pinos do Arduino ao respectivo servo
  
 servo_Garra.attach(8); 
 servo_Ombro.attach(5);  
 servo_Cotovelo.attach(6);
 servo_Base.attach(3);
 }
 }//FIM DO SETUP

void loop() {
//verifica se foi enviado um caractere para a serial
  if(Serial.available() > 0)
 
 {   
//armazena a posição de um ponteiro para os caracteres do vetor 
  int index = 0;
    delay(100); 
//deixa o buffer encher
  int numerChar = Serial.available();
//atribui o numero de caracteres digitados  
  if(numerChar > 15) numerChar = 15; 
//evita o estouro do buffer 
 while(numerChar--)

 //executa até que numero de caracteres(numerChar) seja zero 
 {
   buffer[index++] = Serial.read();
}
 //le a serial e armazena no vetor   
  dividString(buffer); 
//chama a função dividString com buffer como parametro
 }
}
  void dividString(char* Entrada){
 Serial.println(" "); 
Serial.print("                 Entrada de dados: "); 
 Serial.println(Entrada);
//ESPAÇO...............vazio
 Serial.println("....................................");
//MOSTRE OS DADOS PARA DIREITA>>
 Serial.print(">> ");
 char* parameter;
 //variavel para acessar os elementos do vetor data
 parameter = strtok (Entrada, " ,"); 
//divide a string quando encontrar um espaço ou uma vírgula
 while(parameter != NULL) //_Parametro é diferente de vazio
//executa enquanto parameter não estiver vazia
 {
definiPosition(parameter); 
 parameter = strtok (NULL, " ,"); // função strtok interrompe a string quando encontra espaço ou virgula
                                        //  strtok quando quer movimentar dois ao mesmo tempo exemplo (garra A 180 e punho P 80)
//preenche o vetor com caracteres NULL 
}
//Limpa o texto e os buffers seriais
for(int x=0; x<16; x++)
{
 buffer[x]='\0'; 
} 
 Serial.flush(); 
//libera caracteres que estejam na linha serial, deixando-a pronta para in/outs
  }

void definiPosition(char* grau)
{
 if((grau[0] == 'B') || (grau[0] == 'b')) 
//verifica a  letra inicial  de (qual servo 'B' Base ou  'b' base)
 {
 int Ang = strtol(grau+1, NULL, 10);   
  //define Angulo como numero na proxima parte do texto
   Ang = constrain(Ang,0,180); 
//Garante que Angulo esteja entre 0 e 180 graus 
 servo_Base.write(Ang);   
   //atribui o grau da posição do eixo do servo
  Serial.print("MOTOR da BASE foi definido para o angulo : "); 
 Serial.println(Ang);
 }

 if((grau[0] == 'O') || (grau[0] == 'o'))
 {
  int Ang = strtol(grau+1, NULL, 10);
    Ang = constrain(Ang,0,180);
  servo_Ombro.write(Ang);
  Serial.print("MOTOR do OMBRO foi definido para o angulo: ");
  //MOSTRE O GRAU(ANGULO)
  Serial.println(Ang);
 }     
                  
 if((grau[0] == 'C') || (grau[0] == 'c')) 
 {
  int Ang = strtol(grau+1, NULL, 10); 
   Ang = constrain(Ang,0,180);
  servo_Cotovelo.write(Ang);
  Serial.print("MOTOR do COTOVELO foi definido para o angulo: ");
  Serial.println(Ang);
 } 
 if((grau[0] == 'G') || (grau[0] == 'g'))
 {
  int Ang = strtol(grau+1, NULL, 10);
    Ang = constrain(Ang,0,180);
  servo_Garra.write(Ang);
 
 Serial.print("MOTOR da GARRA foi definido para o angulo: ");
  Serial.println(Ang);
 }
 // Fim do void definiPosition
}//FIM DO LOOP
//FIM DA PROGRAMAMAÇÃO
















