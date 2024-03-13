# CYBERcobra assembler

Данный репозиторий содержит программу ассемблера и ISA для архитектуры [CYBERcobra 3000 Pro 2.1](https://github.com/MPSU/APS/tree/master/Labs/04.%20Primitive%20programmable%20device).

## ISA

Набор команд схож с набором *rv32i*

  1.  `add`  `rd` , `rs1`, `rs2`
  1.  `sub`  `rd` , `rs1`, `rs2`
  1.  `xor`  `rd` , `rs1`, `rs2`
  1.  `or`   `rd` , `rs1`, `rs2`
  1.  `and`  `rd` , `rs1`, `rs2`
  1.  `sra`  `rd` , `rs1`, `rs2`
  1.  `sll`  `rd` , `rs1`, `rs2`
  1.  `srl`  `rd` , `rs1`, `rs2`
  1.  `slts` `rd` , `rs1`, `rs2`
  1.  `sltu` `rd` , `rs1`, `rs2`
  1.  `blt`  `rs1`, `rs2`, `imm`
  1.  `bltu` `rs1`, `rs2`, `imm`
  1.  `bge`  `rs1`, `rs2`, `imm`
  1.  `bgeu` `rs1`, `rs2`, `imm`
  1.  `beq`  `rs1`, `rs2`, `imm`
  1.  `bne`  `rs1`, `rs2`, `imm`
  1.  `li`   `rd` , `imm`
  1.  `j`    `imm`
  1.  `in`   `rd` — Загрузка в регистр `rd` данных с внешнего устройства.
  1.  `out` — Вывод данных на внешнее устройство. Является псевдоинструкцией для инструкции `add` `x0`, `x1`, `x0`

## Ассемблер

Транслирует язык ассемблера обсуждаемой архитектуры в машинные коды киберкобры.

### Сборка программы

*   **Внешние зависимости**:
    *   CatchV3 — нужен только для сборки тестов. Исполняемые файл можно собрать и без него.
*   **Система сборки** — meson.

### Запуск программы

Программа взаимодействует со средой через дескрипторы `stdin`, `stdout`, `stderr`. Таким образом можно использовать средства ОС для перенаправления соответствующих потоков.

На вход принимается текстовый файл, написанный на языке ассемблера, на выход поступает **текстовый** файл с транслированными машинными инструкциями записанными в шестнадцатеричной системе счисления. Если во входном тексте обнаружена ошибка, то программа сообщит об этом через соответствующий дескриптор ошибки.

Пример ассемблирования файла `program.s` с записью результата в `program.mem` в `powershell`:

```powershell
Get-Content .\test\program.s | .\build\cybercobra_assembler.exe > .\build\program.mem
```

### Язык ассемблера

1.  Поддерживаются все инструкции из [ISA](#isa).
1.  Каждая инструкция должна быть на отдельной строке.
1.  Регистровые операнды записываются в виде: `x0`-`x31`, а `imm` операнды в виде знаковых десятичных чисел.
1.  Пробельные символы игнорируются.
1.  Поддерживаются однострочные комментарии (игнорируются).

    ```
    add x1, x2, x3 # x1 = x2 + x3
    ```
1.  Поддерживаются метки.

    ```
    start:
      j start
    ```

Пример программы на языке можно найти [здесь](./test/program.s).
