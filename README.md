# 🎓 Sistema de Gestão Acadêmica Kolping (MAARD-eng)

O **MAARD-eng** é uma solução robusta desenvolvida em C para o gerenciamento de ecossistemas escolares. O projeto aplica conceitos avançados de **Estruturas de Dados Dinâmicas** para resolver problemas reais de alocação de vagas, histórico de notas e gerenciamento de pessoal, garantindo performance e integridade de memória.

---

## 🏗️ Arquitetura do Sistema e Engenharia de Dados

O software foi projetado sobre quatro pilares da Engenharia de Computação para garantir uma manipulação eficiente da memória Heap do seu notebook:

### 1. Listas Encadeadas (Gerenciamento Global e Local)
* **Professores**: Uma lista encadeada simples que armazena o corpo docente global, permitindo inserções e buscas dinâmicas.
* **Alunos e Disciplinas**: Uma estrutura hierárquica onde cada nó "Aluno" contém o início de uma lista secundária de "Disciplinas", permitindo que cada estudante tenha sua grade curricular alocada dinamicamente conforme sua série.



### 2. Fila Dinâmica (Controle de Transbordo)
* **Comportamento FIFO**: Utilizada quando uma turma atinge o limite máximo de vagas, movendo novos registros para um estado de espera.
* **Otimização $O(1)$**: A estrutura `FilaEspera` utiliza ponteiros para `inicio` e `fim`, garantindo que a inserção e a remoção ocorram em tempo constante.



### 3. Pilha de Segurança (Sistema de Undo)
* **Snapshot de Memória**: Antes de qualquer alteração de nota ou remoção, o sistema empilha um nó de `Acao` na pilha de segurança.
* **Recuperação de Estado**: Caso ocorra um erro de digitação, a função de "Desfazer" recupera o estado anterior diretamente da pilha, restaurando os dados originais.



### 4. Gerenciamento de Memória (Heap Engine)
* **Limpeza em Cascata**: O sistema implementa um motor de encerramento (`encerrar_sistema`) que percorre todas as estruturas (Turmas, Professores, Alunos e Filas) para garantir a liberação completa de memória e evitar *memory leaks*.

---

## 🚀 Funcionalidades Principais

* **Matrícula Automatizada**: Sistema inteligente que promove automaticamente o próximo aluno da fila de espera para a turma assim que uma vaga é aberta por remoção.
* **Portal do Docente**: Interface completa para lançamento, alteração e remoção de notas com suporte a "Desfazer".
* **Portal da Coordenação**: Gerenciamento centralizado de turmas e cadastro de professores com geração automática de e-mail institucional.
* **Relatório Final**: Processamento de toda a lista de alunos para gerar estatísticas de desempenho, aprovados e reprovados.

---

## 🛠️ Instruções de Compilação e Execução

Para atender aos requisitos de entrega do projeto, utilize o compilador `gcc` seguindo os comandos abaixo no seu terminal:

### 1. Pré-requisitos
Certifique-se de que os arquivos de código fonte (`.c`) e os cabeçalhos (`.h`) estejam localizados no mesmo diretório.

### 2. Comando de Compilação
Abra o terminal e execute: `gcc main.c -o sistema_kolping`

### 3. Comando de Execução
Inicie o sistema com o comando: `./sistema_kolping`

---

## 👥 Autores (Equipe de Engenharia)

Este projeto foi desenvolvido pelos acadêmicos de Engenharia de Computação:

* **DIEGO CARVALHO CAVALCANTE**
* **JOÃO FELIPE TUNES OLIVEIRA**
* **MIZAEL PARIS LEITE**
* **EVANDRO JOSÉ DOS SANTOS NETO**
* **KELVIN FAGUNDES GOMES DE SOUZA**
* **MATEUS ALVES DE ALMEIDA RODRIGUES DANTAS**

---
*Este software é um projeto integrador desenvolvido para a disciplina de Estrutura de Dados I.*
