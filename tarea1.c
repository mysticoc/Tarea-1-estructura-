#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura  que represente a a un grupo de clientes en espera
typedef struct {
  char id[50];
  int cantidad_personas;
  char prioridad[20];
  time_t hora_registro;
} Grupo;


/**
  * Despliega el menú principal en la consola.
  * Utiliza limpiarpantalla() para mantener la interfaz ordenada.
  */
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


/**
  * Registra un nuevo cliente en la cola de espera.
  * Asigna memoria dinámica para el grupo y establece la prioridad inicial
  * como "Estándar" y la hora actual.
  */
void registrar_grupo(List *lista) {
  // Asignación de memoria para el nuevo registro.
  Grupo *nuevo_grupo = (Grupo *)malloc(sizeof(Grupo));
  if (nuevo_grupo == NULL) {
    puts("Error de memoria.");
    return; // Sale de la función si falla la asignación.
  }
  printf("Ingrese el ID o  Nombre del cliente: ");
  scanf(" %49[^\n]", nuevo_grupo->id); // Lee hasta 49 carácteres. permitiendo espacios.

  printf("Ingrese  la cantidad de personas: ");
  scanf("%d", &nuevo_grupo->cantidad_personas);

  // Valores por defecto al registrar
  strcpy(nuevo_grupo->prioridad, "Estándar");
  nuevo_grupo->hora_registro = time(NULL);

  // Inserta el nuevo grupo al final de la lista.
  list_pushBack(lista, nuevo_grupo);
  printf("Grupo registrado exitosamente con prioridad 'Estándar'.\n");
}


/**
  * Modifica la prioridad de un cliente existente.
  * Realiza una búsqueda secuencial por ID y actualiza el campo de prioridad.
*/
void asignar_prioridad(List *lista) {
  char id_buscar[50];
  int opcion_prioridad;

  printf("Ingrese el ID o Nombre del cliente: ");
  scanf(" %49[^\n]", id_buscar);

  Grupo *grupo_encontrado = NULL;
  Grupo *grupo_actual = (Grupo *)list_first(lista);

  // Busqueda lineal en la lista enlazada
  while (grupo_actual != NULL) {
    if (strcmp(grupo_actual->id, id_buscar) == 0) {
      grupo_encontrado = grupo_actual;
      break; // Detiene la búsqueda al encontrar la primera coincidencia
    }
    grupo_actual = (Grupo *)list_next(lista);
  }

  // Si el cliente existe, presenta opciones de actualización
  if (grupo_encontrado != NULL) {
    printf("Seleccione la nueva prioridad:\n");
    printf("1) VIP\n2) Grupo Grande\n3) Estándar\nOpción: ");
    scanf("%d", &opcion_prioridad);

    // Asignación de la nueva categoría segun la entrada del usuario
    if (opcion_prioridad == 1) strcpy(grupo_encontrado->prioridad, "VIP");
    else if (opcion_prioridad == 2) strcpy(grupo_encontrado->prioridad, "Grupo Grande");
    else if (opcion_prioridad == 3) strcpy(grupo_encontrado->prioridad, "Estándar");
    else printf("Opción inválida. Se mantiene la prioridad actual.\n");
    
    printf("Prioridad actualizada a '%s'.\n", grupo_encontrado->prioridad);
  } else {
      printf("Aviso: No se encontró ningún grupo con el ID/Nombre ingresado.\n");
  } 
}

/**
  * Imprime todos los clientes en espera respetando el orden de prioridad.
  * Itera la lista 3 veces (una por categoría) para mantener el ordenamiento
  * estable sin necesidad de algoritmos de reordenamiento complejos.
  */
void mostrar_lista_pendiente(List *lista) {
  printf("--- Lista de Espera ---\n");
  char *prioridades[] = {"VIP", "Grupo Grande", "Estándar"};
  int contador = 1;

  // Bucle externo para iterar segun niveles de prioridad.
  for (int i = 0; i < 3; i++) {
    Grupo *grupo_actual = (Grupo *)list_first(lista);
    while (grupo_actual != NULL) {
      // Solo imprime si el grupo coincide con la prioridad de la iteración actual
      if (strcmp(grupo_actual->prioridad, prioridades[i]) == 0) {
        // Formatea la marca de tiempo a un formato de hora legible (HH:MM)
        struct tm *tm_info = localtime(&grupo_actual->hora_registro);
        char buffer[10];
        strftime(buffer, 10, "%H:%M", tm_info);
        printf("%d. [%s] %s - %d personas (Hora: %s)\n", contador++, grupo_actual->prioridad, grupo_actual->id, grupo_actual->cantidad_personas, buffer);
      }
      grupo_actual = (Grupo *)list_next(lista);
    }
  }
  // Mensaje alternativo si la lista estaba vacía.
  if (contador == 1) {
    printf("La lista de espera está vacía.\n");
  }
}


/**
  * Extrae de la lista al cliente con mayor prioridad para asignar mesa.
  * Busca secueniclamente respetando las prioridades y elimina el nodo de la lista.
  */
void asignar_mesa(List *lista) {
  char *prioridades[] = {"VIP", "Grupo Grande", "Estándar"};
  Grupo *grupo_asignado = NULL;

  // Busca al primer cliente que coincida con la prioridad más alta disponible
  for (int i = 0; i < 3; i++) {
    Grupo *grupo_actual = (Grupo *)list_first(lista);
    while (grupo_actual != NULL) {
      if (strcmp(grupo_actual->prioridad, prioridades[i]) == 0) {
        grupo_asignado = grupo_actual;
        list_popCurrent(lista); // Elimina el nodo de la lista enlazada
        break; // Detiene la búsqueda interna al encontrar el candidato
      }
      grupo_actual = (Grupo *)list_next(lista);
    }
    if (grupo_asignado != NULL) break; // Detiene la búsqueda externa si ya hay un asignado
  }
  // Despliegue de datos y liberación de memoria del cliente asignado
  if (grupo_asignado != NULL) {
    printf("Mesa asignada exitosamente:\n");
    printf("- Cliente: %s\n", grupo_asignado->id);
    printf("- Personas: %d\n", grupo_asignado->cantidad_personas);
    printf("- Prioridad: %s\n", grupo_asignado->prioridad);
    free(grupo_asignado); // Previene fugas de memoria
  } else {
    printf("Aviso: No hay grupos pendientes en la lista de espera.\n");
  }
}


/**
  * Busca y muestra todos los detalles de un cliente en específico.
  */
void buscar_reserva(List *lista) {
  char id_buscar[50];
  printf("Ingrese el ID o Nombre del cliente a buscar: ");

  // Limpieza del buffer de entrada para evitar lectura de saltos de linea
  int caracter_temporal;
  while ((caracter_temporal = getchar()) != '\n' && caracter_temporal != EOF);
  fgets(id_buscar, 50, stdin);
  id_buscar[strcspn(id_buscar, "\n")] = '\0'; // Elimina el salto de linea agregado por fgets

  Grupo *grupo_actual = (Grupo *)list_first(lista);

  // Recorre la lista buscando coincidencia exacta
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
      return; // Termina la función exitosamente.
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
  List *lista_espera = list_create(); // Inicialización de una lista doblemente enlazada

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
    // Pausa la ejecución para que el usuario pueda leer los resultados
    if (opcion != '6') presioneTeclaParaContinuar();
  } while(opcion != '6');

  // Bucle de limpieza para liberar la memoria dinámica de cualquier elemento basura
  Grupo *grupo_a_liberar = (Grupo *)list_first(lista_espera);
  while (grupo_a_liberar != NULL) {
    list_popCurrent(lista_espera); // Elimina el nodo
    free(grupo_a_liberar); // Libera el bloquer de memoria de la estructura
    grupo_a_liberar = (Grupo *)list_first(lista_espera);
  }
  list_clean(lista_espera); // Destruye la estructura general de la lista
  return 0;
}