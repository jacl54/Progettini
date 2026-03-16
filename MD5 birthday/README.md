Questo programma è un semplice bruteforce che prova ad usare la collisione di hash MD5 per ridurre il tempo necessario
a trovare la password corretta; è molto basilare e non è il metodo più efficiente per utilizzare il principio del
birthday attack (bisognerebbe avere un pool di hash maggiore per sfruttarne il principio).
 

# Birthday

Il principio del birthday ci dice che per avere la probabilità del 50% che due persone in un gruppo abbiano lo stesso compleanno
bastano ci basta avere un gruppo di 23 elementi; è un principio usabile con qualunque funzione di hash per via delle collisioni (dato che il numero di hashcodes possibili è minore del numero di stringhe possibili); non avendo un pool di 365 elementi ma di 
16^32 il costo è parecchio maggiore e con le successive funzioni di hash sviluppate il costo computazionale va solo ad incrementare. 