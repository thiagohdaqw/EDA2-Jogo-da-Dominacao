#!/bin/bash

<< 'comment'
Ele funciona copiando o conteúdo dos arquivos `*.h` declarados em `jogador.c` 
para um arquivo resultante `jogador.submit.c`, que é o arquivo que pode ser
submetido no MOJ. Tanto o programa resultante de `jogador.c` quanto o de 
`jogador.submit.c` podem ser compilados e executados localmente com o script
`build.sh`.

`extract-replace.sh` assume que:
- arquivos `*.h` e `jogador.c` estão no mesmo diretório que o script.
- todo arquivo `.h` define o cabeçalho com `<NOME_ARQUIVO_MAIUSCULO>_H_INCLUDED`
e termina com `#endif // <NOME_ARQUIVO_MAIUSCULO>_H_INCLUDED` (é possível criar 
um snippet no vscode para facilitar a definição do cabeçalho). Tudo o que está 
entre essas duas strings é copiado para o arquivo resultante.
comment


main () {
  outputfile="main.submit.c"
  main_inputfile="main.c"

  cp $main_inputfile $outputfile
  include_files=$(find_include_files $main_inputfile)
  debug_extract=$(extract_replace "$include_files")

  remove_includes_from_outputfile;

  # echo "debug"
  # echo "$debug_extract"
}


# Procura os `#include "*.h"` dentro do arquivo que é recebido 
# como argumento
find_include_files() {
  includes=$(cat $1 | grep -E "#include\s+\"" | grep -v "\/\/" | grep -v "\/\*")

  while IFS= read -r line; do
    file=$(echo $line | sed -E "s/#include\s+\"(.*)\"/\1/")
    echo "$file"
  done <<< "$includes"
}


extract_replace() {
  # https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash
  files="$1"
  while IFS= read -r file; do
    filename="${file%.*}" # assume que é do tipo arquivo.h e está no mesmo diretório
    filename_uppercased=${filename^^}
    
    marker_start="#define\s+${filename_uppercased}_H_INCLUDED"
    marker_end="#endif\s+\/\/\s+${filename_uppercased}_H_INCLUDED"
    print_string="/$marker_start/,/$marker_end/p"

    # TODO: limpar includes.h dos includes.h
    content_in_include_file=$(sed -n -E "$print_string" $file)
    # apaga primeira e última linhas.
    content_in_include_file=$(echo "$content_in_include_file" | sed '1d;$d')

    echo "$content_in_include_file" > tmp_content_file

    marker_replace="#include\s+\"${filename}.h\""
    # https://stackoverflow.com/questions/6790631/use-the-contents-of-a-file-to-replace-a-string-using-sed/6790967
    sed -i -E "/$marker_replace/{
      s/$marker_replace//g
      r tmp_content_file
    }" $outputfile

    # para propositos de depuracao
    # echo "$content_in_include_file" > tmp_content_file
    # echo "##### replace at: \"$marker_replace\" in file $outputfile"
    # echo "$content_in_include_file"
  done <<< "$files"
  rm tmp_content_file
}

# Arquivos `.h` podem incluir outros `.h` e isso dá problemas de redeclaração.
remove_includes_from_outputfile() {
  sed -i -E '/#include\s+\"(.*)\"/d' $outputfile
}

main