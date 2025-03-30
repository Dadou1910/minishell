# Minishell

## 🐚 Description

`minishell` est une ré-implémentation simplifiée d’un shell UNIX, développée dans le cadre du cursus 42.  
L’objectif est de comprendre en profondeur le fonctionnement d’un interpréteur de commandes, en recréant des fonctionnalités essentielles d’un terminal.

Ce projet met en œuvre des concepts clés du système UNIX comme :
- les **processus** (`fork`, `execve`, `wait`)
- la **gestion des signaux**
- les **pipes**
- les **redirections de fichiers**
- la gestion des **variables d’environnement**

---

## 🚀 Fonctionnalités implémentées

- Exécution des commandes avec chemins relatifs et absolus
- Commandes built-in :  
  `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections : `>`, `>>`, `<`, `<<` (heredoc)
- Pipes `|`
- Gestion fine des signaux `CTRL-C`, `CTRL-\`
- Parsing avancé avec gestion des quotes (`'`, `"`) et des variables (`$USER`, `$?`)
- Gestion des erreurs et du statut de retour (`$?`)

---

## 🔧 Compilation

```bash
make
```

---

## 🧪 Utilisation

./minishell

Vous pouvez ensuite taper des commandes comme :
```bash
ls -l | grep .c > list.txt
echo "Bonjour $USER"
cat << EOF
hello
EOF
```
---

## 📁 Structure du projet
``` bash
minishell/
├── builtins/         # Implémentation des built-ins
├── exec/             # Exécution des commandes
├── includes/         # Fichiers d'en-tête
├── parsing/          # Analyse syntaxique et expansion
├── Libft/            # Librairie personnelle
├── Makefile
└── readline.supp     # Fichier de suppression pour Valgrind
```

📚 Règles spécifiques au projet

    Langage : C 

    Respect du style 42 (Norme)

    Aucune fonction interdite (selon la version 42)

    Gestion de la mémoire sans leaks (valgrind --leak-check=full)

👤 Auteur

Projet réalisé par :

    👤 @Dadou1910
    👤 Jealefev

📄 Licence

Projet réalisé dans le cadre du cursus 42.
À usage éducatif uniquement.
