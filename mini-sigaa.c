#include <stdio.h>   // Biblioteca padrão para funções de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para funções de alocação de memória, conversão de tipos, etc.
#include <string.h>  // Biblioteca padrão para funções de strings

#define TAM_NOME 50  // Define o tamanho máximo do nome do aluno
#define TAM_TITLE 30 // Define o tamanho máximo do título do professor
#define TAM_SALA 20  // Define o tamanho máximo do nome da sala
#define TAM_TURMA 30 // Define o tamanho máximo da turma
#define TAM_HR 20    // Define o tamanho máximo do horário da turma

/*
 * MINI SIGAA
 * Este código é um exemplo de como implementar estruturas e funções em C 
 * para representar e manipular alunos e turmas (como um mini SIGAA).
 */

// Estrutura para representar um aluno
typedef struct {
	char nome[TAM_NOME];  // Nome do aluno
	int matricula;        // Número de matrícula do aluno
	float cra;            // Coeficiente de Rendimento Acadêmico (CRA) do aluno
	int idade;			  // Idade do aluno
} t_aluno;

// Estrutura para representar um professor
typedef struct {
	char nome[TAM_NOME]; 		// Nome do professor
	int cod_departamento; 		// Código do departamento do professor
	int ano_contratacao;  		// Ano de Contratação do professor
	int idade;					// Idade do professor
	char titulo[TAM_TITLE]; 	// Titulação do professor
} t_professor;


// Estrutura para representar uma turma
typedef struct {
	char nome[TAM_NOME]; 		// Nome da turma
	char horario[TAM_HR]; 		// Horário da turma
	t_aluno* alunos[TAM_TURMA]; // Ponteiro para um array de alunos
	t_professor* professores; 	// Ponteiro para um professor
	int tam_turma;    			// Tamanho da turma (número de alunos)
	char sala[TAM_SALA];        // Número da sala de aula
} t_turma;

// Função para criar um novo aluno
t_aluno* criar_aluno(char* nome, int matricula, float CRA, int idade){
	t_aluno* novo_aluno = (t_aluno*)malloc(sizeof(t_aluno));	// Aloca memória
	if (novo_aluno == NULL){									// Verifica se a alocação foi bem sucedida
		printf("Erro ao alocar a memória para aluno.\n"); 		// Se não foi, exibe uma mensagem de erro e encerra o programa
		exit(1);
	}

	strcpy(novo_aluno->nome, nome);								// Copia os valores passado como argumento para a estrutura do aluno
	novo_aluno->matricula = matricula;
	novo_aluno->cra = CRA;
	novo_aluno->idade = idade;
	return novo_aluno;											// Retorna o ponteiro para o aluno criado
}

// Função para criar um novo professor
t_professor* criar_professor(char* nome, int cod_departamento, int ano_contratacao, int idade, char* titulo){
	t_professor* novo_professor = (t_professor*)malloc(sizeof(t_professor));	// Aloca memória
	if (novo_professor == NULL){												// Verifica se a alocação foi bem sucedida
		printf("Erro ao alocar a memória para professor.\n"); 					// Se não foi, exibe uma mensagem de erro e encerra o programa
		exit(1);
	}

	strcpy(novo_professor->nome, nome);											// Copia os valores passado como argumento para a estrutura do professor
	novo_professor->cod_departamento = cod_departamento;
	novo_professor->ano_contratacao = ano_contratacao;
	novo_professor->idade = idade;
	strcpy(novo_professor->titulo, titulo);
	return novo_professor;														// Retorna o ponteiro para o professor criado
}

// Função para criar uma nova turma
t_turma* criar_turma(char* nome, char* horario, char* sala){
	t_turma* nova_turma = (t_turma*)malloc(sizeof(t_turma));	// Aloca memória
	if (nova_turma == NULL){									// Verifica se a alocação foi bem sucedida
		printf("Erro ao alocar a memória para turma.\n"); 		// Se não foi, exibe uma mensagem de erro e encerra o programa
		exit(1);
	}

	strcpy(nova_turma->nome, nome);								// Copia os valores passado como argumento para a estrutura da turma
	strcpy(nova_turma->horario, horario);
	strcpy(nova_turma->sala, sala);
	nova_turma->tam_turma = 0;
	return nova_turma;											// Retorna o ponteiro para a turma criada
}


// Função para cadastrar um aluno em uma turma
int registro_aluno_turma(t_turma* turma, t_aluno* aluno) {
	if (turma->tam_turma < TAM_TURMA) {					// Verifica se a turma já atingiu o número máximo de alunos	
		turma->alunos[turma->tam_turma] = aluno;		// Adiciona o aluno ao array de alunos da turma
		turma->tam_turma++;								// Incrementa o número de alunos na turma
		return turma->tam_turma;						// Retorna o número de alunos na turma
	} else {
		printf("Turma cheia!\n");						// Se a turma já atingiu o número máximo de alunos, exibe mensagem de erro
		return -1;										// Retorna -1 para indicar que a operação falhou
	}
}

// Função para associar um professor a uma turma
void associa_professor_turma(t_turma* turma, t_professor* professor){
	// Atribui o ponteiro para o professor passado como argumento à turma
	turma->professores = professor;
}

// Função para exibir informações de um aluno
void exibir_aluno(t_aluno* aluno) {
    printf("\n--------------------\n");
    printf("Nome: %s\n", aluno->nome);
    printf("Matricula: %d\n", aluno->matricula);
    printf("CRA: %.2f\n", aluno->cra);
    printf("Idade: %d\n", aluno->idade);
    printf("--------------------\n\n");
}

// Função para exibir informações de um professor
void exibir_professor(t_professor* professor) {
	printf("\n--------------------\n");
    printf("Nome: %s\n", professor->nome);
    printf("SIAPE: %d\n", professor->cod_departamento);
    printf("Idade: %d\n", professor->idade);
    printf("Titulacao: %s\n", professor->titulo);
	printf("--------------------\n\n");
}

// Função para exibir informações de uma turma
void exibir_turma(t_turma* turma) {
    printf("\n\n================================\n");
    printf("Nome da Turma: %s\n", turma->nome);
    printf("Horario: %s\n", turma->horario);
    printf("Sala: %s\n", turma->sala);
    printf("Professor: \n");
    exibir_professor(turma->professores);
    printf("Alunos: \n");
    for (int i = 0; i < turma->tam_turma; i++) {
		exibir_aluno(turma->alunos[i]);
    }
    printf("================================\n");
}


/* Função para calcular o CRA dos alunos da turma
float calcula_media_cra_turma(t_turma *t){
	float soma_cra = 0, media_cra;
	for (int i = 0; i < t->tam_turma; i++) {
		soma_cra+=t->alunos[i].cra;
	}
	media_cra = (soma_cra/t->tam_turma);

	return media_cra;
} */


// Função principal
// Cadastra a turma e exibe as informações dos alunos
int main() {
	// Criação de alguns alunos
    t_aluno *aluno1 = criar_aluno("Maria da Silva", 123, 9.5, 20);
    t_aluno *aluno2 = criar_aluno("Jose Fernandes", 456, 8.7, 22);

    // Criação de dois professores
    t_professor* professor1 = criar_professor("Dr. Carlos", 789, 2010 ,45, "PhD");
    t_professor* professor2 = criar_professor("Dra. Ana", 101, 2005, 40, "PhD");

    // Criação de duas turmas
    t_turma* turma1 = criar_turma("Algorithms", "08:00 - 10:00", "Sala 105");
    t_turma* turma2 = criar_turma("Data Structures", "10:00 - 12:00", "Sala 106");

    // Cadastro dos alunos nas turmas
    registro_aluno_turma(turma1, aluno1);
    registro_aluno_turma(turma1, aluno2);
    registro_aluno_turma(turma2, aluno1);
    registro_aluno_turma(turma2, aluno2);

    // Cadastro dos professores nas turmas
    associa_professor_turma(turma1, professor1);
    associa_professor_turma(turma2, professor2);

    // Exibição das informações da turma
    exibir_turma(turma1);
    exibir_turma(turma2);

    // Liberar a memória alocada
    free(aluno1);
    free(aluno2);
    free(professor1);
    free(professor2);
    free(turma1);
    free(turma2);

	return 0;
}
