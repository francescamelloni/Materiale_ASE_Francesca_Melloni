/*

WAR: 
div.d f3,f1,f2
l.d  f1,v3(r1)
L’hazard che si presenta è un data hazard di tipo WAR (Write After Read). 
Questo hazard si verifica quando un’istruzione successiva (in questo caso la load) scrive su un registro (f1) che l’istruzione precedente (in questo caso la div) legge (f1). 
Il problema sarà che la prima istruzione andrà a leggere un operando sbagliato perché l’istruzione successiva avrà sovrascritto un nuovo valore (perché termina prima). 
Delle possibili soluzioni per questo hazard sono:
-	 l’introduzione di uno stallo della pipeline. L’istruzione di load viene ritardata, quindi messa in pausa, finchè la divisione ha terminato di leggere f1.
-	Si effettua il renaming dei registri, se il processore lo permette, così che la load venga fatta su un registro diverso da f1.
-	Se l’architettura lo permette, si può effettuare un’esecuzione fuori ordine e si potrebbe rinviare la load fino a che la div o tutte le istruzioni che usano f1 prima della load siano terminate. Questo caso non è sempre possibile.

********************************************************************************************************************

RAW:
add.d f4,f1,f2
div.d f4,f4,f3
L’hazard che si presenta è un data hazard di tipo RAW (Read After Write). 
Si verifica quando un’istruzione cerca di leggere un dato che non è ancora stato scritto da un'istruzione precedente. Quindi l’istruzione successiva (div) legge dal registro (f4) un valore non ancora aggiornato dall’istruzione precedente (add).
Possiamo risolvere questo hazard nei seguenti modi:
-	Introduzione di uno stallo. . L’istruzione della divisione viene ritardata, quindi messa in pausa, finchè l’addizione ha terminato il calcolo di f4.
-	Meccanismo di forwarding:  la divisione legge il valore di f4 direttamente dalla fine della fase di execute dell’addizione. Questa soluzione è possibile solo se il processore supporta tale meccanismo.
-	Se l’architettura lo permette, si può effettuare un’esecuzione fuori ordine .

********************************************************************************************************************

WAW:
Si verifica quando due istruzioni cercano di scrivere nello stesso registro, ma in ordine sbagliato a causa di esecuzione out-of-order.
-	Introduzione di uno stallo. . 
-	Si effettua il renaming dei registri, se il processore lo permette, così che la load venga fatta su un registro diverso da f1.
-	Se l’architettura lo permette, si può effettuare un’esecuzione fuori 

********************************************************************************************************************

HAZARD STRUTTURALE
Il tipo di hazard che potrebbe crearsi è di tipo strutturale visto che l’unità di divisione non è pipelined,ovvero non può eseguire più istruzioni in parallelo. 
Una possibile soluzione al problema è quella di adottare la tecnica dell’instruction rescheduling in modo da anticipare alcune istruzioni che
non dipendono dall’unità di divisione per evitare o diminuire gli stalli dovuti a questo hazard.

********************************************************************************************************************

ECCEZIONE
1) una trap viene caricata (fetch stage)nel ciclo successivo  
2) all'istruzione che ha generato la exception e quelle successive viene impedito di scrivere in 
memoria 
3) l'handler e ettua delle operazioni, prima tra tutte salva il PC dell'istruzione che ha generato 
l'exception. Alla fine può o terminare l'esecuzione o riprendere dall'istruzione 

********************************************************************************************************************

BRANCH DELAY SLOT
Viene eseguita una sola iterazione del programma, in quanto l’istruzione di Halt viene 
eseguita completamente e il programma si ferma alla fine della prima iterazione. Il nuovo 
tempo di esecuzione del programma è di xxx (compreso HALT) cicli di clock.

********************************************************************************************************************

CAMMINO FORWARDING
L’unità di forwarding riconosce l’hazard nella fase di decode e abilita il ‘bypass’ da una fase all’altra.

********************************************************************************************************************

ROB
contiene:
Instruction type: branch,store or register
destination: register number o memory adress
value: risultato dell'istruzione prima del commit
ready: stato dell'istruzione

********************************************************************************************************************

ARCHITETTURA HARDWARE
L'architettura Harvard fa riferimento all'esistenza di due memorie separate tra dati e codice.
1) una operazione di load o store 
2) durante la fase M della prima avviene la fase F della seconda
Vedeendo queste coppie di istruzione, fanno accesso alle due memorie separata. La prima fa accesso alla memoria di dati e la seconda alla memoria di 
codice, in questo modo non è necessario uno stallo del processore. 
********************************************************************************************************************





































































*/