#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
int id;
char nome[50];
float salario;
int ativo; // 0 ou 1
} Registro;
void imprimir_registro(const Registro *r) {
printf("ID: %d | Nome: %s | Salário: R$ %.2f | Ativo: %s\n",
r->id, r->nome, r->salario, r->ativo ? "Sim" : "Não");
}
int main(void) {
FILE *fp;
Registro registros[3] = {
{1, "Ana Costa", 5500.50, 1},
{2, "Bruno Silva", 6200.75, 1},
{3, "Carlos Souza", 4800.00, 0}
};
Registro lido;
// ===== ESCRITA BINÁRIA =====
fp = fopen("dados.bin", "wb");
if (fp == NULL) {
perror("Erro ao criar arquivo binário");
return EXIT_FAILURE;
}
// fwrite: escreve blocos de dados
// size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
size_t escritos = fwrite(registros, sizeof(Registro), 3, fp);
printf("Registros escritos: %zu\n\n", escritos);
fclose(fp);
// ===== LEITURA BINÁRIA SEQUENCIAL =====
fp = fopen("dados.bin", "rb");
if (fp == NULL) {
perror("Erro ao abrir arquivo binário");
return EXIT_FAILURE;
}
printf("=== Leitura Sequencial ===\n");
// fread: lê blocos de dados
// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
while (fread(&lido, sizeof(Registro), 1, fp) == 1) {
imprimir_registro(&lido);

}
// ===== LEITURA ALEATÓRIA =====
printf("\n=== Leitura Aleatória (Registro 2) ===\n");
// Calcular posição do registro 2 (índice 1)
long posicao = 1 * sizeof(Registro);
fseek(fp, posicao, SEEK_SET);
if (fread(&lido, sizeof(Registro), 1, fp) == 1) {
imprimir_registro(&lido);
}
// ===== ATUALIZAÇÃO DE REGISTRO =====
printf("\n=== Atualização do Registro 3 ===\n");
fclose(fp);
// Abrir em modo leitura/escrita
fp = fopen("dados.bin", "r+b");
if (fp == NULL) {
perror("Erro ao abrir para atualização");
return EXIT_FAILURE;
}
// Ir para o registro 3 (índice 2)
fseek(fp, 2 * sizeof(Registro), SEEK_SET);
// Ler registro atual
fread(&lido, sizeof(Registro), 1, fp);
printf("Antes: ");
imprimir_registro(&lido);
// Modificar
lido.ativo = 1;
lido.salario = 5000.00;
// Voltar à posição do registro
fseek(fp, 2 * sizeof(Registro), SEEK_SET);
// Escrever de volta
fwrite(&lido, sizeof(Registro), 1, fp);
// Verificar atualização
fseek(fp, 2 * sizeof(Registro), SEEK_SET);
fread(&lido, sizeof(Registro), 1, fp);
printf("Depois: ");
imprimir_registro(&lido);
fclose(fp);
// ===== INFORMAÇÕES SOBRE O ARQUIVO =====
fp = fopen("dados.bin", "rb");
fseek(fp, 0, SEEK_END);
long tamanho = ftell(fp);
printf("\n=== Informações do Arquivo ===\n");
printf("Tamanho total: %ld bytes\n", tamanho);
printf("Tamanho do registro: %zu bytes\n", sizeof(Registro));
printf("Número de registros: %ld\n", tamanho / sizeof(Registro));
fclose(fp);
return EXIT_SUCCESS;
}