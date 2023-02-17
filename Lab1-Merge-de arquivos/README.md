# EN: Lab 1: File Merge

Specification: "You must write a program that merges two files whose records are sorted, generating a single file whose records are the union of the original records of the two files, sorted.

Your program will receive two strings and nothing else from the standard input. The two strings are the names of two files on which the merge operation must be applied.

Each of the files will be in the format described below. The files have multiple records. Each record has two fields, the first one is an integer written in binary mode, through a call to the fwrite function with a pointer to a long long int from C. The second field of each record is a sequence of printable letters, without the end-of-line \ n, whose size is exactly the integer stored in the first field. For example, a possible record would be [(binary representation of 5) abcde]. Note that there is no end of line, nor \ 0 byte delimiting the end of the string in the record.

The files passed have their records sorted lexicographically by the content of the second field. The lexicographic order is the same used by the strcmp function from C.

Your program must perform the Merge of the two files and generate a single file that contains the sorted union of the records of the two files named in the input. A Merge can be executed by simultaneously traversing the two files and generating the output. You must allocate and free memory to store the strings of the fields of the records of the files, because it is not possible to predict the size of the string field in advance.

The name of the output file must be the first file name passed concatenated with the string ".merge"

Your program must print the sequence of strings of the second fields of the records of the resulting Merge file generated on the standard output, in the order in which they are in the output file (sorted)."

The files provided by the professor are in the TestCases folder.


# PT: Lab 1: Merge de Arquivos

Especificação: "Você deve escrever um programa que faz o merge de dois arquivos cujos registros estão ordenados, gerando um único arquivo cujos registros sejam a união dos registros originais dos dois arquivos, ordenados.

Seu programa receberá da entrada padrão duas strings e nada mais. As duas strings são os nomes de dois arquivos sobre os quais deve ser aplicada a operação de merge.

Cada um dos arquivos estará no formato descrito a seguir. Os arquivos têm múltiplos registros. Cada registro tem dois campos, sendo o primeiro um inteiro escrito em modo binário, através de uma chamada para a função fwrite com um apontador para um long long int do C. O segundo campo de cada registro é uma sequência de letras passíveis de impressão em tela, sem o fim-de-linha \n, cujo tamanho é exatamente o número inteiro armazenado no primeiro campo. Por exemplo, um possível registro seria [(representação-binária-de-5)abcde]. Note que não há fim de linha, nem byte \0 delimitando fim da string no registro.

Os arquivos passados têm seus registros ordenados lexicograficamente pelo conteúdo do segundo campo. A ordem lexicográfica é a mesma utilizada pela função strcmp do C.

Seu programa deve realizar o Merge dos dois arquivos e gerar um único arquivo que contenha a união ordenada dos registros dos dois arquivos nomeados na entrada. Um Merge pode ser executado percorrendo-se simultaneamente os dois arquivos e gerando a saída. Você deve alocar e liberar memória para armazenar as strings dos campos dos registros dos arquivos, pois não é possível prever o tamanho do campo de string com antecedência.

O nome do arquivo de saída deve ser o primeiro nome de arquivo passado concatenado com a string ".merge"

Seu programa deve imprimir na saída padrão a sequência de strings dos segundos campos dos registros do arquivo resultante do Merge gerado, na ordem em que eles estão no arquivo de saída (ordenados)."


Os arquivos disponibilizados pelo professor estão na pasta TestCases.