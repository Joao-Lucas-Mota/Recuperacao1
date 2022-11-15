/* Joao Lucas Mota Nogueira da Costa
a) Usando, C, C++, Python ou Java, crie uma estrutura de dados chamada
minhaNovaFila que deverá usar como representação em memória uma lista linkada.
Para testar esta estrutura você  precisará  criar  uma  fila  com  100 registros
compostos  de  uma  string com  até  100 caracteres e um valor numérico do
conjunto dos números reais. Para gerar os strings e os valores  números  você
deverá  usar  um  gerador  de  números  randômicos  baseado  no Mersenne
Twister. Durante a criação dos registros você deverá escolher, aleatóriamente
dois destes registros para testar a função de busca. Uma vez que a lista tenha
sido criada você deve contar o tempo necessário para tirar 20% dos  registros
desta fila e o  tempo  necessário  para encontrar a posição na fila onde estão
dois  dos  registros  criados.  Neste  exercício,  o  tempo  gasto  em  todas as
operações  com  a estrutura de dados deverá ser registrado. A saída esperada
será feita por meio de um arquivo onde teremos a fila original impressa na
horizontal  com  comprimento  inferior  a  5 registros  por  linha,  seguida da
fila  depois  da exclusão de 20% dos seus registros, também na horizontal. As
últimas linhas do arquivo de saída serão reservadas para o registro dos tempos
médios utilizados para cada uma das operações da estrutura de dados (criação,
inclusão, exclusão, nova inclusão) como  estes tempos serão muito pequenos será
necessário  tirar as médias com, no mínimo, 50 repetições. */

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;

class noFila {
public:
  int val;
  string str;
};

class minhaNovaFila {
public:
  int n; // numero de itens na fila
  noFila **listaNos;
  minhaNovaFila(int x);
  ~minhaNovaFila();
  void insereItemFila(int i, int v, string s);
  void removeItemFila();
  bool buscaItemFila(int k);
};

minhaNovaFila::minhaNovaFila(int x) {
  this->n = 0;
  noFila *lista[x];
  for (int i = 0; i < n; i++) {
    lista[i] = new noFila;
  }
  listaNos = lista;
}

minhaNovaFila::~minhaNovaFila() {
  for (int i = 0; i < n; i++) {
    noFila *no1 = listaNos[i];
    noFila *ant = nullptr;
    while (no1) {
      no1 = ant;
      delete ant;
    }
  }
}

void minhaNovaFila::insereItemFila(int i, int v, string s) {
  noFila *aux = new noFila;
  aux->val = v;
  aux->str = s;
  listaNos[i] = aux;
  this->n++;
}

void minhaNovaFila::removeItemFila() {
  listaNos[0] = nullptr;
  for (int i = 0; i < n; i++) {
    listaNos[i] = listaNos[i + 1];
  }
  this->n--;
}

bool minhaNovaFila::buscaItemFila(int k) {
  for (int i = 0; i < n; i++) {
    if (k == listaNos[i]->val) {
      return true;
    }
  }
  return false;
}

void mostraFila(minhaNovaFila fila) {
  cout << "Numero de itens na fila: " << fila.n << '\n' << endl;
  cout << "Fila:" << endl;
  for (int i = 0; i < fila.n; i++) {
    cout << "[" << fila.listaNos[i]->val << ", ";
    cout << fila.listaNos[i]->str << "]" << endl;
  }
  cout << "\nFim da impressao da fila\n" << endl;
}

int main() {

  int v, x, j = 0, teste_busca[2];
  string s = "";

  // array de caracteres para a geracao de strings aleatorios
  char chars[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  // cria um aleatorizador via mersenne twister
  random_device a;
  mt19937 gerador(a());

  // escolhe um numero entre 0 e 35 para determinar um caracter aleatoriamente
  uniform_int_distribution<int> alfa(0, 35);

  // escolhe um numero entre 1 e 1000 para ser os valores ints dos itens
  uniform_int_distribution<int> nums(1, 1000);

  auto str1 = chrono::high_resolution_clock::now();
  minhaNovaFila fila(100); // cria a fila
  auto fin1 = chrono::high_resolution_clock::now();

  // loop for usado para preencher a fila com itens aleatoriamente gerados
  auto str2 = chrono::high_resolution_clock::now();
  for (int i = 0; i < 100; i++) {
    while (j < 100) {
      x = alfa(gerador);
      s = s + chars[x];
      j++;
    }
    j = 0;
    v = nums(gerador);
    fila.insereItemFila(fila.n, v, s);
    s = "";
    // seleciona dois valores gerados para o teste de busca da fila
    if (i == 98) {
      teste_busca[0] = v;
    } else if (i == 99) {
      teste_busca[1] = v;
    }
  }
  auto fin2 = chrono::high_resolution_clock::now();

  // funcao para imprimir a fila
  mostraFila(fila);

  // imprime a fila dentro do arquivo file1
  ofstream file1;
  file1.open("minhaNovaFila.txt");
  file1 << "Numero de itens na fila: " << fila.n << '\n' << endl;
  file1 << "Fila:" << endl;
  for (int i = 0; i < fila.n; i++) {
    file1 << "[" << fila.listaNos[i]->val << ", ";
    file1 << fila.listaNos[i]->str << "]" << endl;
  }
  file1 << "\nFim da impressao da fila\n" << endl;

  // teste de busca por itens existentes na fila
  cout << "Resultado da busca pelo valor " << teste_busca[0] << ": ";
  if (fila.buscaItemFila(teste_busca[0])) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }
  cout << "Resultado da busca pelo valor " << teste_busca[1] << ": ";
  if (fila.buscaItemFila(teste_busca[1])) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }

  // teste de busca pelo item com valor 100 na fila
  cout << "Resultado da busca pelo valor " << 100 << ": ";
  if (fila.buscaItemFila(100)) {
    cout << "true\n" << endl;
  } else {
    cout << "false\n" << endl;
  }

  // imprime os resultados das buscas no file1
  file1 << "Resultado da busca pelo valor " << teste_busca[0] << ": ";
  if (fila.buscaItemFila(teste_busca[0])) {
    file1 << "true" << endl;
  } else {
    file1 << "false" << endl;
  }
  file1 << "Resultado da busca pelo valor " << teste_busca[1] << ": ";
  if (fila.buscaItemFila(teste_busca[1])) {
    file1 << "true" << endl;
  } else {
    file1 << "false" << endl;
  }
  file1 << "Resultado da busca pelo valor " << 100 << ": ";
  if (fila.buscaItemFila(100)) {
    file1 << "true\n" << endl;
  } else {
    file1 << "false\n" << endl;
  }

  // loop for que remove 20% dos itens da fila
  auto str3 = chrono::high_resolution_clock::now();
  int tam = fila.n;
  for (int i = 0; i < tam / 5; i++) {
    fila.removeItemFila();
  }
  auto fin3 = chrono::high_resolution_clock::now();

  // imprime a fila apos a remocao de 20% dos itens
  cout << "Fila apos a remocao de 20% dos itens:\n" << endl;
  mostraFila(fila);

  // imprime a fila apos a remocao de 20% dos itens no arquivo file1
  file1 << "Numero de itens na fila: " << fila.n << '\n' << endl;
  file1 << "Fila apos a remocao de 20% dos itens:" << endl;
  for (int i = 0; i < fila.n; i++) {
    file1 << "[" << fila.listaNos[i]->val << ", ";
    file1 << fila.listaNos[i]->str << "]" << endl;
  }
  file1 << "\nFim da impressao da fila\n" << endl;

  // loop for usado para inserir mais 5 itens na fila
  auto str4 = chrono::high_resolution_clock::now();
  for (int i = 0; i < 5; i++) {
    while (j < 100) {
      x = alfa(gerador);
      s = s + chars[x];
      j++;
    }
    j = 0;
    v = nums(gerador);
    fila.insereItemFila(fila.n, v, s);
    s = "";
  }
  auto fin4 = chrono::high_resolution_clock::now();

  // imprime a fila apos a insercao de 5 novos itens
  cout << "Fila apos a insercao de 5 novo itens:\n" << endl;
  mostraFila(fila);

  // imprime a fila apos a insercao de 5 novos itens dentro do arquivo file1
  file1 << "Numero de itens na fila: " << fila.n << '\n' << endl;
  file1 << "Fila apos a insercao de 5 novos itens:" << endl;
  for (int i = 0; i < fila.n; i++) {
    file1 << "[" << fila.listaNos[i]->val << ", ";
    file1 << fila.listaNos[i]->str << "]" << endl;
  }
  file1 << "\nFim da impressao da fila\n" << endl;

  // calculo da duracao das operacoes em nanossegundos
  auto t1 = chrono::duration_cast<chrono::nanoseconds>(fin1 - str1).count();
  cout << "Tempo para a criacao da fila: " << t1 << " nanossegundos" << endl;
  auto t2 = chrono::duration_cast<chrono::nanoseconds>(fin2 - str2).count();
  auto t2_2 = chrono::duration_cast<chrono::microseconds>(fin2 - str2).count();
  cout << "Tempo para a insercao de 100 itens na fila: " << t2
       << " nanossegundos = " << t2_2 << " microssegundos" << endl;
  auto t3 = chrono::duration_cast<chrono::nanoseconds>(fin3 - str3).count();
  cout << "Tempo para a remocao de 20% dos itens da fila: " << t3
       << " nanossegundos" << endl;
  auto t4 = chrono::duration_cast<chrono::nanoseconds>(fin4 - str4).count();
  auto t4_2 = chrono::duration_cast<chrono::microseconds>(fin4 - str4).count();
  cout << "Tempo para a insercao de mais 5 itens na fila: " << t4
       << " nanossegundos = " << t4_2 << " microssegundos" << endl;

  // imprime os resultados das medicoes de tempo dentro do arquivo file1
  file1 << "Tempo para a criacao da fila: " << t1 << " nanossegundos" << endl;
  file1 << "Tempo para a insercao de 100 itens na fila: " << t2
       << " nanossegundos = " << t2_2 << " microssegundos" << endl;
  file1 << "Tempo para a remocao de 20% dos itens da fila: " << t3
       << " nanossegundos" << endl;
  file1 << "Tempo para a insercao de mais 5 itens na fila: " << t4
       << " nanossegundos = " << t4_2 << " microssegundos" << endl;

  file1.close();
}
