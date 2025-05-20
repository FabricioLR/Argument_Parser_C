# Argument Parser

![GitHub repo size](https://img.shields.io/github/repo-size/FabricioLR/Argument_Parser_C?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/FabricioLR/Argument_Parser_C?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/FabricioLR/Argument_Parser_C?style=for-the-badge)
![Bitbucket open issues](https://img.shields.io/bitbucket/issues/FabricioLR/Argument_Parser_C?style=for-the-badge)
![Bitbucket open pull requests](https://img.shields.io/bitbucket/pr-raw/FabricioLR/Argument_Parser_C?style=for-the-badge)

> Implementação minimalista de um argument parser escrito em C.

## 🚀 Instalando

Apenas copie o arquivo ![argument-pasrser.h](https://github.com/FabricioLR/Argument_Parser_C/blob/master/argument-parser.h) para dentro do seu projeto

## ☕ Usando

Primeiramente, crie um arquivo de configuração, tal como em [argument-parser.config](https://github.com/FabricioLR/Argument_Parser_C/blob/master/examples/argument-parser.config)
```
#name:alias:has_value:required:
-arg1:--argument1:1:1
-arg2:--argument2:0:0
--argument3:0:1:0
-argument10:0:1:1
```

Inicie o parser e comece a utilizar

```
#include "argument-parser.h"

int main(int argc, char **argv){
    parser_init(argc, argv))
    printf("%s\n", get_argument_value("-arg1"));
...
```


## 📫 Contribuindo

Para contribuir, siga estas etapas:

1. Fork este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie um Pull Request.

Como alternativa, consulte a documentação do GitHub em [como criar uma solicitação pull](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).
