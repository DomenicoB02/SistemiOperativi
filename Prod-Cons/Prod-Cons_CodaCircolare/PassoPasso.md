# Spiegazione di tutte le procedure 
## I semafori sono sempre implementati allo stesso modo

## [**procedure.h**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_CodaCircolare/procedure.h) e [**procedure.c**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_CodaCircolare/procedure.c)
- **procedure.h**
Il problema ora non richiede solamente 1 produttore e 1 consumatore, ma chiede di *NUM_PRODUTTORI* e *NUM_CONSUMATORI*. 
Avremo quindi bisogno di oltre ai soliti due semafori *SPAZIO_DISPONIBILE* e *MESSAGGIO_DISPONIBILE* per gestire l'ingresso alla produzione e alla consumazione, anche di *MUTEX_P* e *MUTEX_C* che ci consentiranno di creare delle sezioni critiche all'interno delle nostre procedure e far si che i vari
produttori e consumatori non vadano in conflitto tra loro

La struct in questo preciso algorimo ha sia testa che coda in modo tale da poter simulare una coda circolare, e il buffer non sarà piu singolo ma sarà 
un array di intri di dimensione DIM_BUFFER

Poi ci sono le solite firme delle funzioni *produttore* e *consumatore*


- **procedure.c**

