# Sistema de Cadastro de Avaliações e Notas

Este sistema aplica o conceito de `CRUD` que é um acrônimo para as operações de 
manipulação de dados Create (Criar), Read (Ler), Update (Atualizar) e Delete (Excluir). 
Estas operações são essenciais para manipulação de informações. 

Neste sistema as informações serão salvas em arquivos no formato `csv` 
dentro do diretório `data`.

Em resumo o sistema irá manipular os dados (arquivos `.csv`) da seguinte forma:

### Create (Criar)

Operação de criação de novos dados. Como por exemplo cadastrar um aluno.

### Read (Ler)

Operação para acessar e exibir dados. Por exemplo, abrir um arquivo e ler o seu conteúdo.

### Update (Atualizar)

Operação para executar uma atualização nos dados existentes. 
Isto é, ler um dado de um arquivo, alterar e salvar novamente. 
Por exemplo, o nome do aluno foi cadastrado errado, nesse caso a 
operação de update permite a alteração do nome. 

### Delete (Apagar)
Operação utilizada para remover dados. 
Por exemplo, apagar todos os dados de um aluno. 


## Estrutura do Projeto:

```
sistema_notas/
├─ include/
│  ├─ students.h        # protótipos e structs para alunos
│  ├─ exams.h           # protótipos e structs para avaliações
│  ├─ grades.h          # protótipos e structs para notas
│  └─ utils.h           # utilitários (parsing, helpers)
├─ src/
│  ├─ students.c        # implementação CRUD alunos
│  ├─ exams.c           # implementação CRUD avaliações
│  ├─ grades.c          # implementação CRUD notas
│  ├─ utils.c           # implementação utilitários
│  └─ main.c            # menu e integração
├─ data/
│  ├─ students.csv      # exemplo de dados de alunos
│  ├─ exams.csv         # exemplo de dados de avaliações
│  └─ grades.csv        # exemplo de dados de notas
├─ build.bat            # utilitário para compilar o código fonte
├─ clean.bat            # utilitário limpar arquivos temporários antes da compilação
├─ run.bat              # utilitário verificar se os arquivos de dados existem e executar o programa compilado
├─ topicos_importantes.md # breve explicões sobre algumas funções do código
└─ README.md
```


## Dados


### Arquivos de dados:

- data/students.csv

- data/exams.csv

- data/grades.csv



### Descrição:

Sistema para cadastros de avaliações e notas de alunos salvando os dados em arquivo ``.csv``. 


Observações:

- Nomes cadastrados não devem conter vírgulas.
- Verifique permissões de escrita no diretório ``data/``.

