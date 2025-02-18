#include"MaterialBibliografico.cpp"
#include"Libro.cpp"
#include"Revista.cpp"
#include"Usuario.cpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
using namespace std;


/** @brief agrega un material a la lista
 * 
 *  Esta función primero comprueba que no haya más de 100 materiales. Si se cumple, 
 *  le pide al usuario que ingrese la información de un material, y guarda el puntero en la lista materiales
 * 
 *  @param materiales lista con capacidad para 100 punteros de MaterialBibliografico
 */
void agregarMaterial(MaterialBibliografico* materiales[100]){
    if(materiales[99] != nullptr){
        cout<<"No se pudo agregar el material, ya hay más de 100 materiales"<<endl;
        return;
    }
    string nombre;
    string isbn;
    string autor;
    string tipoLibro;
    cout<<"Ingrese el tipo de material (Libro/Revista): "; cin >> tipoLibro;
    while(tipoLibro != "Libro" && tipoLibro != "Revista"){
        cout<<"Ingrese un tipo válido (Libro/Revista): "; cin >> tipoLibro;
    }
    cout<<"Ingrese el nombre: ";
    cin.ignore();
    getline(cin,nombre);
    cout<<"Ingrese el ISBN: "; 
    getline(cin,isbn);
    cout<<"Ingrese el autor: "; 
    getline(cin,autor);
    if(tipoLibro == "Libro"){
        string fecha;
        string resumen;
        cout<<"Ingrese la fecha de publicacion: "; 
        getline(cin,fecha);
        cout<<"Ingrese el resumen: "; 
        getline(cin,resumen);
        cout<<endl;
        for(int i = 0; i < 100; i++){
            if(materiales[i] == nullptr){
                Libro* l = new Libro(nombre,isbn,autor,false,fecha,resumen);
                materiales[i] = l;
                return;
            }
        }
    } else if(tipoLibro == "Revista"){
        string edicion;
        string mes;
        cout<<"Ingrese el número de edición: "; cin >> edicion;
        cout<<"Ingrese el mes de publicación: "; cin >> mes;
        cout<<endl;
        for(int i = 0; i < 100; i++){
            if(materiales[i] == nullptr){
                Revista* r = new Revista(nombre,isbn,autor,false,edicion,mes);
                materiales[i] = r;
                return;
            }
        }
    }
}

/** @brief Muestra por pantalla los materiales
 * 
 *  Recorre la lista de materiales, imprimiendo su información, hasta que llega al primer nullptr y sale de la función 
 * 
 *  @param materiales Lista de 100 punteros de MaterialBibliografico
 */ 
void mostrarMateriales(MaterialBibliografico* materiales[100]){
    for (int i = 0; i<100; i++){
        if (materiales[i] == nullptr){break;}
        cout<<i+1<<".-\n"<<materiales[i]->mostrarInformacion()<<"\n"<<endl;
    }  
}


/** @brief Busca un material en la lista
 * 
 *  Busca un material en la lista por nombre o por autor ingresado por el usuario
 * 
 *  @param materiales lista de 100 punteros de MaterialBibliografico
 * 
 *  @return puntero al MaterialBibliografico se es encontrado, o nullptr si no
*/
MaterialBibliografico* buscarMaterial(MaterialBibliografico* materiales[100]){
    cout<<"Ingrese 1 para buscar por nombre\nIngrese 2 para buscar por autor"<<endl;
    string op;
    cin>>op;
    while(op != "1" && op != "2"){
        if (op != "1" && op != "2"){
            cout<<"ingrese una opción válida\n"<<endl;
        } 
        cout<<"Ingrese 1 para buscar por nombre\nIngrese 2 para buscar por autor"; cin>>op;   
        
    }
    if(op == "1"){
        string nombre;
        cout<<"Ingrese el nombre del material: ";
        cin.ignore();
        getline(cin,nombre);
        for (int i = 0; i < 100; i++){
            if(materiales[i] != nullptr && materiales[i]->getNombre() == nombre){
                return materiales[i];
            }
        }
    }
    if(op == "2"){
        string autor;
        cout<<"Ingrese el nombre del autor: ";
        cin.ignore();
        getline(cin,autor);
        for (int i = 0; i < 100; i++){
            if(materiales[i] != nullptr && materiales[i]->getAutor() == autor){
                return materiales[i];
            }
        }
    }
    return nullptr;
}

/** @brief Busca un usuario en la lista
 * 
 *  Busca un usuario por nombre o id
 *  Este metodo solo se usa al cargar usuarios
 * 
 *  @param listaUsuarios Lista de punteros de Usuario
 *  @param nombre Nombre del usuario a buscar
 *  @param id ID del usuario a buscar
 *  @return 
 */
Usuario* buscarUsuario(Usuario* listaUsuarios[100], string nombre, string id){
    for(int i = 0; i < 100; i++){
        
        if(listaUsuarios[i] != nullptr){
            if (listaUsuarios[i]->getNombre() == nombre && listaUsuarios[i]->getId() == id)
            {
                return listaUsuarios[i];
            }  
        }
    }
    return nullptr;
}

/** @brief Guarda los usuarios en un txt
 * 
 *  Escribe la informacion de los usuarios en usuarios.txt
 * 
 *  @param usuarios lista de usuarios a guardar
 * 
 */
void guardarUsuarios(Usuario* usuarios[100]){

    ofstream archivo("usuarios.txt");

    if(!archivo.is_open()) {
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }

    for(int i = 0; i < 100;i++){
        if(usuarios[i] != nullptr){
            archivo << usuarios[i]->getNombre() + "," + usuarios[i]->getId()<<endl;
        }
    }

    archivo.close();

    cout<<"Usuarios guardados exitosamente"<<endl;
}

/** @brief Carga la lista de usuarios desde un archivo
 *  
 *  Lee el archivo usuarios.txt, crea instancias de Usuario y las guarda en la lista
 * 
 *  @param listaUsuarios Lista de 100 punteros de usuarios
 * 
 */
void cargarUsuarios(Usuario* listaUsuarios[100]){

    ifstream archivo("usuarios.txt");

    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo usuarios"<<endl;
        return;
    }

    int i = 0;
    string linea;

    while(getline(archivo, linea) && i < 100){
        stringstream ss(linea);
        string nombre,id;
        getline(ss, nombre, ',');
        getline(ss, id, ',');

        listaUsuarios[i] = new Usuario(nombre,id);

        i++;
    }
}

/** @brief Guarda los materiales en un txt
 * 
 * Recorre la lista biblioteca, y guarda la información de los materiales en materiales.txt
 * 
 * @param biblioteca lista de materiales
 * 
 */ 
void guardarBiblioteca(MaterialBibliografico* biblioteca[100]){

    ofstream archivo("materiales.txt");

    if(!archivo.is_open()) {
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }    

    for(int i = 0; i < 100; i++){
        if(biblioteca[i] != nullptr){
            archivo << biblioteca[i]->getLine() << endl;
        }
    }

    archivo.close();

    cout<<"Biblioteca guardada exitosamente"<<endl;
}

/** @brief Carga materiales desde un archivo
 * 
 * Lee el archivo materiales.txt, guarda los materiales en la lista biblioteca, y busca si el usuario que tiene el material existe
 * 
 * @param biblioteca lista de materiales
 * @param listaUsuarios lista de usuarios
 * 
 */
void cargarBiblioteca(MaterialBibliografico* biblioteca[100], Usuario* listaUsuarios[100]){

    ifstream archivo("materiales.txt");

    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo materiales"<<endl;
        return;
    }

    int i = 0;
    string linea;

    while(getline(archivo, linea) && i < 100){
        stringstream ss(linea);
        string tipo,nombre,isbn,autor,prestado,edicion,aux1,aux2,nombreUsuario,idUsuario; 
        getline(ss, tipo, ',');
        getline(ss, nombre, ',');
        getline(ss, isbn, ',');
        getline(ss, autor, ',');
        getline(ss, prestado, ',');
        getline(ss, aux1, ',');
        getline(ss, aux2, ',');
        getline(ss, nombreUsuario, ',');
        getline(ss, idUsuario,',');
        
        bool prestadoBool = false;
        if(prestado == "true"){
            prestadoBool = true;
        }

        if(tipo == "Libro"){
            biblioteca[i] = new Libro(nombre,isbn,autor,prestadoBool,aux1,aux2);
        } else if(tipo == "Revista"){
            biblioteca[i] = new Revista(nombre,isbn,autor,prestadoBool,aux1,aux2);
        }

        Usuario* usuario = buscarUsuario(listaUsuarios,nombreUsuario,idUsuario);
        if(usuario != nullptr && usuario->prestarMaterial(biblioteca[i])){
            biblioteca[i]->setPrestado(true,usuario);
        }
        i++;
    }
    archivo.close();
    cout<<"Se cargó la biblioteca con exito"<<endl;
}

/** @brief Crea un usuario nuevo
 * 
 * Se solicita el nombre e id del usuario y lo agrega a la lista
 * 
 * @param listaUsuarios Lista donde se agrega al usuario
 */  
void crearUsuario(Usuario* listaUsuarios[100]){
    
    for(int i = 0; i < 100; i++){
        if(listaUsuarios[i] == nullptr){
            string nombre;
            string id;
            cout<<"Ingrese el nombre del usuario "; 
            cin.ignore();
            getline(cin,nombre);
            cout<<"Ingrese el id del usuario ";
            cin>>id;
            listaUsuarios[i] = new Usuario(nombre,id);
            return;
        }
        
    }
    cout<<"No se pudo agregar al usuario, ya que ya hay 100 usuarios registrados"<<endl;
}

/** @brief Busca un usuario por su nombre o id
 * 
 * Este metodo es para buscar a un usuario ingresado por el usuario
 * 
 * @param listaUsuarios lista de usuarios a buscar
 * @return Puntero del Usuario encontrado, o nullptr si no lo encuentra
 */  
Usuario* buscarUsuario(Usuario* listaUsuarios[100]){

    int op = 0;
    while(op != 1 && op != 2){
        cout<<"Ingrese 1 para buscar por nombre\nIngrese 2 para buscar por id\n"<<endl;
        cin.ignore();
        cin>>op;
        if (op != 1 && op != 2){
            cout<<"ingrese una opción válida"<<endl;
        }
    }
    if(op == 1){
        string nombre;
        cout<<"Ingrese el nombre del usuario: ";
        cin.ignore();
        getline(cin,nombre);
        for(int i = 0; i < 100; i++){
            if(listaUsuarios[i] != nullptr){
                if (listaUsuarios[i]->getNombre() == nombre){
                    return listaUsuarios[i];
                }
                
            }
        }
    }
    else{
        string id;
        cout<<"Ingrese el id del usuario: ";
        cin>>id;
        for(int i = 0; i < 100; i++){
            if(listaUsuarios[i] != nullptr){
                if (listaUsuarios[i]->getId() == id){
                    return listaUsuarios[i];
                }
                
            }
        }
    }
    return nullptr;
}



/** @brief Funcion principal del programa
 * 
 * Carga los usuarios y materiales, y permite al usuario agregar materiales, administrar usuarios, mostrar informacion y
 * buscar materiales. Al finalizar, guarda los cambios realizados en los txt respectivos.
 * 
 * @return 0 al finalizar correctamente
 * 
 */
int main() {
    Usuario* listaUsuarios[100] = {nullptr};
    cargarUsuarios(listaUsuarios);
    Usuario* usuarioActual = nullptr;
    Usuario* aux;
    MaterialBibliografico* biblioteca[100] = {nullptr};
    cargarBiblioteca(biblioteca,listaUsuarios);
    MaterialBibliografico* materialBuscar = nullptr;
    int opcion = 1;
    while (opcion != 0)
    {
        cout<< "Ingrese la acción a realizar\n 1.- Agregar material bibliografico\n 2.- Mostrar informacion de los materiales\n 3.- Buscar un material\n 4.- Prestar y devolver material\n 5.- Gestion de usuarios"<< endl;
        
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            
            agregarMaterial(biblioteca);
            break;

        case 2:
            mostrarMateriales(biblioteca);
            break;

        case 3:
            materialBuscar = buscarMaterial(biblioteca);
            if(materialBuscar != nullptr){
                cout<<"¡Se encontró el material! Aquí está su información: "<<endl;
                cout<<materialBuscar->mostrarInformacion()<<endl;
            }
            else{
                cout<<"No se encontró el material"<<endl;
                cout<<endl;
            }
            break;
        
        case 4:
            if(usuarioActual==nullptr){
                cout<<"Inicie sesion para pedir o devolver un material"<<endl;
            } else {

                int opPrestamo;
                cout<<"¿Desea pedir prestado (1) o devolver un material (2)?"<<endl;
                cin>>opPrestamo;
                
                while(opPrestamo != 1 && opPrestamo != 2) {
                    cout<<"Ingrese una opción válida"<<endl;
                    cin>>opPrestamo;
                }

                materialBuscar = buscarMaterial(biblioteca);
                if(materialBuscar == nullptr){
                    cout<<"El material ingresado no existe en la biblioteca"<<endl;
                    break;
                }

                if(opPrestamo == 1){
                    if(materialBuscar->isPrestado()){
                        cout<<"El material ya ha sido prestado al usuario "<<materialBuscar->getUsuario()->getNombre()<<endl;
                    }
                    else{
                        if(usuarioActual->prestarMaterial(materialBuscar)){
                            materialBuscar->setPrestado(true,usuarioActual);
                            cout<<"Se ha prestado el material "<<materialBuscar->getNombre()<<" al usuario "<<usuarioActual->getNombre()<<endl;
                        }

                    }
                }
                if(opPrestamo == 2) {
                    if(!materialBuscar->isPrestado()){
                        cout<<"El material no se ha prestado a nadie"<<endl;
                    }
                    else{
                        if(usuarioActual->devolverMaterial(materialBuscar)){
                            cout<<"Se ha devuelto el material "<<materialBuscar->getNombre()<<" por el usuario "<<usuarioActual->getNombre();
                            materialBuscar->setPrestado(false,usuarioActual);
                        }
                    }
                }
            }
            break;

        case 5: 
            int opcionUsuario = 1;
            while(opcionUsuario != 0){
                cout<<"Ingrese la acción a realizar\n"<<endl;
                cout<<" 1.- Crear usuario\n 2.- Cambiar usuario\n 3.- Buscar usuario (ver su información)\n 4.- Eliminar usuario\n 0.-Salir"<<endl;
                cin>>opcionUsuario;

                switch(opcionUsuario){
                    case 1:
                        crearUsuario(listaUsuarios);
                        break;
                    case 2:
                        aux = buscarUsuario(listaUsuarios);
                        if(aux != nullptr){
                            usuarioActual = aux;
                            cout<<"Se ha cambiado al usuario "<<usuarioActual->getNombre()<<endl;
                        } 
                        else{
                            cout<<"El usuario no existe en el sistema"<<endl;
                        }
                        break;
                    case 3:
                        aux = buscarUsuario(listaUsuarios);
                        if(aux != nullptr){
                            cout<<"\nMostrando la informacion del usuario:"<<endl;
                            cout<<"Nombre: "<<aux->getNombre()<<"\nID: "<<aux->getId()<<endl;
                            cout<<"Materiales prestados a "<<aux->getNombre()<<":\n"<<endl;
                            cout<<aux->mostrarMaterialesPrestados()<<endl;
                        }
                        else{
                            cout<<"El usuario no existe en el sistema"<<endl;
                        }
                        break;
                    case 4:
                        aux = buscarUsuario(listaUsuarios);
                        
                        if(aux != nullptr){
                            aux->borrar();
                            delete aux;

                        }
                        else{
                            cout<<"El usuario no existe"<<endl;
                        }
                        break;

                    default:
                        break;
                }
            }
                
        
        }
    }
    guardarBiblioteca(biblioteca);
    guardarUsuarios(listaUsuarios);
    for(int i = 0; i < 100; i++){
        delete biblioteca[i];
    }
    for(int i = 0; i < 100; i++){
        delete listaUsuarios[i];
    }
    return 0;
}