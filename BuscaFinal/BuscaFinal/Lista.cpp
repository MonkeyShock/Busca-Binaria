#include <iostream>
#include "Lista.h"

ListaEncadeada::ListaEncadeada() {
    lista = nullptr;
}

ListaEncadeada::~ListaEncadeada() {
    while (lista != nullptr) {
        Chave* proximoChave = lista->proximo;
        delete lista;  // Deleta o n� Chave atual
        lista = proximoChave;  // Move para o pr�ximo n� Chave
    }
}

void ListaEncadeada::inserir(const string& chave, const string& info) {
    Chave* atual = lista;
    while (atual != nullptr) {
        if (atual->chave == chave) {
            Inf* novoInfo = new Inf;
            novoInfo->info = info;
            novoInfo->proximo = atual->info;
            atual->info = novoInfo;
            return;
        }
        atual = atual->proximo;
    }

    // Se a chave n�o existir, cria um novo n� Chave
    Chave* novoChave = new Chave;
    novoChave->chave = chave;
    Inf* novoInfo = new Inf;
    novoInfo->info = info;
    novoInfo->proximo = nullptr;
    novoChave->info = novoInfo;
    novoChave->proximo = lista;
    lista = novoChave;
}

string ListaEncadeada::buscar(const string& chave) {
    Chave* atual = lista;
    while (atual != nullptr) {
        if (atual->chave == chave) {
            if (atual->info != nullptr) {
                return atual->info->info;
            }
            else {
                return ""; // Se n�o houver informa��o associada � chave
            }
        }
        atual = atual->proximo;

    }
    return ""; 
}


void ListaEncadeada::imprimir() {
    Chave* atual = lista;
    while (atual != nullptr) {
        std::cout << "Chave: " << atual->chave << std::endl;
        Inf* infoAtual = atual->info;
        while (infoAtual != nullptr) {
            std::cout << "  Info: " << infoAtual->info << std::endl;
            infoAtual = infoAtual->proximo;
        }
        atual = atual->proximo;
    }
}
