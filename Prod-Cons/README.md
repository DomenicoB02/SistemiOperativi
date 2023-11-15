## Produttore-Consumatore singolo buffer

Nel problema produttore-consumatore, abbiamo due categorie di processi:
- **Produttori**, che scrivono un messaggio su di una risorsa condivisa
- **Consumatori**, che prelevano il messaggio dalla risorsa condivisa

Pur esistendo un problema (potenziale) di mutua esclusione nell'utilizzo del buffer comune, 
la soluzione impone un ordinamento nelle operazioni dei due processi. 
E' necessario che produttori e consumatori si scambino segnali per indicare rispettivamente l'avvenuto deposito e prelievo.
Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

