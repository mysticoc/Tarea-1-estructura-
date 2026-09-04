# Sistema de Gestión de Lista de Espera para Restaurante

**Repositorio GitHub:** [https://github.com/mysticoc/Tarea-1-estructura-.git](https://github.com/mysticoc/Tarea-1-estructura-.git)

Este Proyecto es una aplicación diseñada para administrar la lista de espera de clientes en un restaurante durante horas de alta demanda, utilizando un sistema de colas con prioridades basado en una Lista doblemente enlazada (TDA List).

## 1. Cómo compilar y ejecutar la tarea

El proyecto depende de los archivos genéricos de la estructura de datos ubicados en la carpeta 'tdas/'. Asegúrese de tener GCC instalado en su sistema.

**Para compilar**
Abre tu terminal en el directorio raíz del proyecto (donde se encuentra 'tarea1.c') y ejecuta el siguiente comando:
```bash
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1

```

**Para ejecutar**
Una vez finalizada la compilación, inicie la aplicación según su sistema operativo: 

```bash
# En Linux o Mac
./tarea1

# En Windows
tarea1.exe

```

## 2. Opciones y estado de las funcionalidades

Todas las funcionalidades requeridas operan correctamente y manejan la memoria de manera eficiente. No hay opciones defectuosas.

- Registrar grupo en lista de espera: Funciona correctamente. Registra el grupo, asigna la prioridad "Estándar" por defecto y guarda la hora exacta (hora actual y chilena)
- Asignar prioridad a cliente: Funciona correctamente. Actualiza la categoría del cliente sin alterar su hora original de ingreso.
- Nostrar lista de espera pendiente: Funciona correctamente. Despliega la lista ordenando primero por prioridad (VIP > Grupo Grande > Estándar) en tiempo lineal mediante recorridos sucesivos.
- Asignar mesa al siguiente cliente: Funciona correctamente. Extrae al cliente de mayor prioridad, libera su memoria asociada y ajusta los punteros de la lista.
- Buscar reserva por ID/Nombre: Funciona correctamente. Encuentra e imprime todos los detalles de un cliente específico.
- Salir (Limpieza de memoria): Funciona correctamente. Al cerrar el programa, el sistema itera sobre los elementos restantes para destruir la lista y evitar fugas de memoria.

## 3. Ejemplo de interacción.

1. Se inicia la aplicación e ingresa al Menu Principal.
2. Se selecciona la Opción 1. Se ingresa el nombre 'Nicolás Garrido' y '2' comensales.
3. Se repite la Opción 1 para agregar a 'Ivan García' y '4' comensales.
4. Se ingresa a la Opción 2, se busca a 'Nicolás Garrido' y se le asigna la prioridad '1' (VIP).
5. 5 Se ingresa a la Opción 3. El sistema imprime primero a 'Nicolás Garrido' etiquetado como [VIP] y debajo a 'Ivan García' como [Estándar].
6. Se ingresa a la Opción 4. El sistema remueve a 'Nicolás Garrido' de la cola y le asigna la mesa.
7. Se selecciona la Opción 6 para cerrar el sistema.

## 4. Contribuciones
* Trabajo realizado de manera individual por Nicolás Ignacio Garrido Vergara- 