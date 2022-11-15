/* Joao Lucas Mota Nogueira da Costa
b) Usando, C, C++, Python ou Java,
crie uma estrutura de dados chamada eitaHeap que deverá usar
como  representação  em  memória  uma  lista  linkada.  Para  testar  esta
estrutura  você precisará criar um heap (min heap) com 100 registros compostos
de uma string com até 100 caracteres e um valor numérico do conjunto dos números
reais. Para gerar os strings e os valores  números  você  deverá  usar  um
gerador  de  números  randômicos  baseado  no Mersenne Twister. Durante a
criação dos registros você deverá escolher, aleatoriamente dez destes registros
para testar a função de busca.
Uma vez que a heap tenha sido criada você deve contar o tempo necessário para
tirar 16% dos registros deste heap, o tempo necessário para encontrar a posição
na fila onde estão os registros escolhidos para teste e o tempo necessário para
inserir 45 registros novos neste heap. Sem dúvida os testes para a localização
dos dez registros selecionados para o resgistro dos  tempos  de  localização
deverão  ser  feitos  com  o  heap originalmente  criado,  antes  da exclusão de
16% ou da inclusão de novos registros. Como a estrutura é muito pequena, todos
os tempos deverão ser calculados na forma de média o que implica na repetição
dos processos de criação, inserção, remoção, busca e nova inserção, no mínimo 50
vezes. A saída esperada será feita por meio de um arquivo onde teremos o heap
estruturado em formato de árvore usando ASCII, seguido do heap com menos 16% dos
registros, também estruturado no formato de uma árvore usando ASCII, seguido do
heap após a inclusão de novos registros, seguido dos tempos médios de inclusão,
exclusão, busca e nova  inclusão identificados cada um em sua própria linha. */

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;

typedef struct no {
  int valor;
  string str;
  struct no *esq;
  struct no *dir;
} Arv;

Arv *criaHeap() {
  Arv *Heap = new Arv;
  if (Heap != nullptr) {
    Heap = nullptr;
  }
  return Heap;
}

Arv *inserir(Arv *heap, int v, string s) {
  if (heap == nullptr) {
    Arv *aux = new Arv;
    aux->valor = v;
    aux->str = s;
    aux->esq = nullptr;
    aux->dir = nullptr;
    return aux;
  } else {
    if (v > heap->valor) {
      if (heap->esq == nullptr) { // caso esq seja nulo
        heap->esq = inserir(heap->esq, v, s);
      } else if (heap->dir == nullptr) { // caso dir seja nulo
        if (v > heap->esq->valor) {      // caso v seja maior que esq->valor
          heap->dir = inserir(heap->dir, v, s);
        } else { // caso v seja menor que esq->valor
          int v2;
          v2 = heap->esq->valor;
          heap->esq->valor = v;
          heap->dir = inserir(heap->dir, v2, s);
        }
      } else {                      // caso esq e dir != null
        if (v > heap->dir->valor) { // caso v seja maior que dir->valor
          heap->dir = inserir(heap->dir, v, s);
        } else {
          heap->esq = inserir(heap->esq, v, s);
        }
      }
    } else { // caso v seja menor que heap->valor
      int vAux;
      vAux = heap->valor;
      heap->valor = v;
      if (heap->esq == nullptr) { // caso heap->esq seja nulo
        heap->esq = inserir(heap->esq, vAux, s);
      } else if (heap->dir == nullptr) { // caso heap->dir seja nulo
        if (vAux > heap->esq->valor) {   // caso vAux seja maior que esq->valor
          heap->dir = inserir(heap->dir, vAux, s);
        } else { // caso vAux seja menor que esq->valor
          int v2;
          v2 = heap->esq->valor;
          heap->esq->valor = vAux;
          heap->dir = inserir(heap->dir, v2, s);
        }
      } else {
        if (vAux > heap->dir->valor) { // caso vAux seja maior que dir->valor
          heap->dir = inserir(heap->dir, vAux, s);
        } else {
          heap->esq = inserir(heap->esq, vAux, s);
        }
      }
    }
    return heap;
  }
}

void remover(Arv *heap, int i) {
  if (i % 2 == 1) {
    if (heap->esq != nullptr) {
      heap->valor = heap->esq->valor;
      heap->str = heap->esq->str;
      remover(heap->esq, i);
    }
  } else {
    if (heap->dir != nullptr) {
      heap->valor = heap->dir->valor;
      heap->str = heap->dir->str;
      remover(heap->dir, i);
    }
  }
}

void imprimir_arvore(Arv *raiz, int ident) {
  ofstream file;
  file.open("eitaHeap.txt", ios::app);
  int i = 1;
  if (raiz != nullptr) {
    while (i <= ident) {
      cout << ("\t");
      file << ("\t");
      i++;
    }
    if (ident == 0) {
      cout << raiz->valor << endl;
      file << raiz->valor << endl;
      imprimir_arvore(raiz->esq, ident + 1);
      imprimir_arvore(raiz->dir, ident + 1);
    } else {
      cout << '+' << raiz->valor << '\n' << endl;
      file << '+' << raiz->valor << '\n' << endl;
      imprimir_arvore(raiz->esq, ident + 1);
      imprimir_arvore(raiz->dir, ident + 1);
    }
  }
}

void imprimir_strings(Arv *heap) {
  ofstream file;
  file.open("eitaHeap.txt", ios::app);
  cout << "[ " << heap->str << " ]" << endl;
  file << "[ " << heap->str << " ]" << endl;
  if (heap->esq != nullptr) {
    imprimir_strings(heap->esq);
  }
  if (heap->dir != nullptr) {
    imprimir_strings(heap->dir);
  }
}

int main() {
  ofstream file;
  int v, x, j = 0, teste_busca[2];
  string s = "";
  char chars[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  random_device a;
  mt19937 gerador(a());
  uniform_int_distribution<int> alfa(0, 35);
  uniform_int_distribution<int> nums(1, 1000);
  auto str1 = chrono::high_resolution_clock::now();
  Arv *eitaHeap = criaHeap();
  auto fin1 = chrono::high_resolution_clock::now();
  auto str2 = chrono::high_resolution_clock::now();
  for (int i = 0; i < 100; i++) {
    while (j < 100) {
      x = alfa(gerador);
      s = s + chars[x];
      j++;
    }
    j = 0;
    v = nums(gerador);
    eitaHeap = inserir(eitaHeap, v, s);
    s = "";
  }
  file.open("eitaHeap.txt");
  file << "Arquivo Resposta:\n" << endl;
  file.close();
  auto fin2 = chrono::high_resolution_clock::now();
  imprimir_arvore(eitaHeap, 0);

  file.open("eitaHeap.txt", ios::app);
  file << "\nStrings dos itens:\n" << endl;
  file.close();
  cout << "\nStrings dos itens:\n" << endl;
  imprimir_strings(eitaHeap);
  cout << '\n' << endl;

  cout << "Removendo 16% dos itens..." << endl;
  auto str3 = chrono::high_resolution_clock::now();
  for (int i = 0; i < 16; i++) {
    remover(eitaHeap, i);
  }
  auto fin3 = chrono::high_resolution_clock::now();
  file.open("eitaHeap.txt", ios::app);
  cout << "Heap pos remocao de 16% dos itens:\n" << endl;
  file << "Heap pos remocao de 16% dos itens:\n" << endl;
  file.close();
  imprimir_arvore(eitaHeap, 0);

  file.open("eitaHeap.txt", ios::app);
  file << "\nStrings dos itens:\n" << endl;
  file.close();
  cout << "\nStrings dos itens:\n" << endl;
  imprimir_strings(eitaHeap);
  cout << '\n' << endl;
  file << '\n' << endl;

  cout << "\nAdicionando mais 30 itens...\n" << endl;
  auto str4 = chrono::high_resolution_clock::now();
  for (int i = 0; i < 30; i++) {
    while (j < 100) {
      x = alfa(gerador);
      s = s + chars[x];
      j++;
    }
    j = 0;
    v = nums(gerador);
    eitaHeap = inserir(eitaHeap, v, s);
    s = "";
  }
  auto fin4 = chrono::high_resolution_clock::now();
  file.open("eitaHeap.txt", ios::app);
  cout << "Heap apos a insercao de mais 30 itens:" << endl;
  file << "Heap apos a insercao de mais 30 itens:" << endl;
  file.close();
  imprimir_arvore(eitaHeap, 0);
  file.open("eitaHeap.txt", ios::app);
  file << "\nStrings dos itens:\n" << endl;
  file.close();
  cout << "\nStrings dos itens:\n" << endl;
  imprimir_strings(eitaHeap);
  cout << '\n' << endl;
  file << '\n' << endl;

  auto t1 = chrono::duration_cast<chrono::nanoseconds>(fin1 - str1).count();
  cout << "Tempo para a criacao do heap: " << t1 << " Nanossegundos" << endl;
  file << "Tempo para a criacao do heap: " << t1 << " Nanossegundos" << endl;
  auto t2 = chrono::duration_cast<chrono::nanoseconds>(fin2 - str2).count();
  cout << "Tempo para a insercao de itens no heap: " << t2 << " Nanossegundos"
       << endl;
  file << "Tempo para a insercao de itens no heap: " << t2 << " Nanossegundos"
       << endl;
  auto t3 = chrono::duration_cast<chrono::nanoseconds>(fin3 - str3).count();
  cout << "Tempo para a remocao de itens do heap: " << t3 << " Nanossegundos"
       << endl;
  file << "Tempo para a remocao de itens do heap: " << t3 << " Nanossegundos"
       << endl;
  auto t4 = chrono::duration_cast<chrono::nanoseconds>(fin4 - str4).count();
  cout << "Tempo para a inclusao de novos itens no heap: " << t4
       << " Nanossegundos" << endl;
  file << "Tempo para a inclusao de novos itens no heap: " << t4
       << " Nanossegundos\n\n"
       << endl;

  file.close();
  delete (eitaHeap);
}
