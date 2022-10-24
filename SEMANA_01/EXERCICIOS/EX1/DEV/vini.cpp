#include <stdio.h>
#include <iostream>
using namespace std;
// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores mínimo e máximo e retorna esse valor
int converteSensor(int minimo, int maximo, int neutroP){
    int posicaoP = int((float(neutroP-minimo)/float(maximo-minimo))*100);
    return posicaoP;
}
// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor
int leSensor(){
    int value;
    cin >> value;
    cout << value;
   return value;
}
// 3 - Faça uma função que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor
int InsertArray(int valorNovo, int ultimoIndex, int *v, int valorMaximo){
    int *array = v;
    array[ultimoIndex] = valorNovo;
    return ultimoIndex++;
}
// while()
// int medida = readSensor
// 4 - Faça uma função que recebe um vetor com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta maior distância.
const char *direcaoMenorCaminho(int *i, int *d)
{
    const char *dir[] = {"Direita", "Esquerda", "Frente", "Tras"};
    int p = 0;
    for (int o = 0; o < 4; o++)
    {
        if (i[o] > *d)
        {
            *d = i[o];
            p = o;
        }
    }
    return dir[p];
}
// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso
bool leComando(){
    char resposta;
    cout << printf("Deseja continuar? 'S' para Sim, 'N' para Não") << endl;
    cin >> resposta;
    if(resposta == 'N'){
        return false;
    }else{
        return true;
    }
}
// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", "Frente", "Tras").
// Em outras palavras, o robô tem 4 semsores, um em cada ponto, e eles vão indicar para o robô em que direção ele deve se mover.
// A cada passo, ele verifica as distâncias aos objetos, de cada direção,
//e vai "mapeando" o terreno para uma movimentação futura, armazenando estas distancias em um vetor fornecido como parâmetro.
// No final a função retorna a ultima posicao preenchida do vetor.
// Esta função deve também ir lendo os 4 sensores até que um comando de pare seja enviado.
// Para simular os sensores e os comandos de pare, use as funções já construídas nos ítens anteriores
//e em um looping contínuo até que um pedido de parada seja enviado pelo usuário.
//Complete a função com a chamada das funções já criadas
int dirige(int *v,int maxv){
    int maxVetor = maxv;
    int *vetorMov = v;
    int posAtualVetor = 0;
    int dirigindo = 1;
    while(dirigindo){
        int medida = leSensor(); /// .. Chame a função de de leitura da medida para a "Direita"
        medida = converteSensor(medida,0,830);
        posAtualVetor = InsertArray(medida, posAtualVetor , v, maxVetor); // Chame a função para armazenar a medida no vetor
        ///////////////////////////////////////////////////////////////////////////
        medida = leSensor();
        int minimo_valor = leSensor(); int maximo_valor = leSensor(); int posicao_valorN = leSensor();
        medida = converteSensor(minimo_valor, maximo_valor, posicao_valorN);
        // Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
        // ................
        ///////////////////////////////////////////////////////////////////////////
        dirigindo = leComando();
    }
    return posAtualVetor;
}
// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){
    int *vetorMov = v;
    int maiorDir = 0;
    for(int i = 0; i< tamPercorrido; i+=4){
       const char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
        printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
    }
}
int main(int argc, char** argv) {
    int maxVetor = 100;
    int vetorMov[maxVetor*4];
    int posAtualVet = 0;
    posAtualVet = dirige(vetorMov,maxVetor);
    percorre(vetorMov,posAtualVet);
    return 0;
}