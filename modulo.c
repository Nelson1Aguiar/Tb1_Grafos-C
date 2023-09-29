#include "lib.h"

void menu() {
    Grafo* grafo;
    int v,op,vOrigem,vFinal;
    printf("Bem vindo! Digite a quantidade de vertices que seu novo grafo tera: \n");
    scanf("%d",&v);
    grafo=criarGrafo(v);
    do{
        puts("------------------------------DIGITE SUA OPCAO------------------------------\n\n");
        printf("\t1 - Adicionar nova aresta\n\t2 - Exibir grafo\n\t3 - Informar se existe caminho euleriano\n\t4 - Criar um novo grafo\n\t0 - Sair\n");
        scanf("%d",&op);
        switch (op) {
            case 1:
                puts("Digite o par de vertices dessa aresta\n");
                printf("De: ");
                scanf("\t%d",&vOrigem);
                printf("Para: ");
                scanf("\t%d",&vFinal);
                if(vOrigem>(v-1) || vFinal>(v-1) || vOrigem<0 || vOrigem<0){
                    printf("VERTICE NAO EXISTENTE, EXISTEM APENAS OS VERTICES DE O ATE %d\n\n",vFinal-1);
                    system("pause");
                    system("cls");
                    break;
                }
                addAresta(grafo,vOrigem,vFinal);
                system("cls");
                break;
            case 2:
                printGrafo(grafo);
                break;
            case 3:
                if(temCaminhoEuleriano(grafo)){
                    puts("Existe caminho euleriano no grafo em questao!");
                }else{
                    puts("Nao existe caminho euleriano no grafo em questao!");
                }
                break;
            case 4:
                for(int i=0;i<v;i++){
                    liberarLista(grafo->listaAdj[i]);
                }
                free(grafo);
                printf("Digite a quantidade de vertices que seu novo grafo tera: \n");
                scanf("%d",&v);
                grafo= criarGrafo(v);
                break;
            case 0:
                for(int i=0;i<v;i++){
                    liberarLista(grafo->listaAdj[i]);
                }
                free(grafo);
                break;
            default:
                printf("OPCAO INVALIDA!");
                break;
        }
    }while(op!=0);
}

//FUNÇÃO QUE CRIA UM NO PARA A LISTA DE ADJACÊNCIA
Lista* criarNo(int num) {
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
    Lista* novoNo1 = criarNo(fim);
    novoNo1->prox = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNo1;

    Lista* novoNo2 = criarNo(origem);
    novoNo2->prox = grafo->listaAdj[fim];
    grafo->listaAdj[fim] = novoNo2;
}

//FUNÇÃO DE EXIBIR O GRAFO EM FORMA DE LISTA DE ADJACÊNCIA
void printGrafo(Grafo* grafo) {
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