 //
// #Created by guill on 26/04/2023.
//
#include <iostream>
#include <cstring>
#define MAX_LENGTH 15
#define FALSE 0
#define TRUE 1
#define MAX_MAIL_LENGHT 20
struct Node{
    char nombre[MAX_LENGTH];
    int num;
    int edad;
    char mail[MAX_MAIL_LENGHT];
    char ciudad[MAX_LENGTH];
    char hobbies[5][MAX_LENGTH];
    struct Node* siguiente;
    struct Node* previo;
};

struct Arraynode{
    struct Node* first;
    struct Node* last;
};
Arraynode usuarios = {NULL, NULL};

void newuser(char* User,int edad, char* mail, char* ciudad, char hobbies[][MAX_LENGTH]){
    Node* newuser = new Node;
    strncpy(newuser->nombre, User, MAX_LENGTH);
    newuser->edad = edad;
    strncpy(newuser->mail, mail, MAX_LENGTH);
    strncpy(newuser->ciudad, ciudad, MAX_LENGTH);
    for(int i=0; i<5; i++ ){
        strncpy(newuser->hobbies[i], hobbies[i], MAX_LENGTH);
    }

    newuser->siguiente = NULL;
    newuser->previo = usuarios.last;

    if(usuarios.last){
        usuarios.last->siguiente = newuser;
        usuarios.last = newuser;
        newuser->num = newuser->previo->num + 1;

    } else{
        usuarios.first = newuser;
        usuarios.last = newuser;
        newuser->num = 1;
    }
}
void inituser(){
    char nombre[MAX_LENGTH], mail[MAX_MAIL_LENGHT], ciudad[MAX_LENGTH], hobbies[5][MAX_LENGTH];
    int edad;
    printf("Introduce tu Username ");
    scanf("%s",nombre);

    printf("Introduce tu edad: ");
    scanf("%s", &edad);

    printf("Introduce tu mail: ");
    scanf("%s", mail);

    printf("Introduce tu ciudad: ");
    scanf("%s", ciudad);
    printf("Introduce tus 5 hobbies/ gustos \n");
    for (int i = 0; i < 5; ++i) {
        scanf("%s", hobbies[i]);
    }
    newuser(nombre, edad, mail, ciudad, hobbies);
    printf("Hola %s, Bienvenido a nuestra aplicacion!\n", nombre);
    printf("Tu ID es: %d",usuarios.last->num);
}
void initfuser(){

}
void listuser() {
    Node* user = usuarios.first;
    printf("Lista usuarios:\n");
    while (user) {
        printf("ID %d: %s\n", user->num, user->nombre);
        user = user->siguiente;
    }
 }

Node* operuserfound(){
    int id;
    Node* actualuser;
    actualuser=usuarios.first;
    printf("Introduce el ID que quiera operar:\n");

    scanf("%d",&id);
    printf("%d",id);
    for(int i=1;i<=id;i++){
        actualuser=actualuser->siguiente;
    }
    return actualuser;
}
void operusermenu(){
    Node* user;
    int opcion;
    user = operuserfound();
    printf("Bienvenido %s, ya puedes operar en tu cuenta!", user->nombre);

    bool exit = FALSE;
    while (exit == FALSE){
        printf("\nMenu de usuario\n");
        printf(
                "1. Enviar solicitudes de amistad\n"
                "2. Gestionar solicitudes pendientes\n"
                "3. Realizar una publicacion\n"
                "4. Listar las publicaciones del usuario seleccionado"
                "5. Volver al memu principal\n"
                "Elija una opcion:"
                );
        scanf("%d", &opcion);
        printf("\n");
        switch (opcion) {
            case 1:
                printf("Seleccion: Enviar solicitudes de amistad\n");

                break;

            case 2:
                printf("Seleccion: Gestionar las solicitudes pendientes\n");

                break;

            case 3:
                printf("Seleccion: Realizar publicacion\n");

                break;
            case 4:
                printf("Seleccion: Listar las publicaciones del usuario\n");

                break;
            case 5:
                printf("Seleccion: Volver al menu principal\n");
                exit = TRUE;
                break;
            default:
                printf("Opcion no valida, intente de nuevo\n");
                break;

        }

    }
}

void menu() {
    int opcion;
    bool exit = FALSE;
    while (exit == FALSE) {

        printf("\nBienvenido a nuestra aplicacion\n");
        printf(
                "1. Iniciar nuevo usuario\n"
                "2. Listar todos los usuarios\n"
                "3. Operar como un usuario especifico\n"
                "4. Salir\n"
                "Elija una opcion:"
        );
        scanf("%d", &opcion);
        printf("\n ");
        if (opcion == 1) {
            int op2;
            printf("1. Crear usuario manualmente\n2.iniciar usuario mediante un fichero");
            scanf("%d",&op2);
           while (op2!=1 && op2!=2) {

               if (op2 == 1) inituser();
               if (op2 == 2) initfuser();
               printf("Introduzca una opcion valida");
           }

        }
        else if (opcion == 2)listuser();
        else if (opcion == 3)operusermenu();
        else if (opcion == 4)exit = TRUE;
        else printf("Escoge una entre las 4 opciones!");


    }

}

