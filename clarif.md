## TYPES DE NOTE 	

* **note** : *identificateur*, *titre*, *date_creation*, *date_derniere_modif*, *archive* (booléen).
* les classes **article**, **tache** , **image**, **audio**, **video** dérivent de la classe **note**

* **article** : **text**
* **image** : *description*, *fichier image*
* **audio** : *description*, *fichier image*
* **video** : *description*, *fichier image*

* **tache** : *action* (string), *priorite* (int) optionnelle, *date_echeance* optionnelle, *statut("en attente","en cours", "terminée")
	*  Une tache est initialement en attente

## GESTION DES DIFFERENTES VERSIONS

* A chaque édition d'une note, la version précédente est sauvegardée dans un historique
* il est possible de restaurer une ancienne version comme version actuelle de la note
* utilisation du Design Pattern **Memento**

## RELATION ENTRE NOTES

* **relation** : *titre*, *description*, *couple_note* (tableau)
* il est possible de *créer*, *enrichir et *supprimer* une relation
* Chaque couple peut être caractérisé par un label, et peut être édité
* Une relation est par défaut orientée, **(x,y)** (relation de la note x vers la note y)
* L'utilisateur peut créer des relations non-orientées
* Une relation est seulement définit entre les deux dernières versions des notes
* L'application peut visualiser une relation
* L'application peut afficher l'ensemble des **ascendants/descendants** d'une note qui est en relation avec d'autres notes
	
	* Relation **REFERENCE**
		* orientée 
		*  \ref{idy}

## SUPPRESSION NOTE

* la suppression d'une note entraîne la suppression de tous les couples de relation dans lesquels elle est engagée
* Le point précédent ne concerne pas la relation **REFERENCE**

	* ARCHIVES
		* Une note référencée ne peut être supprimée, elle est archivée (**édition impossible**)
		* Lorsque une note est archivée, le booléen *archive* passe à "non"
		* Une note archivée n'étant engagée dans une aucune relation peut être supprimée
		* Si un ensemble de note archivées se font uniquement référence entre-elles, alors l'utilisateur peut les supprimer
		* l'application demande à l'utilisateur pour les deux points précédents s'il veut supprimer les notes archivées

	* CORBEILLE 	
		* Une note supprimée est d'abord mise dans une corbeille
		* Les notes notes dans la corbeille peuvent être restaurées
		* L'utilisateur peut vider la corbeille et supprimer de manière définitive les éléments qui y sont
		* A chaque sortie d'application, l'application propose à l'utilisateur de vider la corbeille
		* Ce vidage peut être effectué par défaut à chaque sortie d'application via les paramètres

## ELEMENTS D'INTERFACE

* vue principale :

	* **partie gauche** :
		 * affichage des **notes actives**
		 * affichage affichage ergonomique des **tâches** (en fonction des priorités et dates échues)
		 * affichage *discret* des notes **archivées**
	 
	* **partie centrale** :
		* affiche une note particulière
		
	* **partie droite**  (optionnelle) :
		* affichage de l'**arborescence des ascendants et des descendants** de la note en partie centrale
		
* vue secondaire :
	
	* dédiée à la gestion et visualisation de chacune des relations
	
## SAUVEGARDE DU CONTEXTE

* Tous les paramètres et l'état de l'application lors de la dernière exécution sont récupérés 

## FONCTIONS ANNULER ET RETABLIR 

* **annuler** : *Ctrl+Z*
* **rétablir** : *Ctrl+Y*

## ENSEMBLE DES DESIGN PATERNEL A EXPLOTIER POTENTIELLEMENT 

* **decorator, factory, abstract factory, builder, bridge, composite, iterator, template method, adapter, visitor, strategy, facade, memento**