# satellites-parses
Парсер файлов с данным о спутниках

В рамках тестового задания:

Написать программу, которая:
1. читает файлы .status
2. извлекает из них списки спутников и даты в которые были совершены измерения (as of date, первая строка)
3. выводим для каждой даты список имен спутников (первый столбец) тех из них, для которых имеются измерения (т.е. поля start, end и т.д. заполнены)

Уточнения:
- файлы следует читать и парсить асинхронно
- список имен спутников должен быть выведен в том же порядке, что указан в файле
- регистр имен спутников должен быть сохранен
- если имеются дубликаты спутников (при наличии измерений хотя бы у одного из них), то необходимо выводить только первый с пометкой в виде символа "+"
- если файл пустой, не соответствует ожидаемому формату или имеет размер более 10 мб, то необходимо вывести соответствующее предупреждение и прекратить его обработку

Допускается:
- любым способом передавать программе список файлов для парсинга
- читать сразу весь файл в буфер
- считать, что длина каждого поля ограничена пробелами в заголовке, а строки не переносятся


