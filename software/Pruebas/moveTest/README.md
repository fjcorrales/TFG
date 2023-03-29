esteMoveTest se creo con la intención de saber como se le puede dar movimiento a un mesh además de investigar las posibles colisiones.

Lo que se encuentra en esta carpeta son los ficheros del propio nivel, sin embargo los importantes son los de move.h y move.cpp, estos son los que generan un componente de escena generico al cual se le ha ido añadiendo código para implementar la funcionalidad deseada.

La funcionalidad descrita tanto en el grafico de eventos como en el código es para hacer a una mesh moverse cuando el jugador se encuentra en un rango definido por una hitbox y que en caso de que este se salga de otro rango definido por una segunda hitbox se reinice el movimiento. 
