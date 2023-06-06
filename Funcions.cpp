
//Importación de las librerias y definición.
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <cstring>
#define MAX_LENGTH 20
#define FALSE 0
#define TRUE 1
#define MAX_MAIL_LENGHT 20


//Nodo es la estructura inicial. Esta contiene los datos del usuario correspondiente.
struct Node {
    char nombre[MAX_LENGTH];
    //EXTRA: hemos hecho puedas ponter una contraseña en tu perfil y asi solo poder entrar con esta.
    char password[MAX_LENGTH];
    bool ispass;
    int num;
    int edad;
    char mail[MAX_MAIL_LENGHT];
    char ciudad[MAX_LENGTH];
    char hobbies[5][MAX_LENGTH];
    struct Node* siguiente;
    struct Node* previo;
    struct RequestQueue* solicitudes;
    struct FriendsQueue* Amigos;
    struct Post* lista;
};
//Esta estructura es
//Aquest estructura es una Biblioteca on s'emmagatzema tots els posts fets.
struct charcount{
    //post(palabra)
    char post[MAX_LENGTH][150];
    //repeticions del post(conteo)
    int reppost[MAX_LENGTH];
};
//Una estructura que emmagatzema el primer i l'ultim usuari guardat. Aquesta estructura es fa servir per recorrer tots els usuaris
struct Arraynode{
    struct Node* first;
    struct Node* last;
};

//L'estructura Friend conté un punter Node, que representa un amic, i un punter a Friend, que representa el següent amic en una llista enllaçada.
 struct Friend{
     Node* amigo;
     Friend* next;
 };

 //L'estructura FriendsQueue conté dos punters a Friend, que representen el primer i l'últim amic a la cua d'amics.
 struct FriendsQueue{
     Friend* primero;
     Friend* ultimo;
 };

//L'estructura Post conté un vector de caràcters de mida 120, que representa el contingut d'una aplicaciço, i un punter a Post, representa la següent publicació en una llista enllaçada.
struct Post {
    char contenido[120];
    struct Post* siguiente;
};

struct Node* usersearch(char* nombre);
void addfriend(struct Node* solicitante, struct Node* receptor);
void searchrandfrients(struct Node* solicitante);
void listuser();
Node *operuserfound(int i);
void operusermenu(struct Node* user);
void menu();
void processFriendRequests(struct Node* usuario);
int isfriend(struct Node* usuario, struct Node* amigo);

struct Request{
     struct Node* solicitante;
     struct Node* receptor;
     struct Request* siguiente;
};

struct RequestQueue{
     Request* primero;
     Request* ultimo;
};
struct charcount* Admincount=(struct charcount*) malloc(sizeof(struct charcount));
void Admininicialization(){
    for (int i=0;i<MAX_LENGTH;i++) {
        memset(Admincount->post[i],0,sizeof(Admincount->post[i]));
        Admincount->reppost[i] = 0;
    }
}

struct Arraynode usuarios = {NULL,NULL};


// FUNCIONES PARA SOLICITUDES Y GESTIONES DE AMISTAD.
//FUNCIONS PER SOLICITAR
RequestQueue* createRequestQueue(){
     struct RequestQueue* queue = (struct RequestQueue*) malloc(sizeof(struct RequestQueue));
     queue->primero = NULL;
     queue->ultimo = NULL;
     return queue;
};

// PARA ENCOLAR UNA NUEVA SOLICITUD DE AMISTAD
void enqueueRequest(RequestQueue* queue, struct Node* solicitante, struct Node* receptor){
    struct Request* nuevaSolicitud = (struct Request*) malloc(sizeof(struct Request));
    nuevaSolicitud->solicitante = solicitante;
    nuevaSolicitud->receptor = receptor;
     nuevaSolicitud->siguiente = NULL;

    if (queue->primero == NULL){
        queue->primero = nuevaSolicitud;
        queue->ultimo = nuevaSolicitud;
    } else {
        queue->ultimo->siguiente = nuevaSolicitud;
        queue->ultimo = nuevaSolicitud;
    }
}

int isfriend(struct Node* usuario, struct Node* amigo){

    if(usuario->Amigos->primero==NULL){

        return FALSE;
    }

    struct Friend* actual = usuario->Amigos->primero;
    while(actual != usuario->Amigos->ultimo){
        if( actual->amigo->num == amigo->num){
            return TRUE;
        }

        actual = actual->next;
    }

    if( actual->amigo->num == amigo->num){
        return TRUE;
    }
    return FALSE;
}

void addfriend(struct Node* solicitante,struct Node* receptor){
     if (receptor == NULL){
         printf("No se ha encontrado al usuario!\n");
         return;
     }

     if(isfriend(solicitante,receptor)){

         printf("Ya eres amig@ de %s\n",receptor->nombre);
         return;
     }



     struct Request* nuevaSolicitud = (struct Request*) malloc(sizeof(struct Request));
     nuevaSolicitud->solicitante = solicitante;
     nuevaSolicitud->receptor = receptor;
     nuevaSolicitud->siguiente = NULL;

     if(receptor->solicitudes == NULL) {
         receptor->solicitudes = createRequestQueue();
     }

     enqueueRequest(receptor->solicitudes, solicitante, receptor);
     printf("Solicitud de amistad enviada a %s.\n",receptor->nombre);

}
void soltofriend(Node* receptor, Node* solicitante ){

    Request* actualuser=receptor->solicitudes->primero;
    Friend* Amigo = (struct Friend*)malloc(sizeof(struct Friend));
    Friend* Amigo2 = (struct Friend*)malloc(sizeof(struct Friend));

    Amigo->amigo=solicitante;
    Amigo->next=NULL;
    Amigo2->amigo=receptor;
    Amigo2->next=NULL;
    if (actualuser->solicitante==solicitante){
        receptor->solicitudes->primero=actualuser->siguiente;
        if(solicitante->Amigos->primero==NULL){

            solicitante->Amigos->primero=Amigo2;
            solicitante->Amigos->ultimo=Amigo2;

        }
        else {
            solicitante->Amigos->ultimo->next = Amigo2;
            solicitante->Amigos->ultimo = solicitante->Amigos->ultimo->next;
        }
        if(receptor->Amigos->primero==NULL){

            receptor->Amigos->primero=Amigo;
            receptor->Amigos->ultimo=Amigo;
            return;
        }
        receptor->Amigos->ultimo->next=Amigo;
        receptor->Amigos->ultimo=receptor->Amigos->ultimo->next;
        return;



    }


    while(actualuser->siguiente!=receptor->solicitudes->ultimo){
        if (actualuser->siguiente->solicitante==solicitante){
            if(solicitante->Amigos->primero==NULL){

                solicitante->Amigos->primero=Amigo2;
                solicitante->Amigos->ultimo=Amigo2;

            }
            else {
                solicitante->Amigos->ultimo->next = Amigo2;
                solicitante->Amigos->ultimo = solicitante->Amigos->ultimo->next;
            }
            if(receptor->Amigos->primero==NULL){
                receptor->Amigos->primero=Amigo;
                receptor->Amigos->ultimo=Amigo;

                return;
            }
            receptor->Amigos->ultimo->next=Amigo;
            receptor->Amigos->ultimo=receptor->Amigos->ultimo->next;
            actualuser->siguiente=actualuser->siguiente->siguiente;
            return;

        }
        actualuser=actualuser->siguiente;
    }
    if (actualuser->siguiente->solicitante==solicitante){
        if (actualuser->siguiente->solicitante==solicitante){
            if(solicitante->Amigos->primero==NULL){

                solicitante->Amigos->primero=Amigo2;
                solicitante->Amigos->ultimo=Amigo2;

            }
            else {
                solicitante->Amigos->ultimo->next = Amigo2;
                solicitante->Amigos->ultimo = solicitante->Amigos->ultimo->next;
            }
            if(receptor->Amigos->primero==NULL){
                receptor->Amigos->primero=Amigo;
                receptor->Amigos->ultimo=Amigo;

                return;
            }
            receptor->Amigos->ultimo->next=Amigo;
            receptor->Amigos->ultimo=receptor->Amigos->ultimo->next;
            actualuser->siguiente=actualuser->siguiente->siguiente;
            receptor->solicitudes->ultimo=actualuser;
            return;

        }


    }

}

void acceptFriendRequest(struct Node* usuario, struct Node* solicitante){

    struct RequestQueue* queue = usuario->solicitudes;
    struct Request* solicitud = queue->primero;
    struct Request* anterior = NULL;

    while(solicitud != NULL){
        if(solicitud->solicitante == solicitante){
            soltofriend(usuario, solicitante);
            if(anterior == NULL){
                queue->primero = solicitud->siguiente;
            } else {
                anterior->siguiente = solicitud->siguiente;
            }
            free(solicitud);
            printf("Solicitud de amistad aceptada.\n");
            return;
        }
        anterior = solicitud;
        solicitud = solicitud->siguiente;
    }
    printf("No se encontró la solicitud de amistad de %s.\n", solicitante->nombre);
}

 void rejectFriendRequest(struct Node* usuario, struct Node* solicitante){
     if(usuario->solicitudes == NULL){
         printf("No tienes solicitudes de amistad pendientes.\n");
         return;
     }

     struct RequestQueue* queue = usuario->solicitudes;
     struct Request* solicitud = queue->primero;
     struct Request* anterior = NULL;

     while(solicitud != NULL){
         if(solicitud->solicitante == solicitante){
             if(anterior == NULL){
                 queue->primero = solicitud->siguiente;
             } else {
                 anterior->siguiente = solicitud->siguiente;
             }
             free(solicitud);
             printf("Solicitud de amistad rechazada.\n");
             return;
         }
         anterior = solicitud;
         solicitud = solicitud->siguiente;
     }
     printf("No se encontró la solicitud de amistad de %s.\n", solicitante->nombre);
 }

 Node *operuserfound(int id){
     Node* actualuser;
     actualuser=usuarios.first;
     if(id>usuarios.last->num) return NULL;

     for(int i=1;i<=id-1;i++){
         actualuser=actualuser->siguiente;
     }
     return actualuser;
 }
void processFriendRequests(struct Node* usuario){
    if(usuario->solicitudes->primero == NULL){
        printf("No tienes solicitudes de amistad pendientes.\n");
        operusermenu(usuario);
    }

    struct RequestQueue* queue = usuario->solicitudes;
    struct Request* solicitud = queue->primero;

    while (solicitud != NULL){
        struct Node* solicitante = solicitud->solicitante;
        printf("Tienes una solicitud de amistad de %s\n",solicitante);
        printf("1. Aceptar solicitud\n"
        "2. Rechazar solicitud\n"
        "3. Ver siguiente solicitud\n"
        "4. Volver al menu de usuario\n"
        "Elige una opcion: ");

        int opcion;
        scanf("%d", &opcion);
        switch (opcion){
            case 1:
                acceptFriendRequest(usuario, solicitante);
                processFriendRequests(usuario);
                break;
            case 2:
                rejectFriendRequest(usuario,solicitante);
                processFriendRequests(usuario);
            case 3:
                if(solicitud==queue->ultimo){
                    printf("\nNo tienes mas solicitudes");
                }
                solicitud=solicitud->siguiente;
            case 4:
                operusermenu(usuario);

            default:
                printf("Opcion no valida, intente de nuevo\n");
                break;
        }

    }

    return;
}
void showAcceptedFriendships(struct Node* usuario){
    struct Friend* actual = usuario->Amigos->primero;

    if(actual == NULL){
        printf("No tienes amistades aceptadas.\n");
        return;
    }
    printf("Tus amistades aceptadas:\n");
    while (actual!=NULL){
        printf(" - %s\n", actual->amigo->nombre);
        actual = actual->next;
    }
}
void searchrandfriends(struct Node* solicitante ){
     int i=0, k;
     struct Node* actualuser;
     while(i<3){
         k=1+rand()%(usuarios.last->num);
         actualuser=usuarios.first;
         for(int j=1;j<k;j++){
             actualuser=actualuser->siguiente;
         }
         if(actualuser != solicitante && !isfriend(solicitante,actualuser)){
             addfriend(solicitante,actualuser);
             i++;
         }
     }
}

void doPost(struct Node* usuario, char* contenido){
    struct Post* nueva = (struct Post*)malloc(sizeof(struct Post));
    strncpy(nueva->contenido, contenido, 120);
    nueva->contenido[120] = '\0';
    nueva->siguiente = NULL;
    if(usuario->lista == NULL){
        usuario->lista = nueva;
    }
    else {
        struct Post *ultima = usuario->lista;
        while (ultima->siguiente != NULL) {
            ultima = ultima->siguiente;
        }
        ultima->siguiente = nueva;
    }
}
void revisalista(struct Node* usuario){
    printf("Lista de publicaciones %s: \n", usuario->nombre);
    struct Post* publicacion = usuario->lista;
    while (publicacion != NULL){
        printf("%s\n", publicacion->contenido);
        publicacion= publicacion->siguiente;
    }
}

struct Node* usersearch(char* nombre){
    struct Node* actual = usuarios.first;
    int i;
    while (actual != NULL){
        i=0;
        while(nombre[i] != '\0' && actual->nombre[i] != '\0'){
            if(nombre[i] != actual->nombre[i]){
                break;
            }
            i++;
        }
        if (nombre[i] == '\0' && actual->nombre[i] == '\0'){
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}



// DONDE SE GUARDAN LAS SOLICITUDES DE AMISTAD.

void newuser(char* User,int edad, char* mail, char* ciudad, char hobbies[][MAX_LENGTH]){
    Node* newuser = new Node;
    strncpy(newuser->nombre, User, MAX_LENGTH);
    newuser->edad = edad;
    strncpy(newuser->mail, mail, MAX_LENGTH);
    strncpy(newuser->ciudad, ciudad, MAX_LENGTH);
    newuser->Amigos =(struct FriendsQueue*) malloc(sizeof(struct FriendsQueue));
    newuser->Amigos->primero = NULL;
    newuser->Amigos->ultimo = NULL;
    newuser->solicitudes =(struct RequestQueue*) malloc(sizeof(struct RequestQueue));
    newuser->solicitudes->primero = NULL;
    newuser->solicitudes->ultimo = NULL;
    newuser->ispass=FALSE;
    memset(newuser->password, 0, sizeof( newuser->password));

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
 void initfuser() {
     char nombreArchivo[100], nombre[MAX_LENGTH], correo[MAX_MAIL_LENGHT], hobby[4][MAX_LENGTH], edadstr[MAX_LENGTH];
     char caracter, ciudad[MAX_LENGTH], separation = ';';
     int edad, i = 0, j = 0;
     FILE *archivo;

     printf("Ingresa el nombre del archivo: ");
     scanf("%s", nombreArchivo);
     archivo = fopen(nombreArchivo, "r");

     if (archivo == NULL){
         printf("No se pudo abrir el archivo.\n");
         return;
     }
     printf("Contenido del archivo: \n");
     fgetc(archivo);
     fgetc(archivo);
     fgetc(archivo);
     while ((caracter = fgetc(archivo)) != EOF){
         if (caracter == separation){
             switch (j) {
                 case 0:
                     nombre[i] = '\0';
                     printf("Nom: %s\n", nombre);
                     break;
                 case 1:
                     edadstr[i]= '\0';
                     edad = atoi(edadstr);

                     break;
                 case 2:
                     correo[i] = '\0';
                     printf("Correo: %s\n", correo);
                     break;
                 case 3:
                     ciudad[i] = '\0';
                     printf("Ciudad: %s\n", ciudad);
                     break;
                 default:
                     hobby[j - 4][i] = '\0';

                     break;
             }
             i = 0;
             j++;
             if (j>7){
                 newuser(nombre,edad,correo,ciudad,hobby);
                 j=0;
             }
         } else{
             switch (j) {
                 case 0:
                     nombre[i]= caracter;
                     break;
                 case 1:
                     edadstr[i] = caracter;
                     break;
                 case 2:

                     correo[i] = caracter;
                     break;
                 case 3:
                     ciudad[i] = caracter;
                     break;
                 default:
                     hobby[j - 4][i] = caracter;
                     break;

             }
             i++;
         }
     }
     fclose(archivo);

 }

void listuser() {
    char option;
    Node* user = usuarios.first;
    printf("Lista usuarios:\n");
    while (user) {
        printf("ID %d: %s\n", user->num, user->nombre);
        user= user->siguiente;
    }
    printf("Introduzca cualquier caracter para continuar:");
    scanf("%s",&option);
    return;
 }
void printfriendlist(struct FriendsQueue* Amigos){
    if(Amigos->primero==NULL){
        printf("No tienes amigos");
        return;
    }
    Friend* actualfriend=Amigos->primero;
    int i=1;
    while(actualfriend!=Amigos->ultimo){
        printf("Amigo %d: %s      ID:%d",i,actualfriend->amigo->nombre,actualfriend->amigo->num);
        i++;
        actualfriend=actualfriend->next;
    }
    printf("Amigo %d: %s      ID:%d",i,actualfriend->amigo->nombre,actualfriend->amigo->num);
    return;

}
void Admincountadd(char post[150]){
    int i=0,eq=TRUE,j;
    while(Admincount->reppost[i]!=0&&i<MAX_LENGTH){
        j=0;
        eq=TRUE;
        while(post[j]!=0&&eq==TRUE){
            if(post[j]!=Admincount->post[i][j]){
                eq=FALSE;
            }
            j++;

        }
        if(eq==TRUE) {
            Admincount->reppost[i]++;
            if (i == 0) {
                return;

            }
            while (Admincount->reppost[i] > Admincount->reppost[i - 1]){


                std::swap(Admincount->reppost[i], Admincount->reppost[i - 1]);

                std::swap(Admincount->post[i], Admincount->post[i - 1]);

                i--;
                if (i == 0) {
                    return;
                }
            }
            return;
        }
        i++;
    }

    j=0;
    while(post[j]!=0){
        Admincount->post[i][j]=post[j];
        j++;
    }

    Admincount->reppost[i]=1;
    return;
}
void toppost(){
    int i=0;
    if(Admincount->reppost[i]==0){
        printf("No se ha publicado ningun post");
        return;
    }

    while(i<10&&Admincount->reppost[i]!=0){
        printf("Top %d: '%s'\n",i+1,Admincount->post[i]);
        i++;
    }
}
void operusermenu(struct Node* user){


    bool exit = FALSE;
    while (exit == FALSE){
        printf("\nMenu de usuario\n");
        printf(
                "1. Enviar solicitudes de amistad\n"
                "2. Gestionar solicitudes pendientes\n"
                "3. Realizar una publicacion\n"
                "4. Listar las publicaciones del usuario seleccionado\n"
                "5. Agregar amigos aleatorios\n"
                "6. Mostrar lista de amigos\n"
                "7. Palabras mas utilizadas\n"
        );
        if(user->ispass==TRUE) {
            printf("8. Cambiar password\n"
                   "9. Volver al memu principal\n"
            );
        }
        else{
            printf("8. Crear una nueva password\n"
                   "9. Volver al memu principal\n"
            );
        }
        if(user->num==1){
            printf("10. Contador de admin\n");
        }
        printf("Elija una opcion: ");
        int opcion;
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion){
            case 1: {

                int id2;
                printf("Seleccion: Enviar solicitudes de amistad\n");
                printf("Ingresa el id de la persona a la que le quieras enviar la solicitud:  ");
                scanf("%d", &id2);
                Node* Receptor = operuserfound(id2);

                if (Receptor != NULL){
                    addfriend(user,Receptor);
                } else{
                    printf("No se ha encontrado al usuario con la id %d.\n", id2);
                }
                break;
            }
            case 2:
                printf("Seleccion: Gestionar las solicitudes pendientes\n");
                processFriendRequests(user);

                break;

            case 3:
                char post[120];
                printf("Seleccion: Realizar publicacion\n");
                printf("Introduzca lo que quieras publicar");
                scanf("%s",post);
                Admincountadd(post);
                doPost(user,post);
                break;
            case 4:
                printf("Seleccion: Listar las publicaciones del usuario\n");
                int id3;
                printf("Ingresa el id de la persona a la que le quieras consultar sus publicaciones:  ");
                scanf("%d", &id3);


                Node *Posting;
                Posting = operuserfound(id3);
                if (Posting != NULL){
                    revisalista(Posting);
                }
                else{
                    printf("No se ha encontrado al usuario con la id %d.\n", id3);
                }
                break;
            case 5:
                printf("Seleccion: Agregar amigos aleatorios\n");

                searchrandfriends(user);
                break;
            case 6:
                printf("Seleccion: Mostrar lista de amigos\n");
                printfriendlist(user->Amigos);
                break;
            case 7:
                printf("Seleccion: Palabras mas utilizadas\n");
                toppost();
                break;
            case 8:
                printf("Seleccion: Cambio de password\n");
                user->ispass=TRUE;
                printf("Introduce la password que desea tener\n");
                char pass[MAX_LENGTH];
                scanf("%s",pass);
                int i;
                i = 0;
                while(pass[i]!=0){
                    user->password[i]=pass[i];
                    i++;
                }
                break;
                
            case 9:
                printf("Seleccion: Volver al menu principal\n");
                menu();
                break;
            case 10:
                if(user->num==1){
                   int i=0;
                   while(Admincount->reppost[i]!=0){
                       printf("'%s' se ha repetido %d ",Admincount->post[i],Admincount->reppost[i]);
                       if(Admincount->reppost[i]==1){
                           printf("vez.\n");
                       }
                       else{
                           printf("veces.\n");
                       }
                       i++;

                   }
                    break;
                }
            default:
                printf("Opcion no valida, intente de nuevo\n");
                break;
        }

    }
}
bool checkpass(char pass[MAX_LENGTH],struct Node* user){
    int i=0;
    while(user->password[i]!=0){
        if(pass[i]!=user->password[i]){
            return FALSE;
        }
        i++;
    }
    if(pass[i]!=0){
        return FALSE;
    }
    return TRUE;
            
}
void enterpass(struct Node* user){
    char pass[MAX_LENGTH];
    printf("Parece que la cuenta de %s esta protegida con una password.\nSi desea acceder debe introducir la password",user->nombre);
    printf("\nDesea acceder a esta cuenta?\n1. Si\n2. No");
    int op;
    while(TRUE) {

        scanf("%d", &op);
        switch (op) {

            case 1:

                while (TRUE) {

                    printf("Introduce la password: ");
                    scanf("%s",pass);
                    if(checkpass(pass,user)){
                        printf("Password correcta\n");
                        printf("Bienvenido %s, ya puedes operar en tu cuenta!", user->nombre);
                        operusermenu(user);
                    }
                    printf("Password incorrecta, desea seguir intentando?\n1. Si\n2. No");
                    op=0;
                    while(op==0){
                        scanf("%d", &op);
                        switch (op) {
                            case 1:
                            case 2:
                                menu();
                            default:
                                printf("Opcion no valida");
                                op=0;

                        
                    }
                }
                break;
            case 2:
                menu();
                break;
            default:
                printf("Opcion no valida");
                break;
        }
        }
    }
}
void menu() {
    bool exit = FALSE;
    while (exit == FALSE) {
        int opcion;

        printf("\nBienvenido a nuestra aplicacion\n");
        printf(
                "1. Iniciar nuevo usuario\n"
                "2. Listar todos los usuarios\n"
                "3. Operar como un usuario especifico\n"
                "4. Salir\n"
                "Elija una opcion:"
        );
        opcion=-1;
        scanf("%d", &opcion);

        printf("\n");
        if (opcion == 1) {
            int op2;
            printf(
                   "1.Crear usuario manualmente\n"
                   "2.iniciar usuario mediante un fichero\n");
            scanf("%d",&op2);
            while (op2!=1 && op2!=2) {
               printf("Introduzca una opcion valida:\n");
            }
            if (op2 == 1) inituser();
            if (op2 == 2) initfuser();
        }
        else if (opcion == 2)listuser();
        else if (opcion == 3){
            Node* user;
            int id;
            printf("Introduce el ID que quiera operar:\n");
            scanf("%d",&id);
            user = operuserfound(id);

            if (user->ispass){

                enterpass(user);
            }
            else {
                printf("Bienvenido %s, ya puedes operar en tu cuenta!", user->nombre);
                operusermenu(user);
            }
        }
        else if (opcion == 4)exit = TRUE;
        else printf("Escoge una entre las 4 opciones!");
    }
}
