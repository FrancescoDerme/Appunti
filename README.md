# Appunti
Appunti è un programma per la correzione automatica di errori sintattici (e non semantici) generati da uno scanner OCR

### Esempio di input-output

-> Dai retta a me, non possono adebitarti nulla.<br/>
Dai retta a me, non possono addebitarti nulla.<br/>
(adebitarti -> addebitarti)

-> Sii tranquillo, tra poco aterreremo all’aereoporto.<br/>
Sii tranquillo, tra poco atterreremo all’aereoporto.<br/>
(aterreremo -> atterreremo)

-> L'aretratezza economica di inizio ottocento nocque all’Europa.<br/>
L'arretratezza economica di inizio ottocento nocque all’Europa. <br/>
(L'aretratezza -> L'arretratezza)

-> Non c’é motivo di chiedersu perchè tu non sia un buon’amico.<br/>
Non c’é motivo di chiedersi perchè tu non sia un buon’amico.<br/>
(chiedersu -> chiedersi)

-> Di fronte a casa mia non ci sono nè cigliegi, nè peschi.<br/>
Di fronte a casa mia non ci sono nè cigliari, nè peschi. <br/>
(cigliegi -> cigliari)

> Quest'ultima correzione è sbagliata. Per un umano è evidente che la correzione giusta sarebbe (cigliegi -> ciliegi) ma questo programma non è in grado di capire la semantica di una frase; tutto ciò che fa è capire se le parole utilizzate nel testo sono presenti nel database che fa da dizionario, e se non ci sono sostituirle con la prima parola trovata giudicata sufficientemente simile all'originale. 

Altri errori che il programma è in grado di rilevare e correggere con successo includono errori di battitura quali
<ul>
   <li>Mancata capitalizzazione all'inizo del testo o dopo un segno di punteggiatura forte</li>
  <li>Mancanza di un full stop al termine del testo</li>
  <li>Mancanza di uno spazio dopo un segno di punteggiatura forte o dopo due segni di punteggiatura deboli</li>
  <li>Errata capitalizzazione di un nome non proprio e non preceduto da segno di punteggiatura forte</li>
  <li>Etc</li>
</ul>
