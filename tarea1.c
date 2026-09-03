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
  scanf(" %49[^\n]", nuevo_grupo->id);

  printf("Ingrese  la cantidad de personas: ");
  scanf("%d", &nuevo_grupo->cantidad_personas);

  strcpy(nuevo_grupo->prioridad, "Estándar");
  nuevo_grupo->hora_registro = time(NULL);

  list_pushBack(lista, nuevo_grupo);
  printf("Grupo registrado exitosamente con prioridad 'Estándar'.\n");
}

void asignar_prioridad(List *lista) {
  char id_buscar[50];
  int opcion_prioridad;

  printf("Ingrese el ID o Nombre del cliente: ");
  scanf(" %49[^\n]", id_buscar);

  Grupo *grupo_encontrado = NULL;
  void *current = list_first(lista);

  while (current != NULL) {
    Grupo *g = (Grupo *)current;
    if (strcmp(g->id, id_buscar) == 0) {
      grupo_encontrado = g;
      break;
    }
    current = list_next(lista);
  }
  if (grupo_encontrado != NULL) {
    printf("Seleccione la nueva prioridad:\n");
    printf("1) VIP\n2) Grupo Grande\n3)Estándar\nOpción: ");
    scanf("%d", &opcion_prioridad);
    if (opcion_prioridad == 1) strcpy(grupo_encontrado->prioridad, "VIP");
    else if (opcion_prioridad == 2) strcpy(grupo_encontrado->prioridad, "Grupo Grande");
    else if (opcion_prioridad == 3) strcpy(grupo_encontrado->prioridad, "Estándar");
    else printf("Opción inválida. Se mantiene la prioridad actual.\n");
  }
}