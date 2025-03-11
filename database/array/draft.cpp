#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
void encontrarValor( std::vector<int> vet, int valor){
     for(int i = 0; i < (int) vet.size(); i++){
        if( vet[i] == valor){
            std::cout << "Achei o " << valor << '\n';
            return;
        }
     }
     std::cout << "Valor não encontrado";
     
}
int main() {
    std::list<int> lista = {1, 2, 3, 4};
    std::list<int> listaPar = {};
    std::vector<int> vetor = {1 , 2 , 3 , 4};
    std::vector<int> vetor2(4 , 1); // 1111
    lista.push_back(5);
    lista.push_back(6);
    lista.pop_back();
    lista.push_front(0);
    lista.push_front(-1);
    lista.pop_front();

    vetor.push_back(5);
    vetor.push_back(6);
    vetor.pop_back();

    auto it = std::find(lista.begin(), lista.end(), 3);
    if(it != lista.end()) {
        std::cout << "Encontrou o valor " << *it << std::endl;
    }
    lista.erase(it);
    auto it2 = std::find(vetor.begin(), vetor.end(), 3);
    vetor.insert(it2, 4);

    for (auto it = lista.begin(); it != lista.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (auto elem : vetor) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    encontrarValor(vetor , 6);


    for(auto elem : lista){
        if(elem % 2 == 0){
            listaPar.push_back(elem);   
    }
    }
    std::cout << '\n';
    std::cout  << "Lista par -> ";
    for(auto elem : listaPar){
        std::cout << elem << " ";
    }
   

}
