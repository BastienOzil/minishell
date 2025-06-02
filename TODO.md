# ✅ Liste des tâches - Projet Minishell

## 📅 Semaine 1 : Organisation et Conception

- [x] Lire et résumer le sujet
- [x] Créer le dépôt GitHub (public ou privé)
- [x] Créer une page Notion ou un fichier pour le glossaire
- [x] Lister les fonctions système autorisées
- [x] Planifier les fichiers à créer (lexer.c, parser.c, etc.)
- [x] Créer un diagramme de structure du projet
- [x] Répartir les rôles dans le binôme
- [x] Ajouter le README de base

## 🔧 Semaine 2 : Parsing

- [x] Implémenter la boucle de prompt avec readline
- [x] Écrire le lexer (tokenisation de la commande)
- [x] Écrire le parser (construction des commandes à exécuter)
- [ ] Gérer les quotes simples et doubles
- [ ] Gérer les variables d'environnement ($, $?)
- [ ] Commencer à stocker les redirections

## 🧪 Semaine 3 : Exécution et Builtins

- [ ] Implémenter fork + execve
- [ ] Gérer les redirections `<`, `>`, `>>`, `<<` (heredoc) (!!PENSER A GERER PLUSIEURS HEREDOC)
- [ ] Implémenter les pipes `|`
- [ ] Implémenter les builtins : echo, cd, pwd, export, unset, env, exit
- [ ] Gérer les erreurs (commandes inconnues, fichiers manquants, etc.)
- [ ] Implémenter la variable globale pour les signaux

## 🧹 Semaine 4 : Tests et Finalisation

- [ ] Gérer les signaux Ctrl+C, Ctrl+D, Ctrl+\ comme bash
- [ ] Écrire des tests manuels pour chaque fonctionnalité
- [ ] Tester avec Valgrind pour éviter les memory leaks
- [ ] Ajouter des commentaires clairs dans le code
- [ ] Terminer le README avec instructions d’utilisation
- [ ] Nettoyer le code selon la Norme 42
- [ ] Préparer la soutenance (oral, défense, questions)
