# Parcial 2 Fabián Mauricio Ospina Arévalo
## Cómo compilarlo

```
g++ -o parqueadero parqueadero.cpp
./parqueadero
```

Librerias usadas(`iostream`, `iomanip`, `string`, `cstring`, `ctime` y `fstream`).

## Qué hace el programa

Cuando se abre aparece un menú con estas opciones:

- **1. Mapa** → muestra el parqueadero en la consola con colores.
- **2. Ingreso** → pide la placa y el tipo (C para carro, M para moto) y lo mete al espacio libre más cercano a la entrada.
- **3. Salida** → pide la placa, calcula el tiempo que estuvo y cuánto tiene que pagar.
- **4. Activos** → muestra los vehículos que están adentro ahora mismo.
- **5. Información del parqueadero** → muestra cuántos espacios hay libres, ocupados y el porcentaje de ocupación.
- **0. Salir** → cierra el programa.

## El mapa

El mapa es una matriz de 18 x 18. Cada celda puede ser:

- Muro (los bordes)
- Vía (por donde pasan los carros)
- Libre (espacio disponible)
- Ocupado (ya hay un vehículo ahí)
- Entrada (arriba a la izquierda)
- Salida (abajo a la derecha)

Se muestra con colores en la terminal para que se vea más fácil cuáles están libres y cuáles ocupados.

## Las tarifas

Están al principio del programa como constantes, por si hay que cambiarlas:

- Carro: $3.476 por hora
- Moto: $1.765 por hora

## Cómo está organizado el código

Usé dos structs:

- **`Vehicle`** guarda los datos de cada vehículo: placa, tipo, hora de entrada, fila y columna donde quedó, y un booleano `active` para saber si todavía está adentro.
- **`ParkingLot`** guarda todo el parqueadero: la matriz del mapa, el arreglo de vehículos y los contadores de libres y ocupados.

Casi todas las funciones reciben las estructuras por puntero (`ParkingLot*` o `Vehicle*`) para no estar copiando los datos cada vez que se llama una función.

El máximo de vehículos está en 90 porque en el mapa caben más o menos esa cantidad de espacios.

## El archivo de historial
Cuando un vehículo sale, el programa guarda una línea en un archivo llamado historial.txt con la placa, el tipo, la hora de entrada, la hora de salida y el total que pagó. Si el archivo no existe lo crea, y si ya existe le agrega la línea al final.

## Partes hechas con ayuda de IA

En el código hay dos partes donde usé IA (Claude) como apoyo, y las dejé marcadas con comentarios:

1. Los **colores de la terminal**: no sabía cómo poner colores en la consola, y la IA me explicó que son códigos ANSI (esas secuencias raras como `\033[32m`).
2. El **cálculo del espacio más cercano a la entrada**: yo solo sabía devolver el primer espacio libre que encontrara, y la IA me explicó cómo medir distancia con la fórmula de Manhattan (sumar la diferencia de filas y de columnas).
3. Me apoye tambien con algunos errores que no sabia como solucionarlos