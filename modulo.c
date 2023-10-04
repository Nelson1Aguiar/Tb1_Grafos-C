#include "lib.h"

void menu() {
    Grafo* grafo;
    int v,op,cont=0;
    FILE *arquivo;
    char linha[100];
    arquivo = fopen("C:\\Users\\User\\Desktop\\Grafo.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        cont+=1;
        if(cont==1){
            v=atoi(&linha[0]);
            grafo=criarGrafo(v);
        }else{
            int origem = atoi(&linha[0]);
            int destino;
            for(int i=1;linha[i]!='\n';i++){
                if(linha[i]!=' '&& linha[i]!='\0'){
                    destino=atoi(&linha[i]);
                    addAresta(grafo,origem,destino);
                }
            }
        }
    }
    fclose(arquivo);

    do{
        puts("------------------------------DIGITE SUA OPCAO------------------------------\n\n");
        printf("\t1 - Exibir grafo\n\t2 - Informar se existe caminho euleriano\n\t0 - Sair\n");
        scanf("%d",&op);
        if(!isdigit(op)){
            printf("OPCAO INVALIDA!\n");
            return;
        }
            switch (op) {
                case 1:
                    printGrafo(grafo);
                    break;
                case 2:
                    if (temCaminhoEuleriano(grafo)) {
                        puts("Existe caminho euleriano no grafo em questao!");
                    } else {
                        puts("Nao existe caminho euleriano no grafo em questao!");
                    }
                    break;
                case 0:
                    for (int i = 0; i < v; i++) {
                        liberarLista(grafo->listaAdj[i]);
                    }
                    free(grafo);
                    break;
                default:
                    printf("OPCAO INVALIDA!\n");
                    break;
            }
    }while(op!=0);
}

//FUNÇÃO QUE CRIA UM NO PARA A LISTA DE ADJACÊNCIA
Lista* criarNo(int num,Lista* lista) {
    Lista* novoNo = (Lista*)malloc(sizeof(Lista));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->num = num;
    novoNo->prox = NULL;
    return novoNo;
}
//FUNÇÃO QUE EXECUTA UMA BUSCA EM LARGURA PARA CHECAR SE O GRAFO É CONEXO,
//LEMBRANDO QUE PARA CHECAR SE ELE TEM UM CAMINHO EULERIANO, ESTAMOS USANDO UM TEOREMA QUE DIZ QUE,
//SE O GRAFO FOR CONEXO E TIVER EXATAMENTE DOIS VÉRTICES DE GRAU ÍMPAR, ENTÃO ELE TEM UM CAMINHO EULERIANO
bool eConexo(Grafo* grafo) {
    bool checado[grafo->v];
    for (int i = 0; i < grafo->v; i++) {
        checado[i] = false;
    }

    int vInicial = 0;
    checado[vInicial] = true;

    int queue[grafo->v];
    int inicioFila= 0, finalFila = 0;
    queue[finalFila++] = vInicial;

    while (inicioFila != finalFila) {
        int vPrimeiroFila = queue[inicioFila++];
        Lista* temp = grafo->listaAdj[vPrimeiroFila];

        while (temp) {
            int listaAdj = temp->num;
            if (!checado[listaAdj]) {
                checado[listaAdj] = true;
                queue[finalFila++] = listaAdj;
            }
            temp = temp->prox;
        }
    }

    //SE AO FIM DA BUSCA EM LARGURA, SOBRAR ALGUM VÉRTICE NÃO PINTADO (FALSE), ENTÃO ELE NÃO É CONEXO!
    for (int i = 0; i < grafo->v; i++) {
        if (!checado[i]) {
            return false;
        }
    }
    return true;
}

//FUNÇÃO QUE CHECA SE HÁ EXATAMENTE DOIS VÉRTICES DE GRAUS ÍMPARES
bool temCaminhoEuleriano(Grafo* grafo){
    if(eConexo(grafo)){
        int qtd=0;
        for(int i=0;i<grafo->v;i++){
            Lista* temp=grafo->listaAdj[i];
            int grau=0;
            while(temp!=NULL){
                grau+=1;
                if(temp->prox==NULL){
                    if(grau % 2 != 0){
                        qtd+=1;
                    }
                }
                temp=temp->prox;
            }
        }
        if(qtd==2){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

//FUNÇÃO QUE DESALOCA A LISTA DE ADJACÊNCIA DE CADA VÉRTICE
void liberarLista(Lista* lista){
    while (lista != NULL) {
        Lista* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

//FUNÇÃO QUE ALOCA O GRAFO COM TODOS OS SEUS VÉRTICES E SUAS LISTAS DE ADJACÊNCIA
Grafo* criarGrafo(int v){
    Grafo* grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->v = v;
    grafo->listaAdj = (Lista**)malloc(v * sizeof(Lista*));
    for (int i = 0; i < v; i++) {
        grafo->listaAdj[i] = NULL;
    }
    return grafo;
}

//FUNÇÃO QUE ADICIONA UMA ARESTA NO GRAFO
void addAresta(Grafo* grafo, int origem, int fim) {
    Lista* novoNo1 = criarNo(fim,grafo->listaAdj[origem]);
    novoNo1->prox = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNo1;
}

//FUNÇÃO DE EXIBIR O GRAFO EM FORMA DE LISTA DE ADJACÊNCIA
void printGrafo(Grafo* grafo) {
    system("cls");
    for (int i = 0; i < grafo->v; i++) {
        Lista* corrente = grafo->listaAdj[i];
        printf("Vertice %d: ", i);
        while (corrente != NULL) {
            printf("%d -> ", corrente->num);
            corrente = corrente->prox;
        }
        printf("NULL\n");
    }
}
