# AgenciaAutosTuxedo

Compilacion

    Ubicarse en la ruta del archivo makefile
        cd /home/oracle/tuxedo/make
    Compilar el archivo makefile con su respectivo nombre
        make -f makefileT4
    Ubicarse en la ruta del archivo ubbconfig (ubbconfig_T4)
        cd ../conf
    Ejecutar los siguientes comandos
        tmloadcf -y ubbconfig_T4
        tmboot -y
        tmadmin
        psc
    Ubicarse en la ruta de los binarios /bin
        cd ../bin
    Ejecutar el archivo del cliente para usar los servicios
        ./clienteT4
    Realizar las operaciones deseades dentro del codigo clienteT4
    Ir al la ruta de los archivos log /log
        cd ../log
    Ejecutar el archivo ULOG con su respectivo nombre (Se ven los servicios que se ejecutaron)
        tail -13 ULOG-S10.012824

En caso de que se encuentre activo el servicio de tuxedo dar de baja con el comando - tmshutdown -y
