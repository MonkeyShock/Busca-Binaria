#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include "Trie.h"
#include "Lista.h"
#include "Leitor.h"

using namespace std;

void Documentos::escreverTXT(const string& inf, string caminhoArquivo) {
    size_t ponto = caminhoArquivo.rfind('.');
    caminhoArquivo = caminhoArquivo.substr(0, ponto) + ".txt";

    ofstream doc(caminhoArquivo, ios::app);
    if (!doc.is_open()) {
        cerr << "Falha em criar o arquivo " << caminhoArquivo << endl;
        return;
    }

    doc << inf << endl;
    doc.close();
}

void Documentos::ProcessarTXT(const string& caminhoArquivo) {
    ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << caminhoArquivo << endl;
        return;
    }

    string linha;
    stringstream textoProcessado;

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string palavra;
        bool primeiraPalavra = true;
        while (ss >> palavra) {
            string palavraLimpa;
            for (char& c : palavra) {
                if (isalpha(static_cast<unsigned char>(c))) {
                    palavraLimpa += tolower(c);
                }
            }

            if (!palavraLimpa.empty()) {
                if (!primeiraPalavra) {
                    textoProcessado << ' ';
                }
                textoProcessado << palavraLimpa;
                primeiraPalavra = false;
            }
        }

        textoProcessado << '\n';
    }

    arquivo.close();

    ofstream arquivoProcessado("texto_processado.txt");
    if (arquivoProcessado.is_open()) {
        arquivoProcessado << textoProcessado.str();
        arquivoProcessado.close();
        cout << "Texto processado salvo em texto_processado.txt" << endl;
    }
    else {
        cerr << "Erro ao criar o arquivo texto_processado.txt" << endl;
    }
}

void Documentos::lerPDF(const string& caminhoArquivo) {
    poppler::document* documento = poppler::document::load_from_file(caminhoArquivo);
    if (!documento || documento->is_locked()) {
        cerr << "Erro ao abrir o arquivo " << endl;
        return;
    }

    int pag = documento->pages();
    for (int i = 0; i < pag; i++) {
        poppler::page* pagina = documento->create_page(i);
        if (!pagina) {
            cerr << "Erro ao abrir a pagina " << endl;
            continue;
        }

        string inf = pagina->text().to_latin1();
        escreverTXT(inf, caminhoArquivo);
    }
}

Trie Documentos::lerTXT(const string& caminhoArquivo) {
    Trie trie;

    ProcessarTXT(caminhoArquivo);

    size_t ponto = caminhoArquivo.rfind('.');
    string caminhoProcessado = caminhoArquivo.substr(0, ponto) + ".txt";

    ifstream arquivo(caminhoProcessado);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << caminhoProcessado << endl;
        return trie;
    }

    string linhaTexto;
    int linha = 1;
    int pagina = 1;
    while (getline(arquivo, linhaTexto)) {
        stringstream ss(linhaTexto);
        string palavra;
        while (ss >> palavra) {
            string palavraLimpa;
            for (char c : palavra) {
                if (isalpha(static_cast<unsigned char>(c))) {
                    palavraLimpa += tolower(c);
                }
            }

            if (!palavraLimpa.empty()) {
                trie.insere(palavraLimpa, to_string(pagina), 0, to_string(linha));
            }
        }
        linha++;
    }
   
    arquivo.close();

    return trie;
}
