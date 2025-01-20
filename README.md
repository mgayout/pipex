# <p align="center">PIPEX [Projet 42]</p>

<div align="center">
	<table>
		<tr><th>NOTE</th>
		<th>ENGLISH VERSION</th></tr>
		<tr><th><img src="https://github.com/mgayout/mgayout/blob/main/img/note/120.png" height="100"></th>
		<th><a href= "https://github.com/mgayout/pipex/blob/master/eng/README.md"><img src="https://github.com/mgayout/mgayout/blob/main/img/english.png" height="100"></a></th></tr>
	</table>
</div>

Le projet `PIPEX` est un programme simule un enchaînement de 2 commandes.

Dans ce projet, nous voyons les différents points suivants :

* La manipulation des `fd` (fichiers + terminal)

* Les `variables d'environnement`

* Les `pid`

* Les `pipes`

### <p align="center">Partie Bonus</p>

La partie `bonus` de ce projet comprends les 2 choses suivantes :

* La gestion de plusieurs pipes

* La gestion des `heredocs`

## <p> </p>

## <p align="center">INSTALLATION</p>

* Pour télécharger `PIPEX` :

```shell
git clone https://github.com/mgayout/pipex.git
```
<div align="center">
	<table>
		<tr><th colspan="2" align="center">Règles</th></tr>
		<tr><td align="center">make</td>
		<td>Compilation</td></tr>
		<tr><td align="center">make bonus</td>
		<td>Compilation des fichiers bonus</td></tr>
		<tr><td align="center">make clean</td>
		<td>Suppression des fichiers objets</td></tr>
		<tr><td align="center">make fclean</td>
		<td>Suppression des fichiers objets et du programme pipex ou pipex_bonus</td></tr>
		<tr><td align="center">make re</td>
		<td>Suppression des fichiers objets et de l'archive suivi d'une compilation</td></tr>
		<tr><td align="center">make rebonus</td>
		<td>Suppression des fichiers objets et de l'archive suivi d'une compilation des fichiers bonus</td></tr>
	</table>
</div>

* Pour tester `PIPEX` :

```shell
./pipex infile cmd1 cmd2 outfile
```
ou
```shell
./pipex_bonus infile cmd1 cmd2 cmd3 ... cmd21 outfile
```
ou
```shell
./pipex_bonus here_doc "mot de passe" cmd1 cmd2 outfile
```