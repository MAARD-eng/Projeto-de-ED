#include "projeto_escola.h"

// Prototipos das funcoes de controle do Integrador
void exibir_cabecalho();
void portal_coordenacao(Professor **lp, Turma **lt, FilaEspera *f);
void portal_docente(Turma *lt, Pilha *seguranca);
void encerrar_sistema(Turma *lt, Professor *lp, FilaEspera *f);
void portal_aluno(Turma *lt);
void limpar_buffer();

int main() {
    // Instanciacao dos Descritores de Estruturas 
    Professor *lista_professores = NULL;
    Turma *lista_turmas = NULL;
    FilaEspera *espera = criar_fila(); 
    Pilha *seguranca = criarPilha();   
    
    int opcao;

    do {
        exibir_cabecalho();
        printf("1. Portal da Coordenacao (Matricula)\n");
        printf("2. Portal do Docente (Notas & Desfazer)\n");
        printf("3. Portal do Aluno (Boletim)\n");
        printf("4. Visualizar Fila de Espera\n");
        printf("5. Remover Aluno (Abrir Vaga)\n");
        printf("0. Sair e Liberar Memoria\n");
        printf("----------------------------\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            limpar_buffer(); 
            continue;
        }
        limpar_buffer();
        
        switch(opcao) {
            case 1: 
                entrar_menu(1);
                portal_coordenacao(&lista_professores, &lista_turmas, espera); 
                break;
            case 2: 
                entrar_menu(2);
                portal_docente(lista_turmas, seguranca); 
                break;
            case 3: 
                entrar_menu(3);
                portal_aluno(lista_turmas); 
                break;
            case 4:
                entrar_menu(4);
                exibir_fila(espera); 
                break;
            case 5: {
                entrar_menu(5);
                char mat_aux[20]; 
                printf("Matricula para remover: ");
                scanf("%s", mat_aux);
                limpar_buffer();

                remover_aluno_turma(lista_turmas, mat_aux, espera); 
                break;
            }
            case 0: 
                printf("\nEncerrando Sistema Kolping");
                encerrar_sistema(lista_turmas, lista_professores, espera); 
                free(seguranca); 
                printf("\n[STATUS] Memória Heap limpa.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// LOGICA DE INTEGRACAO TECNICA 

void exibir_cabecalho() {
    printf("\n========================================");
    printf("\n       SISTEMA ESCOLAR KOLPING          ");
    printf("\n========================================\n");
}

void portal_coordenacao(Professor **lp, Turma **lt, FilaEspera *f) {
    int sub_op;
    printf("\n PORTAL DA COORDENACAO ");
    printf("\n1. Matricular Aluno (Lista/Fila)");
    printf("\n2. Cadastrar Professor (Lista Global)");
    printf("\n0. Voltar");
    printf("\nEscolha: ");
    
    if (scanf("%d", &sub_op) != 1) {
        limpar_buffer();
        return;
    }
    limpar_buffer();

    if (sub_op == 1) {
        char nome[100], mat[20];
        int serie;

        printf("\n--- MATRICULA DE ALUNO ---");
        printf("\nNome: "); scanf(" %[^\n]", nome);
        printf("Matricula: "); scanf("%s", mat);
        printf("Serie (6-12): "); scanf("%d", &serie);
        limpar_buffer();

        Aluno *novo = matricular_aluno(mat, nome, serie);

        if (*lt == NULL) {
            *lt = criar_turma("TURMA-A", serie, 5); 
        }

        processar_matricula_turma(*lt, novo, f);
    } 
    else if (sub_op == 2) {
        char id[15], nome[100], depto[50];
        
        printf("\n--- CADASTRO DE PROFESSOR ---");
        printf("\nID (Ex: KOLP-01): "); scanf("%s", id);
        printf("Nome: "); scanf(" %[^\n]", nome);
        printf("Departamento: "); scanf(" %[^\n]", depto);
        limpar_buffer();

        Professor *novo_p = criar_professor(id, nome, depto);
        inserir_professor_global(lp, novo_p);
        printf("\n[SUCESSO] Professor %s cadastrado na Lista Global!\n", nome);
    }
}

void encerrar_sistema(Turma *lt, Professor *lp, FilaEspera *f) {
    printf("\nLimpando Heap Engine");
    
    // 1. Limpa Professores
    while (lp) {
        Professor *temp = lp;
        lp = lp->proximo;
        free(temp);
    }
    
    // 2. Limpa Fila de Espera
    while (f && f->quantidade > 0) {
        desenfileirar(f); 
    }
    if(f) free(f);

    // 3. Limpa Turmas
    while (lt) {
        Turma *temp = lt;
        lt = lt->proximo_turma;

        free(temp);
    }
    
    printf("\nMemoria liberada com sucesso. Ate logo!\n");
}

void portal_aluno(Turma *lt) {
    if (!lt) {
        printf("\nErro: Nenhuma turma cadastrada.\n");
        return;
    }
    char mat[20];
    printf("\n--- PORTAL DO ALUNO ---\nMatricula: ");
    scanf("%s", mat);
    limpar_buffer();

    Aluno *a = buscar_aluno(lt->lista_alunos, mat); 
    if (a) {
        exibir_boletim(a);
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

/* Exibe as disciplinas do aluno para ajudar na digitacao */
static void listar_disciplinas_aluno(Aluno *a) {
    if (!a) return;
    printf("Disciplinas disponíveis:\n");
    Disciplina *d = a->lista_disciplinas;
    int n = 1;
    while (d) { printf("  %d. %s\n", n++, d->nome); d = d->proximo; }
}

void portal_docente(Turma *lt, Pilha *seguranca) {
    if (!lt) {
        printf("\n[AVISO] Nenhuma turma cadastrada. Use o Portal da Coordenacao.\n");
        return;
    }

    int sub_op;
    printf("\n========================================\n");
    printf("    PORTAL DO DOCENTE — KOLPING          \n");
    printf("    Turma: %-10s | %d aluno(s)      \n", lt->codigo, lt->qtd_atual);
    printf("========================================\n");
    printf("1. Lancar Nota\n");
    printf("2. Alterar Nota existente\n");
    printf("3. Remover Nota (Zerar)\n");
    printf("4. Consultar Notas de um Aluno\n");
    printf("5. Desfazer Ultima Alteracao de Nota\n");
    printf("6. Gerar Relatorio Final (Fechamento)\n");
    printf("0. Voltar\n");
    printf("----------------------------------------\n");
    printf("Escolha: ");

    if (scanf("%d", &sub_op) != 1) { limpar_buffer(); return; }
    limpar_buffer();

    if (sub_op == 1) {
        char mat[20], materia[50]; int u, p; float nota;
        printf("\n--- LANCAR NOTA ---\n");
        printf("Matricula: "); scanf("%s", mat); limpar_buffer();
        Aluno *a = buscar_aluno(lt->lista_alunos, mat);
        if (!a) { printf("[ERRO] Aluno nao encontrado.\n"); return; }
        listar_disciplinas_aluno(a);
        printf("Disciplina: "); scanf(" %[^\n]", materia);
        printf("Unidade (1-4): "); scanf("%d", &u);
        printf("Prova (1-2): ");   scanf("%d", &p);
        printf("Nota (0-10): ");   scanf("%f", &nota); limpar_buffer();
        lancar_nota_validada(lt->lista_alunos, seguranca, mat, materia, u, p, nota);

    } else if (sub_op == 2) {
        char mat[20], materia[50]; int u, p; float nota;
        printf("\n--- ALTERAR NOTA ---\n");
        printf("Matricula: "); scanf("%s", mat); limpar_buffer();
        Aluno *a = buscar_aluno(lt->lista_alunos, mat);
        if (!a) { printf("[ERRO] Aluno nao encontrado.\n"); return; }
        consultar_notas_aluno(lt->lista_alunos, mat);
        listar_disciplinas_aluno(a);
        printf("Disciplina: ");       scanf(" %[^\n]", materia);
        printf("Unidade (1-4): ");    scanf("%d", &u);
        printf("Prova (1-2): ");      scanf("%d", &p);
        printf("Nova nota (0-10): "); scanf("%f", &nota); limpar_buffer();
        alterar_nota(lt->lista_alunos, seguranca, mat, materia, u, p, nota);

    } else if (sub_op == 3) {
        char mat[20], materia[50]; int u, p;
        printf("\n--- REMOVER NOTA (ZERAR) ---\n");
        printf("Matricula: "); scanf("%s", mat); limpar_buffer();
        Aluno *a = buscar_aluno(lt->lista_alunos, mat);
        if (!a) { printf("[ERRO] Aluno nao encontrado.\n"); return; }
        listar_disciplinas_aluno(a);
        printf("Disciplina: ");    scanf(" %[^\n]", materia);
        printf("Unidade (1-4): "); scanf("%d", &u);
        printf("Prova (1-2): ");   scanf("%d", &p); limpar_buffer();
        remover_nota(lt->lista_alunos, seguranca, mat, materia, u, p);

    } else if (sub_op == 4) {
        char mat[20];
        printf("\n--- CONSULTAR NOTAS ---\n");
        printf("Matricula: "); scanf("%s", mat); limpar_buffer();
        consultar_notas_aluno(lt->lista_alunos, mat);

    } else if (sub_op == 5) {
        printf("\n--- DESFAZER ULTIMA ALTERACAO DE NOTA ---\n");
        desfazer_nota(seguranca);

    } else if (sub_op == 6) {
        printf("\n--- FECHAMENTO / RELATORIO FINAL ---\n");
        gerar_relatorio_final(lt);

    } else if (sub_op == 0) {
        voltar_menu();
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
