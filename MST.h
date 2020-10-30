/*
 Este progrma .h sirve para encontrar el MST de un grafo NO dirigido 
 contiene tres algoritmos (Prim , Krusckal con DFS , Kruscal con Union-Find)
 implemntado en c++.
Referencias:
[1] https://www.lawebdelprogramador.com/foros/Dev-C/707658-medir-tiempo-de-ejecucion.html
[2]https://www.tutorialspoint.com/cplusplus-program-to-implement-adjacency-matrix
[3]http://mauricioavilesc.blogspot.com/2015/08/matriz-dinamica-en-c.html

	Autora(a) : Ximena Hutchinson Quinto
*/
#include <iostream> // Para el manejo de datos cin y cout 
#include <fstream> //Para el manejo de archivos
#include <vector> //Para el manejo de vectores
#include <ctime>  //Para el manejo del tiempo de ejecución [1]
#define INF 9999999 //Para la representacion del Infinito
using namespace std;
unsigned t0, t1;  //Variables para medir el tiempo de ejecucion
vector<int> parent; //Vector para guardar los papás
class MST{	
	private: 
	vector<int> visited; //Vector que se ocupara para ver los nodos visitados
    vector <int> pesos; //Vector que se ocupara para guardar los pesos de las aristas
    bool flag; //Este bool solo pude ser true o false y se ocupara la deteccion de ciclos
    int nodes; // Variable que contiene el numero de nodos del grafo
    int **Grafo; // Inicializacion de una matriz dinamica [3]
    int **Grafo2;
	
	public:
	// Prim con key-value 
	/*Este metodo recibe el nombre del archivo que contiene	el grafo y regresa el MST con su costo total*/
	float prim(string archivo){
	t0=clock(); //Se pone al prinicpio para medir el tiempo de ejecucion
	int n , a, c , d, z ; // n-> no. nodos a->aristas
	int  suma; //Para el costo total del MST

	 	ifstream miArchivo(archivo);//Obtener el string del nombre del archivo que se desea abrir
		miArchivo >> n >> a;//En la primera linea del txt se encuentra el numero de nodos y de aristas 
							//que se guardaran en estas variables respectivamente
		int V = n;   //Paso el numero de nodos a la variable V 
		long  GrafoP [V][V]; // Declaro una Matriz de tamaño NodosxNodos , donde estara el Grafo[2]
	 // Inicializo todos los espacios de la matriz en cero*Esto se hace para que no se le meten valores basuara a la matriz
	     for(int i = 0; i < V; i++) {
	      for(int j = 0; j < V; j++) {
	         GrafoP[i][j]=0;
	      }
  		 }	 
		if (miArchivo.is_open())
		{
			for(int i = 0; i<a ; i++)  // Este for va desde 0 hasta el numero de aristas para leer los datos
									 //siguientes de archivo.txt
			{
				miArchivo >> c >> d>> z; // c-> nodo 1 , d -> nodo 2 , z -> peso
			    GrafoP[c][d] = z;  //Guardo los pesos de las aristas en las coordenas correspondientes 
			    GrafoP[d][c] = z; // a sus nodos , como es un grafo No dirigido tambien lo hago de nodo 2 a nodo 1 
	
			}
			miArchivo.close(); //Cerrar el archivo
		}
		else
		{
			cout<< "Error al abrir el archivo"<<endl;//Si el archivo no se encuentra en la misma o hay 
													 //Un error en el archivo se mostrara este mensaje
		}		
   /*Este parte comentada sirve para imprimir tu matriz si deseas
   para comprobar los valores que se ingresaron*/
  /* for(int i = 0; i < V; i++) {
      for(int j = 0; j < V; j++) {
         cout << GrafoP[i][j] << " ";
      }
      cout << endl;
   }*/
	int no_a= 0;  //Variable que va ayudar a controlar el numero de aristas encontrada	
  //Vector para el control de los nodos selecciondos
  //Seleccionado -> true , los inicializamos todos en false
  vector<bool> selected(V, false);  //Recordar que V contiene el numero de nodos del grafo
  //Aqui se establece en que nodo se desea empezar la búsqueda
  //empezaramos por el cero asi que lo haremos true para que ya esta visitado
  selected[0] = true; 
  int x;  //  numero fila 
  int y;  // numero columna

	/* Para cada vértice en el conjunto del selecciondo se encuentran todos los vértices adyacentes
    , se calcula el peso desde el vértice seleccionado si el vértice ya habia sido seleccionado
	 se descarta de lo contrario se elige otro vértice más cercano al vértice seleccionado al principio.*/
  while (no_a< V - 1) {    /*El numero de aristas de un MST siempre sera (V-1)*/
    int min = INF; //Key value a infinito 
    x = 0;
    y = 0;
    for (int i = 0; i < V; i++) { 
      if (selected[i]) { 
        for (int j = 0; j < V; j++) {
          if (!selected[j] && GrafoP[i][j]) {  // Que no este seleccionado y que si haya arista
            if (min > GrafoP[i][j]) {
              min = GrafoP[i][j]; //Ahora al key value se le pasa el numero que esta en el Grafo la posicion [i][j] 
              x = i;            
              y = j;
            }
          }
        }
      }
    }
    cout <<"("<< x << "," << y << "," << GrafoP[x][y] << ")"; //Se imprime la fila  la columna de la matriz para que ver de que nodo a que nodo 
    cout << endl;											 //tambien su peso , que es la interseccion
    selected[y] = true; //Ahora ese nodo es marcado como seleccionado
    no_a++; //Se aumenta uno al contador de las aristas
    suma = suma + GrafoP[x][y]; //Para ir sumando los pesos de las aristas seleccionadas 
    
  }
    t1 = clock(); //Para decir que aqui debe de parar de contar el tiempo de ejecucion
    double time = (double(t1-t0)/CLOCKS_PER_SEC); // [1]
    cout << "TIEMPO:" << time * 1000 << "ms" << endl;
    return (float)suma; //Regresar el costo total

	}
	//Metodos utilizamos para Union-Find
	//Encuentra el set del vertice p
	int Find(int p) 
		{ 
		  if( p == parent[p] ){ //Si estoy en la raiz, retorno la raiz
	        return p;                   
	     }
	    else return Find( parent[p] );    
		} 
	/*Union de i y j , regresa false si i y j ya estan en el mismo set*/
	void Union(int i, int j) 
		{ 
		    int a = Find(i); //Obtengo la raiz de la componente del vértice i
		    int b = Find(j);//Obtengo la raiz de la componente del vértice j
		    
		    parent[a] = b; //Mezclo ambos arboles , actualizando su padre de alguno de ellos como la raiz de otro
		}
	// Kruskal con Union-Find para detección de ciclos
	/*Este metodo recibe el nombre del archivo que contiene el grafo y regresa el MST con su costo total*/
	float kruskalUF(string archivo)
	{
	t0=clock();
    int n , aristas, c , d, z ; // n-> no. nodos a->aristas

	int costo = 0; // Para el costo total del MST

	 	ifstream miArchivo(archivo);
		miArchivo >> n >> aristas;
		int   V = n; //Paso el numero de nodos a la variable V 
		int  GrafoU [V][V]; // Declaro una Matriz de tamaño NodosxNodos , donde estara el Grafo[2]
		 // Inicializo todos los espacios de la matriz en cero
	     for(int i = 0; i < V; i++) {
	      for(int j = 0; j < V; j++) {
	         GrafoU[i][j]=0;
	      }
  		 }	  
		if (miArchivo.is_open())
		{
			for(int i = 0; i<aristas ; i++) // Este for va desde 0 hasta el numero de aristas para leer los datos
									        //siguientes de archivo.txt
			{
				miArchivo >> c >> d>> z;// c-> nodo 1 , d -> nodo 2 , z -> peso				
			    GrafoU[c][d] = z;//Guardo los pesos de las aristas en las coordenas correspondientes 
			    GrafoU[d][c] = z;// a sus nodos , como es no dirigido tambien lo hago de nodo 2 a nodo 1 

			}
			miArchivo.close(); //Cierro el archivo
		}
		else
		{
			cout<< "Error al abrir el archivo"<<endl;
		}				
  /*Este parte comentada sirve para imprimir tu matriz si deseas  para comprobar los valores que se ingresaron*/
  /*for(int i = 0; i < V; i++) {
      for(int j = 0; j < V; j++) {
         cout << GrafoU[i][j] << " ";
      }
      cout << endl;
   }*/
	parent.resize(V); 	//Inicializo el vector para ver a los papas de los nodos 
						//con eltamaño de nodos que hay en el grafo
	    //Este for le asigna el padre a los nodos , al principio
		// cada uno es su propio padre 
	    for (int i = 0; i < V; i++) {
	    	    parent[i] = i; 
	    	     
		}
		//Para que deje de correr el tiempo de ejecuccion
	    int no_aristas = 0;  //Para el control de las arists encontradas
	    while (no_aristas < V - 1) { /*El numero de aristas de un MST siempre sera (V-1)*/
	        int min = INF, a =0, b = 0; //Inicializamos variables que utilizaremos 
	        for ( int k = 0; k <V; k++) { //Estos for hacen que pases por todas los nodos de 
	            for (int l = 0; l < V; l++) { //la matriz 
	                if (Find(k) != Find(l)&& GrafoU[k][l] < min && GrafoU[k][l]!=0) { //Ve si los nodos no tienen el mismo padre en el metodo
	                	min = GrafoU[k][l]; 										//Find(p); tambien no entra a este if si el peso es cero 
	                    a = k; //pasa los valores de los nodos encontrados a		//por que eso significa que no hay arista
	                    b = l; //a y b para ver si se pueden usar dependiendo de lo que regrese el Union
	                   
	                } 
	            } 
	        } 
	    Union(a, b);  //Si esto regresa true se hace lo de abajo si no ,no 
	     
		 cout <<"("<< a << "," << b << "," <<min<< ")"; //Se imprime el nodo1 y el nodo2 y su peso
   			 cout << endl;
   			no_aristas++;//Se aumenta uno al contador de las aristas
       costo += min; //Llevar la sumatoria de costo final
	    }  
	    t1 = clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC); //[1]
        cout.precision(2);
        cout << "TIEMPO:" << time *100 << "ms" << endl;
        return (float)costo; //Regreso el costo total del MSt

}

	/*Detencion de ciclos por dfs , regresa true->si hay ciclo y false -> no ciclo
	-1 -> No visitados (Blanco)
	0 -> Siendo Visitados (Gris)
	1 -> Completamente visitados (Negro)
	Recibe el nodo a analizar y su padre*/
	void dfs(int s, int padre){ 
        if(visited[s] = -1){ //Hacer el nodo que entra como visitado
            visited[s] = 0;
        }
        for(int i = 0; i < nodes; i++){ 
            if(Grafo2[s][i] != 0 && i != padre){ //Si el peso no es cero y el nodo no es igual a papa
                if(visited[i] == -1){ //Si no ha sido visitado 
                    dfs(i,s); //llamo al dfs recursivamete 
                }
                if(visited[i] == 0){ //Si quieres analizar un nodo que esta siendo visitado
                    flag = true; //Si hay ciclos se regresa un true 
                }
            }
        }
        visited[s] = 1;// Hasta que se termina el proceso del for , maraco el nodo como completamente visitado
    }

	// Kruskal con DFS para detección de ciclos
	/*Este metodo recibe el nombre del archivo que contiene el grafo y regresa el MST con su costo total*/
	float kruskalDFS(string archivo){		
        int n , aristas, c , d, z ; //n-> nodos aristas->aristas
        int mincost = 0;//Par guardar el Costo total del MST
        ifstream miArchivo(archivo); //Leer la primera linea del txt donde se encuentra el numero de nodos y aristas
        miArchivo >> n >> aristas; 
        nodes = n;    //La variables nodes ahora tiene el valor de n
        pesos.resize(aristas); //Establecer el tamaño del vector de pesos como el numero de aristas 
		//Esteblacer el tamaño de mis matrices 
		Grafo= new int*[nodes];
		for(int i = 0;i <nodes; i++){
			Grafo[i] = new int[nodes];
		}
		Grafo2= new int*[nodes]; //El Grafo 2 es donde ire guardando el MST
		for(int f = 0;f <nodes; f++){
			Grafo2[f] = new int[nodes];
		}
		//Inicializar mis dos matrices en cero . Esto ayuda que no les entre algun valor basura
        for(int i = 0; i < nodes; i++) {  
            for(int j = 0; j < nodes; j++) {
                Grafo[i][j]=0;
                Grafo2[i][j]=0;
            }
        }          
        if (miArchivo.is_open())
        {
            for(int i = 0; i<aristas ; i++)  // Este for va desde 0 hasta el numero de aristas para leer los datos
									         //siguientes de archivo.txt
            {
                miArchivo >> c >> d>> z;  // c-> nodo 1 , d -> nodo 2 , z -> peso
                Grafo[c][d] = z;//Guardo los pesos de las aristas en las coordenas correspondientes 			
                Grafo[d][c] = z;// a sus nodos , como es un Grafo No dirigido tambien lo hago de nodo 2 a nodo 1
                if(Grafo[c][d]!=0){	 //Si el peso no es cero meto el peso al vector de pesos
                    pesos.at(i) = Grafo[c][d];
                }
            }
            miArchivo.close();//Ciero el archivo
        }
        else
        {
            cout<< "Error al abrir el archivo"<<endl; ////Si el archivo no se encuentra en la misma o hay un error en el archivo se mostrara este mensaje									
        }
        visited.resize(nodes);//Establecer ell tamaño del vector para los nodos visitados al de los nodos
      //Ordeno el vector de mis pesos de manera creciente usando BubbleSort y los guardo en el vector de pesos
        int temp;
        for(int i=1;i<aristas;++i){
            for(int j=0;j<(aristas-i);++j){
                if(pesos[j]>pesos[j+1])
                {
                    temp=pesos[j];
                    pesos[j]=pesos[j+1];
                    pesos[j+1]=temp;
                }
            }
        } 	
        int min = INF, a =0, b = 0; //Inicializo variables que se utilizaran dentro del while   
        for(int i = 0 ; i<aristas; i++){ //Este for es para que se pase por tadas los pesos de nuestro vector de pesos
            for (int j = 0; j < nodes; j++) {  //Marco todo los nodos como no visitados
                visited[j] = -1; 
            }
            for ( int k = 0; k <nodes; k++) { 
                for (int l = 0; l < nodes; l++) {
                    if (Grafo[k][l]!=0 &&  pesos.at(i)==Grafo[k][l]  ) { //Para que entre a este if que a y b tenga en valor de los nodos
                        a=k;											//el peso del grafo tiene que ser igual al primer peso de nuestro 
                        b=l;											//vector de pesos que esta ordenado de manera creciente
                    }
                } 
            }
      	 //   min = Grafo[a][b]; 
            Grafo2[a][b] = Grafo[a][b]; //Guardo los valores de los nodos en el Grafo2
            Grafo2[b][a] = Grafo[b][a];
            flag = false;
            dfs(a,a); //Mando los nodos a dfs para ver si generan ciclo en el MST
            if(!flag) //Entra a este if solo si NO se genera ciclo, lo tengo que negar por que es false cuando no hay ciclo
            {
                min = Grafo[a][b];//Se guaarda el valor del peso de la arista	  
                cout <<"("<< a << "," << b << "," << min << ")" << endl;	  
                mincost += min; //Llevo la sumatoria del costo Total
                Grafo[a][b] = 0;  //Hago el peso cero para que ya no tome en cuenta esa arista
                Grafo[b][a] = 0; //Tambien la coordenada al reves por ser un grafo no dirigido
            }
            else
            {
                Grafo2[a][b] = 0; //Si hay ciclo elimino esa arista de mi MST , que esta guardado el Grafo2
                Grafo2[b][a] = 0;	
            }
        }
     	t1 = clock(); //Para que termine el tiempo de ejecuccion 
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "TIEMPO:" << time * 1000 << "ms" << endl;
        cout.precision(3);
        return (float)mincost;  //Regresar el costo	
	}	
}; //Asi se tiene que cerrar una clase


