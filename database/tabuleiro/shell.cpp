#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

class Jogador {
    int nome;
    int posicao;
    bool livre;
public:
    Jogador(int nome = 0) : nome(nome) {
        this->posicao = 0;
        this->livre = true;
    }
    bool estaLivre() {
        return this->livre;
    }
    int getNumJogador() {
        return this->nome;
    }
    int getPosicao() {
        return this->posicao;
    }
    void setPosicao(int posicao) {
        this->posicao = posicao;
    }
    void setLivre(bool livre) {
        this->livre = livre;
    }
    string toString() {
        return "player" + to_string(this->nome + 1) + ": ";
    }
};

class Tabuleiro {
    vector<int> listaArmadilha;
    vector<shared_ptr<Jogador>> jogadores;
    bool andar {false};
    int vez = 0;
    int tabuleiroZise;
public:
    Tabuleiro(int nJogadores = 0, int tabuleiroZise = 48) : tabuleiroZise(tabuleiroZise) {
        for (int i = 0; i < nJogadores; i++) {
            this->jogadores.push_back(make_shared<Jogador>(i));
        }
        andar = true;
    }

    void addArmadilha(int value) {
        this->listaArmadilha.push_back(value);
    }

    void jogar(int value) {
        shared_ptr<Jogador> j = jogadores[vez];
        if (andar == false) {
            cout << "game is over" << endl;
            return;
        }
        if (!j->estaLivre()) {
            if (value % 2 == 0) {
                j->setLivre(true);
                cout << "player" << to_string(j->getNumJogador() + 1) << " se libertou" << endl;
            } else {
                cout << "player" << to_string(j->getNumJogador() + 1) << " continua preso" << endl;
            }
            vez = (vez + 1) % this->jogadores.size();
            return;
        }
        int novaPosicao = j->getPosicao() + value;
        if (novaPosicao > this->tabuleiroZise) {
            j->setPosicao(this->tabuleiroZise);
            cout << "player" << to_string(j->getNumJogador() + 1) << " ganhou" << endl;
            andar = false;
            return;
        }
        cout << "player" << to_string(j->getNumJogador() + 1) << " andou para " << novaPosicao << endl;
        j->setPosicao(novaPosicao);

        for (int i : this->listaArmadilha) {
            if (novaPosicao == i) {
                cout << "player" << to_string(j->getNumJogador() + 1) << " caiu em uma armadilha" << endl;
                j->setLivre(false);
                break;
            }
        }
        vez = (vez + 1) % this->jogadores.size();
    }

    string str() {
        string saida;
        for (shared_ptr<Jogador> j : this->jogadores) {
            string aux;
            for (int i = 0; i <= this->tabuleiroZise; i++) {
                if (i == j->getPosicao()) {
                    aux += to_string(j->getNumJogador() + 1);
                } else {
                    aux += ".";
                }
            }
            saida += j->toString() + aux + "\n";
        }
        saida += "traps__: ";
        for (int i = 0; i <= this->tabuleiroZise; i++) {
            bool temArmadilha = false;
            for (int j : this->listaArmadilha) {
                if (i == j) {
                    temArmadilha = true;
                    break;
                }
            }
            if (temArmadilha) {
                saida += "x";
            } else {
                saida += ".";
            }
        }
        return saida;
    }
};

int main() {
    Tabuleiro tabuleiro;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int nPlayers, size;
            ss >> nPlayers >> size;
            tabuleiro = Tabuleiro(nPlayers, size);
        } else if (cmd == "addTrap") {
            int pos;
            ss >> pos;
            tabuleiro.addArmadilha(pos);
        } else if (cmd == "roll") {
            int value;
            ss >> value;
            tabuleiro.jogar(value);
        } else if (cmd == "show") {
            cout << tabuleiro.str() << endl;
        } else {
            cout << "fail: command not found" << endl;
        }
    }
}
