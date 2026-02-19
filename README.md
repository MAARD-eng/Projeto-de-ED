# 🎓 Sistema de Gestão Acadêmica Kolping (MAARD-eng)

O **MAARD-eng** é uma solução robusta desenvolvida em C para o gerenciamento de ecossistemas escolares. O projeto aplica conceitos avançados de **Estruturas de Dados Dinâmicas** para resolver problemas reais de alocação de vagas, histórico de notas e gerenciamento de pessoal, garantindo performance e integridade de memória.

## 🏗️ Arquitetura do Sistema e Engenharia de Dados

O software foi projetado sobre quatro pilares da Engenharia de Computação para garantir uma manipulação eficiente da memória Heap:

### 1. Listas Encadeadas (Gerenciamento Global e Local)
* **Professores:** Uma lista encadeada simples que armazena o corpo docente global, permitindo inserções e buscas dinâmicas.
* **Alunos e Disciplinas:** Uma estrutura hierárquica onde cada nó "Aluno" contém o início de uma lista secundária de "Disciplinas", permitindo que cada estudante tenha sua grade curricular alocada dinamicamente conforme sua série (Fundamental ou Médio).

### 2. Fila Dinâmica (Controle de Transbordo)
* **Comportamento FIFO:** Utilizada quando uma turma atinge o limite máximo de vagas, movendo novos registros para um estado de espera.
* **Otimização $O(1)$:** A estrutura `FilaEspera` utiliza ponteiros para `inicio` e `fim`, garantindo que a inserção e a remoção ocorram em tempo constante.

### 3. Pilha de Segurança (Sistema de Undo)
* **Snapshot de Memória:** Antes de qualquer alteração de nota ou remoção, o sistema empilha um nó de `Acao`.
* **Recuperação de Estado:** Caso ocorra um erro de digitação, a função de "Desfazer" recupera o estado anterior diretamente da pilha.

### 4. Gerenciamento de Memória (Heap Engine)
* **Limpeza em Cascata:** O sistema implementa um motor de encerramento (`encerrar_sistema`) que percorre todas as estruturas (Turmas, Professores, Alunos e Filas) para garantir a liberação completa de memória, evitando *memory leaks*.

---

## 🚀 Funcionalidades Principais

* **Matrícula Automatizada:** Sistema inteligente que promove automaticamente o próximo aluno da fila de espera para a turma assim que uma vaga é aberta.
* **Portal do Docente:** Interface completa para lançamento, alteração e remoção de notas com validação rigorosa de dados.
* **Portal da Coordenação:** Gerenciamento centralizado de turmas e cadastro de professores.
* **Relatório de Fechamento:** Processamento de toda a lista de alunos para gerar estatísticas de desempenho.

---

## 🛠️ Detalhes de Implementação

* **Linguagem:** C (Padrão C99/C11).
* **Robustez:** Implementação de `limpar_buffer()` para estabilidade contra entradas inválidas.
* **Persistência:** Uso de ponteiros de ponteiros para garantir que as alterações sejam refletidas em todos os módulos.

---

## Guia Técnico: Sistema Escolar Kolping

Este documento detalha os procedimentos de compilação, execução e as diretrizes arquiteturais do sistema de gestão acadêmica desenvolvido em linguagem C.

### 🛠️ 1. Preparação do Ambiente
Para garantir a compilação correta, os seguintes arquivos devem estar no mesmo diretório de trabalho:
* **main.c**: Contém o fluxo de controle, menus e a lógica de integração.
* **projeto_escola.h**: Header contendo as definições de estruturas (Listas Encadeadas, Filas e Pilhas) e as implementações das funções de negócio.

### 💻 2. Instruções de Compilação
O projeto utiliza o padrão C99 e pode ser compilado via terminal utilizando o **GCC**:

#### Comando Padrão:
gcc main.c -o sistema_kolping

#### Execução:
    Windows: sistema_kolping.exe

    Linux/macOS: ./sistema_kolping

## 👥 Autores (Equipe de Engenharia)

Este projeto foi desenvolvido pelos acadêmicos de Engenharia de Computação:

* **DIEGO CARVALHO CAVALCANTE**
* **JOÃO FELIPE TUNES OLIVEIRA**
* **MIZAEL PARIS LEITE**
* **EVANDRO JOSÉ DOS SANTOS NETO**
* **KELVIN FAGUNDES GOMES DE SOUZA**
* **MATEUS ALVES DE ALMEIDA RODRIGUES DANTAS**

---
*Este software é um projeto integrador desenvolvido para a disciplina de Estrutura de Dados.*
