#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

/*
 * Estrutura que modela uma carta do jogo super trunfo.
 */
struct Carta {
	char estado;
	char codigo[4]; // ex: A01\0
	char cidade[50];
	int populacao;
	float area;
	float pib;
	int pontos_turisticos;

	// campos calculados dinamicamente
	float densidade_populacional;
	float pib_per_capita;

	int cadastro_realizado; // 0 para falso, qualquer outra coisa true
};

/*
 * Imprimi tela de boas vindas.
 */
void imprimir_instrucoes(void);

/*
 * Menu inicial com as opções de cadastrar cartas ou comparar cartas.
 * Parâmetros de entrada:
 * 	- carta1: Referência para a primeira carta.
 * 	- carta2: Referência para a segunda carta.
 * As referências precisam ser alocadas previamente.
 * Após selecionar cadastrar cartas, o processo de cadastro para as duas cartas é iniciado.
 * Após selecionar comparar cartas, então testa se as cartas foram cadastradas previamente e
 * um erro indicando para cadastrar as cartas primeiro caso contrário e volta para o menu inicial.
 * Caso positivo exibe o menu de comparação.
 */
void menu_inicial(struct Carta *carta1, struct Carta *carta2);

/*
 * Imprime os atributos disponiveis para comparação.
 */
void imprime_atributos(int indice);

/*
 * Menu que permite ao usuário escolher qual atributo será usado para comparação.
 * Depois realiza a comparação
 * Parâmetros de entrada:
 * 	- carta1: Referência para a primeira carta
 * 	- carta2: Referência para a segunda carta
 * As referências já devem ter sido alocadas e as cartas cadastradas.
 */
void menu_comparacao(struct Carta *carta1, struct Carta *carta2);

/*
 * Função que permite cadastrar uma nova carta.
 */
void cadastrar_carta(int indice, struct Carta *carta);

/*
 * Função que imprime uma carta no terminal.
 */
void imprimir_carta(struct Carta *carta);

/*
 * Função que calcula a densidade populacional.
 * Retorna erro se a area for 0.
 */
float calcula_densidade_populacional(int populacao, float area);

/*
 * Função que calcula o pib per capita.
 * Retorna erro se a populacao for 0.
 */
float calcula_pib_per_capita(float pib, int populacao);

/*
 * Compara cartas com base no atributo passado como parametro e imprime a carta vencedora
 */
void compara_cartas(struct Carta *carta1, struct Carta *carta2, int atributo);

/*
 * Dado uma carta e um inteiro que corresponde à um atributo da carta,
 * retorna o valor do atributo.
 */
float busca_valor_por_atributo(struct Carta *carta, int atributo);

/*
 * Dado um inteiro que corresponde à um atributo da carta,
 * retorna a descrição ou nome do atributo.
 */
const char *busca_descricao_por_atributo(int atributo);

/*
 * Compara cartas com base nos dois atributos passado como parametro e imprime a carta vencedora
 * A comparação se dá com base na soma dos valores dos dois atributos
 */
void compara_cartas_multiplo(struct Carta *carta1, struct Carta *carta2, int atributo1, int atributo2);

/*
 * Menu que exibe a opção de continuar jogando ou encerrar o jogo
 */
int deseja_continuar(void);

/*
 * Compara dois atributos do tipo inteiro.
 */
void compara_int(int a, int b, char *carta_a, char *carta_b, const char *atributo, int vence_o_maior);

/*
 * Compara dois atributos do tipo ponto flutuante.
 */
void compara_float(float a, float b, char *carta_a, char *carta_b, const char *atributo, int vence_o_maior);

/*
 * ============= FUNÇÕES DE ENTRADADA DE DADOS ===================
 * Criei essas funções com base em documentação na internet para
 * resolver o problema que, ao ler qualquer coisa, após ler uma
 * string usando scanf, o input não era lido corretamente.
 * Aparentemente a explicação é de que a função scanf não lê o
 * caractere de nova linha, e ele fica lá no buffer stdin, e ai
 * quando vai usar o scanf de novo pra outra coisa, esse caractere
 * de nova linha que ficou lá perdido é lido primeiro e buga tudo.
 */
void ler_string(char *str, size_t length);
char ler_char(void);
float ler_float(void);
int ler_int(void);

int main(int argc, char *argv[])
{
	struct Carta *carta1 = malloc(sizeof(struct Carta));
	struct Carta *carta2 = malloc(sizeof(struct Carta));

	do 
	{
		imprimir_instrucoes();
		menu_inicial(carta1, carta2);
	} while(deseja_continuar());

	free(carta1);
	free(carta2);

	return 0;
}

void cadastrar_carta(int indice, struct Carta *carta)
{
	printf("===== CADASTRO DE CARTAS =====\n");
	printf("CARTA %d\n", indice);

	printf("Estado: ");
	carta->estado = ler_char();

	printf("Código: ");
	ler_string(carta->codigo, sizeof(carta->codigo));

	printf("Nome da Cidade: ");
	ler_string(carta->cidade, sizeof(carta->cidade));

	printf("População: ");
	carta->populacao = ler_int();

	printf("Área: ");
	carta->area = ler_float();

	printf("PIB: ");
	carta->pib = ler_float();

	printf("Número de pontos turísticos: ");
	carta->pontos_turisticos = ler_int();

	carta->densidade_populacional = calcula_densidade_populacional(carta->populacao, carta->area);
	carta->pib_per_capita = calcula_pib_per_capita(carta->pib, carta->populacao);
	carta->cadastro_realizado = 1;
}

void imprimir_carta(struct Carta *carta)
{
	printf("\n===========\n");

	printf("Estado: %c\n", carta->estado);
	printf("Código: %s\n", carta->codigo);
	printf("Nome da Cidade: %s\n", carta->cidade);
	printf("População: %d\n", carta->populacao);
	printf("Área: %f\n", carta->area);
	printf("PIB: %f\n", carta->pib);
	printf("Número de pontos turísticos: %d\n", carta->pontos_turisticos);
	printf("Densidade populacional: %f\n", carta->densidade_populacional);
	printf("PIB per capita: %f\n", carta->pib_per_capita);
}


float calcula_densidade_populacional(int populacao, float area)
{
	if(area == 0)
	{
		printf("Erro ao calcular densidade populacional. Área não pode ser zero.");
		exit(1);
	}

	return (float) populacao / area;
}

float calcula_pib_per_capita(float pib, int populacao)
{
	if(populacao == 0)
	{
		printf("Erro ao calcular PIB per capita. População não pode ser zero.");
		exit(1);
	}

	return pib / (float) populacao;
}

void compara_cartas(struct Carta *carta1, struct Carta *carta2, int atributo)
{
	printf("\n\n\nCOMPARANDO CARTAS.........");
	switch(atributo)
	{
		case 1:
			compara_int(carta1->populacao, carta2->populacao, carta1->codigo, carta2->codigo, "população", 1);
			break;
		case 2:
			compara_float(carta1->area, carta2->area, carta1->codigo, carta2->codigo, "área", 1);
			break;
		case 3:
			compara_float(carta1->pib, carta2->pib, carta1->codigo, carta2->codigo, "PIB", 1);
			break;
		case 4:
			compara_int(carta1->pontos_turisticos, carta2->pontos_turisticos, carta1->codigo, carta2->codigo, "pontos turisticos", 1);
			break;
		case 5:
			compara_float(carta1->densidade_populacional, carta2->densidade_populacional, carta1->codigo, carta2->codigo, "densidade populacional", 0);
			break;
		case 6:
			compara_float(carta1->pib_per_capita, carta2->pib_per_capita, carta1->codigo, carta2->codigo, "PIB per capita", 1);
			break;
		default:
			printf("\n\nAtributo inválido!!!\n");
			break;
	}
}

const char *busca_descricao_por_atributo(int atributo)
{
	const char *atributos[] = {
		"população",
		"área",
		"PIB",
		"pontos turísticos",
		"densidade populacional",
		"PIB per capita"
	};

	if (atributo < 1 || atributo > 6)
	{
		return "atributo inválido";
	}

	return atributos[atributo - 1];
}

float busca_valor_por_atributo(struct Carta *carta, int atributo)
{
	switch(atributo)
	{
		case 1:
			return (float) carta->populacao;
		case 2:
			return carta->area;
		case 3:
			return carta->pib;
		case 4:
			return (float) carta->pontos_turisticos;
		case 5:
			return carta->densidade_populacional;
		case 6:
			return carta->pib_per_capita;
		default:
			printf("\n\nAtributo inválido!!!\n");
			return -1;
	}
}

void compara_cartas_multiplo(struct Carta *carta1, struct Carta *carta2, int atributo1, int atributo2)
{
	float carta_a_valor1 = busca_valor_por_atributo(carta1, atributo1);
	float carta_a_valor2 = busca_valor_por_atributo(carta1, atributo2);

	float carta_b_valor1 = busca_valor_por_atributo(carta2, atributo1);
	float carta_b_valor2 = busca_valor_por_atributo(carta2, atributo2);

	char descricao[128];
	snprintf(descricao, sizeof(descricao), "%s + %s",
			busca_descricao_por_atributo(atributo1),
			busca_descricao_por_atributo(atributo2));
	
	compara_float(carta_a_valor1 + carta_a_valor2, carta_b_valor1 + carta_b_valor2, carta1->codigo, carta2->codigo, descricao, 1);
}

// Referencia: https://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
void ler_string(char *str, size_t length)
{
	fflush(stdout);
	fgets(str, length + 1, stdin);
	str[strcspn(str, "\n")] = 0;
}

char ler_char(void)
{
	char dummy[3];
	fgets(dummy, 3, stdin);

	return dummy[0];
}

// Funcao baseada no mesmo artigo acima. O scanf estava causando problemas sempre deixando uma linha nova no buffer
float ler_float(void)
{
	char buf[128], *endptr;
	double value;

	for (;;)
	{
		fflush(stdout);

		if (!fgets(buf, sizeof(buf), stdin))
		{
			exit(EXIT_FAILURE);
		}

		buf[strcspn(buf, "\n")] = '\0';
		errno = 0;
		value = strtod(buf, &endptr);

		if (errno == ERANGE)
		{
			printf("Numero fora do limite.\n");
			continue;
		}

		if (endptr == buf || *endptr != '\0')
		{
			printf("Numero invalido.\n");
			continue;
		}

		return (float) value;
	}
}

// Funcao baseada no mesmo artigo acima. O scanf estava causando problemas sempre deixando uma linha nova no buffer
int ler_int(void)
{
	char buf[128];
	char *endptr;
	long value;

	for (;;)
	{
		fflush(stdout);

		if (!fgets(buf, sizeof(buf), stdin))
		{
			exit(EXIT_FAILURE);
		}

		buf[strcspn(buf, "\n")] = '\0';

		errno = 0;
		value = strtol(buf, &endptr, 10);

		if (errno == ERANGE)
		{
			printf("Numero fora dos limites.\n");
			continue;
		}

		if (endptr == buf || *endptr != '\0')
		{
			printf("Numero inválido.\n");
			continue;
		}

		return (int) value;
	}
}

void imprimir_instrucoes(void)
{
	// Arte gerada através do seguinte site:
	// https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type+Something+&x=none&v=4&h=4&w=80&we=false
	printf("\n\n");
	printf("  _________                           ___________                    _____       \n");
	printf(" /   _____/__ ________   ___________  \\__    ___/______ __ __  _____/ ____\\____  \n");
	printf(" \\_____  \\|  |  \\____ \\_/ __ \\_  __ \\   |    |  \\_  __ \\  |  \\/    \\   __\\/  _ \\ \n");
	printf(" /        \\  |  /  |_> >  ___/|  | \\/   |    |   |  | \\/  |  /   |  \\  | (  <_> )\n");
	printf("/_______  /____/|   __/ \\___  >__|      |____|   |__|  |____/|___|  /__|  \\____/ \n");
	printf("        \\/      |__|        \\/                                    \\/             \n\n");

	printf("Bem vindo ao Jogo Super Trunfo!!!\n");
	printf("Primeiro selecione a opção de cadastrar cartas. Cadastre as duas cartas com todos os atributos corretamente.\n");
	printf("Após isso selecione a opção de comparar cartas e escolha por qual atributo você gostaria de comparar as cartas.\n\n");
}

void menu_inicial(struct Carta *carta1, struct Carta *carta2)
{
	printf("Opções: \n");
	printf("1. Cadastrar cartas.\n");
	printf("2. Comparar cartas.\n");

	int opcao = ler_int();
	switch(opcao)
	{
		case 1:
			cadastrar_carta(1, carta1);
			imprimir_carta(carta1);

			cadastrar_carta(2, carta2);
			imprimir_carta(carta2);

			break;
		case 2:
			if(carta1->cadastro_realizado && carta2->cadastro_realizado)
			{
				menu_comparacao(carta1, carta2);
			}
			else
			{
				printf("\nCadastre as cartas antes de selecionar a opção de comparação.\n\n");
			}
			break;
		default:
			printf("Opção inválida!");
	}
}

void imprime_atributos(int indice)
{
	printf("Selecione o %d° atributo que você quer usar para comparar as cartas: \n", indice);
	printf("1. População\n");
	printf("2. Área\n");
	printf("3. PIB\n");
	printf("4. Pontos turísticos\n");
	printf("5. Densidade populacional\n");
	printf("6. PIB per capita\n");
}

void menu_comparacao(struct Carta *carta1, struct Carta *carta2)
{
	imprime_atributos(1);
	int atributo1 = ler_int();

	imprime_atributos(2);
	int atributo2 = ler_int();

	if(atributo1 == atributo2)
	{
		printf("\n\nEscolha atributos diferentes para comparação!!!\n\n");
		return;
	}

	compara_cartas(carta1, carta2, atributo1);
	compara_cartas(carta1, carta2, atributo2);

	compara_cartas_multiplo(carta1, carta2, atributo1, atributo2);
}

int deseja_continuar(void)
{
	printf("\n\nDeseja continuar jogando? 1. Não / Qualquer outro número. Sim\n");
	int opcao = ler_int();
	return opcao - 1;
}

void compara_int(int a, int b, char *carta_a, char *carta_b, const char *atributo, int vence_o_maior)
{
	if(a == b)
	{
		printf("\nCarta %s empatou com carta %s, pois ambas possuem o mesmo valor de %s: %d\n",
				carta_a,
				carta_b,
				atributo,
				a);
		return;
	}

	int a_ganhou = vence_o_maior ? a > b : a < b;

	printf("\nA carta %s ganhou pois tem %s %s, %d contra %d da carta %s\n",
			a_ganhou ? carta_a : carta_b,
			atributo,
			vence_o_maior ? "maior" : "menor",
			a_ganhou ? a : b,
			a_ganhou ? b : a,
			a_ganhou ? carta_b : carta_a);
}

void compara_float(float a, float b, char *carta_a, char *carta_b, const char *atributo, int vence_o_maior)
{
	if(a == b)
	{
		printf("\nCarta %s empatou com carta %s, pois ambas possuem o mesmo valor de %s: %f\n",
				carta_a,
				carta_b,
				atributo,
				a);
		return;
	}

	int a_ganhou = vence_o_maior ? a > b : a < b;

	printf("\nA carta %s ganhou pois tem %s %s, %f contra %f da carta %s\n",
			a_ganhou ? carta_a : carta_b,
			atributo,
			vence_o_maior ? "maior" : "menor",
			a_ganhou ? a : b,
			a_ganhou ? b : a,
			a_ganhou ? carta_b : carta_a);
}
