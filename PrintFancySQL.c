#include <stdlib.h>
#include <stdio.h>
#include <string.h>


size_t charCount(char *string){
    size_t len = 0;
    size_t i = 0;
    char byte = 0;
    while(string[i] != 0x00){
        byte = string[i];
        if(byte < 0){ // check for special char
            //printf("%c <-\n", string[i]);
            while(string[i] < 0)i++;
            // printf("i:%d\n", i);
        }else{i++;}
        len = len+1;
        // memcmp(byte&0x111111ff, 0xffffffff);
        // printf("%d = %ld\n", i, byte);
    }
    return len;
}


void PrintFancyTerminal(char ***txt, size_t n, size_t m){

    char len[m];
    memset(len, 0, sizeof(m));
    // printf("%s", *txt);
    char sum = 0;
    for (size_t i = 0; i < sizeof(txt); i++){
        // printf("%s\n", *(txt+i)); // in memoria esistono solo array monodimensionali
        // printf("%lu\n", charCount(*(txt+i)));
        
        if(charCount(*(txt+i)) > len[i % m]){ // memorizzo la lungheza della stringa più lunga delle colonne
            len[i % m] = charCount(*(txt+i));
        }
    }

    size_t slen = 0;

    // calcolo la lunghezza di tutta la una riga
    for (size_t i = 0; i < m; i++){   
            // printf("i:%d\n", i);
            // printf("%d ", len[i]);
            slen += len[i % m] + 4; // lunghezza stringhe + 4 char = due spazi e un + all'inizio(2 char)
        }
    slen += 3; // il + finale e il nuova riga

    char edge[slen]; // array for edge row
    strcpy(edge, "");

    for (size_t i = 0; i < m; i++){
        strcat(edge, "+");
        for (size_t j = 0; j < len[i % m]+2; j++){
            strcat(edge, "-");  
        }
    }
    strcat(edge, "+\n");

    char data[slen]; // array per memorizzare riga con dati

    // printf("%d\n", slen);
    slen += slen * 2 * n; // lunghezza della stringa finale =  riga + riga*2(edge + data) * numero di righe
    // printf("%d\n", slen);

    char result[slen]; // array stringa finale
    strcpy(result, "");

    for (size_t k = 0; k < n; k++){   
        strcpy(data, ""); // pulisco array data
        for (size_t i = k*m; i < (k+1)*m; i++){
            strcat(data, "| "); // aggiungo | e spazio ad inizio riga
            strcat(data, *(txt+i)); // copio la stringa con i dati
            // calcolo spazi = (len massima stringa x colonna +1 spazio) - lunghezza stringa valore attuale
            size_t spaces = len[i % m]+1 - charCount(*(txt+i));
            for (size_t j = 0; j < spaces; j++){
                strcat(data, " ");  
            }
        }
        strcat(data, "|\n"); // aggiungo ai dati l'ultimo |

        strcat(result, edge); // aggiungo al risultato il bordo
        strcat(result, data); // aggiungo al risultato i dati

    }
    strcat(result, edge); // aggiungo al risultato l'ultimo bordo
    printf("%s\n", result);
    
}


int main(int argc, char const *argv[])
{
    char *Text[2][4] = {{"Product Code", "Values","Description", "Note"},
    {"test","10,000","questa è una prova","questa è una nota"}};
    PrintFancyTerminal(&Text, 2, 4);
    // char test[] = "questa è una nota";
    // printf("len:%d\n", charCount(&test));
    return 0;
}
