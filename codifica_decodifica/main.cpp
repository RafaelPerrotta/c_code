#include <iostream> // biblioteca de entrada e saida
#include <fstream> //leitura e escrita em arquivos
#include <sstream>
#include <string>
#include <conio.h>

#define NOME_ARQUIVO "informacao.txt"

using namespace std;

int findCaracter(string texto, char caracter) {
    bool flag = true;
    int i = 0;
    while(flag && i <= texto.size()) { //enquanto flag true e i < que tamanho do texto
        if(texto[i] == caracter) {
            flag = false;
            return i; // retorna posicao
        }
        i++;
    }
    return 0; // retorna 0, se nao encontrar

}


class Pessoa {
private:
    char caracterUm;
    char caracterDois;
    string informacao;

public:
    static int retornarNumeroInstancias(string texto);
    static string capturaTexto();
    static string lerArquivo();
    static void controllerCodificar();
    static void controllerDecodificar();
    static void escreverListaArquivo(Pessoa * pessoas, int dimensao);
    static void preencherListaPessoas(Pessoa*ptr, string texto, int dimensao);

    string toString();
    void descriptografarArquivo();
    void exibirPessoa();
    void criptografarArquivo();

    char getCaracterUm() const;
    void setCaracterUm(char);
    char getCaracterDois() const;
    void setCaracterDois(char);
    string getInformacao() const;
    void setInformacao(char);
    void setInformacao(string);

};

void Pessoa::controllerCodificar(){
    string texto;
    texto = Pessoa::capturaTexto();
    int dimensao, i;
    dimensao = 0;

    dimensao = Pessoa::retornarNumeroInstancias(texto);
    Pessoa pessoas[dimensao];
    Pessoa::preencherListaPessoas(pessoas, texto, dimensao);

    for(i = 0; i < dimensao; i++){
        pessoas[i].criptografarArquivo();
        //pessoas[i].exibirPessoa();
    }

    Pessoa::escreverListaArquivo(pessoas, dimensao);
    cout << "Decodificado com sucesso. \n";
    for(i = 0; i < dimensao; i++){
        //pessoas[i].criptografarArquivo();
        cout << "Informacao criptografada:" << pessoas[i].getInformacao() << "\n";
    }
}

void Pessoa::controllerDecodificar(){
    int dimensao,i;
    char c1,c2;

    string novoTexto;

    cout << "Digite caracter 1:\n";
    cin >> c1;
    cout << "Digite caracter 2:\n";
    cin >> c2;
    cout << c1 << c2 << "\n";

    novoTexto = Pessoa::lerArquivo();

    Pessoa pessoaDescodificada;
    pessoaDescodificada.setCaracterUm(c1);
    pessoaDescodificada.setCaracterDois(c2);

    dimensao = Pessoa::retornarNumeroInstancias(novoTexto);
    Pessoa outrasPessoas[dimensao];
    Pessoa::preencherListaPessoas(outrasPessoas, novoTexto, dimensao);
    for(i = 0; i < dimensao; i++){
        if(outrasPessoas[i].getCaracterUm() == pessoaDescodificada.getCaracterUm()
           && outrasPessoas[i].getCaracterDois() == pessoaDescodificada.getCaracterDois()) {
            pessoaDescodificada.setInformacao(outrasPessoas[i].getInformacao());
            pessoaDescodificada.descriptografarArquivo();
            pessoaDescodificada.exibirPessoa();
        }

    }

}


void Pessoa::exibirPessoa() {
    cout << "Caracter Um: " << this->getCaracterUm() << "\n";
    cout << "Caracter Dois: " << this->getCaracterDois() << "\n";
    cout << "Informacao: " << this->getInformacao() << "\n";
}

string Pessoa::toString() {
    string linha;
    linha.push_back(this->getCaracterUm());
    linha.push_back(';');
    linha.push_back(this->getCaracterDois());
    linha.push_back(';');
    linha.append(this->getInformacao());

    //cout << "linha: " << linha << "\n";
    return linha;
}


void Pessoa::preencherListaPessoas(Pessoa*ptr, string texto, int dimensao){
    int i = 0;
    do{

        (ptr+i)->setCaracterUm(texto[findCaracter(texto,';') - 1]);

        texto =  texto.substr(findCaracter(texto,';') + 1 , texto.size() - 1);

        (ptr+i)->setCaracterDois(texto[findCaracter(texto,';') - 1]);
        texto =  texto.substr(findCaracter(texto,';') + 1, texto.size() - 1);

        if(findCaracter(texto, '&')) {
            (ptr+i)->setInformacao(texto.substr(0, findCaracter(texto, '&')));
            texto = texto.substr(findCaracter(texto, '&') + 1, texto.size()- 1);
        } else {
            (ptr+i)->setInformacao(texto.substr(0, texto.size()));
        }

        i++;
    }while(i < dimensao);
}

int Pessoa::retornarNumeroInstancias(string texto){
    int i;
    int j = 0;
    for(i = 0; i < texto.size(); i++) {
        if(texto[i] == '&') {
            j++;
        }
    }
    return j+1;
}
void Pessoa::escreverListaArquivo(Pessoa * pessoas, int dimensao) {
    //Escreve os dados em um .txt
    int i;
    string texto = "";
    ofstream out(NOME_ARQUIVO);
    if(!out) {
        cout << "O arquivo não pode ser aberto!";
    }
    for(i = 0; i < dimensao; i++){
        string linha = (pessoas+i)->toString();
        if(i < dimensao - 1){
            linha.push_back('&');
            linha.push_back('\n');
        }
        texto += linha;
    }
    out << texto;
    out.close();
}
string Pessoa::capturaTexto() {
    string texto;
    string input;
    cout << "Entre com os dados:\n";
   // Captura o texto, enquanto não encontra o @
    while(input.compare("@")) {
        cin >> input;

        if(input.compare("@")) {
            texto += input;
        }
    }
    return texto;
}

 string Pessoa::lerArquivo() {

    stringstream buffer;
    ifstream arquivo(NOME_ARQUIVO);
    if(!arquivo) {
        cout << "O arquivo não pode ser aberto!";
        return "";
    }

    buffer << arquivo.rdbuf();
    return buffer.str();
}

void Pessoa::criptografarArquivo() {
    int i;
    string texto;
    texto = this->getInformacao();
    for(i = 0; i < texto.size(); i++) {
        if(texto[i] == this->getCaracterDois())
            texto[i] = this->getCaracterUm();

    }
    this->setInformacao(texto);
}

void Pessoa::descriptografarArquivo() {
    int i;
    string texto;
    texto = this->getInformacao();
    for(i = 0; i < texto.size(); i++) {
        if(texto[i] == this->getCaracterUm())
            texto[i] = this->getCaracterDois();

    }
    this->setInformacao(texto);
}

char Pessoa::getCaracterUm() const {
    return caracterUm;
}

void Pessoa::setCaracterUm(char caracterUm) {
    this->caracterUm = caracterUm;
}

char Pessoa::getCaracterDois() const {
    return caracterDois;
}

void Pessoa::setCaracterDois(char caracterDois) {
    this->caracterDois = caracterDois;
}

string Pessoa::getInformacao() const {
    return informacao;
}

void Pessoa::setInformacao(char caracter) {
    this->informacao += caracter;
}

void Pessoa::setInformacao(string informacao) {
    this->informacao = informacao;
}

int main() {
    char opcao;

    do {
        cout << "(1) para inserir dados. \n";
        cout << "(2) para recuperar dados.\n";
        cout << "(0) para sair.\n";
        cout << "Entre com a opcao desejada: ";
        cin.get(opcao);

        switch(opcao) {
        case '1':
            cout << "Inserindo dados.\n";
            Pessoa::controllerCodificar();
            break;
        case '2':
            cout << "Recuperando dados.\n";
            Pessoa::controllerDecodificar();
            break;
        case '0':
            cout << "Finalizando.\n";
            break;
        default:
            cout << "Opcao invalida. Digite uma opcao valida.\n";
        }
        getchar();
    } while(opcao != '0');

    return 0;
}

