#ifndef SYNTREE_H_INCLUDED
#define SYNTREE_H_INCLUDED

/* *** structures *********************************************************** */

/**Kurzbeschreibung:
 * syntree_t verwaltet seine Knoten in einem Array, das mit syntree_nid 
 * indiziert werden kann.
 * node_t kann sowohl Zahlenknoten als auch Containerknoten sein.
 * Ein Containerknoten kennt mit tag_t den rechtesten und linkesten Knoten
 * seines Inhalts.
 */

enum nodetype {NUMBERNODE, TAGNODE};

typedef int syntree_nid;

typedef struct
{
	syntree_nid nodeLeft;
	syntree_nid nodeRight;
} tag_t;

typedef struct
{
	enum nodetype type;
	union content
	{
		int number;
		tag_t tag;
	} data;
	syntree_nid prevNode;
	syntree_nid nextNode;
} node_t;

/**@brief Struktur des abstrakten Syntaxbaumes.
 */
typedef struct
{
	syntree_nid index;
    node_t* nodes;
} syntree_t;

/* *** interface ************************************************************ */

/**@brief Initialisiert einen neuen Syntaxbaum.
 * @param self  der zu initialisierende Syntaxbaum
 * @return 0, falls keine Fehler bei der Initialisierung aufgetreten sind,
 *      != 0 ansonsten
 */
extern int
syntreeInit(syntree_t* self);

/**@brief Gibt den Syntaxbaum und alle assoziierten Strukturen frei.
 * @param self  der freizugebende Syntaxbaum
 */
extern void
syntreeRelease(syntree_t* self);

/**@brief Erstellt einen neuen Knoten mit einem Zahlenwert als Inhalt.
 * @param self    der Syntaxbaum
 * @param number  die Zahl
 * @return ID des neu erstellten Knoten
 */
extern syntree_nid
syntreeNodeNumber(syntree_t* self, int number);

/**@brief Kapselt einen Knoten innerhalb eines anderen Knotens.
 * @param self  der Syntaxbaum
 * @param id    der zu kapselnde Knoten
 * @return ID des neu erstellten Knoten
 */
extern syntree_nid
syntreeNodeTag(syntree_t* self, syntree_nid id);

/**@brief Kapselt zwei Knoten innerhalb eines Knoten.
 * @param self  der Syntaxbaum
 * @param id1   erster Knoten
 * @param id2   zweiter Knoten
 * @return ID des neu erstellten Knoten
 */
extern syntree_nid
syntreeNodePair(syntree_t* self, syntree_nid id1, syntree_nid id2);

/**@brief Hängt einen Knoten an das Ende eines Listenknotens.
 * @param self  der Syntaxbaum
 * @param list  Listenknoten
 * @param elem  anzuhängender Knoten
 * @return ID des Listenknoten
 */
extern syntree_nid
syntreeNodeAppend(syntree_t* self, syntree_nid list, syntree_nid elem);

/**@brief Hängt einen Knoten an den Anfang eines Listenknotens.
 * @param self  der Syntaxbaum
 * @param elem  anzuhängender Knoten
 * @param list  Listenknoten
 * @return ID des Listenknoten
 */
extern syntree_nid
syntreeNodePrepend(syntree_t* self, syntree_nid elem, syntree_nid list);

/**@brief Gibt alle Zahlenknoten rekursiv (depth-first) aus.
 * @param self  der Syntaxbaum
 * @param root  der Wurzelknoten
 */
extern void
syntreePrint(const syntree_t* self, syntree_nid root);

#endif /* SYNTREE_H_INCLUDED */
