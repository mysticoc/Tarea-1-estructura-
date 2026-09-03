#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stblib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char id[50];
  int cantidad_personas;
  char prioridad[20];
  time_t hora_registro;
} Grupo;

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("  Sistema de Lista de Espera - Restaurante");
    puts("========================================");
    puts("1) Registrar grupo en lista de espera");
    puts("2) Asignar prioridad a cliente");
    puts("3) Mostrar lista de espera pendiente");
    puts("4) Asignar mesa al siguiente grupo");
    puts("5) Buscar reserva por ID/Nombre");
    puts("6) Salir");
}

void registrar_grupo(List *lista) {
  Grupo *nuevo_grupo = (Grupo *)malloc(sizeof(Grupo));
  if (nuevo_grupo == NULL) {
    puts("Error de memoria.");
    return;
  }
  printf("Ingrese el ID o  Nombre del cliente: ");
  scanf(" %49[^\n]", ) 
}