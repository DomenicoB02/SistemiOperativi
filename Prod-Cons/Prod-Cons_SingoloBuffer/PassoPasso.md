# Spiegazione di tutte le procedure
## [**semafori.h**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_SingoloBuffer/semafori.h) e [**semafori.c**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_SingoloBuffer/semafori.c)
Implementazione solita dei semafori

## [procedure.h](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_SingoloBuffer/procedure.h) e [procedure.c](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_SingoloBuffer/procedure.c)
Partiamo dal .h

Introduciamo *SPAZIO_DISPONIBILE* e *MESSAGGIO_DISPONIBILE* che saranno i nomi dei nostri 
semafori e le firme delle funzioni *produttore* e *consumatore*

Invece per quanto riguarda il .c possiamo vedere lo sviluppo delle due funzioni
- [**produttore**] Dove la *Wait_Sem* iniziale decrementa di uno il semaforo *SPAZIO_DISPONIBILE* che era inizialmente uno, cosi da evitare che si attivi un altro produttore, e con la funzione *Signal_Sem* incremento di uno il semaforo *MESSAGGIO_DISPONIBILE* per darela possibilità al consumatore di cominciare il suo funzionamento una volta richiamato nel main. 
La procedura mostrata in questo esempio inserisce un valore randomico nel buffer, con ciò si conclude la produzione
- [**consumatore**] Qui la funzione *Wait_Sem* decrementa il semaforo *MESSAGGIO_DISPONIBILE* in modo tale da non far accedere ad altri consumatori allo stesso messaggio.
Qui non c'è una modifica del buffer (**p*) ma solo una stampa.
In fine abbiamo la funzione *Signal_Sem* che incrementa di uno il semaforo *SPAZIO_DISPONIBILE* in modo tale da rendere possibile di nuovo la produzione in caso venisse richiamata

## [**main.c**](https://github.com/PacxeN/SistemiOperativi/blob/Esercizi/Prod-Cons/Prod-Cons_SingoloBuffer/main.c)
Il main è dove avviene la gestione di tutto ciò che è stato detto prima.

Dal rigo 18 al rigo 22 abbiamo l'inizializzazione della chiave per la shm e della stessa shm attraverso il comando shmget, infine c'è un controllo per l'apertura della shm

Viene poi inizializzato un puntatore a *p* su cui verrà fatto l'attach alla shm

Dal rigo 30 al rigo 41 vengono inizializzati i semafori, fatta eccezione per il rigo 37 dove viene inizializzato **p* a 0 che potrebbe essere messo anche subito dopo la sua chiamata a rigo 26

La chiave si crea nello stesso modo nella quale viene creata la chiave per la shm, poi attraverso semget istanziamo lo spazio per due semafori con la stessa chiave e utilizziamo un ciclo per controllare la corretta apertura dei semafori

Attraverso semctl possiamo inizializzare sia *SPAZIO_DISPONIBILE* che *MESSAGGIO_DISPONIBILE*, rispettivamente al valore 1 e al valore 0

Dopo l'inizializzazione dei semafori, utilizziamo la funzione fork per splittare il codice in 2 processi in questo caso, un processo padre del quale non ci interessa e che quindi non verrà utilizzato, utilizzeremo solo il processo figlio che verra identificato attraverso il controllo ``if(pid==0)`` se volessi il processo padre mi basterebbe scrivere ``if(pid>0)``
all'interno della prima fork utilizzeremo il *consumatore* mentre nel secondo caso utilizzeremo il *produttore*, in entrambi i casi per uscire dai rispettivi if avremo bisogno della funzione ``exit(1)`` 

Finito di utilizzare sia l'uno che l'altro e dato che abbiamo solo un buffer utilizzeremo un semplice ``wait(NULL)`` per attendere la terminazione delle funzioni precedenti

In fine deallochiamo sia semafori che memorie condivise sempre utilizzando ``shmctl`` e ``semctl`` ma utilizzando flg diverse




