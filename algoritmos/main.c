#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define tam_bucket 1000
#define num_bucket_radix 10
#define max_bits 32

// Estrutura para que uma funcao possa retornar a quantidade de comparacoes
typedef struct {  							//e movimentacoes ao mesmo tempo
        int compara;
        int movimenta;
} contador;
// Estrutura usada no bucketsort
 typedef struct {
         int topo;
         int balde[tam_bucket];
 }bucket;

// Estrutura usada no quicksort deterministico e no probabilistico
typedef struct {
        contador cont;
        int retorno;
}contador_quick;
// Estrutura usada no radixsort com subrotina o countingsort
typedef struct {
        contador cont;
        int *vet;
} vetor_auxiliar;

/* Bolha Com Flag*/
contador BolhaComFlag (int L[], int n){
    contador cont;
    int comp=0, mov=0;
    int flag; // Identificador das troca. Caso flag==1 é porque houve troca.
    int j;
    int i = 1;
    do {
        flag = 0; // Caso não haja troca, flag permanecerá 0, e assim sairá
        for (j=0; j<=(n-1-i);j++) {        //do laço (Lista Ordenada)
            /* A lista L percorrerá do 1º ao penúltimo elemento, sempre */
            comp++; 						//comparando com seu subsequente
            if (L[j]>L[j+1]) {
               flag = 1; //Garantirá que o laço externo se repita pelo menos
               // Troca                                 		//mais uma vez
               int aux = L[j];
               L[j] = L[j+1];
               L[j+1] = aux;
               mov++;
            }
        }
        i++;
    } while (flag==1); // Se houve troca, refaça o processo

    cont.compara = comp;
    cont.movimenta = mov;
    return cont;
}

/* Cocktail Sort (bubble sort bidirecional) */
contador CocktailSort (int list[], int n){
    contador cont;
    int length, bottom, top, swapped, i, aux;
    int comp=0, mov=0;
    bottom = 0;
    top = n - 1;
    swapped = 0;
    while(swapped == 0 && bottom < top)//Se não houver troca de posições ou
    {                                   //o ponteiro que sobe ultrapassar o que
        swapped = 1;                    //desce, o vetor esta ordenado
        // Este for é a “ida” para a direita
        for(i=bottom; i < top; i++)
        {
              comp++;
            if(list[i] > list[i + 1])
            {   //indo pra direita:se o proximo é maior que o atual,
                aux=list[i];
                list[i]=list[i+1];
                list[i+1]=aux;
                mov++;
                swapped = 0;
            }
        }
        // diminui o  `top` porque o elemento com o maior valor
        // já está na direita (atual posição top)
        top = top - 1;
        //Este for é a “ida” para a esquerda
        for(i = top; i > bottom; i = i - 1)
        {
            comp++;
            if(list[i] < list[i - 1])
            {
                aux=list[i];
                list[i]=list[i-1];
                list[i-1]=aux;
                mov++;
                swapped = 0;
            }
        }
        //aumenta o `bottom` porque o menor valor já está
        //na posição inicial (bottom)
        bottom = bottom + 1;
    }
    cont.compara = comp;
    cont.movimenta = mov;
    return cont;
}

/* Inserção */
contador InsertionSort (int L[], int n ){
    contador cont;
    int i,j,comp=0, mov=0;
    int pivo; // Elemento do lado direito que será comparado com os elementos
				//do lado esquerdo, de tal forma que seja inserido já ordenado
    for (i=1;i<n;i++) {
        pivo=L[i];
        j=i-1;
        comp++;
        while (j>=0 && pivo<L[j]) {
              comp++;
              L[j+1] = L[j];
              mov++;
              j--;
        }
        L[j+1]=pivo; // Substitui o elemento duplicado pelo pivo
    }
    cont.compara = comp;
    cont.movimenta = mov;
    return cont;
}

/* Seleção */
contador selection_sort(int num[],int tam){
    contador cont;
  int i, j, min, swap,comp=0,mov=0;
  for (i = 0; i < (tam-1); i++)     //percorre o array para ordenar
   {
    min = i;                      //define o primeiro índice como sendo o menor
    for (j = (i+1); j < tam; j++) { //procura outro índice com valor menor
      comp++;                		//anteriormente marca como menor

      if(num[j] < num[min]) {  //compara se existe outro valor menor que o
        min = j;               //anteriormente marcado determina o índice do
      }                        //novo valor menor encontrado
    }
    if (i != min) {     //compara se o índice definido no início foi modificado
      swap = num[i];             //realiza troca de valores conforme o índices
      num[i] = num[min];
      num[min] = swap;
      mov++;
    }
  }
    cont.compara = comp;
    cont.movimenta = mov;
    return cont;
}

/* ShellSort */
contador shellSort(int *vet, int size){
    int i , j , value,comp=0,mov=0;
    contador cont;
    int gap = 1;
    do {     //divide o vetor em subvetores, calculados pela fórmula de
            //recorrência h=h*3 + 1
        gap = 3*gap+1;
    } while(gap < size);  //executa o código abaixo até ter percorrido
    do {                                               //TODOS os subvetores
        gap /= 3;
        for(i = gap; i < size; i++) {        //percorre o subvetor
            value = vet[i];
            j = i - gap;
            comp++;
            while (j >= 0 && value < vet[j]) {
                comp ++;
                vet [j + gap] = vet[j];
                mov++;
                j -= gap;
            }
            mov++;
            vet [j + gap] = value;
        }
    } while ( gap > 1);
    cont.compara = comp;
    cont.movimenta = mov;
    return cont;
}

/* MergeSort */
// Procedimento Merge
contador merge(int vec[], int vecSize){

  int mid;	//variavel responsavel pelo tamanho da metade do vetor
  int i, j, k;//variaveis para controle do procedimento
  int* tmp;	//variavel responsavel pelo armazenamento temporario do vetor vec
  contador cont;
  int mov =0;
  int comp =0;
  tmp = (int*) malloc(vecSize * sizeof(int));
  if (tmp == NULL) {		//se temp n existir sai.
    exit(1);
  }
  mid = vecSize / 2;
  i = 0;
  j = mid;
  k = 0;
  comp++;
  while (i < mid && j < vecSize) {	//enquanto inicio não atingir o meio e
    if (vec[i] < vec[j]) {			//o meio não passar do tamanho do vetor
      tmp[k] = vec[i++];			//armazena vec[i] em tmp se vec[i]<vec[j]
      mov++;
	}
    else {
      tmp[k] = vec[j++];			//armazena vec[j] em tmp se vec[j]<vec[i]
      mov++;
	}
    ++k;                    //variavel responsavel pelo controle do vetor tmp
  }							//é incrementada para armazenar proximo valor em
  comp++;						//proxima posicao
  if (i == mid) {
      comp++;
    while (j < vecSize) {	//se i atingir o meio e enquanto j<tamanho do vec
      comp ++;              //armazena restante das posições de vec[j] em tmp[k]
      tmp[k++] = vec[j++];
      mov++;
	}
  }
  else {						//se o passo anterior não acontecer o vetor
    while (i < mid) {
      comp++;			        //tmp receberá o restante das posições de vec
      tmp[k++] = vec[i++];		//enquanto i não atingir o meio
	  mov++;
    }
  }

  for (i = 0; i < vecSize; ++i) {//escrever em vec (desordenado) o tmp ordenado
    vec[i] = tmp[i];
    mov++;
  }
  free(tmp);						//libera espaço alocado por tmp
  cont.movimenta = mov;
  cont.compara = comp;
  return cont;

}

//Procedimento MergeSort
contador mergesort(int vec[], int vecSize){
  int mid;
int mov = 0;
int comp = 0;
contador cont;
  comp++;
  if (vecSize > 1) {
    comp++;                 //só passará a executar o procedimento mergesort
    mid = vecSize / 2;		//se vetor tiver mais de 1 elemento.
    mergesort(vec, mid);   //chama procedmiento mergesort até dividir todo vetor
    mergesort(vec + mid, vecSize - mid);//tanto a parte da esquerda como a parte
    cont = merge(vec, vecSize);	//da direita no decorrer das partições é feito
    comp= cont.compara+comp;    	   //o merge das metades
    mov = cont.movimenta+mov;         //ordenando-as ateh se obter tudo ordenado
  }
    cont.movimenta = mov;
    cont.compara = comp;
    return cont;
}

/* QuickSort Determinístico*/
//Procedimento Partição Determinístico - Pivô sempre será o 1º elemento do
contador_quick particaoDet(int P[], int inicio, int fim){    //Vetor recebido

    int mov= 0;
    int comp = 0;
    contador_quick quick;
							//Neste procedimento será feito a organização das
	int PIVO = P[inicio];	//partições do vetor L quantas vezes o procedimento
	      				    //for chamado. Utilizando o pivô como referência de
	int i = inicio + 1;		//comparação, teremos duas variáveis percorrendo
	int j = fim;			//todo o vetor, tendo uma variável indo do começo
							//parao fim (pela direita) e outra do fim para o
	comp++;						//começo (pela esquerda) até ambas se crusarem,
	while (i <= j){
            comp++;          //então o procedimento de troca controlado
		while ((i<=fim) && (P[i] <= PIVO)){	//Enquanto a variável i não passar
			i++;			//do fim e o elemento no vetor L respectivo à
			comp++;			//posição i for menor  que o pivô esse, laço
		}                   //acontecerá. Não será executado quando achar um
							//elemento maior que ou igual ao pivô.
		while (P[j] > PIVO){//Enquanto o elemento no vetor L respectivo à
			j--;			//posição j for maior que o pivô esse, laço
			comp++;			//acontecerá. Não sendo mais executado quando achar
		}                   //um elemento menor que o pivô.
		if (i <= j){	  //Se tiver existido um valor relativo ao pivô maior
			int k = P[j];  //pela esquerda e um valor menor que o pivô pela
			P[j] = P[i];  //direita e as variáveis correspondentes ao controle
			P[i] = k; //das varreduras não tiverem se cruzado é efetuada a troca
			i++;
			j--;
			mov++;
		}
	}
	int k = P[j];			//último swap, onde pivô vai ser posto na posição
	P[j] = P[inicio];		//correta após todas as analises, trocando pivô com
	P[inicio] = k;			//última posição que j armazenou
	mov++;

	quick.cont.compara = comp;
	quick.cont.movimenta = mov;
	quick.retorno = j;
	return quick;
}

//Procedimento QuickSort Determinístico
contador quicksortDet(int P[], int inicio, int fim){//Aqui é feito as partições
	int comp=0;                     //necessárias e então será enviado para
	int mov =0;
	contador cont;
	contador_quick quick;
	comp++;
	if (inicio < fim){	//o procedimento de partição, onde lá serão ordenados
		comp++;			//os valores e de lá retornará o valor do pivo, sendo
		quick = particaoDet(P,inicio,fim);	//utilizado novamente para outras
		int j = quick.retorno;             //partições, até q o vetor P esteja
		mov = quick.cont.movimenta+mov;    //completamente ordenado
		comp = quick.cont.compara+comp;
		if (inicio < j-1){
			cont = quicksortDet(P,inicio,j-1);
			comp = cont.compara+comp;
			mov = cont.movimenta+mov;
		}
		if ((j+1) < fim){
			cont = quicksortDet(P,j+1,fim);
			comp = cont.compara+comp;
			mov = cont.movimenta+mov;
		}
	}
  cont.movimenta = mov;
  cont.compara = comp;
  return cont;
}


/* QuickSort Probabilístico */
//Procedimento de troca
int swap(int *a, int i, int j){
    int mov = 0;
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
    mov++;
    return mov;
}
//Procedimento Partição Probabilístico - Pivô calculado para ser o elemento do
contador_quick particaoProb(int *a, int left, int right, int pivot){
    int pos, i;                                         //meio do Vetor recebido
    int mov =0;
    int comp = 0;
    contador_quick quick;
    mov += swap(a, pivot, right);	//efetuada a primeira troca do pivô com o
    pos = left;						//final da particao que estiver sendo
    for(i = left; i < right; i++){	//analisada variavel i percorrera da
            comp++;
        if (a[i] < a[right]){		//esquerda para a direita quando for
            mov += swap(a, i, pos);	//encontrado um valor que a[right] seja
            pos++;					//menor, faz-se a troca do elemento a[i]
        						//com a[pos]incrementa-se pospara armazenar
		}                           //na proxima posiçãoonde pos vai apontar
    }
    mov += swap(a, right, pos);	//ultima troca efetuada entre a[right] e a[pos]

	quick.retorno = pos;
	quick.cont.compara = comp;
	quick.cont.movimenta = mov;
	return quick;
}

contador quicksortProb(int *a, int left, int right){
    int mov=0;
    int comp=0;
    contador_quick quick;
    contador cont;
    comp++;
    if (left < right) //só executa se o [vetor a] analisado tiver mais de 1
    {                                                               //elemento
        int pivot = (left + right) / 2;			//pivot será sempre o valor do
        quick = particaoProb(a,left,right,pivot);//meio do intervalo dado pos
        int pos = quick.retorno;                 //armazenará o pivot que o
        comp = quick.cont.compara+comp;          //procedimento particaoProb
        mov = quick.cont.movimenta+mov;
        cont = quicksortProb(a, left, pos - 1);	//retornar e em seguida serão
        comp = cont.compara + comp;             //feitas as proximas
        mov = cont.movimenta + mov;
        cont = quicksortProb(a, pos + 1, right);//divisoes ateh se ter todas
        comp = cont.compara + comp;          //particoes organizadas resultando
        mov = cont.movimenta + mov;
    }
    cont.compara = comp;
    cont.movimenta = mov;
    return cont;				//na particao total o vetor principal ordenado
}

/* BucketSort */
// Subrotina do bucketsort
 contador bubble(int v[],int tam){
     contador compara;
     int comp=0;
     int mov=0;
         int i,j,temp,flag;
         if(tam)
                 for(j=0;j<tam-1;j++){
                         flag=0;
                         for(i=0;i<tam-1;i++){
                                comp++;
                                 if(v[i+1]<v[i]){
                                         temp=v[i];
                                         v[i]=v[i+1];
                                         v[i+1]=temp;
                                         mov++;
                                         flag=1;
                                 }
                         }
                         if(!flag)
                                 break;
                 }
    compara.movimenta=mov;
    compara.compara=comp;
    return compara;
 }

// Bucketsort
 contador bucket_sort(int v[],int tam){
     contador compara;
     int comp=0;
     int mov=0;
         bucket *b;
         b = malloc(tam * sizeof(bucket));
         int i,j,k;
 /* 1 */ for(i=0;i<tam;i++)                  //inicializa todos os "topo"
             b[i].topo=0;
 /* 2 */ for(i=0;i<tam;i++){      //verifica em que balde o elemento deve ficar
 	  	     j=(tam)-1;
             while(1){
	            if(j<0)
	               break;
	            comp++;
	            if(v[i]>=j*10){
				   b[j].balde[b[j].topo]=v[i];
	               mov++;
	               (b[j].topo)++;
	               break;
	            }
	            j--;
              }
         }

 /* 3 */ for(i=0;i<tam;i++){                     //ordena os baldes
                comp++;
                if(b[i].topo)
                         compara = bubble(b[i].balde,b[i].topo);
		 }
         mov = compara.movimenta+mov;
         comp = compara.compara+comp;
         i=0;
 /* 4 */ for(j=0;j<tam;j++){    //põe os elementos dos baldes de volta no vetor
                 for(k=0;k<b[j].topo;k++){
                         v[i]=b[j].balde[k];
                         mov++;
                         i++;
                 }
         }
    compara.compara = comp;
    compara.movimenta = mov;
    return compara;
 }

/* RadixSort */
// Radixsort com a subrotina do bucketsort
contador radixsort(int vetor[], int tamanho) {
    contador compara;
    int comp=0;
    int mov=0;
    int i;
    int *b;
    b=malloc(tamanho * sizeof(int));
    int maior = vetor[0];
    int exp = 1;
    for (i = 0; i < tamanho; i++) {
            comp++;
        if (vetor[i] > maior){
            maior = vetor[i]; // Recebe o maior valor do vetor
            mov++;
        }
    }
    comp++;
    while (maior/exp > 0) {
        comp++;
        //int bucket[num_bucket_radix] = { 0 }; //criacao do bucket
        int *bucket;
        bucket = malloc(tamanho * sizeof(int));
         for (i = 0; i < tamanho; i++){
            bucket[i] = 0;
         }
        for (i = 0; i < tamanho; i++)
            bucket[(vetor[i] / exp) % 10]++; //intervalo de valores - cada balde
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1]; //qual intervalo do bucket os elementos
        for (i = tamanho - 1; i >= 0; i--){     			//do vetor ficaram
            b[--bucket[(vetor[i] / exp) % 10]] = vetor[i]; //realiza
            mov++;                       //distribuicao dos elementos no bucket
        }
        for (i = 0; i < tamanho; i++){
            vetor[i] = b[i]; //recebe o vetor ordenado
            mov++;
        }
        exp *= 10;
    }
    compara.compara = comp;
    compara.movimenta = mov;
    return compara;
 }

// Radixsort com a subrotina do countingsort
vetor_auxiliar radixSort(int a[],int tamanho) {
        contador compara;
        vetor_auxiliar vetor;
        int comp=0;
        int mov=0;
        int i;
        int p;
        int min_bits = log2(tamanho*10)+1; // numero minimo de bits necessarios
        int w=max_bits; //para representar o intervalo do vetor maximo de bits
        int d=min_bits;//de um inteiro minimo de bits de um inteiro
        int valor_alocacao = 1<<d; // valor usado para alocar memoria
        int *b;
        b = malloc(sizeof(int)*tamanho);
        int *c;
        c = malloc(sizeof(int)*valor_alocacao);
        for(i=0;i<valor_alocacao;i++)
            c[i]=0;
        for (p = 0; p < w/d; p++) {
            for (i = 0; i < tamanho; i++)
                c[(a[i] >> d * p) & ((1 << d) - 1)]++; // Extrai o inteiro cuja
            for (i = 1; i < 1<<d; i++)   //representação binária é dada por bits
                                         //e faz a contagem
                c[i] += c[i-1]; // Realiza o soma acumulada
            for (i = tamanho - 1; i >= 0; i--){
                comp++;
                b[--c[(a[i] >> d*p)&((1<<d)-1)]]=a[i]; // Ordenacao do vetor
                mov++;
            }
            a=b;

        }
    vetor.cont.compara = comp;
    vetor.cont.movimenta = mov;
    vetor.vet = b;
    return vetor;
}
/* CountingSort */
contador countingsort(int A[], int n){	//recebe vetor e tamanho como parâmetros
	int B[n], i, j, max;
	int mov = 0;
	int comp = 0;
	contador cont;
	max=A[0]; //determinando max
	mov++;
	for (i=1; i<n; i++){//função para analise do maior elemento do vetor dado
	    comp++;
		if (A[i]>max){
			max=A[i];
			mov++;
		}
	}
	int X[max+1];					//declarando um vetor X com m+1 posições
	//inicializando arranjo auxiliar
	for (i=0; i<max+1; i++){			//zerando todas posições de vetor X
		X[i]=0;
	}
	for (i=0; i<n; i++){					//contagem
		X[A[i]]++;
	}
	j=0;
	for (i=0; i<max+1; i++){					//soma acumulada e ordenação
        comp++;
		while (X[i]!=0){
		    comp++;
			B[j]=i;
			j++;
			X[i]--;
		}
	}
	for (i=0; i<n; i++){			//copiando vetor B(auxiliar) para vetor A
		A[i]=B[i];
	}
  cont.movimenta = mov;
  cont.compara = comp;
  return cont;
}

/* HeapSort */
contador heapsort(int a[], int n){
   int i = n/2, pai, filho, t,comp=0,mov=0;
   contador compara;
   while(1)
   {
      comp++;
      if (i > 0)
      {
          i--;
          t = a[i];
      }
      else
      {
          n--;
          comp++;
          if (n == 0){  //quando o tamanho do vetor for 0, irá imprimir o número
          	 	   				   		   	  //de comparações e movimentações
             compara.compara = comp;
             compara.movimenta = mov;
             return compara;
    	  }
          t = a[n];
          a[n] = a[0];
          mov++;
      }
      pai = i;
      /*
        Primeiro será feita a comparação com o filho da esquerda.
      */
      filho = i*2 + 1;
      comp++;
      while (filho < n)
      {
         /*
            Se o filho da esquerda for menor do que o filho da direita,
           então será feita a troca do filho que será comparado.
         */
          comp++;
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          if (a[filho] > t)
          {
             a[pai] = a[filho];
             pai = filho;
             filho = pai*2 + 1;
             mov++;
          }
          else
             break;
      }
      a[pai] = t;
      mov++;
   }
}

// Função para gerar lista randômica aleatória
void geraListaAleat(int P[] , int tam){
     int i;
     srand(time(0));
     for(i=0;i<tam;i++)
        P[i]= abs(rand()%(10*tam));
}

// Função para gerar lista randômica aleatória
void geraListaCres(int P[] , int tam){
	int i;
	for (i = 0; i <= tam-1; i++)
		P[i] = i;
}

// Função para gerar lista randômica aleatória
void geraListaDecres(int P[] , int tam){
	int i;
	for (i = 0; i <= tam-1; i++)
		P[tam-i-1] = i;
}

// Função para gerar lista auxiliar, preservando a lista original para
void copiaLista(int A[], int B[] , int tam){   //manipularmos apenas a auxiliar
     int i;
     for(i=0;i<tam;i++)
        B[i]=A[i];
}

//Função para imprimir lista anterior aos métodos
void imprimeListaArqAnt(int L[], int tam, FILE *arq){
	int i;
	for (i = 0; i<tam;i++)
		{
			if (i == 0)					//será impresso o vetor P sem ordenação
				fprintf(arq,"Antes = [");
			fprintf(arq," %d",L[i]);
			if (i == tam-1)
				fprintf(arq," ]\n",L[i]);
		}
}

//Função para imprimir lista após as ordenações
void imprimeListaArqDep(int L[], int tam, FILE *arq){
	int i;
	for (i = 0; i<tam;i++)
		{
			if (i == 0)					//será impresso o vetor P sem ordenação
				fprintf(arq,"Depois = [");
			fprintf(arq," %d",L[i]);
			if (i == tam-1)
				fprintf(arq," ]\n\n",L[i]);
		}
}

//Função para imprimir lista anterior e após de uma única vez
void imprimeLista(int L[], int Aux[], int tam, FILE *arq, int result){
	imprimeListaArqAnt(L,tam,arq);
	imprimeListaArqDep(Aux,tam,arq);
	if (result == EOF)
    	printf("\n\t\tErro na gravacao!");
    else
    	printf("\n\t\tArquivo exportado com sucesso\n\n");
}

/*****************************************************************************/
/***************************** FUNÇÃO PRINCIPAL ******************************/
/*****************************************************************************/


int main(int argc,char **args){
	FILE *arq;
	int *L, *Aux, i, result, tipo , opcao , tam;
	char modo[13];
    contador varContador;
    vetor_auxiliar vetor;
    clock_t Tempo;// tempo de execucao do algoritmo
	tam=atoi(args[1]);	//tamanho da lista
	tipo=atoi(args[2]);	//tipo de lista
	L = malloc(tam * sizeof(int));
    Aux = malloc(tam * sizeof(int));
    if(L==NULL || Aux==NULL)// falta de memoria
    {
	    printf("falta de memoria!\n");
	    free(L);
	    free(Aux);
	    exit(0);
    }
    switch (tipo)
    {
    	case 1: strcpy(modo,"Aleatoria");
    			geraListaAleat(L,tam);
    			printf("Voce escolheu o tipo:    1 - Aleatorio\n");
    			break;
    	case 2: strcpy(modo,"Decrescente");
    			geraListaDecres(L,tam);
    			printf("Voce escolheu o tipo:    2 - Decrescente\n");
    			break;
    	case 3: strcpy(modo,"Crescente");
                printf("Voce escolheu o tipo:    3 - Crescente\n");
    			geraListaCres(L,tam);
    			break;
        default: printf("Erro ao selecionar o modo!");
                 exit(0);
                 break;
    }
    printf("Tamanho do vetor:    %d",tam);
    copiaLista(L,Aux,tam);
    if(	tam <= 100){
    	arq = fopen("saida.txt","wt");
		if(arq == NULL){
			printf("Insucesso na criacao de arquivo!\n");
			return;
		}
		printf("\n\nLista menor ou igual a 100 elementos detectada\n\n");
	}

    	if (tam <= 50000){
            // Bolha Com Flag
			Tempo=clock();
			varContador = BolhaComFlag(Aux, tam);
			Tempo=clock()-Tempo;
			printf("\nBolha com Flag: (%d elementos - %s)",tam,modo);
	    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	    	if(tam <= 100){
	    		result = fprintf(arq,"Bolha com Flag:\n");
    			imprimeLista(L,Aux,tam,arq,result);
	    	}
			copiaLista(L,Aux,tam);

            // CocktailSort
	    	Tempo=clock();
            varContador = CocktailSort (Aux, tam);
			Tempo=clock()-Tempo;
			printf("\nCocktail: (%d elementos - %s)",tam,modo);
	   		printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	    	if(tam <= 100){
	    		result = fprintf(arq,"CocktailSort:\n");
    			imprimeLista(L,Aux,tam,arq,result);
	    	}
			copiaLista(L,Aux,tam);

			// Inserção
	    	Tempo=clock();
            varContador = InsertionSort (Aux,tam);
            Tempo=clock()-Tempo;
			printf("\nInsercao: (%d elementos - %s)",tam,modo);
	    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	    	if(tam <= 100){
	    		result = fprintf(arq,"Insercao:\n");
    			imprimeLista(L,Aux,tam,arq,result);
	    	}
			copiaLista(L,Aux,tam);

			// Seleção
	    	Tempo=clock();
			varContador = selection_sort(Aux,tam);
			Tempo=clock()-Tempo;
			printf("\nSelecao: (%d elementos - %s)",tam,modo);
	    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	    	if(tam <= 100){
	    		result = fprintf(arq,"Selecao:\n");
    			imprimeLista(L,Aux,tam,arq,result);
	    	}
    	}

		copiaLista(L,Aux,tam);
		//ShellSort
		Tempo=clock();
		varContador = shellSort(Aux,tam);
		Tempo=clock()-Tempo;
		printf("\nShellSort: (%d elementos - %s)",tam,modo);
    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
		if(tam <= 100){
	    	result = fprintf(arq,"ShellSort:\n");
    		imprimeLista(L,Aux,tam,arq,result);
	   	}
		copiaLista(L,Aux,tam);

		//MergeSort
		Tempo=clock();
		varContador = mergesort(Aux,tam);
		Tempo=clock()-Tempo;
		printf("\nMergeSort: (%d elementos - %s)",tam,modo);
    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
    	if(tam <= 100){
	    	result = fprintf(arq,"MergeSort:\n");
    		imprimeLista(L,Aux,tam,arq,result);
	   	}
		copiaLista(L,Aux,tam);

if((tipo==1 && tam<=600000)||(tipo==2 && tam<40000)||(tipo==3 && tam<40000)){
		  //QuickSort Determinístico
		  Tempo=clock();
		  varContador = quicksortDet(Aux,0,tam-1);
		  Tempo=clock()-Tempo;
		  printf("\nQuickSort Deterministico: (%d elementos - %s)",tam,modo);
    	  printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	      printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	      if(tam <= 100){
		  	  	result = fprintf(arq,"QuickSort Deterministico:\n");
	    		imprimeLista(L,Aux,tam,arq,result);
		  }
		  copiaLista(L,Aux,tam);
        }
		else{
	 	  printf("\nPROCEDIMENTO NAO EXECUTADO PARA TAMANHO PEDIDO");
		  printf("\nQuickSort Deterministico: (%d elementos - %s)",tam,modo);
	      printf("\nComparacoes: X Movimentacoes: X Tempo: Xms\n");
		}

		//QuickSort Probabilístico
    	Tempo=clock();
		varContador = quicksortProb(Aux,0,tam-1);
		Tempo=clock()-Tempo;
		printf("\nQuickSort Probabilistico: (%d elementos - %s)",tam,modo);
    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
    	if(tam <= 100){
	    	result = fprintf(arq,"QuickSort Probabilistico:\n");
    		imprimeLista(L,Aux,tam,arq,result);
	   	}
		copiaLista(L,Aux,tam);

if((tipo==1 && tam<=480000)||(tipo==2 && tam<200000)||(tipo==3 && tam<=200000))
{
			// CountingSort
	    	Tempo = clock();
			varContador = countingsort(Aux,tam);
			Tempo=clock()-Tempo;
			printf("\nCountingSort: (%d elementos - %s)",tam,modo);
	    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	    	if(tam <= 100){
		    	result = fprintf(arq,"CountingSort:\n");
	    		imprimeLista(L,Aux,tam,arq,result);
		   	}
			copiaLista(L,Aux,tam);
}
		else{
	 	    printf("\nPROCEDIMENTO NAO EXECUTADO PARA TAMANHO PEDIDO");
			printf("\nCountingSort: (%d elementos - %s)",tam,modo);
	    	printf("\nComparacoes: X Movimentacoes: X Tempo: Xms\n");
		}

if((tipo==1 && tam<=150000)||(tipo==2 && tam<=150000)||(tipo==3 && tam<=150000))
{
			// BucketSort
			Tempo=clock();
			varContador = bucket_sort(Aux,tam);
			Tempo=clock()-Tempo;
	    	printf("\nBucketSort: (%d elementos - %s)",tam,modo);
			printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
	    	if(tam <= 100){
		    	result = fprintf(arq,"BucketSort:\n");
	    		imprimeLista(L,Aux,tam,arq,result);
		   	}
			copiaLista(L,Aux,tam);
}
		else{
	 	    printf("\nPROCEDIMENTO NAO EXECUTADO PARA TAMANHO PEDIDO",tam,modo);
			printf("\nBucketSort: (%d elementos - %s)");
	    	printf("\nComparacoes: X Movimentacoes: X Tempo: Xms\n");
		}
		// RadixSort (CountingSort)
		Tempo=clock();
		vetor = radixSort(Aux,tam);
		Tempo=clock()-Tempo;
		Aux = vetor.vet;
        printf("\nRadixSort (CountingSort): (%d elementos - %s)",tam,modo);
    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
    	if(tam <= 100){
	    	result = fprintf(arq,"RadixSort (CountingSort):\n");
    		imprimeLista(L,Aux,tam,arq,result);
	   	}
		copiaLista(L,Aux,tam);

		// RadixSort (BucketSort)
		Tempo=clock();
		varContador = radixsort(Aux,tam);
		Tempo=clock()-Tempo;
        printf("\nRadixSort (BucketSort): (%d elementos - %s)",tam,modo);
    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
    	if(tam <= 100){
	    	result = fprintf(arq,"RadixSort (BucketSort):\n");
    		imprimeLista(L,Aux,tam,arq,result);
	   	}
		copiaLista(L,Aux,tam);

		// HeapSort
		Tempo=clock();
		varContador = heapsort(Aux,tam);
		Tempo=clock()-Tempo;
		printf("\nHeapSort: (%d elementos - %s)",tam,modo);
    	printf("\nComparacoes: %d Movimentacoes: %d",varContador.compara,varContador.movimenta);
	    	printf(" Tempo: %6.2fms\n",(float)Tempo/CLOCKS_PER_SEC*1000);
    	if(tam <= 100){
	    	result = fprintf(arq,"HeapSort:\n");
    		imprimeLista(L,Aux,tam,arq,result);
	   	}
		copiaLista(L,Aux,tam);
    if (arq && tam <= 100)
        fclose(arq);
    free(L);
    free(Aux);
	return 0;
}
