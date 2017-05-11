
git commit -m "nomDuFichier" : permet d'ajouter une description

git log : Historique

l'option -a permet de mettre a jour les fichiers déjà existants dans l'index :   
git commit -a -m "Ajouté itinéraire dans checklist-vacances.md"

aller sur un commit de l'historique : git checkout SHADduCommit

aller a la branche principale (commit le plus récent) : git checkout master 

Fait l'inverse du commit precedent (attention nouveau commit dans l'historique) : git revert SHADuCommit

modifier le message de votre dernier commit (pas encore pushé sur l'origine) :

git commit --amend -m "Votre nouveau message"

pas de commit encore, annuler tous les changements pas encore commit : git reset --hard‌

git branch nouvelle-branche
git checkout nouvelle-branche
git checkout -b ma-branche  -> combinaison des deux precedentes 

qui a fait les modifs sur ce fichier : git blame nomdufichier.extension
renvoie directement les détails du commit recherché en saisissant le début de son sha  : git show 05b1233 

mettre en attentes des modifs sur une branche :git stash
recuperer les modifs : git stash pop 