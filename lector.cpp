#include <iostream>
#include <cstdio>
using namespace std;


struct Usuario {
	int num_cliente;
	char username[50];
	int DNI;
	char nombre[50];
	int clave;
	float saldo;

};



int mostrarUsuario(){
	FILE* archivo = fopen("USUARIO.dat","rb");
	if (archivo!=NULL){
		Usuario usuario;
		while(fread(&usuario, sizeof(Usuario),1,archivo)==1){
			cout<<"Usuario encontrado: "<<endl;
			cout<<"Numero de cliente: "<<usuario.num_cliente<<endl;
			cout<<"Nombre de usuario: "<<usuario.username<<endl;
			cout<<"DNI: "<<usuario.DNI<<endl;
			cout<<"Nombre: "<<usuario.nombre<<endl;
			cout<<"Clave de usuario: "<<usuario.clave<<endl;
			cout<<"Saldo: "<<usuario.saldo<<endl;
			cout<<endl;
		}
		fclose(archivo);
		
		
	}else{
		cout<<"No se pudo abrir el archivo para lectura."<<endl;
	}
	return 0;
	
}



int main(){
	mostrarUsuario();
	return 0;
}

