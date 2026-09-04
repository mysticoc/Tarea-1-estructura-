#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
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
    puts("4) Asignar mesa al siguiente cliente/s");
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

  Grupo *grupo_actual = (Grupo *)list_first(lista);
  while (grupo_actual != NULL) {
    if (strcmp(grupo_actual->id, id_buscar) == 0) {
      grupo_encontrado = grupo_actual;
      break;
    }
    grupo_actual = (Grupo *)list_next(lista);
  }
  
  if (grupo_encontrado != NULL) {
    printf("Seleccione la nueva prioridad:\n");
    printf("1) VIP\n2) Grupo Grande\n3) Estándar\nOpción: ");
    scanf("%d", &opcion_prioridad);
    if (opcion_prioridad == 1) strcpy(grupo_encontrado->prioridad, "VIP");
    else if (opcion_prioridad == 2) strcpy(grupo_encontrado->prioridad, "Grupo Grande");
    else if (opcion_prioridad == 3) strcpy(grupo_encontrado->prioridad, "Estándar");
    else printf("Opción inválida. Se mantiene la prioridad actual.\n");
    
    printf("Prioridad actualizada a '%s'.\n", grupo_encontrado->prioridad);
  } else {
      printf("Aviso: No se encontró ningún grupo con el ID/Nombre ingresado.\n");
  } 
}

void mostrar_lista_pendiente(List *lista) {
  printf("--- Lista de Espera ---\n");
  char *prioridades[] = {"VIP", "Grupo Grande", "Estándar"};
  int contador = 1;
  for (int i = 0; i < 3; i++) {
    Grupo *grupo_actual = (Grupo *)list_first(lista);
    while (grupo_actual != NULL) {
      if (strcmp(grupo_actual->prioridad, prioridades[i]) == 0) {
        struct tm *tm_info = localtime(&grupo_actual->hora_registro);
        char buffer[10];
        strftime(buffer, 10, "%H:%M", tm_info);
        printf("%d. [%s] %s - %d personas (Hora: %s)\n", contador++, grupo_actual->prioridad, grupo_actual->id, grupo_actual->cantidad_personas, buffer);
      }
      grupo_actual = (Grupo *)list_next(lista);
    }
  }
  if (contador == 1) {
    printf("La lista de espera está vacía.\n");
  }
}

void asignar_mesa(List *lista) {
  char *prioridades[] = {"VIP", "Grupo Grande", "Estándar"};
  Grupo *grupo_asignado = NULL;

  for (int i = 0; i < 3; i++) {
    Grupo *grupo_actual = (Grupo *)list_first(lista);
    while (grupo_actual != NULL) {
      if (strcmp(grupo_actual->prioridad, prioridades[i]) == 0) {
        grupo_asignado = grupo_actual;
        list_popCurrent(lista);
        break;
      }
      grupo_actual = (Grupo *)list_next(lista);
    }
    if (grupo_asignado != NULL) break;
  }
  if (grupo_asignado != NULL) {
    printf("Mesa asignada exitosamente:\n");
    printf("- Cliente: %s\n", grupo_asignado->id);
    printf("- Personas: %d\n", grupo_asignado->cantidad_personas);
    printf("- Prioridad: %s\n", grupo_asignado->prioridad);
    free(grupo_asignado);
  } else {
    printf("Aviso: No hay grupos pendientes en la lista de espera.\n");
  }
}

void buscar_reserva(List *lista) {
  char id_buscar[50];
  printf("Ingrese el ID o Nombre del cliente a buscar: ");
  int caracter_temporal;
  while ((caracter_temporal = getchar()) != '\n' && caracter_temporal != EOF);
  fgets(id_buscar, 50, stdin);
  id_buscar[strcspn(id_buscar, "\n")] = '\0';

  Grupo *grupo_actual = (Grupo *)list_first(lista);
  while (grupo_actual != NULL) {
    if (strcmp(grupo_actual->id, id_buscar) == 0) {
      struct tm *tm_info = localtime(&grupo_actual->hora_registro);
      char buffer[10];
      strftime(buffer, 10, "%H:%M", tm_info);
      printf("\n--- Detalles de la Reserva ---\n");
      printf("Cliente: %s\n", grupo_actual->id);
      printf("Cantidad de personas: %d\n", grupo_actual->cantidad_personas);
      printf("Prioridad: %s\n", grupo_actual->prioridad);
      printf("Hora de registro: %s\n", buffer);
      return;
    }
    grupo_actual = (Grupo *)list_next(lista);
  }
  printf("Error: No se encontró la reserva con el ID '%s'.\n", id_buscar);
}

int main(){
  // Todos los comandos de abajo fueron buscados para poder establecer la hora chilena.
  #ifdef _WIN32 
    _putenv("TZ=America/Santiago");
  #else
    setenv("TZ", "America/Santiago", 1);
  #endif
  tzset();
  // Todos los comandos de arriba fueron buscados para poder establecer la hora chilena.
  
  char opcion;
  List *lista_espera = list_create();

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
      case '1':
        registrar_grupo(lista_espera);
        break;
      case '2':
        asignar_prioridad(lista_espera);
        break;
      case '3':
        mostrar_lista_pendiente(lista_espera);
        break;
      case '4':
        asignar_mesa(lista_espera);
        break;
      case '5':
        buscar_reserva(lista_espera);
        break;
      case '6':
        puts("Saliendo del sistema...");
        break;
      default : 
        puts("Opción no válida.");
    }
    if (opcion != '6') presioneTeclaParaContinuar();
  } while(opcion != '6');

  Grupo *grupo_a_liberar = (Grupo *)list_first(lista_espera);
  while (grupo_a_liberar != NULL) {
    list_popCurrent(lista_espera);
    grupo_a_liberar = (Grupo *)list_first(lista_espera);
  }
  list_clean(lista_espera);
  return 0;
}