# Gestão de Horários de Engenharia Informática
## Projeto 1 - Algoritmos e Estruturas de Dados (AED)


O objetivo deste projeto prende-se com a criação de uma aplicação terminal-based que permita gerir os horários e as turmas dos alunos de Engenharia Informática e Computação.
A documentação do código pode ser encontrada [aqui](https://github.com/Juskocode/Shedule_management_LEIC).


### Funcionalidades implementadas:



#### Listagens

- Alunos inscritos por ano/UC/turma/em mais de n UCs: ordem alfabética ou por UP;
- Turmas de um ano, de uma UC, ou todas: ordem por nº de alunos (crescente e decrescente);
- UCs de um ano ou todas: ordem por nº de alunos (crescente e decrescente);
- Ver ano curricular dos alunos e ordenação dos 3 anos (crescente/decrescente por nº de alunos);
  Horários: de um aluno, de uma turma e de uma Unidade Curricular.

#### Modificações de Turmas

- Inscrição de estudantes em turmas (várias, se for pretendido): primeira inscrição de um estudante e inscrição em mais turmas de um estudante já existente;
- Desinscrição de um estudante (de turma(s) ou do sistema);
- Trocas de turmas: troca de turma (ou várias, se pretendido) de uma UC OU troca de turma entre dois estudantes (trocam entre si).


#### Gestão de Pedidos de Modificação
- Permite gerir o que foi feito na funcionalidade numerada com o número (2) -> exceto desinscrições, que são instantâneas.
- Listagem de pedidos ainda não processados (a processar no final do dia);
- Listagem de pedidos que foram rejeitados (podem ser eliminados opcionalmente pelo utilizador, porque são meramente informativos);
- Satisfazer pedidos -> é uma das opções do menu, que deve ser acionada no final do dia. Satisfaz todos os pedidos possíveis e recusa aqueles que não são possíveis devido a sobreposição/lotação/desequilíbrio.
- Ficam todos guardados em ficheiros (menos os que foram satisfeitos -> atualiza o ficheiro dos estudantes).

-----------------------------------------
Project by:
Grupo G17 - André Freitas, Ricardo Peralta, Sara Cortez

> [FEUP-L.EIC011] Algoritmos e Estruturas de Dados, 2023/2024