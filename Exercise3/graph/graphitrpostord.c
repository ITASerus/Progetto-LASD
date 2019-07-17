
#include "graphitrpostord.h"

#include "../stack/vec/stackvec.h"
#include "../adt/ptr/adtptr.h"

/* ************************************************************************** */

void* graphPostOrderIteratorConstruct(void* type, void* graph) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphPostOrderIterator*)malloc(sizeof(GraphPostOrderIterator));

    GraphPostOrderIterator* iter = iterator->iterator;
    GraphObject* graphObject = (GraphObject*)graph;

    // Assegno il grafo, alloco i colori e li inizializzo
    iter->graph = graphObject;

    iter->support = (SupportPost*)malloc(sizeof(SupportPost) * graphObject->numVertex); //TODO: Mettere -1?
    ITRObject* vertexIterator = graphVertices(graphObject);
    for(int i = 0; i < graphObject->numVertex; i++) {
        iter->support[i].name = ((Vertex*)itrElement(vertexIterator))->name;
        iter->support[i].color = 'b';

        itrSuccessor(vertexIterator);
    }
    itrDestruct(vertexIterator);

    StackType* stackType = ConstructStackVecType();
    iter->stackVertices = stkConstruct(stackType);
    iter->stackAdjacent = stkConstruct(stackType);
    iter->stackIndexes = stkConstruct(stackType);
    iter->ptrType = ConstructPointerDataType();
    iter->verticesIterator = graphVertices(graphObject);

    DataObject* data = adtConstruct(iter->ptrType);

    // Richiamo l'iteratore per prendere il primo vertice
    if(!itrTerminated(iter->verticesIterator)) {
        Vertex* vertex = itrElement(iter->verticesIterator);
        iter->indexVertices = 0;

        iter->currentVertex = vertex;
        iter->support[iter->indexVertices].color = 'g';

        itrSuccessor(iter->verticesIterator); //??

        //Costruisco l'iteratore dei suoi adiacenti
        iter->currentAdjIterator = graphVertexEdges(iter->graph, iter->currentVertex->name);
        while(!itrTerminated(iter->currentAdjIterator)) {
            Vertex* adjVertex = itrElement(iter->currentAdjIterator);
            int adjIndex = 0;
            while(iter->support[adjIndex].name != adjVertex->name) {
                adjIndex++;
            }

            itrSuccessor(iter->currentAdjIterator); //TODO ??

            // Se il vertice è bianco continuo con la discesa
            if(iter->support[adjIndex].color == 'b') {
                // Salvo gli stati nello stack e continuo la discesa
                adtSetValue(data, &adjIndex); //TODO: ??
                stkPush(iter->stackIndexes, data);
                adtSetValue(data, iter->currentVertex);
                stkPush(iter->stackVertices, data);
                adtSetValue(data, iter->currentAdjIterator);
                stkPush(iter->stackAdjacent, data);

                // Il vertice bianco diventa il nuovo vertice corrente
                iter->currentVertex = adjVertex;
                iter->support[adjIndex].color = 'g';

                // Il nuovo iteratore degli adiacenti è relativo a questo vertice bianco
                iter->currentAdjIterator = graphVertexEdges(iter->graph, adjVertex->name);
            }
        }
        itrDestruct(iter->currentAdjIterator);
    }
    else {
        iter->currentVertex = NULL;
    }

    adtDestruct(data);

    return iterator;
}

void graphPostOrderIteratorDestruct(void* iterator) {
    GraphPostOrderIterator* iter = (GraphPostOrderIterator*) iterator;
    StackType* stackType = iter->stackVertices->type;

    // Distruggo l'iteratore ed il suo tipo
    itrDestruct(iter->verticesIterator);

    stkClear(iter->stackVertices);
    stkClear(iter->stackAdjacent);
    stkClear(iter->stackIndexes);
    stkDestruct(iter->stackIndexes);
    stkDestruct(iter->stackVertices);
    stkDestruct(iter->stackAdjacent);
    DestructStackVecType(stackType);
    DestructPointerDataType(iter->ptrType);
    free(iter->support);
    free(iter);
}

bool graphPostOrderIteratorTerminated(void* iterator) {
    // Ritorno true solo se non ho un corrente
    return ((GraphPostOrderIterator*) iterator)->currentVertex == NULL;
}

void* graphPostOrderIteratorElement(void* iterator) {
    return ((GraphPostOrderIterator*) iterator)->currentVertex;
}

void graphPostOrderIteratorSuccessor(void* iterator) {
    GraphPostOrderIterator* iter = (GraphPostOrderIterator*) iterator;
    DataObject* dataptr;
    DataObject* data = adtConstruct(iter->ptrType);

    // Se lo stack è vuoto non si può risalire e si setta itr->curr a null per forzare l'uscita
    if(!stkEmpty(iter->stackVertices)) {

        // Prendo dallo stack i nuovi elementi correnti e faccio la ricerca dei prossimi
        dataptr = stkTopNPop(iter->stackVertices);
        iter->currentVertex = adtGetValue(dataptr);
        adtDestruct(dataptr);

        dataptr = stkTopNPop(iter->stackIndexes);
        iter->indexVertices = (int)adtGetValue(dataptr); //TODO: ??
        adtDestruct(dataptr);


        dataptr = stkTopNPop(iter->stackAdjacent);
        iter->currentAdjIterator = adtGetValue(dataptr);
        adtDestruct(dataptr);

        //terminerà quando troverà un elemento senza adiacenti (o senza adiacenti bianchi)
        while(!itrTerminated(iter->currentAdjIterator)) {
            Vertex* adjVertex = itrElement(iter->currentAdjIterator);
            int adjIndex = 0;
            while(iter->support[adjIndex].name != adjVertex->name) {
                adjIndex++;
            }

            itrSuccessor(iter->currentAdjIterator);

            if(iter->support[adjIndex].color == 'b') {
                // Salvo gli stati nello stack e continuo la discesa
                adtSetValue(data, &iter->indexVertices); //TODO: ??
                stkPush(iter->stackIndexes, data);
                adtSetValue(data, iter->currentVertex);
                stkPush(iter->stackVertices, data);
                adtSetValue(data, iter->currentAdjIterator);
                stkPush(iter->stackAdjacent, data);

                // Il vertice bianco diventa il nuovo vertice corrente
                iter->currentVertex = adjVertex;
                iter->support[adjIndex].color = 'g';

                // Il nuovo iteratore degli adiacenti è relativo a questo vertice bianco
                iter->currentAdjIterator = graphVertexEdges(iter->graph, adjVertex->name);
            }
        }
        itrDestruct(iter->currentAdjIterator);
    }
    else {
        iter->currentVertex = NULL;
    }

    if(!iter->currentVertex) {
        // Controllo se ci sono altri vertici bianchi da cui far partire la dfs
        while(!itrTerminated(iter->verticesIterator) && !iter->currentVertex) {
            Vertex* nextVertex = itrElement(iter->currentAdjIterator);
            int nextIndex = 0;
            while(iter->support[nextIndex].name != nextVertex->name) {
                nextIndex++;
            }

            if(iter->support[nextIndex].color == 'b') {
                // Se trovo un vertice bianco sarà il prossimo vertice della dfs
                iter->currentVertex = nextVertex;
                iter->indexVertices = nextIndex;

                iter->support[iter->indexVertices].color = 'g';
                iter->currentAdjIterator = graphVertexEdges(iter->graph, nextVertex->name);

                //terminerà quando troverà un elemento senza adiacenti (o senza adiacenti bianchi)
                while(!itrTerminated(iter->currentAdjIterator)) {
                    Vertex* innerVertex = itrElement(iter->currentAdjIterator);
                    int innerIndex = 0;
                    while(iter->support[innerIndex].name != innerVertex->name) {
                        innerIndex++;
                    }

                    itrSuccessor(iter->currentAdjIterator);

                    if(iter->support[innerIndex].color == 'b') {
                        // Salvo gli stati nello stack e continuo la discesa
                        adtSetValue(data, &iter->indexVertices); //TODO: ??
                        stkPush(iter->stackIndexes, data);
                        adtSetValue(data, iter->currentVertex);
                        stkPush(iter->stackVertices, data);

                        adtSetValue(data, iter->currentAdjIterator);
                        stkPush(iter->stackAdjacent, data);

                        // Il vertice bianco diventa il nuovo vertice corrente
                        iter->currentVertex = innerVertex;
                        iter->indexVertices = innerIndex;
                        iter->support[innerIndex].color = 'g';

                        // Il nuovo iteratore degli adiacenti è relativo a questo vertice bianco
                        iter->currentAdjIterator = graphVertexEdges(iter->graph, innerVertex->name);
                    }
                }
                itrDestruct(iter->currentAdjIterator);
            }

            itrSuccessor(iter->verticesIterator);
        }
    }

    adtDestruct(data);
}


ITRType* ConstructGraphPostOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = graphPostOrderIteratorConstruct;
    type->destruct = graphPostOrderIteratorDestruct;

    type->terminated = graphPostOrderIteratorTerminated;

    type->getElement = graphPostOrderIteratorElement;

    type->successor = graphPostOrderIteratorSuccessor;

    return type;
}

void DestructGraphPostOrderIterator(ITRType* type) {
    free(type);
}