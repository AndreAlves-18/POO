
# Pesquisa sobre C++

- **Quais as vantagens de uma linguagem compilada em relação a uma interpretada?**  
  Linguagens compiladas geralmente apresentam melhor desempenho, pois o código é traduzido para linguagem de máquina antes da execução, permitindo execução mais rápida e otimizações do compilador. Já as interpretadas executam linha a linha, tornando-as mais lentas, mas oferecem flexibilidade e depuração em tempo real.

- **Quais os tipos de comentários em C++?**  
  Em C++, há dois tipos de comentários: de linha única, usando `//`, e de múltiplas linhas, delimitados por `/* ... */`.

- **O include é um comando para o compilador ou para o pré-processador?**  
  `#include` é um comando para o pré-processador que insere o conteúdo de um arquivo no programa antes da compilação.

- **O que é o pré-processador? Todos os comandos iniciados por # são para o pré-processador?**  
  O pré-processador realiza substituições no código antes da compilação, como inclusão de arquivos e definição de macros. Sim, todos os comandos iniciados por `#`, como `#define` e `#include`, são instruções para o pré-processador.

- **O que é um namespace? Cite outras linguagens que possuem algo similar.**  
  Namespace é uma forma de organizar e evitar conflitos de nomes em grandes projetos. Linguagens como Python, Java e C# também possuem mecanismos similares para organização e escopo.

- **Qual o conceito de escopo em uma linguagem de programação?**  
  Escopo define onde uma variável ou função é visível e pode ser acessada no código.

- **Qual a diferença entre uma variável local e uma global?**  
  Variáveis locais existem apenas dentro do bloco onde são declaradas, enquanto variáveis globais são acessíveis em qualquer parte do programa.

- **Quando uma variável é alocada na Stack e quando é alocada na Heap?**  
  Variáveis locais e temporárias são alocadas na Stack, enquanto objetos alocados dinamicamente (usando `new` ou `malloc`) são alocados na Heap.

- **Quais as formas de se inicializar uma variável em C++? Qual a mais recomendada?**  
  C++ permite inicializar variáveis com lista de inicialização `{}`, igual `=`, ou diretamente `()`. A lista de inicialização `{}` é recomendada por evitar conversões indesejadas.

- **O que é o buffer de entrada e saída padrão? Como manipular esses buffers?**  
  O buffer de entrada e saída armazena dados antes de processá-los. Manipula-se com `cin` e `cout` e pode-se forçar a saída com `flush`.

- **O buffer de entrada sempre são sempre teclado e tela ou podem ser redirecionados?**  
  Os buffers de entrada e saída podem ser redirecionados para arquivos ou outros dispositivos.

- **Quais os tipos primitivos de dados em C++?**  
  Tipos primitivos incluem `int`, `float`, `double`, `char`, `bool`, entre outros.

- **Quais os principais modificadores de tipo em C++?**  
  Modificadores incluem `signed`, `unsigned`, `short`, `long`, e `const`.

- **Como funciona a palavra reservada auto?**  
  `auto` permite que o compilador deduza automaticamente o tipo da variável com base em seu valor inicial.

- **Como fazer a conversão entre tipos primitivos em C++ e qual é a sintaxe do static_cast? Qual a diferença entre static_cast e reinterpret_cast?**  
  Converte-se tipos com `static_cast<type>(value)`, que realiza conversões seguras e checadas. `reinterpret_cast` é usado para conversões de ponteiros e é menos seguro.

- **Qual a diferença entre o ++ antes e depois de uma variável?**  
  `++x` incrementa o valor e depois o utiliza. `x++` utiliza o valor atual e só então incrementa.

- **Reescreva o seguinte código sem usar os operadores unários ++ e --:**  

```cpp
int a = 5;
int b = a;
a = a + 1;
a = a + 1;
b = b - 1;
int c = a + b; 
std::cout << a << " " << b << " " << c << '\n';
```

- **Na sintaxe de if e else, existe algum padrão que defina quando usar chaves ou não? Não apenas sobre a sintaxe, mas sobre a legibilidade e boas práticas de programação?**  
  O uso de chaves `{}` é recomendado mesmo em comandos únicos, pois aumenta a clareza e evita erros ao expandir o código.

- **C++ aceita inicialização de variáveis dentro de um if? No modelo `if (int x = 5; x < value) { ... }`?**  
  Sim, C++ aceita inicialização de variáveis dentro de um `if`, útil para condicional local.

- **Como funciona um operador ternário? Quando vale a pena substituir um if else por um operador ternário?**  
  O operador ternário `cond ? expr1 : expr2` substitui um `if-else` simples e melhora a legibilidade em condições concisas.

- **Em C++, funções são elementos de primeira classe? O que isso significa?**  
  Não, em C++ funções não são de primeira classe, mas podem ser manipuladas como ponteiros ou lambdas, oferecendo alguma flexibilidade.

- **Qual seria a sintaxe para uma função lambda que recebe dois inteiros e retorna a soma deles?**  
  `[&](int a, int b) { return a + b; }`

- **Para que serve um return em uma função que não retorna nada?**  
  `return` em funções `void` permite sair da função antes do final.

- **Em uma função, é melhor criar vários ifs, elses ou múltiplos pontos de return?**  
  Depende do caso. Múltiplos `return`s podem aumentar a legibilidade em funções pequenas, mas if/else é preferível para maior clareza em funções longas.

- **A passagem de parâmetros em C++ pode ser cópia, ponteiro ou referência. Qual a diferença entre cada uma delas?**  
  Cópia cria uma duplicata; ponteiro passa o endereço, permitindo modificação; referência passa o valor sem cópia adicional e permite alteração.

- **O que é um parâmetro default em uma função?**  
  Parâmetros default têm valores atribuídos se nenhum valor for passado.

- **O que é uma função inline? Quando vale a pena usar uma função inline?**  
  Funções `inline` são expandidas no local de chamada, economizando tempo de chamada para funções pequenas.

- **O que seria uma sobrecarga de função? Como o compilador diferencia duas funções com o mesmo nome?**  
  Sobrecarga permite funções com o mesmo nome, diferenciadas por tipos ou quantidade de parâmetros.

- **Qual a diferença entre passar um parâmetro por cópia ou por referência constante? Quando usar cada um?**  
  Cópia duplica o valor; referência constante evita cópia, útil para grandes objetos ou parâmetros somente leitura.

- **Qual a diferença entre declaração e definição de uma função?**  
  Declaração especifica assinatura; definição inclui implementação.

- **O que é a tabela de símbolos de um programa? Como ela é usada pelo compilador?**  
  Tabela de símbolos armazena nomes e informações sobre variáveis e funções, usada pelo compilador para verificar escopo e tipos.
 
- **Qual o tipo padrão de um texto "Hello World" em C++?**  
  O tipo padrão é `const char[]` ou `const char*`.

- **Quais as formas de se criar um laço de repetição em C++?**  
  C++ oferece `for`, `while` e `do-while`.

- **O que fazem o continue e o break em um laço de repetição?**  
  `continue` pula para a próxima iteração; `break` termina o laço.

- **Pesquise onde o C++ é mais utilizado e quais as vantagens de se usar essa linguagem em relação a outras.**  
  C++ é amplamente usado em sistemas de alto desempenho, como jogos, motores gráficos e sistemas embarcados, por sua eficiência e controle de memória.

- **Quais são as principais linguagens que concorrem com C++ e quais as vantagens de cada uma delas?**  
  Java, C#, e Rust são concorrentes do C++. Java oferece portabilidade; C# é otimizado para aplicativos Windows; Rust proporciona segurança e eficiência de memória.
