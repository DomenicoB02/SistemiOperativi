# Spiegazione di tutte le procedure 
## I semafori sono sempre implementati allo stesso modo

## [**procedure.h**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_CodaCircolare/procedure.h) e [**procedure.c**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_CodaCircolare/procedure.c)
#### **procedure.h**
Il problema ora non richiede solamente 1 produttore e 1 consumatore, ma chiede di *NUM_PRODUTTORI* e *NUM_CONSUMATORI*. 
Avremo quindi bisogno di oltre ai soliti due semafori *SPAZIO_DISPONIBILE* e *MESSAGGIO_DISPONIBILE* per gestire l'ingresso alla produzione e alla consumazione, anche di *MUTEX_P* e *MUTEX_C* che ci consentiranno di creare delle sezioni critiche all'interno delle nostre procedure e far si che i vari
produttori e consumatori non vadano in conflitto tra loro
La struct in questo preciso algorimo ha sia testa che coda in modo tale da poter simulare una coda circolare, e il buffer non sarà piu singolo ma sarà 
un array di intri di dimensione DIM_BUFFER
Poi ci sono le solite firme delle funzioni *produttore* e *consumatore*


#### **procedure.c**
Cominciamo con il produttore

Abbiamo la sezione principale che viene aperta e chiusa rispettivamente da ``Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);`` e da ``Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);`` e che quindi prima viene decrementato di uno *SPAZIO_DISPONIBILE* e in fine aumentato di uno *MESSAGGIO_DISPONIBILE* per dare la possibilità di entrare nel ciclo al consumatore

All'interno abbiamo ``Wait_Sem(ds_sem, MUTEX_P);`` e ``Signal_Sem(ds_sem, MUTEX_P);`` che costituiscono la sezione critica, in modo tale che quando verranno eseguiti piu produttori alla volta non vadano in conflitto e ognuno aspetterà il suo turno per entrare nella sezione quando questa sarà disponibile

Ora veniamo al motivo del perche si chiama coda circolare, nella sezione critica l'elemento di testa del buffer (che opera attraverso *p*) viene riempito con un elemento randomico

Il consumatore invece come funziona?

Abbiamo sempre il primo sbarramento dato da ``Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);`` e ``Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);`` che quindi verranno attivati quando *MESSAGGIO_DISPONIBILE* avrà valore 1 (poi decrementato a 0)e quindi effettivamente ci sarà un messaggio da poter leggere e termineranno quando il semaforo *SPAZIO_DISPONIBILE* sarà pari a 1 (incrementato da 0) cosi che, nel caso di una chiamata del produttore, possa cominciare a lavorare.

Qui la sezione critica è data da ``Wait_Sem(ds_sem, MUTEX_C);`` e da ``Signal_Sem(ds_sem, MUTEX_C);`` 
