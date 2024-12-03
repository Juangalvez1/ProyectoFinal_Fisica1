#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double MaxValue(double matriz[100][2], double max, int indice, int times, int pos){
    if(indice < times){
        if(indice == 0){
            max = matriz[indice][pos]; //Para el primer caso pone el valor max como el primer valor encontrado
            return MaxValue(matriz, max, indice + 1, times, pos);
        } else {
            if(matriz[indice][pos] > max && matriz[indice][pos] != INFINITY){ //Condicion para cambiar a el maximo omitiendo el infinito
                max = matriz[indice][pos];
                return MaxValue(matriz, max, indice + 1, times, pos); //continua evaluando
            } else {
                return MaxValue(matriz, max, indice + 1, times, pos); //continua evaluando
            }
        }
    } else {
        return max; //retorna el valor maximo encontrado
    }
}

double MinValue(double matriz[100][2], double min, int indice, int times, int pos){
    if(indice < times){
        if(indice == 0){
            min = matriz[indice][pos]; //Para el primer caso pone el valor max como el primer valor encontrado
            return MinValue(matriz, min, indice + 1, times, pos);
        } else {
            if(matriz[indice][pos] < min && matriz[indice][pos] != -INFINITY){ //Condicion para cambiar a el maximo omitiendo el menos infinito
                min = matriz[indice][pos];
                return MinValue(matriz, min, indice + 1, times, pos); //continua evaluando
            } else {
                return MinValue(matriz, min, indice + 1, times, pos); //continua evaluando
            }
        }
    } else {
        return min; //retorna el valor minimo encontrado
    }
}

void Graficar(char graphic[101][26], double result[100][2], int evaluations){
    int cordX = 0, cordY = 0; //Coordenadas usadas para graficar los ejes
    double indiceX = 0, indiceY = 0; //Indices utilizados para
    double longitudX = 0, longitudY = 0; //Distancia entre min y max de x y f(x)
    int ejeX = 0, ejeY = 0; //Indices para el ejex y ejey
    double minDominio = 0, maxDominio = 0; //Valores minimos y maximos del dominio (x)
    double minRange = 0, maxRange = 0; //Valores minimos y maximos del rango(f(x))

    minDominio = MinValue(result, 0, 0, evaluations, 0);
    maxDominio = MaxValue(result, 0, 0, evaluations, 0);
    minRange = MinValue(result, 0, 0, evaluations, 1);
    maxRange = MaxValue(result, 0, 0, evaluations, 1);

    longitudX = fabs(maxDominio - minDominio); //Calcula la distancia entre los valores extremos del dominio
    longitudY = fabs(maxRange - minRange); //Calcula la distancia entre los valores extremos del rango

    //Condiciones para graficar el eje asi este por fuera del dominio o rango
    if(minRange > 0) //Cuando todos los valores estan por encima del ejex
        minRange = 0;
    if(maxRange < 0) //Cuando todos los valores estan por debajo del ejex
        maxRange = 0;
    if(minDominio > 0){ //Cuando todos los valores estan a la der del ejey
        minDominio = 0;
        longitudX = maxDominio; //La distancia sera del valor maximo del dominio
    }
    if(maxDominio < 0) //Cuando todos los alores estan a la izq del ejey
        longitudX = fabs(minDominio); //La distancia sera el valor absoluto del valor minimo del dominio

    //printf("\nValues:\n%lf\n%lf\n%lf\n%lf\n", minDominio, maxDominio, minRange, maxRange);    

    //printf("\nLongitudes: %lf\t%lf\n", longitudX, longitudY);

    ejeX = (fabs(maxRange - 0) * 24.) / longitudY; //Calcula el indice en Y para guardar el ejex
    ejeY = (fabs(0 - minDominio) * 99.) / longitudX; //Calcula el indice en X para guardae el ejey
    
    //Condiciones para evitar problemas de ejes
    if (ejeX > 24)
        ejeX = 24;

    //Pone eje Y
    if(ejeY >= 0 && ejeY <= 99){ //Rango para imprimir el eje Y
        for(; cordX < 25; cordX += 1){
        graphic[ejeY][cordX] = 179; //Caracter Barra Vertical
        }
    }

    //Pone eje X
    if(ejeX >= 0 && ejeX <= 24){ //Rango para imprimir el ejeX
        for(; cordY < 100; cordY += 1){
            graphic[cordY][ejeX] = 196; //Caracter Barra Horizontal
        }
    }

    //printf("\nEjes: %i\t%i\n", ejeX, ejeY);

    graphic[ejeY][ejeX] = 197; //Pone el caracter del cruce entre los ejes

    for(int i = 0; i < evaluations; i += 1){ //Guarda los valores de x en el grafico
        int posx = (fabs(result[i][0] - minDominio) * 99.) / longitudX; //Calcula la posx en la que se empieza a guardar el valor del dominio
        char value[10] = "";
        sprintf(value, "%.2f", result[i][0]); //Guardamos el valor del dominio en una string para guardar char por char en la grafica
        if(i == evaluations - 1){ //Si es el ultimo valor que lo guarde en la pos -1 para que lo imprima completo
            posx -= 1;
        }
        for(int evaluations = 0; evaluations < 10; evaluations += 1){ //For par guardar el valor numerico en forma de caracteres en la grafica
            if (value[evaluations] != '\0'){
                graphic[posx + evaluations - 2][ejeX + 1] = value[evaluations];
            }
        }
    }

    for(int i = 0; i < evaluations; i += 1){ //Guarda los valores de y en el grafico
        double posy = 0;
        if(result[i][1] >= minRange && result[i][1] <= maxRange){ //Verificamos el valor a guardar para el ejey es parte del rango de la funcion
            posy = (fabs(result[i][1] - minRange) * 24.) / longitudY; //Calcula la posy en la que se empieza a guardar el valor del dominio
        } else { //de lo contrario avanzaremos un caso
            i += 1;
            posy = (fabs(result[i][1] - minRange) * 24.) / longitudY;
        }
        //printf("posy: %lf", posy);
        char value[10] = "";
        sprintf(value, "%.2f", result[i][1]); //Guardamos el valor del dominio en una string para guardar char por char en la grafica
        for(int evaluations = 0; evaluations < 10; evaluations += 1){ //For par guardar el valor numerico en forma de caracteres en la grafica
            if (value[evaluations] != '\0'){
                if(ejeY < 3){ //Caso que la grafica este a la izq
                    //printf("%c", value[evaluations]);
                    //printf(" %i\t%i\n", ejeY + 3 + evaluations, 24 - (int)round(posy));
                    graphic[ejeY + 3 + evaluations][24 - (int)round(posy)] = value[evaluations];
                } else if(ejeY > 96){ //Caso que la grafica esta en el medio
                    //printf("%c", value[evaluations]);
                    //printf(" %i\t%i\n", ejeY - 8 + evaluations, 24 - (int)round(posy));
                    graphic[ejeY - 5 + evaluations][24 - (int)round(posy)] = value[evaluations];
                } else { //Caso que la grafica este a la der
                    //printf("%c", value[evaluations]);
                    //printf(" %i\t%i\n", ejeY - 3 + evaluations, 24 - (int)round(posy));
                    graphic[ejeY - 3 + evaluations][24 - (int)round(posy)] = value[evaluations];
                }
            }
        }
    }
    
    //Guarda en el arreglo de 100x25 las posiciones de las x de la funcion a graficar escalando los ejes
    for(int count = 0; count < evaluations ; count += 1){
        indiceY = round((fabs(maxRange - result[count][1]) * 24.) / longitudY); //Calcula el indice en y para este valor de la funcion
        //printf("\nIndice Y: %lf\t", indiceY);

        indiceX = (fabs(result[count][0] - minDominio) * 99.) / longitudX; //Calcula el indice en x para este valor de la funcion
        //printf("Indice X: %lf", indiceX);

        if(isinf(result[count][1])){ //Verificamos si el valor del punto a mostrar es inf
            NULL; //No se muestra
        } else {
            graphic[(int)indiceX][(int)indiceY] = 'x';
        }
    }
    printf("\n");
    for(int i = 0; i < 26; i += 1){ //For para mostrar la grafica
        for(int evaluations = 0; evaluations < 101; evaluations += 1){
            printf("%c", graphic[evaluations][i]);
        }
        printf("\n");
    }
    
    printf("\n");
}
// x = 2 * root(h*y)
//x distancia horizontal    h altura del agua sobre el agujero  y altura del agujero
int main(){
    int agujeros = 0;
    float decremento = 0, alturaBotella = 0;
    double resultados[100][2] = {{0}};
    char grafica[101][26] = {{'\0'}};

    printf("Buenos dias\nEste programa calcula y grafica la distancia a la que llega un chorro de agua al salir por un agujero en una botella\nIngrese la cantidad de agujeros de la botella: ");
    scanf("%i", &agujeros);

    printf("Ingrese cuanto disminuye el nivel del agua en cada medicion de cada agujero (metros): ");
    scanf("%f", &decremento);

    printf("Ingrese la altura de la botella (metros): ");
    scanf("%f", &alturaBotella);

    for(int i = 0; i < agujeros; i++){
        float alturaAgujero = 0, alturaAgua = 0;
        printf("\nAgujero %i\n", i + 1);
        printf("\nIngrese la altura del agujero desde la base de la botella (metros): ");
        scanf("%f", &alturaAgujero);

        printf("Ingrese la altura del nivel del agua por encima del agujero (metros): ");
        scanf("%f", &alturaAgua);

        int evaluations = 0;
        for(; alturaAgua - (evaluations * decremento) > 0; evaluations++){
            float distanciaX = 2. * sqrt(alturaAgujero * (alturaAgua - (evaluations * decremento)));
            resultados[evaluations][0] = alturaAgua - (evaluations * decremento);
            resultados[evaluations][1] = distanciaX;
        }

        memset(grafica, 32, sizeof(grafica));

        printf("\nDistancias en X (metros)\n");
        Graficar(grafica, resultados, evaluations);

        printf("%-80sAltura del agua (metros)\n", "");
    }

}