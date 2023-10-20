# Pasos de Compilacion

En primer lugar, se asume que se seguiran los siguientes pasos en la maquina virtual (VM) de la asignatura.

## Creacion de Makefile

El archivo Makefile fue creado con el software CMake, el cual viene instalado con la VM. En el caso de que no este instalada en un entorno Ubuntu, se puede instalar con el siguiente comando en el terminal: 

	sudo apt-get install -y install cmake

Para crear el archivo Makefile con CMake, se debe ir a la carpeta "build" dentro de la carpeta "tarea-3-acevedo-reyes". Para hacer esto, se debe hacer el siguiente comando en el terminal, desde la carpeta "tarea-3-acevedo-reyes":

	cd build

Una vez dentro de build, se debe ejecutar el siguiente comando en el terminal:

	cmake ..
	
Se debe haber creado exitosamente el Makefile.

## Ejecucion de Makefile y Creacion de Ejecutable

Una vez que se creo el Makefile (junto con otros archivos no relevantes) en la carpeta "build", sin cambiar de directorio, se hace el siguiente comando en el terminal:

	make
	
Al ejecutarse el comando anterior, se habra creado en la carpeta "build" el archivo "calculadora", siendo este el ejecutable del codigo fuente.

## Ejecucion del Ejecutable

Para correr el ejecutable, se hace el siguiente comando en la consola de la carpeta "build":

	./calculadora