#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

const int MAX_USUARIOS = 100; 
//tamaño maximo del arreglo de usuarios (prueba)


struct Usuario {
	int num_cliente;
	char username[50];
	int DNI;
	char nombre[50];
	int clave;
	float saldo;

};


Usuario usuarios [MAX_USUARIOS]; //arreglo  para almacenarlos
int numUsuarios = 0; //inicializador de cantidad de usuarios


//funcion para ver si se repite DNI y/o username 
bool repetido(int DNI, const char* username) {
    for (int i = 0; i < numUsuarios; ++i) {
        if (usuarios[i].DNI == DNI || strcmp(usuarios[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}



Usuario Registro_usuario(){
//funcion registrar usuario ==> va a llamar a la funcion de control DNI y/o username
	Usuario usuario;
	
	cin.ignore();
	cout<<"Ingrese su nombre: ";
	cin.getline(usuario.nombre,50);
	
	
	cout<<"Ingrese su DNI:";
	cin>>usuario.DNI;
	
	cin.ignore();
	cout<<"Ingrese el username que va a utilizar:"<<endl;
	cin.getline(usuario.username,50);
	
	
	cout<<"Ingrese su clave: ";
	cin>>usuario.clave;
	cin.ignore();
	
	
	//ahora verifico la repeticion
	if(repetido(usuario.DNI, usuario.username)){
		cout<<"El DNI o el username ya estan registrados."<<endl;
		usuario.num_cliente = -1; //no se registra
		return usuario;
	}


	if (numUsuarios < MAX_USUARIOS) {
        usuario.num_cliente = numUsuarios + 1; 
        usuario.saldo = 10000; // inicializaa saldo en 10,000
        usuarios[numUsuarios++] = usuario; // agrega el usuario y actualiza el contador
    } else {
        cout << "Capacidad máxima de usuarios alcanzada." << endl;
        usuario.num_cliente = -1; // no agrega al usuario porque se alcanza el maximo
    }
	
	return usuario;
}





int main() {
    const char* archivo = "usuario.dat";

	//leo el archivo
    FILE* arch_usuario = fopen(archivo, "rb");
    if (arch_usuario) {
        while (fread(&usuarios[numUsuarios], sizeof(Usuario), 1, arch_usuario) == 1) {
            numUsuarios++;
        }
        fclose(arch_usuario);
    }


    cout << "Bienvenido al apartado de carga de cliente." << endl;
    cout << endl;
    string cargar_cliente = "si";

    while (cargar_cliente != "no") {
        Usuario usuario = Registro_usuario();
        
        if (usuario.num_cliente != -1) { // agrega cuando se cumple
            // solo añade de 1 en 1 (append), pero puedo agregar varios
            arch_usuario = fopen(archivo, "ab");
            if (!arch_usuario) {
                cerr << "No se pudo abrir el archivo para escritura." << endl;
                return 1;
            }
            
            fwrite(&usuario, sizeof(Usuario), 1, arch_usuario);
            fclose(arch_usuario);
            cout << "Usuario registrado exitosamente." << endl;
        }

        cout << "¿Desea cargar otro cliente? (si/no): ";
        getline(cin, cargar_cliente);
    }

    cout << endl;
    cout << "La carga del archivo fue exitosa." << endl;

    return 0;
}
