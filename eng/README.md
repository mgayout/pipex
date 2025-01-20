# <p align="center">PIPEX [42 Project]</p>

<div align="center">
	<table>
		<tr><th>GRADE</th>
		<th>FRENCH VERSION</th></tr>
		<tr><th><img src="https://github.com/mgayout/mgayout/blob/main/img/note/120.png" height="100"></th>
		<th><a href= "https://github.com/mgayout/pipex"><img src="https://github.com/mgayout/mgayout/blob/main/img/french.png" height="100"></a></th></tr>
	</table>
</div>

The `PIPEX` project is a program that simulates a sequence of 2 commands.

In this project, we see the following different points:

* Handling `fd` (files + terminal)

* `environment variables`

* The `pid`

* The `pipes`

### <p align="center">Bonus Part</p>

The `bonus` part of this project includes the following 2 things:

* Managing multiple pipes

* Management of `heredocs`

## <p> </p>

## <p align="center">INSTALLATION</p>

* To download `PIPEX` :

```shell
git clone https://github.com/mgayout/pipex.git
```
<div align="center">
	<table>
		<tr><th colspan="2" align="center">Rules</th></tr>
		<tr><td align="center">make</td>
		<td>Compilation</td></tr>
		<tr><td align="center">make bonus</td>
		<td>Bonus files compilation</td></tr>
		<tr><td align="center">make clean</td>
		<td>Deleting object files</td></tr>
		<tr><td align="center">make fclean</td>
		<td>Deleting object files and the programm so_long or so_long_bonus</td></tr>
		<tr><td align="center">make re</td>
		<td>Deleting object files and the programm followed by compilation</td></tr>
		<tr><td align="center">make rebonus</td>
		<td>Deleting object files and the programm followed by bonus files compilation</td></tr>
	</table>
</div>

* To test `PIPEX` :

```shell
./pipex infile cmd1 cmd2 outfile
```
ou
```shell
./pipex_bonus infile cmd1 cmd2 cmd3 ... cmd21 outfile
```
ou
```shell
./pipex_bonus here_doc "password" cmd1 cmd2 outfile
```