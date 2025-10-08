#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carta {
	char estado;
	char codigo[2];
	char cidade[50];
	int populacao;
	float area;
	float pib;
	int pontos_turisticos;
};

void cadastrar_carta(int indice, struct Carta *carta);
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
void ler_string(char *str);

/*
 * Criei essa função pelo mesmo motivo da de cima
 */
char ler_char(void);

int main(int argc, char *argv[])
{
	struct Carta *carta1 = malloc(sizeof(struct Carta));
	struct Carta *carta2 = malloc(sizeof(struct Carta));

	cadastrar_carta(1, carta1);
	imprimir_carta(carta1);

	//cadastrar_carta(2, carta2);
	//imprimir_carta(carta2);

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
	ler_string(carta->codigo);
}

void imprimir_carta(struct Carta *carta)
{
	printf("\n===========\n");

	printf("Estado: %c\n", carta->estado);

	printf("Código: %s\n", carta->codigo);
}

void ler_string(char *str)
{
	scanf("%s", str);
	getchar();
}

char ler_char(void)
{
	char c;
	scanf("%c", &c);
	getchar();

	return c;
}
