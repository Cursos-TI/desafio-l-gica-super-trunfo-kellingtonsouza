#include <stdio.h>
#include <string.h>

// Definição da estrutura para representar uma carta do Super Trunfo
typedef struct {
    char estado[3];         // Ex: "SP"
    char codigo_carta[5];   // Ex: "C01"
    char nome_cidade[50];   // Ex: "São Paulo"
    int populacao;          // Ex: 12300000
    float area;             // Ex: 1521.1
    float pib;              // Ex: 720.0
    int num_pontos_turisticos; // Ex: 10
    float densidade_populacional; // Calculado: População / Área
    float pib_per_capita;         // Calculado: PIB / População
} CartaCidade;

/**
 * @brief Função para inicializar uma carta com os dados fornecidos e calcular os atributos derivados.
 * * @param carta Ponteiro para a estrutura CartaCidade a ser inicializada.
 * @param estado A sigla do estado.
 * @param codigo O código da carta.
 * @param nome O nome da cidade.
 * @param pop A população da cidade.
 * @param ar A área da cidade (em km²).
 * @param pib_total O Produto Interno Bruto (em bilhões).
 * @param pontos O número de pontos turísticos.
 */
void inicializar_carta(
    CartaCidade *carta,
    const char *estado,
    const char *codigo,
    const char *nome,
    int pop,
    float ar,
    float pib_total,
    int pontos
) {
    // Copia os dados básicos para a estrutura
    strncpy(carta->estado, estado, sizeof(carta->estado) - 1);
    carta->estado[sizeof(carta->estado) - 1] = '\0';
    
    strncpy(carta->codigo_carta, codigo, sizeof(carta->codigo_carta) - 1);
    carta->codigo_carta[sizeof(carta->codigo_carta) - 1] = '\0';
    
    strncpy(carta->nome_cidade, nome, sizeof(carta->nome_cidade) - 1);
    carta->nome_cidade[sizeof(carta->nome_cidade) - 1] = '\0';
    
    carta->populacao = pop;
    carta->area = ar;
    carta->pib = pib_total; // PIB em bilhões
    carta->num_pontos_turisticos = pontos;

    // --- CÁLCULO DOS ATRIBUTOS DERIVADOS ---

    // 1. Densidade Populacional: População / Área (hab/km²)
    if (carta->area > 0) {
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0.0;
    }

    // 2. PIB per capita: (PIB * 1,000,000,000) / População (R$ por habitante)
    // Usamos o PIB em bilhões e a população em unidade, então o cálculo já resulta em per capita
    // Nota: O PIB é float (em Bilhões), a População é int (em unidades).
    if (carta->populacao > 0) {
        // Multiplicamos o PIB (em Bilhões) por 10^9 e dividimos pela População.
        // Como o foco é a comparação, podemos simplificar e usar PIB em bilhões/População
        // para manter as ordens de grandeza. Para o cálculo real, seria:
        // carta->pib_per_capita = (carta->pib * 1000000000.0) / (float)carta->populacao;
        // Vamos manter a simplificação para a comparação:
        carta->pib_per_capita = (carta->pib * 1000000000.0) / (float)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0;
    }
}

/**
 * @brief Função para exibir os dados de uma carta, incluindo os atributos calculados.
 * * @param carta A estrutura CartaCidade a ser exibida.
 */
void exibir_carta(const CartaCidade carta) {
    printf("  Código: %s\n", carta.codigo_carta);
    printf("  Cidade: %s (%s)\n", carta.nome_cidade, carta.estado);
    printf("  População: %'d hab\n", carta.populacao);
    printf("  Área: %.2f km²\n", carta.area);
    printf("  PIB: R$ %.2f bilhões\n", carta.pib);
    printf("  Pontos Turísticos: %d\n", carta.num_pontos_turisticos);
    printf("  --- Atributos Derivados ---\n");
    printf("  Densidade Populacional: %.2f hab/km²\n", carta.densidade_populacional);
    printf("  PIB per capita: R$ %.2f\n", carta.pib_per_capita);
}

/**
 * @brief Função principal do programa.
 */
int main() {
    // Define o atributo de comparação (escolha feita diretamente no código)
    // 1: População, 2: Área, 3: PIB, 4: Densidade Populacional, 5: PIB per capita
    const int ATRIBUTO_ESCOLHIDO = 4; // Exemplo: Comparar por Densidade Populacional

    // --- CADASTRO DAS DUAS CARTAS ---

    CartaCidade carta1;
    inicializar_carta(
        &carta1,
        "SP",             // Estado
        "C01",            // Código
        "São Paulo",      // Nome
        12396372,         // População (IBGE 2021)
        1521.1,           // Área (km²)
        768.61,           // PIB (em R$ Bilhões, 2020)
        15                // Pontos Turísticos
    );

    CartaCidade carta2;
    inicializar_carta(
        &carta2,
        "RJ",             // Estado
        "C02",            // Código
        "Rio de Janeiro", // Nome
        6772497,          // População (IBGE 2021)
        1200.3,           // Área (km²)
        359.21,           // PIB (em R$ Bilhões, 2020)
        20                // Pontos Turísticos
    );

    // --- EXIBIÇÃO DAS CARTAS ---
    printf("=========================================\n");
    printf("           SUPER TRUNFO CIDADES          \n");
    printf("=========================================\n\n");
    
    printf("--- Carta 1 ---\n");
    exibir_carta(carta1);
    printf("\n");

    printf("--- Carta 2 ---\n");
    exibir_carta(carta2);
    printf("\n");

    // --- COMPARAÇÃO DO ATRIBUTO ESCOLHIDO ---

    // Variáveis para armazenar o valor do atributo e o nome para exibição
    float valor1 = 0.0;
    float valor2 = 0.0;
    char nome_atributo[50];
    int carta_vencedora = 0; // 1 para Carta 1, 2 para Carta 2, 0 para Empate

    // Seleção do atributo e determinação da vitória/derrota (Regra de Trunfo)
    switch (ATRIBUTO_ESCOLHIDO) {
        case 1: // População: Maior valor vence
            strcpy(nome_atributo, "População");
            valor1 = (float)carta1.populacao;
            valor2 = (float)carta2.populacao;
            if (valor1 > valor2) carta_vencedora = 1;
            else if (valor2 > valor1) carta_vencedora = 2;
            break;
        case 2: // Área: Maior valor vence
            strcpy(nome_atributo, "Área (km²)");
            valor1 = carta1.area;
            valor2 = carta2.area;
            if (valor1 > valor2) carta_vencedora = 1;
            else if (valor2 > valor1) carta_vencedora = 2;
            break;
        case 3: // PIB: Maior valor vence
            strcpy(nome_atributo, "PIB (R$ Bilhões)");
            valor1 = carta1.pib;
            valor2 = carta2.pib;
            if (valor1 > valor2) carta_vencedora = 1;
            else if (valor2 > valor1) carta_vencedora = 2;
            break;
        case 4: // Densidade Populacional: **Menor** valor vence
            strcpy(nome_atributo, "Densidade Populacional (hab/km²)");
            valor1 = carta1.densidade_populacional;
            valor2 = carta2.densidade_populacional;
            // A regra é inversa: o MENOR valor vence
            if (valor1 < valor2) carta_vencedora = 1;
            else if (valor2 < valor1) carta_vencedora = 2;
            break;
        case 5: // PIB per capita: Maior valor vence
            strcpy(nome_atributo, "PIB per capita (R$)");
            valor1 = carta1.pib_per_capita;
            valor2 = carta2.pib_per_capita;
            if (valor1 > valor2) carta_vencedora = 1;
            else if (valor2 > valor1) carta_vencedora = 2;
            break;
        default:
            printf("Erro: Atributo de comparação inválido.\n");
            return 1;
    }

    // --- EXIBIÇÃO DO RESULTADO DA COMPARAÇÃO ---

    printf("=========================================\n");
    printf("  Comparação de cartas (Atributo: %s)\n", nome_atributo);
    printf("=========================================\n");

    // Formato de exibição do valor baseado no atributo (para melhor usabilidade)
    if (ATRIBUTO_ESCOLHIDO == 1) { // População (int)
        printf("  Carta 1 - %s (%s): %.0f\n", carta1.nome_cidade, carta1.estado, valor1);
        printf("  Carta 2 - %s (%s): %.0f\n", carta2.nome_cidade, carta2.estado, valor2);
    } else if (ATRIBUTO_ESCOLHIDO == 5) { // PIB per capita (R$)
        printf("  Carta 1 - %s (%s): R$ %.2f\n", carta1.nome_cidade, carta1.estado, valor1);
        printf("  Carta 2 - %s (%s): R$ %.2f\n", carta2.nome_cidade, carta2.estado, valor2);
    } else if (ATRIBUTO_ESCOLHIDO == 3) { // PIB (Bilhões)
         printf("  Carta 1 - %s (%s): R$ %.2f Bilhões\n", carta1.nome_cidade, carta1.estado, valor1);
         printf("  Carta 2 - %s (%s): R$ %.2f Bilhões\n", carta2.nome_cidade, carta2.estado, valor2);
    } 
    else { // Área, Densidade Populacional
        printf("  Carta 1 - %s (%s): %.2f\n", carta1.nome_cidade, carta1.estado, valor1);
        printf("  Carta 2 - %s (%s): %.2f\n", carta2.nome_cidade, carta2.estado, valor2);
    }


    printf("\n");
    if (carta_vencedora == 1) {
        printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
    } else if (carta_vencedora == 2) {
        printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
    } else {
        printf("Resultado: Empate!\n");
    }
    printf("=========================================\n");

    return 0;
}