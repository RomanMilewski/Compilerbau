#include "syntree.h"
#include <stdlib.h> 
#include <stdio.h>


syntree_nid newNode(syntree_t* self)
{
	(self->index)++;
	syntree_nid id = self->index;
	self->nodes = realloc(self->nodes, (id+1)*sizeof(node_t));
	if (self->nodes == NULL){
		fprintf(stderr, "Could not allocate memory!\n");
        exit(1);
	}
	
	return id;
}

int syntreeInit(syntree_t* self)
{
	self->index= 0;
	self->nodes = calloc(1, sizeof(node_t));
	if (self->nodes == NULL){
		fprintf(stderr, "Could not allocate memory!\n");
        return 1;
	}
	
	return 0;
}

void syntreeRelease(syntree_t* self)
{
	free(self->nodes);
}

syntree_nid syntreeNodeNumber(syntree_t* self, int number)
{
	syntree_nid id = newNode(self);
	(self->nodes[id]).type = NUMBERNODE;
	(self->nodes[id]).data.number = number;
	(self->nodes[id]).prevNode = 0;
	(self->nodes[id]).nextNode = 0;
	
	return id;
}

syntree_nid syntreeNodeTag(syntree_t* self, syntree_nid id)
{
	//Kann bereits ein beliebiges Element im Baum neu kapseln, sodass alle
	//Pointer aktualisiert werden

	syntree_nid leftNeighbor = (self->nodes[id]).prevNode;
	syntree_nid rightNeighbor = (self->nodes[id]).nextNode;

	syntree_nid idNew = newNode(self);
	(self->nodes[idNew]).type = TAGNODE;
	(self->nodes[idNew]).data.tag.nodeLeft = id;
	(self->nodes[idNew]).data.tag.nodeRight = id;
	(self->nodes[idNew]).prevNode = leftNeighbor;
	(self->nodes[idNew]).nextNode = rightNeighbor;
	
	if(leftNeighbor != 0) {(self->nodes[leftNeighbor]).nextNode = idNew;}
	if(rightNeighbor != 0) {(self->nodes[rightNeighbor]).prevNode = idNew;}
	(self->nodes[id]).prevNode = 0;
	(self->nodes[id]).nextNode = 0;
	
	return idNew;
}

syntree_nid syntreeNodePair(syntree_t* self, syntree_nid id1, syntree_nid id2)
{
	//Unter der Annahme, dass id1 und id2 direkt nebeneinander liegen
	
	syntree_nid leftNeighbor = (self->nodes[id1]).prevNode;
	syntree_nid rightNeighbor = (self->nodes[id2]).nextNode;
	
	syntree_nid idNew = newNode(self);
	(self->nodes[idNew]).type = TAGNODE;
	(self->nodes[idNew]).data.tag.nodeLeft = id1;
	(self->nodes[idNew]).data.tag.nodeRight = id2;
	(self->nodes[idNew]).prevNode = leftNeighbor;
	(self->nodes[idNew]).nextNode = rightNeighbor;
	
	if(leftNeighbor != 0) {(self->nodes[leftNeighbor]).nextNode = idNew;}
	if(rightNeighbor != 0) {(self->nodes[rightNeighbor]).prevNode = idNew;}
	(self->nodes[id1]).prevNode = 0;
	(self->nodes[id1]).nextNode = id2;
	(self->nodes[id2]).prevNode = id1;
	(self->nodes[id2]).nextNode = 0;
	
	return idNew;
	
}

syntree_nid syntreeNodeAppend(syntree_t* self, syntree_nid list, syntree_nid elem)
{
	//Unter der Annahme, dass elem nicht bereits aus dem Baum stammt und so
	//keine falschen Pointer bei alten Nachbarelementen bleiben
	
	syntree_nid rightElem = (self->nodes[list]).data.tag.nodeRight;
	
	(self->nodes[rightElem]).nextNode = elem;
	(self->nodes[elem]).prevNode = rightElem;
	(self->nodes[elem]).nextNode = 0;
	(self->nodes[list]).data.tag.nodeRight = elem;
	
	return list;
}

syntree_nid syntreeNodePrepend(syntree_t* self, syntree_nid elem, syntree_nid list)
{
	//Unter der Annahme, dass elem nicht bereits aus dem Baum stammt und so
	//keine falschen Pointer bei alten Nachbarelementen bleiben

	syntree_nid leftElem = (self->nodes[list]).data.tag.nodeLeft;
	
	(self->nodes[leftElem]).prevNode = elem;
	(self->nodes[elem]).nextNode = leftElem;
	(self->nodes[elem]).prevNode = 0;
	(self->nodes[list]).data.tag.nodeLeft = elem;
	
	return list;
}

void syntreePrint(const syntree_t* self, syntree_nid root)
{
	switch((self->nodes[root]).type){
		case NUMBERNODE:
			printf("(%d)", (self->nodes[root]).data.number);
			break;
		case TAGNODE:
			printf("{");
			syntree_nid leftElem = (self->nodes[root]).data.tag.nodeLeft;
			syntreePrint(self, leftElem);
			while((self->nodes[leftElem]).nextNode != 0){
				leftElem = (self->nodes[leftElem]).nextNode;
				syntreePrint(self, leftElem);
			}
			printf("}");
			break;
		default:
			fprintf(stderr, "Invalid type assigned to node!\n");
			exit(1);
	}
}


