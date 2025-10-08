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
};

void imprimir_instrucoes(void);

/*
 * Função que permite cadastrar uma nova carta.
 */
void cadastrar_carta(int indice, struct Carta *carta);

/*
 * Função que imprime uma carta no terminal.
 */
void imprimir_carta(struct Carta *carta);

/*
 * Criei essa função com base em documentação na internet para
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

	imprimir_instrucoes();

	cadastrar_carta(1, carta1);
	imprimir_carta(carta1);

	cadastrar_carta(2, carta2);
	imprimir_carta(carta2);

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

	printf("Bem vindo ao Jogo Super Trunfo!!! Primeiramente, vamos cadastrar as cartas que serão usadas durante as partidas.\n\n");
}
